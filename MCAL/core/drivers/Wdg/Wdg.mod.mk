#Wdg
inc-y += $(ROOTDIR)/drivers/Wdg 
obj-$(USE_WDG) += Wdg.o
obj-$(USE_WDG) += Wdg_Lcfg.o
obj-$(USE_WDG)-$(CFG_TMS570) += Wdg_PBcfg.o
obj-$(USE_WDG)-$(CFG_MPC5748G) += Wdg_PBcfg.o
obj-$(USE_WDG)-$(CFG_MPC5746C) += Wdg_PBcfg.o
obj-$(USE_WDG)-$(CFG_ZYNQ) += Wdg_PBcfg.o
obj-$(USE_WDG)-$(CFG_RH850) += Wdg_PBcfg.o
obj-$(USE_WDG)-$(CFG_RH850) += Wdg_rh850f1h.o
vpath-$(USE_WDG)-$(CFG_RH850) += $(ROOTDIR)/drivers/Wdg