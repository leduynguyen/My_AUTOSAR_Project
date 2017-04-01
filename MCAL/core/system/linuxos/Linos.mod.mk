# Linos

obj-$(USE_LINOS) += Os_Cfg.o sys_tick.o os_linos.o linos_logger.o os_main.o os_stubs.o
obj-$(USE_LINOS) += os_task_linos.o arch.o
obj-$(USE_LINOS) += os_counter_linos.o os_alarm_linos.o os_init_linos.o os_event_linos.o
inc-$(USE_LINOS) += $(ROOTDIR)/arch/gnulinux/gnulinux/kernel
vpath-$(USE_LINOS) += $(ROOTDIR)/arch/gnulinux/gnulinux/kernel
inc-$(USE_LINOS) += $(ROOTDIR)/system/linuxos
inc-$(USE_LINOS) += $(ROOTDIR)/system/StbM
vpath-$(USE_LINOS) += $(ROOTDIR)/system/linuxos
CFLAGS += -D__PROGNAME__=\"$(PROJECTNAME)\"


# Antons ADPM project doesn't use the MCU module, but needs Mcu.o
ifndef USE_MCU
obj-$(USE_LINOS) += Mcu.o
endif
#

# RedHat 6 and Centos 6 and Ubuntu 12 
# needs the RealTime library to be defined. (GCC 4.8)
ifneq ($(OS),Windows_NT)
	ifdef USE_LINOS
	LDFLAGS += -lrt
	endif
endif

# Ubuntu 12 needs this too.
#LDFLAGS += -Wl,--no-as-needed

ifneq ($(OS),Windows_NT)
    # Database module
    obj-$(USE_LINOS_DB) += database.o
    #Sqlite3 devel library needed for this.
    ifdef USE_LINOS_DB
    LDFLAGS += -lsqlite3
    endif
    #
endif
