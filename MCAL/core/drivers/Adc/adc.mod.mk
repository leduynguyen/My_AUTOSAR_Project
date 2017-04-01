#ADC
obj-$(USE_ADC)-$(CFG_TMS570) += Adc.o
obj-$(USE_ADC)-$(CFG_TMS570) += Adc_tms570.o
obj-$(USE_ADC)-$(CFG_RH850) += Adc.o
obj-$(USE_ADC)-$(CFG_RH850) += Adc_rh850.o
obj-$(USE_ADC)-$(CFG_MPC560X) += Adc_560x.o
obj-$(USE_ADC)-$(CFG_MPC5668) += Adc_560x.o
obj-$(USE_ADC)-$(CFG_MPC5744P) += Adc_560x.o
obj-$(USE_ADC)-$(CFG_MPC5777M) += Adc_560x.o
obj-$(USE_ADC)-$(CFG_MPC5748G) += Adc_560x.o
obj-$(USE_ADC)-$(CFG_MPC5747C) += Adc_560x.o
obj-$(USE_ADC)-$(CFG_MPC5746C) += Adc_560x.o
obj-$(USE_ADC)-$(CFG_MPC5645S) += Adc_560x.o
obj-$(USE_ADC)-$(CFG_MPC5643L) += Adc_560x.o
obj-$(USE_ADC)-$(CFG_SPC56XL70) += Adc_560x.o
obj-$(USE_ADC)-$(CFG_HC1X) += Adc.o
obj-$(USE_ADC)-$(CFG_STM32F1X) += Adc.o
obj-$(USE_ADC)-$(CFG_MPC5516) += Adc_eQADC.o
obj-$(USE_ADC)-$(CFG_MPC5567) += Adc_eQADC.o
obj-$(USE_ADC)-$(CFG_MPC563XM) += Adc_eQADC.o
obj-$(USE_ADC)-$(CFG_MPC5644A) += Adc_eQADC.o
obj-$(USE_ADC)-$(CFG_ZYNQ) += Adc.o
obj-$(USE_ADC)-$(CFG_JACINTO) += Adc.o
obj-$(USE_ADC)-$(CFG_JAC5) += Adc_jacinto.o
obj-$(USE_ADC)-$(CFG_JAC5E) += Adc_jacinto.o
obj-$(USE_ADC)-$(CFG_JAC6) += AdcOnSpi.o
obj-$(USE_ADC) += Adc_Cfg.o
ifneq ($(CFG_TMS570),y)
ifneq ($(CFG_RH850F1H),y)
ifneq ($(CFG_JACINTO),y)
obj-$(USE_ADC) += Adc_Internal.o
endif
endif
endif
vpath-y += $(ROOTDIR)/drivers
inc-y += $(ROOTDIR)/drivers
vpath-y += $(ROOTDIR)/drivers/Adc
inc-y += $(ROOTDIR)/drivers/Adc

# New style ADC driver
vpath-$(CFG_TMS570) += $(ROOTDIR)/drivers/Adc
inc-$(CFG_TMS570) += $(ROOTDIR)/drivers/Adc
vpath-$(CFG_RH850F1H) += $(ROOTDIR)/drivers/Adc
inc-$(CFG_RH850F1H) += $(ROOTDIR)/drivers/Adc

inc-$(USE_ADC) += $(ROOTDIR)/drivers/Adc
