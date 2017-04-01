# Can
ifdef CFG_MPC5777M
obj-$(USE_CAN)-$(CFG_MPC5777M) += Can_mcan.o
else
ifdef CFG_TMS570
obj-$(USE_CAN)-$(CFG_TMS570) += Can_dcan.o
else
ifdef CFG_JACINTO
obj-$(USE_CAN)-$(CFG_JACINTO) += Can_dcan.o
else
obj-$(USE_CAN) += Can.o
endif
endif
endif

pb-obj-$(USE_CAN) += Can_PBcfg.o
pb-pc-file-$(USE_CAN) += Can_Cfg.h 
obj-$(USE_CAN)-$(CFG_ZYNQ) += Can_zynq.o
obj-$(USE_CAN)-$(CFG_RH850) += Can_rscan.o
vpath-$(USE_CAN)-$(if $(CFG_ARMV7_AR)$(CFG_RH850),y) += $(ROOTDIR)/drivers/Can
inc-$(USE_CAN)-$(if $(CFG_ARMV7_AR)$(CFG_RH850),y) += $(ROOTDIR)/drivers/Can

vpath-$(USE_CAN)-$(if $(CFG_JACINTO)$(CFG_TMS570),y) += $(ROOTDIR)/drivers/Can

inc-$(USE_CAN) += $(ROOTDIR)/drivers/Can