# Mcu

obj-$(USE_MCU) += Mcu.o
obj-$(USE_MCU) += Mcu_LCfg.o
obj-$(USE_MCU) += Mcu_PBcfg.o
obj-$(USE_MCU)-$(CFG_MPC5516) += Mcu_mpc5xxx.o
obj-$(USE_MCU)-$(CFG_MPC5567) += Mcu_mpc5xxx.o
obj-$(USE_MCU)-$(CFG_MPC5668) += Mcu_mpc5xxx.o
obj-$(USE_MCU)-$(CFG_MPC563XM) += Mcu_mpc5xxx.o
obj-$(USE_MCU)-$(CFG_SPC56XL70) += Mcu_mpc5xxx.o
obj-$(USE_MCU)-$(CFG_MPC5643L) += Mcu_mpc5xxx.o
obj-$(USE_MCU)-$(CFG_MPC5644A) += Mcu_mpc5xxx.o
obj-$(USE_MCU)-$(CFG_MPC5645S) += Mcu_mpc5xxx.o
obj-$(USE_MCU)-$(CFG_MPC560X) += Mcu_mpc5xxx.o
obj-$(USE_MCU)-$(CFG_PPC) += Mcu_Arc_Common.o
obj-$(USE_MCU)-$(CFG_ARM) += Mcu_Arc_Common.o
obj-$(USE_MCU)-$(CFG_MPC57XX) += Mcu_Hw_mpc57xx.o
obj-$(USE_MCU)-$(CFG_RH850F1H) += Mcu_rh850f1h.o
obj-$(USE_MCU)-$(CFG_RH850F1L) += Mcu_rh850f1l.o
obj-$(USE_MCU)-$(CFG_RH850) += rh850_handlers.o
obj-$(USE_MCU)-$(CFG_TC29X) += Mcu_tc2xx.o
obj-$(USE_MCU)-$(CFG_TMS570) += Mcu_tms570.o
obj-$(USE_MCU)-$(CFG_TMS570) += Mcu_tms570_core.o
obj-$(USE_MCU)-$(CFG_TMS570) += Mcu_armv7ar_handlers.o
obj-$(USE_MCU)-$(CFG_FCCU) += Mcu_fccu.o



ifeq ($(filter Mcu_Arc_Jacinto.o,$(obj-y)),)
obj-$(USE_MCU)-$(CFG_JACINTO) += Mcu_Arc_Jacinto.o
obj-$(USE_MCU)-$(CFG_JAC6) += Mcu_Arc_Jacinto6.o
obj-$(USE_MCU)-$(CFG_JAC5E) += Mcu_Arc_Jacinto5.o
obj-$(USE_MCU)-$(CFG_JAC5) += Mcu_Arc_Jacinto5.o
endif
# These targets use generic Mcu.c
inc-$(USE_MCU) += $(ROOTDIR)/drivers/Mcu 
vpath-$(USE_MCU)-$(if $(CFG_TMS570)$(CFG_RH850)$(CFG_TC29X)$(CFG_MPC55XX),y) += $(ROOTDIR)/drivers/Mcu

ifeq ($(CFG_MCU_ARC_CONFIG),y)
ifeq ($(filter Mcu_Arc_mpc55xx.o Mcu_Arc_mpc56xx.o Mcu_Arc_mpc5744p.o Mcu_Arc_mpc5777m.o Mcu_Arc_mpc5748g.o,$(obj-y) $(obj-y-y)),)
obj-$(USE_MCU)-$(if $(CFG_MPC5516)$(CFG_MPC5668)$(CFG_MPC5567),y) += Mcu_Arc_mpc55xx.o
obj-$(USE_MCU)-$(if $(CFG_MPC563XM)$(CFG_SPC56XL70)$(CFG_MPC5643L)$(CFG_MPC5644A)$(CFG_MPC5645S)$(CFG_MPC560X),y) += Mcu_Arc_mpc56xx.o
obj-$(USE_MCU)-$(if $(CFG_MPC5744P),y) += Mcu_Arc_mpc5744p.o
obj-$(USE_MCU)-$(if $(CFG_MPC5777M),y) += Mcu_Arc_mpc5777m.o
obj-$(USE_MCU)-$(if $(CFG_MPC5748G),y) += Mcu_Arc_mpc5748g.o
obj-$(USE_MCU)-$(if $(CFG_MPC5746C),y) += Mcu_Arc_mpc5748g.o
obj-$(USE_MCU)-$(if $(CFG_MPC5747C),y) += Mcu_Arc_mpc5748g.o
endif
endif

vpath-y += $(ROOTDIR)/$(ARCH_PATH-y)/integration
ifeq ($(filter Mcu_Arc_Zynq.o,$(obj-y)),)
obj-$(USE_MCU)-$(CFG_ZYNQ) += Mcu_Arc_Zynq.o
endif




