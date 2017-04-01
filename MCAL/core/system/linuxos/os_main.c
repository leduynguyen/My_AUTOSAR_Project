
/*-------------------------------- Arctic Core ------------------------------
 * Copyright (C) 2013, ArcCore AB, Sweden, www.arccore.com.
 * Contact: <contact@arccore.com>
 *
 * You may ONLY use this file:
 * 1)if you have a valid commercial ArcCore license and then in accordance with
 * the terms contained in the written license agreement between you and ArcCore,
 * or alternatively
 * 2)if you follow the terms found in GNU General Public License version 2 as
 * published by the Free Software Foundation and appearing in the file
 * LICENSE.GPL included in the packaging of this file or here
 * <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>
 *-------------------------------- Arctic Core -----------------------------*/

#include <stdio.h>
#ifndef _WIN32
#include <pthread.h>
#endif
#include <setjmp.h>
#ifndef _WIN32
#include <unistd.h> /* sleep */
#include <stdlib.h> /* exit */
#include <ctype.h>  /* isprint */
#include <errno.h>
#include <signal.h>
#include <fcntl.h>  /* open */
#include <asm/param.h> /* HZ */
#endif

#include "linos_logger.h" /* Logger functions */
#include <time.h>
#include <sys/stat.h> // umask

#include "version.h"
#include "EcuM.h"

#include <os_i.h>	/* GEN_TASK_HEAD  */
#include <os_sys.h>  /* OS_SYS_PTR */
#include <Rte_StbM_Type.h> /* StbM Linos_StbM_GetCurrentTime */

#include "os_main.h"

#if defined(USE_LINOS_DB) && !defined(_WIN32)
  #include "database.h"
#endif

#define NSEC_PER_SEC    1000000000

/* Global variables */

int daemonise = 1;

extern const OsTaskConstType  Os_TaskConstList[OS_TASK_CNT];


#if defined(USE_TCPIP)
extern int gnulinuxTcpBindAny;
#endif

ThreadTaskType ThreadTasks[(OS_TASK_CNT+GNULINUX_TASK_CNT)]; /* Normal tasks and special GNULinux tasks */

int loops = 999; /* Infinate loops */

int DebugMask = 0; /* IMPROVEMENT SimonG Use this mask for debugging */

char *progname = NULL ; // Gets set in main(). Portable implementation of GNUs program_invocation_short_name

char pid_file_name[64]; // /var/run/X.pid

char bit_event_file_name[64]; // File to store the event bit signal in.

#if defined(USE_LINOS_DB)
char db_file_name[64];
#endif

/* 	*/
int stop_at_runtime = 0;

extern void EcuM_Init(void);



Std_ReturnType Linos_GetCurrentTime( struct timespec *tp )
{
#ifndef _WIN32
    if (clock_gettime(CLOCK_REALTIME, tp)) {
        logger(LOG_ERR, "Linos_GetCurrentTime. problems getting CLOCK_REALTIME");
        return E_NOT_OK;
    }
#endif
    return E_OK;
}

#ifndef _WIN32
static clockid_t get_clockid(int fd)
{
#define CLOCKFD 3
#define FD_TO_CLOCKID(fd)       ((~(clockid_t) (fd) << 3) | CLOCKFD)

        return FD_TO_CLOCKID(fd);
}
#endif
/*
 *  Get PTP time.
 *  Normally requires root access
 *  because of the rights on PTP_DEVICE
 *
*/
Std_ReturnType Linos_GetCurrentPTPTime( struct timespec *tp )
{
#ifndef _WIN32
    char *ptp_device = PTP_DEVICE;
    clockid_t clkid;
    int fd;

    fd = open(ptp_device, O_RDONLY);
    if (fd < 0) {
        logger(LOG_ERR, "Linos_GetCurrentPTPTime opening %s: %s\n", ptp_device, strerror(errno));
        return E_NOT_OK;
    }

    clkid = get_clockid(fd);
    if (CLOCK_INVALID == clkid) {
        logger(LOG_ERR, "Linos_GetCurrentPTPTime failed to read clock id\n");
        return E_NOT_OK;
    }

    if (clock_gettime(clkid, tp)) {
        logger(LOG_ERR, "Linos_GetCurrentPTPTime clock_gettime");
        return E_NOT_OK;
    }


#endif
    return E_OK;
}


/*
 *
 * Linuxos implementation of StbM_GetCurrentTime
 *
 * This just compares the Linux PHC to the system clock.
 * If there is a larger difference than 1 OS tick then we
 * treat this as a timeout.
 *
 * GLOBAL_TIME_BASE and TIMEOUT are only implemented.
 *
*/

Std_ReturnType Linos_StbM_GetCurrentTime( StbM_SynchronizedTimeBaseType timeBaseId, StbM_TimeStampType* timeStampPtr, StbM_UserDataType* userDataPtr )
{
#ifndef _WIN32
	Std_ReturnType retValue;
	struct timespec tpsys, tpptp;

	unsigned int msec_tick = (1000/OsTickFreq); /* Maximum diff between PHC and system clock is based on OsTickFreq */
	unsigned long nsec_max_diff = ( msec_tick * 1000000);
	unsigned long nsec_diff;

	StbM_TimeBaseStatusType timeBaseStatus = 0;

	/* Start-up is out of sync */
	static uint8_t GLOBAL_TIME_BASE = 0; 	/* bit 3 This is static as it is only SET and never UNSET. SRS_StbM_20025 */
	static uint8_t TIMEOUT = 1;		/* bit 0 This is also static to detect changes between calls to this function. */
	uint8_t in_sync = 0;


	retValue = Linos_GetCurrentTime(&tpsys);

	if ( retValue != E_OK )
	{
		logger(LOG_ERR, "Linos_StbM_GetCurrentTime. Error getting current time.");
		return retValue;
	}
	else
	{
		retValue = Linos_GetCurrentPTPTime(&tpptp);
		if ( retValue != E_OK )
		{
			logger(LOG_ERR, "Linos_StbM_GetCurrentTime. Error getting current PTP time.");
			return retValue;
		}
	}

	if ((tpsys.tv_nsec < 0)||(tpsys.tv_sec < 0))
	{
		logger(LOG_ERR, "Linos_StbM_GetCurrentTime. Negative time is not supported in PTP.\n");
		return E_NOT_OK;
	}

	timeStampPtr->nanoseconds = (tpsys.tv_nsec & 0xffffffff);
	timeStampPtr->seconds = (tpsys.tv_sec & 0xffffffff);
	timeStampPtr->secondsHi = ((tpsys.tv_sec >> 32) & 0xffff);

	/* Test if in sync */
	if ( tpptp.tv_sec == tpsys.tv_sec )
	{
		if ( (tpptp.tv_nsec - tpsys.tv_nsec) < 0 )
		{
			nsec_diff = (tpsys.tv_nsec - tpptp.tv_nsec);
		}
		else
		{
			nsec_diff = (tpptp.tv_nsec - tpsys.tv_nsec);
		}

		if ( nsec_diff < nsec_max_diff )
		{
			/* In Sync */
			in_sync = 1;
		}
	}

	if ( in_sync )
	{
		/* In Sync */
		if ( GLOBAL_TIME_BASE == 0 )
		{
			GLOBAL_TIME_BASE = 1;
			logger_mod((LOGGER_MOD_LINOS|LOGGER_SUB_OS_MAIN), LOG_INFO, "Linos_StbM_GetCurrentTime GLOBAL_TIME_BASE is SET");
			
		}

		if ( TIMEOUT == 1 )
		{
			TIMEOUT = 0;
			logger_mod((LOGGER_MOD_LINOS|LOGGER_SUB_OS_MAIN), LOG_INFO, "Linos_StbM_GetCurrentTime TIMEOUT is CLEARed");
		}
	}
	else
	{
		/* NOT In Sync */
		if ( TIMEOUT == 0 )
		{
			TIMEOUT = 1;
			logger_mod((LOGGER_MOD_LINOS|LOGGER_SUB_OS_MAIN), LOG_INFO, "Linos_StbM_GetCurrentTime TIMEOUT is SET");
		}
	}

	timeBaseStatus = (StbM_TimeBaseStatusType)TIMEOUT;
	timeBaseStatus |= (StbM_TimeBaseStatusType) ( GLOBAL_TIME_BASE <<3 );

	timeStampPtr->timeBaseStatus =  timeBaseStatus;

	return retValue;
#else
	return 0;
#endif
}


/*
 * Normalise timespec
 *
 * If tv_nsec >= NSEC_PER_SEC then
 * add to tv_sec and reduce tv_nsec
 * until tv_nsec < NSEC_PER_SEC
 *
*/
void tsnorm(struct timespec *ts) 
{
#ifndef _WIN32
    while (ts->tv_nsec >= NSEC_PER_SEC) 
    {
        ts->tv_nsec -= NSEC_PER_SEC;
        ts->tv_sec++;
    }
#endif
}

#ifndef _WIN32
/* Used by WaitEvent in os_event.c */
struct timespec timesdiff(struct timespec *start, struct timespec *end)
{

    struct timespec temp;
    if ((end->tv_nsec-start->tv_nsec)<0) {
        temp.tv_sec = end->tv_sec-start->tv_sec-1;
        temp.tv_nsec = 1000000000+end->tv_nsec-start->tv_nsec;
    } else {
        temp.tv_sec = end->tv_sec-start->tv_sec;
        temp.tv_nsec = end->tv_nsec-start->tv_nsec;
    }
    return temp;
}
#endif

/*
 *
 *
 *  gnulinux_timer (Runs in seperate thread)
 *
 *  Increment the counter OsTickFreq times per second. Max 1000Hz (1ms) ??
 *
 *  This sleeps different amounts of time to ensure accuracy.
 *
 *
*/
void gnulinux_timer(void) {
#ifndef _WIN32
	unsigned int msec = (1000/OsTickFreq); /* How long to wait for every tick */

	unsigned int usecs = msec * 1000; /* Wait time in microseconds */


	struct timespec t;

	clock_gettime(CLOCK_REALTIME, &t); // Get current time.
	t.tv_nsec+=(usecs * 1000);

	logger_mod((LOGGER_MOD_LINOS|LOGGER_SUB_OS_MAIN), LOG_INFO, "gnulinux_timer calling IncrementCounter() every %ldms (%dHz)", msec, OsTickFreq);

	while(1) {
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &t, NULL); // IMPROVEMENT SimonG check for return EINTR. Caused by signals.
		IncrementCounter(0);
		// logger (LOG_INFO, "\t\t\t\t\t\t\t\t\t\t\t OS_SYS_PTR->tick is now %u", OS_SYS_PTR->tick);
		t.tv_nsec+=(usecs * 1000);
		tsnorm(&t);
	}
#endif
}




/*
 *
 *
 *
 *
 * 	MAIN
 *
 *
 *
 *
 *
*/



void TaskWrapper(int TaskId)
{
    while(1)
    {
        if (setjmp((struct __jmp_buf_tag *)ThreadTasks[TaskId].stack_env))
        {
            /* Terminate task has been called */
            //logger(LOG_INFO, "TaskWrapper Terminate task has been called");
            usleep(1000); /* Sleep 1 ms */
        }
        else
        {
            if (ThreadTasks[TaskId].pthread_status == GNULINUX_PTHREAD_FUNCTION_STARTED)
            {
#ifndef _WIN32
                /* Initialise the Wait/Set event pthread lock */
                pthread_mutex_init((pthread_mutex_t *)&ThreadTasks[TaskId].mutex_lock, NULL);
                pthread_cond_init((pthread_cond_t *)&ThreadTasks[TaskId].cond, NULL);
                /*						*/
                ThreadTasks[TaskId].entry(); /* Call the function defined in the task entry */
#endif
            }
            else
            {
                //logger(LOG_INFO, "TaskWrapper waiting to re-activate task");
                usleep(1000); /* Sleep 1 ms */
            }
        }
    }
}


void* StartTask(void *arg)
{
#ifndef _WIN32
    int i;
    pthread_t id = pthread_self();

    for (i=0; i< (OS_TASK_CNT+GNULINUX_TASK_CNT);i++){
    /* Normal tasks and special GNULinux tasks. eg. clock/alarm task */
        if(pthread_equal(id,ThreadTasks[i].tid)){
        /* General filtering of tasks */
        switch (i)
        {
            case TASK_ID_OsIdle:
               	logger_mod((LOGGER_MOD_LINOS|LOGGER_SUB_OS_MAIN), LOG_INFO, "NOT Calling %s TaskId(%d)", ThreadTasks[i].name, i);
            break;

            default:
                if ( ThreadTasks[i].pthread_status != GNULINUX_PTHREAD_STARTING )
                {
                    logger(LOG_ERR, "Task %s TaskId(%d) is NOT in state GNULINUX_PTHREAD_STARTING", ThreadTasks[i].name, i);
                    pthread_exit(NULL);
                    return NULL;
                }
                logger_mod((LOGGER_MOD_LINOS|LOGGER_SUB_OS_MAIN), LOG_INFO, "Calling %s TaskId(%d)", ThreadTasks[i].name, i);
                ThreadTasks[i].pthread_status = GNULINUX_PTHREAD_FUNCTION_STARTED;

                TaskWrapper(i);
            break;
        }
        }
    }
#endif
    return NULL;
}


void list_all_events() {

	int i;

	logger_mod((LOGGER_MOD_LINOS|LOGGER_SUB_OS_MAIN), LOG_INFO, "Listing all task events");

	for( i=0; i < OS_TASK_CNT; i++) {

		logger_mod((LOGGER_MOD_LINOS|LOGGER_SUB_OS_MAIN), LOG_INFO, "IMPROVEMENT %s", ThreadTasks[i].name);
	}

}


#if defined(USE_LINOS_DB) && !defined(_WIN32)
int callback_print_runtime (char *reg_type, int argc, char **argv, char **azColName)
{
    int i;

    int address,value;

    /* Loop through the columns in the DB record. */
    for(i=0; i<argc; i++)
    {
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        if ( strcmp (azColName[i],"registeraddress") == 0 )
        {
            address = atoi(argv[i]);
        }
        else if ( strcmp (azColName[i],"registervalue") == 0 )
        {
            value = atoi(argv[i]);
        }

    }

    if ( address == DB_ECU_RUNTIME_REG_ADDRESS )
    {
        logger(LOG_INFO, "Runtime at start-up is %ld s", value);
    }

    return 0;
}
#endif

static void usage()
{

    printf("%s\n",progname);
    printf("%s\n", ArcticCore_Version.info);
    printf("USAGE: %s  \n", progname);
#if defined(USE_TCPIP)
    printf("-b bind (listen) to INADDR_ANY instead of the configured ip address\n");
#endif
#if defined(USE_LINOS_DB)
    printf("Database file is here %s\n", db_file_name);
#endif
#ifdef USE_SYSLOG
    printf("-f stay in foreground. Instead of deamonising.\n");
#endif
    printf("-l loops (999 = infinite).\n");
    printf("-m <BITMASK> to set the debug mask. decimal or 0xHEX. See logger.h\n");
    printf("-r stop at runtime. For test.\n");
}


int settings(int argc, char **argv )
{
        int index;
        int c;
#ifndef _WIN32
        opterr = 0;
#endif
        // See usage() function above
    while ((c = getopt (argc, argv, "bfhl:m:rt")) != -1)
    {

        switch (c)
        {
        case 'b':
#if defined(USE_TCPIP)
            gnulinuxTcpBindAny = TRUE;
#endif
        break;

        case 'l':
#ifndef _WIN32
            loops = atoi(optarg);
#endif
        break;

        case 'm':
#ifndef _WIN32
            //DebugMask = atoi(optarg);
	    DebugMask = strtol(optarg, (char **) NULL, 0); // Accept a digit in decimal or hex
	    printf("DebugMask = 0x%02X\n");
#endif
        break;

        case 'f':
#ifdef USE_SYSLOG
            logger_set_output(3); /* Syslog + fprintf */
#else
            logger_set_output(1); /* fprintf */
#endif
            daemonise = 0; /* Do NOT deamonise */
            loops = 10;
        break;

        case 'h':
                     usage();
                     exit(0);
                 break;

        case 'r':
            stop_at_runtime = 1;
        break;


        case 't':
            EcuM_Init();
                     list_all_events();
                     exit(0);
                 break;

        case '?':
#ifndef _WIN32
                    if ((optopt == 'l')||(optopt == 'm')||(optopt == 'e'))
                    {
                            fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                    }
                    else if (isprint (optopt))
                    {
                            fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                    }
                    else
                    {
                            fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                    }
#endif
                     return 1;
               default:
                     abort ();
               }
        }
#ifndef _WIN32
    for (index = optind; index < argc; index++)
        {
        fprintf(stderr, "Non-option argument %s", argv[index]);
        return 0;
    }
#endif
    return 0;
}


static void close_sigint(int exit_code) {

    logger(LOG_INFO, "Shutting down ... ");
    //logger(LOG_INFO, "Killing threads."); // IMPROVEMENT SimonG
    // pthread_cancel

#if defined(USE_LINOS_DB) && !defined(_WIN32)
    db_close();
#endif

    unlink(pid_file_name);

    logger(LOG_INFO, "Done!");
#ifdef USE_SYSLOG
    logger_open_close ( 0, progname );
#endif
    exit(exit_code);
}


void read_event_file(void) {

	FILE *rc;
	char line[80];

	TaskType TaskId;
	EventMaskType Mask;

	logger(LOG_INFO, "SIG HUP caught. Reading events from file %s", bit_event_file_name);

	rc = fopen(bit_event_file_name, "r");
	if ( rc == NULL ) {
		logger(LOG_ERR, "Oops problems opening event file %s", bit_event_file_name);
	} else {
		while(fgets(line, 80, rc) != NULL) {
			logger_mod((LOGGER_MOD_LINOS|LOGGER_SUB_OS_MAIN), LOG_INFO, "Line : %s", line);
			TaskId = atoi(strtok (line,"-"));
			Mask = strtol(strtok (NULL, "\0"),NULL,0); // 0xabcdef00
			logger_mod((LOGGER_MOD_LINOS|LOGGER_SUB_OS_MAIN), LOG_INFO, "SetEvent( TaskType %d, EventMaskType [0x%.8X] )",
					TaskId, Mask);
			SetEvent( TaskId, Mask );
		}
		fclose(rc);
	}
}


void signal_handler(int sig)
{
#ifndef _WIN32
        switch(sig) {
        case SIGHUP:
        read_event_file();
    break;

        case SIGTERM:
    case SIGINT:
        close_sigint(0);
    break;

    default:
                logger(LOG_ERR, "Unknown signal (%d) %s ignored.", sig, strsignal(sig));
    }
#endif
}


int start_thread( int threadId )
{
#ifndef _WIN32
    int err;
    pthread_attr_t attr;

    if ( ThreadTasks[threadId].pthread_status == GNULINUX_PTHREAD_FUNCTION_TERMINATED)
    {
        err = E_OK;
       	logger_mod((LOGGER_MOD_LINOS|LOGGER_SUB_OS_TASK), LOG_DEBUG, "Restarting a terminated task (%s).", ThreadTasks[threadId].name);

        ThreadTasks[threadId].pthread_status = GNULINUX_PTHREAD_FUNCTION_STARTED;

        /* Initialise the Wait/Set event pthread lock */
        pthread_mutex_init((pthread_mutex_t *)&ThreadTasks[threadId].mutex_lock, NULL);
        pthread_cond_init((pthread_cond_t * )&ThreadTasks[threadId].cond, NULL);
        /*						*/

        //ThreadTasks[threadId].entry(); /* Call the function defined in the task entry */

        return err;
    }

    /* Only start a new task if the old task has ended. */
    if ( ThreadTasks[threadId].pthread_status != GNULINUX_PTHREAD_EMPTY )
    {
        if ( ThreadTasks[threadId].pthread_status == GNULINUX_PTHREAD_FUNCTION_STARTED)
        {
            logger(LOG_NOTICE, "This thread is still running. Can't restart thread [%d](%s)",
                                threadId, ThreadTasks[threadId].name);
        }
        else
        {
            logger(LOG_ERR, "This thread is not empty. Can't create thread [%d](%s)",
                threadId, ThreadTasks[threadId].name);
            err = -1;
        }
        return err;
    }


    ThreadTasks[threadId].pthread_status = GNULINUX_PTHREAD_STARTING;

    /* Initialize thread creation attributes */

        err = pthread_attr_init(&attr);
        if (err != 0)
            handle_error_en(err, "pthread_attr_init");

// IMPROVEMENT Set prio, affinity etc.
//        if (stack_size > 0) {
//        	err = pthread_attr_setstacksize(&attr, stack_size);
//        	if (err != 0)
//			handle_error_en(err, "pthread_attr_setstacksize");
//	}
//
//	sched_setaffinity( etc.
//

    err = pthread_create((pthread_t * restrict)&(ThreadTasks[threadId].tid), NULL, &StartTask, NULL);

    if (err != 0)
        logger(LOG_ERR, "\ncan't create thread :[%s]", strerror(err));

    /* Destroy the thread attributes object, since it is no longer needed */
    err = pthread_attr_destroy(&attr);
    if (err != 0)
        handle_error_en(err, "pthread_attr_destroy");

    return err;
#else
    return 0;
#endif
}


void init_threads()
{
	int i;

	logger_mod((LOGGER_MOD_LINOS|LOGGER_SUB_OS_MAIN), LOG_INFO, "Starting threads ...");

	for (i=0; i< (OS_TASK_CNT+GNULINUX_TASK_CNT);i++){

		if ( ThreadTasks[i].autostart == TRUE ) {
			start_thread(i);
		}
	}
}


int demonise(void)
{
	// Daemonise

	int i;
	int rc = 0;
#ifndef _WIN32

	// Our process ID and Session ID
	pid_t pid, sid;
	char str[10]; // PID string for /var/run

	logger_mod((LOGGER_MOD_LINOS|LOGGER_SUB_OS_MAIN), LOG_INFO, "starting the daemonizing process");

	// Open the PID file
	rc = open(pid_file_name,O_RDWR|O_CREAT|O_EXCL,0640);
	if ( rc < 0 ) {
		logger(LOG_ERR, "Oops problems opening pid file %s errno: %d (%s)",
				pid_file_name, errno, strerror(errno));
		exit(EXIT_FAILURE); /* Do NOT remove the PID file */
	}

	// Fork off the parent process
	pid = fork();
	if (pid < 0)
	{
		logger(LOG_ERR, "Problems forking the parent process.");
		exit(EXIT_FAILURE); // ERROR
	}
	// If we got a good PID, then
	// we can exit the parent process.
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	// Change the file mode mask
	umask(0);

	// Create a new SID for the child process
	sid = setsid();
	if (sid < 0) {
		// Log the failure
		logger(LOG_ERR, "Problems creating SID for the child process.");
		close_sigint(EXIT_FAILURE);
	}

	// Change the current working directory
	if ((chdir("/")) < 0) {
		// Log the failure
		logger(LOG_ERR, "Problems changing the current working directory.");
		close_sigint(EXIT_FAILURE);
	}
	else
	{
		logger_mod((LOGGER_MOD_LINOS|LOGGER_SUB_OS_MAIN), LOG_INFO, "Daemonised !!");
	}


	// Close out the standard file descriptors
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	i=open("/dev/null",O_RDWR); /* open stdin */
	dup(i); /* stdout */
	dup(i); /* stderr */
	//

	// Save the PID
	// Lock to prevent multiple processes
	if (lockf(rc,F_TLOCK,0)<0)
	{
		logger(LOG_ERR, "Oops problems locking pid file %s.", pid_file_name);
		close_sigint(EXIT_FAILURE);
	}

	sprintf(str,"%d\n",getpid());
	write(rc,str,strlen(str)); // record pid to lockfile
	logger(LOG_INFO, "PID run file is %s containing the PID %s", pid_file_name, str);
	// close(rc); // Dont close to hold the lock.

#endif
	return rc;
}





int main(int argc, char *argv[])
{
	int rc = 0;

	int running = 1;

#ifndef _WIN32
	struct timespec tp;
#endif

	//progname = argv[0]; // Get this programs name.
	progname =  __PROGNAME__; // Get this programs name. Defined in Makefile

#ifdef USE_SYSLOG
	logger_open_close ( 1, progname );
#endif

	/* Save the PID file here */
	//strcat(pid_file_name, "/var/run/");
	strcat(pid_file_name, "/tmp/");
	strcat(pid_file_name, progname);
	strcat(bit_event_file_name,pid_file_name); /* Put the event file in the same place as the pid file */
#if defined(USE_LINOS_DB)
	strcat(db_file_name,pid_file_name); /* Put the database file in the same place as the pid file */
	strcat(db_file_name, ".sqlite3");
#endif
	strcat(pid_file_name, ".pid");
	strcat(bit_event_file_name,BIT_EVENT_FILE_NAME_SUFFIX);
	logger(LOG_INFO, "Bit event file name is %s",bit_event_file_name);

	if (settings(argc, argv))
	{
		usage();
		exit(1);
	}
#ifndef _WIN32
	logger(LOG_INFO,"Main. HZ is %ld CLOCKS_PER_SEC is %ld OsTickFreq is %ld", 
			HZ, CLOCKS_PER_SEC, OsTickFreq);
#endif
	logger(LOG_INFO,"%s", ArcticCore_Version.info);

	//OS_DEBUG(D_ALARM,"SIMONG TEST\n");

#ifndef _WIN32
	/* Catch these signals */
	signal(SIGHUP, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGQUIT, signal_handler);

	// Ignore these signals (deamonise)
	signal(SIGCHLD,SIG_IGN); /* child terminate signal */
	signal(SIGTSTP,SIG_IGN); /* ignore tty signals */
	signal(SIGTTOU,SIG_IGN);
	signal(SIGTTIN,SIG_IGN);
#endif


	if (daemonise)
	{
		demonise();
	}
	else
	{
		logger(LOG_INFO, "No daemonising.");

	}

#if defined(USE_LINOS_DB) && !defined(_WIN32)
	if ( db_init (db_file_name) )
	{
		logger(LOG_ERR,"Failed to initialize ArcCore CAL database '%s'", db_file_name);
		close_sigint(EXIT_FAILURE);
	}
	else
	{
		logger(LOG_INFO,"Opened ArcCore CAL database '%s'", db_file_name);
	}
#endif


	/* *************** START ********************** */

#if defined(USE_LINOS_DB) && !defined(_WIN32)
	rc = db_get_register ( DB_ECU_RUNTIME_REG_ADDRESS, 1, callback_print_runtime);

	if ( rc != DB_OK )
	{
		logger(LOG_ERR, "ERROR: process_query DB ERROR: %d", rc);
	}
#endif
#ifndef _WIN32
	Linos_GetCurrentTime(&tp);

	logger(LOG_INFO,"Start-up @ clock real time:      %ld.%09ld or %s",
			tp.tv_sec, tp.tv_nsec, ctime(&tp.tv_sec));
#endif
	if (stop_at_runtime)
	{
		close_sigint(rc);
		return rc;
	}


	EcuM_Init(); /* This calls InitOS() */
	init_threads();

	/* THIS is the Main Thread */

	/* All this is just for test */
	int sleep_time_s = 1;
	while (running)
	{
		if ( loops != 999 ) {
			logger(LOG_INFO, "Loops left %d\n", loops);
			if ( loops > 1 ) {
				loops--;
			} else {
				running=0;
			}
		}
#ifndef _WIN32
		sleep(sleep_time_s);
#endif
#if defined(USE_LINOS_DB) && !defined(_WIN32)
		rc = db_inc_register (DB_ECU_RUNTIME_REG_ADDRESS, sleep_time_s, DB_CREATE_MISSING_WRITE, 1,1); // force_write, writeable
		if ( rc != DB_OK )
		{
			logger(LOG_ERR, "DB_ECU_RUNTIME Problems saving runtime to DB.");
		}
#endif

		/* Linos_StbM_GetCurrentTime TEST */
		if ((DebugMask & (LOGGER_MOD_LINOS|LOGGER_SUB_OS_MAIN)) == (LOGGER_MOD_LINOS|LOGGER_SUB_OS_MAIN))
		{
			StbM_TimeStampType testTime;
			StbM_UserDataType UserData;
			Std_ReturnType testReturn;
			uint8_t flag_timeout = 0, flag_global_time_base = 0;


			testReturn = Linos_StbM_GetCurrentTime(0, &testTime, &UserData);

			if ( testReturn != E_OK )
			{
				logger(LOG_ERR, "os_main : testReturn is %d", testReturn);
			}
			else
			{
				if ( testTime.timeBaseStatus & 0x01 )
					flag_timeout = 1;

				if ( testTime.timeBaseStatus & 0x08 )
					flag_global_time_base = 1;

				logger(LOG_INFO, "os_main : sys TIME : %d.%d.%09d \tflag_timeout:%d\tflag_global_time_base:%d\n",
						testTime.secondsHi, testTime.seconds, testTime.nanoseconds, flag_timeout, flag_global_time_base);
			}
			/*				*/
		}
	}

	close_sigint(rc);
	return rc;
}
