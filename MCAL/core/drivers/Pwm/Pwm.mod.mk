#Pwm
obj-$(USE_PWM) += Pwm_Lcfg.o
obj-$(USE_PWM) += Pwm_PBcfg.o
obj-$(USE_PWM)-$(CFG_MPC5604P) += PwmFlex.o
obj-$(USE_PWM)-$(CFG_MPC5744P) += PwmFlex.o
obj-$(USE_PWM)-$(CFG_MPC5643L) += PwmFlex.o
obj-$(USE_PWM)-$(CFG_SPC56XL70) += PwmFlex.o
obj-$(USE_PWM)-$(CFG_MPC5746C) += Pwm.o
obj-$(USE_PWM)-$(CFG_MPC5748G) += Pwm.o
obj-$(USE_PWM)-$(CFG_MPC560X) += Pwm.o
obj-$(USE_PWM)-$(CFG_MPC5606S) += Pwm.o
obj-$(USE_PWM)-$(CFG_MPC5668) += Pwm.o
obj-$(USE_PWM)-$(CFG_HC1X) += Pwm.o
obj-$(USE_PWM)-$(CFG_STM32F1X) += Pwm.o
obj-$(USE_PWM)-$(CFG_MPC5516) += Pwm.o
obj-$(USE_PWM)-$(CFG_MPC5567) += Pwm.o
obj-$(USE_PWM)-$(CFG_MPC563XM) += Pwm.o
obj-$(USE_PWM)-$(CFG_MPC5644A) += Pwm.o
obj-$(USE_PWM)-$(CFG_MPC5645S) += Pwm.o
obj-$(USE_PWM)-$(CFG_TMS570) += Pwm.o
obj-$(USE_PWM)-$(CFG_TMS570) += epwm.o
obj-$(USE_PWM)-$(CFG_ZYNQ) += Pwm.o
obj-$(USE_PWM)-$(CFG_JACINTO) += Pwm.o
obj-$(USE_PWM)-$(CFG_JACINTO) += Pwm_jacinto.o
obj-$(USE_PWM)-$(CFG_JAC6) += epwm.o
obj-$(USE_PWM)-$(CFG_JAC6) += epwm_asr.o
obj-$(USE_PWM)-$(CFG_RH850F1L) += Pwm.o
obj-$(USE_PWM)-$(CFG_RH850F1L) += Pwm_taud.o

inc-$(USE_PWM)-$(if $(CFG_TMS570)$(CFG_JAC6),y) += $(ROOTDIR)/drivers/Pwm/epwm
vpath-$(USE_PWM)-$(if $(CFG_TMS570)$(CFG_JAC6),y) += $(ROOTDIR)/drivers/Pwm/epwm

vpath-$(USE_PWM)-$(if $(CFG_JACINTO)$(CFG_RH850),y) += $(ROOTDIR)/drivers/Pwm
inc-$(USE_PWM) += $(ROOTDIR)/drivers/Pwm
