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

/** @tagSettings DEFAULT_ARCHITECTURE=TMS570 */
/** @reqSettings DEFAULT_SPECIFICATION_REVISION=4.1.2 */

#define SPI_HW_SOURCE 1


#include "Spi.h"
#include "Spi_Hw.h"
#include "SchM_Spi.h"
#include "Cpu.h"

#define SPI_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

/* static structures */
static Spi_HwInstType Spi_HwSeqIdInst_t[SPI_MAX_HWUNIT];
/* job event structure, for actual job */
static Spi_HwEventType Spi_HwJobEvent_at[SPI_MAX_HWUNIT];
/* data structure for Spi_Dlc.c */
static Spi_DlcEventType Spi_DlcSetEvent_t[SPI_MAX_HWUNIT];

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
/* mode variable */
static Spi_AsyncModeType Spi_HwMode_t;
#endif

#define SPI_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"


/* prototypes */

#define SPI_START_SEC_CODE
#include "MemMap.h"

static FUNC(void, SPI_CODE) Spi_HwJobConsumeEvent(uint16_least HW_Inst_Nr_u8);
static FUNC(void, SPI_CODE) Spi_HwSeqConsumeEvent(uint16_least HW_Inst_Nr_u8);
static FUNC(void, SPI_CODE) Spi_HwSeqNext(uint16_least HW_Inst_Nr_u8);
static FUNC(void, SPI_CODE) Spi_HwSeqComplete(uint16_least HW_Inst_Nr_u8);
static FUNC(void, SPI_CODE) Spi_HwSeqCleanUp(uint16_least HW_Inst_Nr_u8);
static FUNC(void, SPI_CODE) Spi_HwSeqAdjust(uint16_least SequenceID);

static FUNC(void, SPI_CODE) Spi_HwJobsSort(void);
static FUNC(void, SPI_CODE)Spi_HwJobTransmit(uint16_least HW_Inst_Nr_u8);
static FUNC(void, SPI_CODE)Spi_HwJobClear(uint16_least SequenceID);
static FUNC(Std_ReturnType, SPI_CODE)Spi_HwJobQueue(uint16_least SequenceID);

static void Spi_GlobalSuspend(void);
static void Spi_GlobalRestore(void);

imask_t irqState;

/* functions */

static void Spi_GlobalSuspend(void)
{
    SchM_Enter_Spi_EA_0();
}

static void Spi_GlobalRestore(void)
{
    SchM_Exit_Spi_EA_0();
}

static FUNC(void, SPI_CODE) Spi_HwSeqConsumeEvent(uint16_least HW_Inst_Nr_u8)
{
    uint16_least SeqId_u16;
    Spi_HwEventDefType ev_loc_t ;

    SeqId_u16  = Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdAkt_u8;

    Spi_GlobalSuspend();
    /* back it up */
    ev_loc_t = (Spi_HwEventDefType) Spi_HwSeqEvent_at[SeqId_u16].Event_u8 ;
    /* consume event in global structure */
    Spi_HwSeqEvent_at[SeqId_u16].Event_u8 = SPI_HW_EV_CONSUMED;
    Spi_GlobalRestore();

    switch (ev_loc_t)
    {
        case SPI_HW_EV_INIT:
        break;

        case SPI_HW_EV_SEQ_START:
        Spi_HwJobEvent_at[HW_Inst_Nr_u8].Event_u8 = SPI_HW_EV_JOB_START ;  /* start first job */
        Spi_HwJobConsumeEvent(HW_Inst_Nr_u8) ;
        break;

        case SPI_HW_EV_CANCEL:
        break;

        case SPI_HW_EV_FAILED:
        /* if a job fails, a sequence also fails ! See Spi_HwJobConsumeEvent() */
        break;

        default:
        break;
    }
}

static FUNC(void, SPI_CODE) Spi_HwJobConsumeEvent(uint16_least HW_Inst_Nr_u8)
{
    Spi_HwEventDefType ev_loc ;

    Spi_GlobalSuspend();
    ev_loc = (Spi_HwEventDefType) Spi_HwJobEvent_at[HW_Inst_Nr_u8].Event_u8 ;
    /* consume event in global structure */
    Spi_HwJobEvent_at[HW_Inst_Nr_u8].Event_u8 = SPI_HW_EV_CONSUMED ;
    Spi_GlobalRestore();

    switch (ev_loc)
    {
        case SPI_HW_EV_INIT:
        break;

        case SPI_HW_EV_JOB_START:
        /* start a job. If this job is synchronous it has to be decoupled from the ISR context */
        if(Spi_DlcSetEvent_t[HW_Inst_Nr_u8].Event_u8 == SPI_DLC_EV_SYNCTX)
        {
            if(Spi_DlcSetEvent(&Spi_DlcSetEvent_t[HW_Inst_Nr_u8]) == E_NOT_OK)
            {
                /* job transfer request was declined */
                Spi_JobsSorted_at[Spi_HwJobEvent_at[HW_Inst_Nr_u8].TaskID_u8].JobStatus_u8 = SPI_JOB_PENDING ;
                Spi_HwJobEvent_at[HW_Inst_Nr_u8].Event_u8 = SPI_HW_EV_JOB_START;
                Spi_DlcSetEvent_t[HW_Inst_Nr_u8].Event_u8 = SPI_DLC_EV_SYNCTX;
            }
            else
            {
                /* no action */
            }
        }
        else
        {
            Spi_HwJobTransmit(HW_Inst_Nr_u8) ;
        }
        break;

        case SPI_HW_EV_JOB_FINISHED:
        /* check if a sequence has completed */
        Spi_HwSeqComplete(HW_Inst_Nr_u8);
        /* transmit a new job if it is pending */
        Spi_HwJobTransmit(HW_Inst_Nr_u8) ;
        break;

        case SPI_HW_EV_CANCEL:
        break;

        case SPI_HW_EV_FAILED:
        /* clean up the failed sequence */
        Spi_HwSeqCleanUp(HW_Inst_Nr_u8);
        /* transmit a new job if it is pending */
        Spi_HwJobTransmit(HW_Inst_Nr_u8) ;
        break;

        default:
        break;
    }
}

/* Requirements : AR_SPI_SR53, AR_SPI_SR54, AR_SPI_SR55 */
static FUNC(void, SPI_CODE) Spi_HwJobsSort(void)
{
    uint16_least JobIdx_u16;    /* job Id index for loop  */
    uint16_least SortedIdx_u16; /* Sorted index for priority array */
    uint16_least PrioIdx_u16;   /* priority index for loop*/
    uint16_least Prio_u16;      /* priority of a job */
    uint8_least  JobId;

    /* sort jobs by priority */
    /* sorting looks like this:
     *  Id             prio             ->  Id          prio
     * Job0             1          ------>  Job1         3
     * Job1             3  -------/         Job2         2
     * Job2             2                   Job4         2
     * Job3             0                   Job0         1
     * Job4             2                   Job3         0*/

    /* this loop decreases the priority from max to min */
    Prio_u16 = SPI_MAX_JOB_PRIO ;
    SortedIdx_u16 = 0U;
    for(PrioIdx_u16 = 0U ; PrioIdx_u16 <= SPI_MAX_JOB_PRIO ; PrioIdx_u16++)
    {
        /* this loop searches for all jobs with the same priority */
        for(JobIdx_u16 = 0U ; JobIdx_u16 < Spi_ConfigPtr_pt->Spi_MaxJobs ; JobIdx_u16++)
        {
            /* scan for actual priority */
            if(Spi_ConfigPtr_pt->Spi_JobCfg[JobIdx_u16].Spi_JobPrio == Prio_u16)
            {
                JobId = Spi_ConfigPtr_pt->Spi_JobCfg[JobIdx_u16].Spi_JobID;
                /* assign first job with highest priority [3,2,1,0] */
                Spi_JobsSorted_at[SortedIdx_u16].JobID_u8 = (uint8)JobId;
                Spi_JobPrioConvTbl_at[JobId] = (uint8)SortedIdx_u16;
                SortedIdx_u16++;
                /* job assigned, scan for next */
            }
            else
            {
                /* no action */
            }
            Spi_JobsSorted_at[JobIdx_u16].SeqID_u8  = 0xFFU ;
        }
        /* scan all jobs for next lower priority */
        Prio_u16--;
    }
}

/***********************************************************************************************************************
 *  Spi_HwJobQueue
 **********************************************************************************************************************/
/*! \brief      This method queues jobs by priority.
 *  \param[in]  none
 *  \param[out] none
 *  \return     none
 *  \pre        Input parameter must not be NULL.
 *  \context    Function is called from task level
 *  \note       Specification of module job handling
 **********************************************************************************************************************/
/* SourceId : SPI_SourceId_055 */
/* Requirements : AR_SPI_SR56, AR_SPI_SR200, AR_SPI_SR205 */
static FUNC(Std_ReturnType, SPI_CODE)Spi_HwJobQueue(uint16_least SequenceID)
{
    uint16_least JobCnt_u16; /* loop over the number of jobs in a sequence */
    uint16_least JobIdx_u16; /* index to loop over the max number of jobs */
    uint16_least JobId_u16;  /* ID of a job*/
    Spi_JobSortedType* JobChain_pt; /* pointer for a sequence chain of jobs */
    
    /* first check all jobs if they are allowed to be queued */
    for(JobCnt_u16 = 2U ; JobCnt_u16 <= (Spi_ConfigPtr_pt->Spi_SeqCfg[SequenceID].Spi_JobList[1U] + 1U) ; JobCnt_u16++)
    {
        /* get first assigned job of a sequence, starts a index 1 */
        JobId_u16  = Spi_ConfigPtr_pt->Spi_SeqCfg[SequenceID].Spi_JobList[JobCnt_u16];
        JobIdx_u16 = Spi_JobPrioConvTbl_at[JobId_u16];
        /* check the job for collision  */
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
        if(  (Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 == SPI_JOB_PENDING)
          || (Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 == SPI_JOB_QUEUED))
        {
            /* the sequence is rejected due to common used jobs */
            return(E_NOT_OK) ;
        }
#elif defined(CFG_TMS570LC43X)
        if(  (Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 == SPI_JOB_PENDING)
          || (Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 == SPI_JOB_ACTIVE))
        {
            /* the sequence is rejected due to common used jobs */
            return(E_NOT_OK) ;
        }
#else
#error This SPI driver does not support this MCU.
#endif
    }
    /* checking passed, continue to queue
     * clear last index marker
     */
    JobChain_pt = (Spi_JobSortedType *) NULL_PTR;
    /* loop over all jobs sorted by priority */
    for(JobCnt_u16 = 2U ; JobCnt_u16 <= ( Spi_ConfigPtr_pt->Spi_SeqCfg[SequenceID].Spi_JobList[1U] + 1U) ; JobCnt_u16++)
    {
        /* get first assigned job of a sequence, starts a index 1 */
        JobId_u16  = Spi_ConfigPtr_pt->Spi_SeqCfg[SequenceID].Spi_JobList[JobCnt_u16] ;
        JobIdx_u16 = Spi_JobPrioConvTbl_at[JobId_u16];
        /* assign the first job with highest priority in a sequence */
        Spi_JobsSorted_at[JobIdx_u16].SeqID_u8   = (uint8)SequenceID ;
        /* job is marked for transfer */
        Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 = SPI_JOB_PENDING ;
        /* now build up job chain */
        if(JobChain_pt != NULL_PTR)
        {
            /* set next pointer to second assigned job */
            JobChain_pt->JobNext_pt = &Spi_JobsSorted_at[JobIdx_u16];
        }
        else
        {
            /* no action */
        }
        /* set global job status*/
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
        Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_JobResult[JobId_u16] = SPI_JOB_PENDING;
#elif defined(CFG_TMS570LC43X)
        Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_JobResult[JobId_u16] = SPI_JOB_QUEUED;
#else
#error This SPI driver does not support this MCU.
#endif
        /* save actual pointer to chain pointer for later use */
        JobChain_pt = &Spi_JobsSorted_at[JobIdx_u16];
    }
    /* all jobs accepted and queued,
     * sequence successfully added
     */
    Spi_HwSeqIdInst_t[Spi_ConfigPtr_pt->Spi_SeqCfg[SequenceID].Spi_JobList[0U]].SeqNrPend_u8++ ;
    return(E_OK) ;
}

/***********************************************************************************************************************
 *  Spi_HwJobClear
 **********************************************************************************************************************/
/*! \brief      This method clears queued jobs.
 *  \param[in]  none
 *  \param[out] none
 *  \return     none
 *  \pre        Input parameter must not be NULL.
 *  \context    Function is called from task level
 *  \note       Specification of module job handling
 **********************************************************************************************************************/
/* SourceId : SPI_SourceId_056 */
/* Requirements : AR_SPI_SR272 */
static FUNC(void, SPI_CODE)Spi_HwJobClear(uint16_least SequenceID)
{
    uint16_least JobIdx_u16; /* index to loop over the max number of jobs */
    uint16_least JobId_u16;  /* ID of a job*/
    P2VAR(Spi_JobSortedType, AUTOMATIC, SPI_VAR_NOINIT) JobChain_pt; /* pointer for a sequence chain of jobs */
    P2VAR(Spi_JobSortedType, AUTOMATIC, SPI_VAR_NOINIT) JobAkt_pt;   /* pointer for a job chain in a sequence */

    /* get first assigned job of a sequence, starts a index 1 */
    JobId_u16   = Spi_ConfigPtr_pt->Spi_SeqCfg[SequenceID].Spi_JobList[2U] ;
    JobIdx_u16  = Spi_JobPrioConvTbl_at[JobId_u16];
    JobChain_pt = &Spi_JobsSorted_at[JobIdx_u16];

    /* now clean up the remaining chained jobs */
    while(JobChain_pt != NULL_PTR)
    {
        /* clear all pending jobs belonging to this sequence */
        JobId_u16 = JobChain_pt->JobID_u8;
#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
        if(  (JobChain_pt->JobStatus_u8 == SPI_JOB_PENDING)
          || (JobChain_pt->JobStatus_u8 == SPI_JOB_QUEUED))
        {
            /* set job state */
            JobChain_pt->JobStatus_u8  = SPI_JOB_OK;
            Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_JobResult[JobId_u16] = SPI_JOB_OK;
        }
#elif defined(CFG_TMS570LC43X)
        if(  (JobChain_pt->JobStatus_u8 == SPI_JOB_PENDING)
          || (JobChain_pt->JobStatus_u8 == SPI_JOB_ACTIVE))
        {
            /* set job state */
            JobChain_pt->JobStatus_u8  = SPI_JOB_OK;
            Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_JobResult[JobId_u16] = SPI_JOB_OK;
        }
#else
#error This SPI driver does not support this MCU.
#endif
        /* save current job */
        JobAkt_pt   = JobChain_pt;
        /* get next job */
        JobChain_pt = JobAkt_pt->JobNext_pt;
        /* and remove the reference */
        JobAkt_pt->JobNext_pt = NULL_PTR;
    }
    /* clear number of jobs */
    Spi_HwSeqEvent_at[SequenceID].NrOfJobs_u8 = 0U ;
    return;
}

#if defined(CFG_TMS570LS12X) || defined(CFG_TMS570LS1114)
static FUNC(void, SPI_CODE)Spi_HwJobTransmit(uint16_least HW_Inst_Nr_u8)
{
    uint16_least JobCnt_u16;
    uint16_least JobIdx_u16;    /* index to loop over the max number of jobs */
    uint16_least SeqId_u16;     /* ID of a sequence */
    uint16_least SeqIdAt_u16;   /* ID of a sequence attached to a job */
    uint16_least SeqIdRep_u16;  /* ID of a sequence reported by a job complete */

    /* skip the remaining code, if no sequence has been queued */
    if(Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqNrPend_u8 == 0U)
    {
        /* Do nothing */
    }
    else
    {
        /* get actual sequence ID */
        SeqId_u16    = Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdAkt_u8;
        /* get reported sequence ID, but beware of the init value */
        SeqIdRep_u16 = Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdRep_u8;

        /* if a synchronous sequence was reported, finish the complete sequence regardless of job priority */
        if(  (SeqIdRep_u16 != 0x00FFU)
          && (Spi_HwSeqEvent_at[SeqIdRep_u16].Guard_u8 == SPI_HW_SYNC) )
        {
            JobIdx_u16 =  Spi_JobPrioConvTbl_at[Spi_HwJobEvent_at[HW_Inst_Nr_u8].TaskID_u8];
            Spi_JobsSorted_at[JobIdx_u16].JobNext_pt->JobStatus_u8 = SPI_JOB_QUEUED ;
            /* now prepare job transmission ! */
            Spi_DlcSetEvent_t[HW_Inst_Nr_u8].JobID_u8 = Spi_JobsSorted_at[JobIdx_u16].JobNext_pt->JobID_u8;
            Spi_DlcSetEvent_t[HW_Inst_Nr_u8].Event_u8 = SPI_DLC_EV_SYNCTX;
            Spi_HwJobEvent_at[HW_Inst_Nr_u8].Event_u8 = SPI_HW_EV_JOB_START;
        }
        else
        {
            /* search for serviceable jobs in the Seq*/
            for(JobCnt_u16 = 2U; JobCnt_u16 <= ( Spi_ConfigPtr_pt->Spi_SeqCfg[SeqId_u16].Spi_JobList[1U] + 1U) ; JobCnt_u16++)
            {
                /* get first assigned job of a sequence, starts a index 1 */
                JobIdx_u16 = Spi_JobPrioConvTbl_at[Spi_ConfigPtr_pt->Spi_SeqCfg[SeqId_u16].Spi_JobList[JobCnt_u16]];

                /* check all jobs if they are marked for transmission     */
                /* one of these jobs will be transmitted, done by queuing */
                if(  (Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 == SPI_JOB_PENDING)
                  || (Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 == SPI_JOB_QUEUED ))
                {
                    /* if a job is marked for transmission, but belongs not to the actual
                     * sequence, it can be transmitted because the JobIdx_u16 loop goes from highest to lowest priority
                     * get Job ID
                     */
                    Spi_DlcSetEvent_t[HW_Inst_Nr_u8].JobID_u8 = Spi_JobsSorted_at[JobIdx_u16].JobID_u8;
                    SeqIdAt_u16                = Spi_JobsSorted_at[JobIdx_u16].SeqID_u8;
                    /* if a sequence is synchronous, handle this first. This also includes a reported sequence
                     * If a job starts a sync sequence, this sequence must be transmitted completely regardless
                     * of the job priority
                     */
                    if(   (Spi_HwSeqEvent_at[SeqId_u16].Guard_u8    == SPI_HW_SYNC)
                       || (Spi_HwSeqEvent_at[SeqIdAt_u16].Guard_u8  == SPI_HW_SYNC))
                    {
                        /* now prepare job transmission ! */
                        Spi_DlcSetEvent_t[HW_Inst_Nr_u8].Event_u8 = SPI_DLC_EV_SYNCTX;
                        Spi_HwJobEvent_at[HW_Inst_Nr_u8].Event_u8 = SPI_HW_EV_JOB_START;
                        /* the transmission should not take place in an ISR context, so break here and schedule again */
                        break;
                    }
                    else
                    {
                        Spi_DlcSetEvent_t[HW_Inst_Nr_u8].Event_u8 = SPI_DLC_EV_ASYNCTX;
                    }
                    /* if the sequence interruptible and a job is not attached to this sequence */
                    if(  (Spi_ConfigPtr_pt->Spi_SeqCfg[SeqId_u16].Spi_SeqInt == TRUE)
                      && (SeqIdAt_u16 != SeqId_u16))
                    {
                        /* prepare job transmission ! */
                        Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 = SPI_JOB_QUEUED ;
                    }
                    /* sequence is not interruptible */
                    else
                    {
                        if(SeqIdAt_u16 == SeqId_u16)
                        {
                            /* job transmission is asynchronous */
                            Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 = SPI_JOB_QUEUED ;
                        }
                        else
                        {
                            /* no action */
                        }
                    }
                    if(Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 == SPI_JOB_QUEUED)
                    {
                        if(Spi_DlcSetEvent(&Spi_DlcSetEvent_t[HW_Inst_Nr_u8]) == E_NOT_OK)
                        {
                            /* job transfer request was declined */
                            Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 = SPI_JOB_PENDING ;
                            Spi_HwJobEvent_at[HW_Inst_Nr_u8].Event_u8 = SPI_HW_EV_JOB_START;
                            Spi_DlcSetEvent_t[HW_Inst_Nr_u8].Event_u8 = SPI_DLC_EV_CONSUMED;
                        }
                        else
                        {
                            /* no action */
                        }
                        break ;
                    }
                }
                else
                {
                    /* no action */
                }
            }
        }
    }
}
#elif defined(CFG_TMS570LC43X)
/***********************************************************************************************************************
 *  Spi_HwJobTransmit
 **********************************************************************************************************************/
/*! \brief      This method transmits queued jobs.
 *  \param[in]  none
 *  \param[out] none
 *  \return     none
 *  \pre        Input parameter must not be NULL.
 *  \context    Function is called from task level
 *  \note       Specification of module job handling
 **********************************************************************************************************************/
static FUNC (void, SPI_CODE)Spi_HwJobTransmit(uint16_least HW_Inst_Nr_u8)
{
    uint16_least JobCnt_u16;
    uint16_least JobIdx_u16;    /* index to loop over the max number of jobs */
    uint16_least SeqId_u16;     /* ID of a sequence */
    uint16_least SeqIdAt_u16;   /* ID of a sequence attached to a job */

    /* skip the remaining code, if no sequence has been queued */
    if(Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqNrPend_u8 == 0U)
    {
        /* Do nothing */
    }
    else
    {
        /* get actual sequence ID */
        SeqId_u16    = Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdAkt_u8;

        /* search for serviceable jobs in the Seq*/
        for(JobCnt_u16 = 2U; JobCnt_u16 <= ( Spi_ConfigPtr_pt->Spi_SeqCfg[SeqId_u16].Spi_JobList[1U] + 1U) ; JobCnt_u16++)
        {
            /* get first assigned job of a sequence, starts a index 1 */
            JobIdx_u16 = Spi_JobPrioConvTbl_at[Spi_ConfigPtr_pt->Spi_SeqCfg[SeqId_u16].Spi_JobList[JobCnt_u16]];

            /* check all jobs if they are marked for transmission     */
            /* one of these jobs will be transmitted, done by queuing */
            if(  (Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 == SPI_JOB_PENDING)
              || (Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 == SPI_JOB_ACTIVE ))
            {
                /* if a job is marked for transmission, but belongs not to the actual
                 * sequence, it can be transmitted because the JobIdx_u16 loop goes from highest to lowest priority
                 * get Job ID
                 */
                Spi_DlcSetEvent_t[HW_Inst_Nr_u8].JobID_u8 = Spi_JobsSorted_at[JobIdx_u16].JobID_u8;
                SeqIdAt_u16                = Spi_JobsSorted_at[JobIdx_u16].SeqID_u8;

                Spi_DlcSetEvent_t[HW_Inst_Nr_u8].Event_u8 = SPI_DLC_EV_ASYNCTX;

                /* if the sequence interruptible and a job is not attached to this sequence */
                if(  (Spi_ConfigPtr_pt->Spi_SeqCfg[SeqId_u16].Spi_SeqInt == TRUE)
                  && (SeqIdAt_u16 != SeqId_u16))
                {
                    /* prepare job transmission ! */
                    Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 = SPI_JOB_ACTIVE ;
                    /* Set Global Status */
                    Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_JobResult[Spi_JobsSorted_at[JobIdx_u16].JobID_u8] = SPI_JOB_PENDING;
                }
                /* sequence is not interruptible */
                else
                {
                    if(SeqIdAt_u16 == SeqId_u16)
                    {
                        /* job transmission is asynchronous */
                        Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 = SPI_JOB_ACTIVE ;
                        /* Set Global Status */
                        Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_JobResult[Spi_JobsSorted_at[JobIdx_u16].JobID_u8] = SPI_JOB_PENDING;
                    }
                    else
                    {
                        /* no action */
                    }
                }
                if(Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 == SPI_JOB_ACTIVE)
                {
                    if(Spi_DlcSetEvent(&Spi_DlcSetEvent_t[HW_Inst_Nr_u8]) == E_NOT_OK)
                    {
                        /* job transfer request was declined */
                        Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 = SPI_JOB_PENDING ;
                        Spi_HwJobEvent_at[HW_Inst_Nr_u8].Event_u8 = SPI_HW_EV_JOB_START;
                        Spi_DlcSetEvent_t[HW_Inst_Nr_u8].Event_u8 = SPI_DLC_EV_CONSUMED;
                    }
                    else
                    {
                        /* no action */
                    }
                    break ;
                }
             }
             else
             {
                 /* no action */
             }
        }
    }
}
#else
#error This SPI driver does not support this MCU.
#endif

static FUNC(void, SPI_CODE) Spi_HwSeqAdjust(uint16_least SequenceID)
{
    if(Spi_HwSeqEvent_at[SequenceID].SeqPrev_pt != NULL_PTR)
    {
        /* adjust pointer to prev sequence */
        if(Spi_HwSeqEvent_at[SequenceID].SeqNext_pt != NULL_PTR)
        {
            Spi_HwSeqEvent_at[SequenceID].SeqNext_pt->SeqPrev_pt = Spi_HwSeqEvent_at[SequenceID].SeqPrev_pt;
        }
    }
    if(Spi_HwSeqEvent_at[SequenceID].SeqNext_pt != NULL_PTR)
    {
        /* adjust pointer to next sequence */
        if(Spi_HwSeqEvent_at[SequenceID].SeqPrev_pt != NULL_PTR)
        {
            Spi_HwSeqEvent_at[SequenceID].SeqPrev_pt->SeqNext_pt = Spi_HwSeqEvent_at[SequenceID].SeqNext_pt;
        }
    }
    /* clear pointer's */
    Spi_HwSeqEvent_at[SequenceID].SeqNext_pt = NULL_PTR;
    Spi_HwSeqEvent_at[SequenceID].SeqPrev_pt = NULL_PTR;
}

/* SourceId : SPI_SourceId_057 */
/* Requirements : AR_SPI_SR45, AR_SPI_SR52, AR_SPI_SR75, AR_SPI_SR138 */
static FUNC(void, SPI_CODE) Spi_HwSeqNext(uint16_least HW_Inst_Nr_u8)
{
    uint16_least SeqId_u16;    /* Id of a sequence */

    /* this sequence was reported as finished */
    SeqId_u16 = Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdRep_u8;
    /* we need to check the sequence which was reported by JobComplete */
    if(Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqNrPend_u8 == 0U)
    {
        /* all sequences were executed, set global status to IDLE */
        /* clear pointer's */
        Spi_HwSeqEvent_at[SeqId_u16].SeqNext_pt = NULL_PTR;
        Spi_HwSeqEvent_at[SeqId_u16].SeqPrev_pt = NULL_PTR;
        Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdAkt_u8  = 0xFFU;
        Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdPend_u8 = 0xFFU;
        Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdRep_u8  = 0xFFU;
        Spi_DrvStatus = SPI_IDLE;
    }
    else
    {
        /* check if this sequence is the one actually being exectuted */
        if(Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdAkt_u8 == SeqId_u16)
        {
            /* set next sequence to execute */
            Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdAkt_u8 = Spi_HwSeqEvent_at[SeqId_u16].SeqNext_pt->TaskID_u8;
        }
        else
        {
            /* no action */
        }
        /* due to the priority of the jobs, any sequence may be reported as finished */
        /* so the pointers need to be adjusted and the next sequence in line has to be executed */
        Spi_HwSeqAdjust(SeqId_u16);
    }
}


/* Requirements : AR_SPI_SR63, AR_SPI_SR152, AR_SPI_SR202 */
static FUNC(void, SPI_CODE) Spi_HwSeqCleanUp(uint16_least HW_Inst_Nr_u8)
{
    uint16_least JobIdx_u16;    /* Index of a job   */
    uint16_least JobId_u16;     /* ID of a job      */
    uint16_least SeqId_u16;    /* Id of a sequence */

    P2VAR(Spi_JobSortedType, AUTOMATIC, SPI_VAR_NOINIT) JobChain_pt; /* pointer for a job chain in a sequence */
    P2VAR(Spi_JobSortedType, AUTOMATIC, SPI_VAR_NOINIT) JobAkt_pt;   /* pointer for a job chain in a sequence */

    /* this sequence was reported as finished */
    SeqId_u16 = Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdRep_u8;
    /* this is set by the DLC module, every time a job has completed */
    JobId_u16   = Spi_HwJobEvent_at[HW_Inst_Nr_u8].TaskID_u8;
    JobIdx_u16  = Spi_JobPrioConvTbl_at[JobId_u16];
    /* set chain pointer */
    JobChain_pt = &Spi_JobsSorted_at[JobIdx_u16];

    /* Enter Critical Section */
    Spi_GlobalSuspend();

    /* next seek all jobs belonging to this sequence  and clear these jobs */
    while(JobChain_pt != NULL_PTR)
    {
        JobId_u16 = JobChain_pt->JobID_u8;
        /* reset sequence ID */
        JobChain_pt->SeqID_u8 = 0xFFU;
        /* set jobstate */
        JobChain_pt->JobStatus_u8  = SPI_JOB_FAILED;
        Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_JobResult[JobId_u16] = SPI_JOB_FAILED;
        /* save current job */
        JobAkt_pt = JobChain_pt;
        /* get next job */
        JobChain_pt = JobAkt_pt->JobNext_pt;
        /* and remove the reference */
        JobAkt_pt->JobNext_pt = NULL_PTR;
    }
    /* clear number of jobs */
    Spi_HwSeqEvent_at[SeqId_u16].NrOfJobs_u8 = 0U;
    /* clear transmission mode */
    Spi_HwSeqEvent_at[SeqId_u16].Guard_u8    = SPI_HW_UNDEF;

    Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqNrPend_u8--;
    /* set sequence result */
    Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_SeqResult[SeqId_u16] = SPI_SEQ_FAILED ;

    /* goto next sequence */
    Spi_HwSeqNext(HW_Inst_Nr_u8);
    /* now call configured sequence error notification */
    if(Spi_ConfigPtr_pt->Spi_SeqCfg[SeqId_u16].Spi_SequenceEndNotification != NULL_PTR)
    {
        Spi_ConfigPtr_pt->Spi_SeqCfg[SeqId_u16].Spi_SequenceEndNotification() ;
    }

    /* Exit Critical Section */
    Spi_GlobalRestore();
}

/* Requirements : AR_SPI_SR61, AR_SPI_SR63, AR_SPI_SR150, AR_SPI_SR209, AR_SPI_SR272, AR_SPI_SR287, AR_SPI_SR289,
 * AR_SPI_SR296 */
static FUNC(void, SPI_CODE) Spi_HwSeqComplete(uint16_least HW_Inst_Nr_u8)
{
    uint16_least SeqId_u16;    /* Id of a sequence */

    /* this sequence was reported as finished */
    SeqId_u16 = Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdRep_u8;

    /* now check if a sequence has completed */
    if(Spi_HwSeqEvent_at[SeqId_u16].NrOfJobs_u8 == 0U)
    {
        /* Enter Critical Section */
        Spi_GlobalSuspend();

        /* check if sequence has been canceled */
        if(Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_SeqResult[SeqId_u16] != SPI_SEQ_CANCELLED)
        {
            /* this part has already been done in the cancel part */
            Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqNrPend_u8--;
            Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_SeqResult[SeqId_u16] = SPI_SEQ_OK;
        }
        /* clear transmission mode */
        Spi_HwSeqEvent_at[SeqId_u16].Guard_u8 = SPI_HW_UNDEF;
        /* goto next sequence, handled in the Processing function */
        Spi_HwSeqNext(HW_Inst_Nr_u8);
        /* call configured sequence end notification */
        if(Spi_ConfigPtr_pt->Spi_SeqCfg[SeqId_u16].Spi_SequenceEndNotification != NULL_PTR )
        {
            Spi_ConfigPtr_pt->Spi_SeqCfg[SeqId_u16].Spi_SequenceEndNotification() ;
        }

        /* Exit Critical Section */
        Spi_GlobalRestore();
    }
    else
    {
        /* no action */
    }
}


/* Requirements : AR_SPI_SR60, AR_SPI_SR62, AR_SPI_SR145, AR_SPI_SR201, AR_SPI_SR202, AR_SPI_SR286, AR_SPI_SR289,
 * AR_SPI_SR293 */
FUNC(void, SPI_CODE) Spi_HwJobComplete(uint16_least Job_u16, uint16_least DLC_u16)
{
    uint16_least JobIdx_u16;    /* Index of a job*/
    uint16_least SeqId_u16;     /* ID of a sequence */

    /* this is set by the DLC module, every time a job has completed */
    JobIdx_u16 = Spi_JobPrioConvTbl_at[Job_u16];
    /* reset job in priority queue */
    /* backup sequence ID */
    SeqId_u16 = Spi_JobsSorted_at[JobIdx_u16].SeqID_u8 ;

    Spi_HwSeqIdInst_t[DLC_u16].SeqIdRep_u8 = (uint8)SeqId_u16;
    Spi_HwJobEvent_at[DLC_u16].TaskID_u8   = (uint8)Job_u16;
    /* reset sequence ID */
    Spi_JobsSorted_at[JobIdx_u16].SeqID_u8 = 0xFFU;

    /* one job less remaining in this sequence */
    if(Spi_HwSeqEvent_at[SeqId_u16].NrOfJobs_u8 > 0U)
    {
        Spi_HwSeqEvent_at[SeqId_u16].NrOfJobs_u8-- ;
    }
    /* call notification */
    if(Spi_ConfigPtr_pt->Spi_JobCfg[Job_u16].Spi_JobEndNotification != NULL_PTR)
    {
        /* call job end notification */
        Spi_ConfigPtr_pt->Spi_JobCfg[Job_u16].Spi_JobEndNotification() ;
    }
    /* set result of the JobID */
    /* this is important to do this after the callback notification */
    /* otherwise if a sequence is queued with the same job, the job is reloaded endless */
    /* Now check if an error was detected and update the status */
    if(Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_DlcResult[DLC_u16] == SPI_DLC_FAILED)
    {
        Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_JobResult[Job_u16] = SPI_JOB_FAILED ;
        Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 = SPI_JOB_FAILED;
        Spi_HwJobEvent_at[DLC_u16].Event_u8 = SPI_HW_EV_FAILED ;
    }
    else
    {
        Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_JobResult[Spi_HwJobEvent_at[DLC_u16].TaskID_u8] = SPI_JOB_OK ;
        Spi_JobsSorted_at[JobIdx_u16].JobStatus_u8 = SPI_JOB_OK;
        Spi_HwJobEvent_at[DLC_u16].Event_u8 = SPI_HW_EV_JOB_FINISHED ;
    }
    /* job was serviced */
    Spi_DlcSetEvent_t[DLC_u16].Event_u8 = SPI_DLC_EV_CONSUMED;

    /* reload the next transmission in the current context (interrupt) */
    Spi_HwJobConsumeEvent(DLC_u16) ;
}

FUNC(void, SPI_CODE) Spi_HwInit(void)
{
    uint16_least SeqIdx_u16 ;
    uint16_least HW_Inst_Nr_u8;   /* Instance of the SPI Hw */

    /* reset global data variables */

    for(HW_Inst_Nr_u8 = 0U ; HW_Inst_Nr_u8 < Spi_ConfigPtr_pt->Spi_MaxDlcs ; HW_Inst_Nr_u8++)
    {
      /* reset the working index of current processed sequence in the sequence event array */
      Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdAkt_u8  = 0xFFU;
      /* reset the working index of a pending sequence in the sequence event array */
      Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdPend_u8 = 0xFFU;
      /* reset the number of current queued sequences */
      Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqNrPend_u8 = 0U;
      /* reset the number of reported sequences */
      Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdRep_u8 = 0xFFU;
      Spi_HwJobEvent_at[HW_Inst_Nr_u8].Event_u8 = SPI_HW_EV_CONSUMED ;
      Spi_DlcSetEvent_t[HW_Inst_Nr_u8].Event_u8 = SPI_DLC_EV_CONSUMED;
    }

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
    Spi_HwMode_t = SPI_INTERRUPT_MODE;
#endif

    for(SeqIdx_u16 = 0U ; SeqIdx_u16 < Spi_ConfigPtr_pt->Spi_MaxSequences ; SeqIdx_u16++)
    {
        Spi_HwSeqEvent_at[SeqIdx_u16].Event_u8 = SPI_HW_EV_CONSUMED ;
        Spi_HwSeqEvent_at[SeqIdx_u16].Guard_u8 = SPI_HW_UNDEF ;
    }
    Spi_HwJobsSort() ;
    Spi_DlcInit() ;
}

FUNC(void, SPI_CODE) Spi_HwDeInit(void)
{
    Spi_DlcClose() ;
}

/* SourceId : SPI_SourceId_061 */
/* Requirements : AR_SPI_SR139, AR_SPI_SR151, AR_SPI_SR199, AR_SPI_SR270, AR_SPI_SR272 */
FUNC(Std_ReturnType, SPI_CODE) Spi_HwSetEvent
(
    P2CONST(Spi_HwEventType, AUTOMATIC, SPI_VAR) Hw_Event_pt
)
{
    uint16_least SeqId_u16;       /* id of a sequence, used as index of the sequence array */
    uint16_least JobNr_u16;       /* number of jobs in a configuration */
    uint16_least HW_Inst_Nr_u8;   /* Instance of the SPI Hw */
    Std_ReturnType Ret_loc ;

    SeqId_u16 = (uint16_least)Hw_Event_pt->TaskID_u8;
    HW_Inst_Nr_u8 =  Spi_ConfigPtr_pt->Spi_SeqCfg[SeqId_u16].Spi_JobList[0U];
    Ret_loc = E_NOT_OK;
    
    if (Hw_Event_pt->Event_u8 == SPI_HW_EV_CANCEL)
    {
        /* start critical section */
        Spi_GlobalSuspend();
        /* only a pending sequence can be cancelled */
        if(Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_SeqResult[SeqId_u16] == SPI_SEQ_PENDING)
        {
            /* only a pending sequence can be canceled */
            /* adjust pointers to next and previous sequence */
            Spi_HwSeqAdjust(SeqId_u16);
            Spi_HwSeqEvent_at[SeqId_u16].Event_u8 = SPI_HW_EV_CANCEL;
            Spi_HwSeqEvent_at[SeqId_u16].Guard_u8 = 0U;
            Spi_HwSeqEvent_at[SeqId_u16].NrOfJobs_u8 = 0U;
            Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqNrPend_u8--;
            /* clear all jobs belonging to this sequence */
            Spi_HwJobClear(SeqId_u16) ;
            Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_SeqResult[SeqId_u16] = SPI_SEQ_CANCELLED ;
        }
        else
        {
            /* no action */
        }
        /* stop critical section */
         Spi_GlobalRestore();
    }
    else
    {
        /* start critical section */
        Spi_GlobalSuspend();
        /* add a pending sequence ? */
        if(Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_SeqResult[SeqId_u16] != SPI_SEQ_PENDING) /* sequence pending ? */
        {
            /* sequence ID is the index of this array Spi_HwSeqEvent_at[] */
            /* try to queue the jobs, if a job belonging to a sequence is still pending, the check fails */
            Ret_loc = Spi_HwJobQueue(SeqId_u16) ;
            if(Ret_loc == E_OK)
            {
                /* set event ID */
                Spi_HwSeqEvent_at[SeqId_u16].Event_u8  = Hw_Event_pt->Event_u8;
                /* set sequence ID */
                Spi_HwSeqEvent_at[SeqId_u16].TaskID_u8 = (uint8)SeqId_u16;
                /* set sequence to pending */
                Spi_ConfigPtr_pt->Spi_GlobalStatus_pt->Spi_SeqResult[SeqId_u16] = SPI_SEQ_PENDING ;
                Spi_DrvStatus = SPI_BUSY ;
                /* guard is used for sync or async tx */
                Spi_HwSeqEvent_at[SeqId_u16].Guard_u8 = Hw_Event_pt->Guard_u8;
                /* get number of jobs from the configuration */
                JobNr_u16 = Spi_ConfigPtr_pt->Spi_SeqCfg[SeqId_u16].Spi_JobList[1U] ;
                Spi_HwSeqEvent_at[SeqId_u16].NrOfJobs_u8 = (uint8)JobNr_u16 ;
                /* assign a queue number to this sequence */
                if(Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqNrPend_u8 == 1U)
                {
                    /* start transmit if no sequence was pending  -> Spi_HwSeqConsumeEvent */
                    Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdAkt_u8  = (uint8)SeqId_u16;
                    Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdPend_u8 = (uint8)SeqId_u16;
                    /* stop critical section */
                    Spi_GlobalRestore();
                    Spi_HwSeqConsumeEvent(HW_Inst_Nr_u8); /* consume event */
                }
                else
                {
                    /* assign pointer to next sequence */
                    Spi_HwSeqEvent_at[Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdPend_u8].SeqNext_pt = &Spi_HwSeqEvent_at[SeqId_u16];
                    /* assign last queued sequence to prev pointer */
                    Spi_HwSeqEvent_at[SeqId_u16].SeqPrev_pt = &Spi_HwSeqEvent_at[Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdPend_u8];
                    /* stop critical section */
                    Spi_GlobalRestore();
                    /* any other transmit is done by the queued sequences, the queue */
                    /* is checked any time a job has completed */
                }
                /* all settings done, now update pending variable */
                Spi_HwSeqIdInst_t[HW_Inst_Nr_u8].SeqIdPend_u8 = (uint8)SeqId_u16;
            }
            else
            {
                /* stop critical section */
                /* shared job still pending !*/
                Spi_GlobalRestore();
            }
        }
        else
        {
            /* sequence is pending! */
            /* stop critical section */
            Spi_GlobalRestore();
        }
    }
    return (Ret_loc);
}

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)

FUNC(void, SPI_CODE) Spi_HwSetMode(Spi_AsyncModeType Mode)
{
    Spi_HwMode_t = Mode;
}
#endif

FUNC(void, SPI_CODE) Spi_HwProcessState(uint16_least HW_Inst_Nr_u8)
{
   /* schedule the event, check if a sequence has completed */
   Spi_HwJobConsumeEvent(HW_Inst_Nr_u8);
}

#define SPI_STOP_SEC_CODE
#include "MemMap.h"
