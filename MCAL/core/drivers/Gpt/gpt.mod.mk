# Gpt
obj-$(USE_GPT) += Gpt.o
obj-$(USE_GPT) += Gpt_Cfg.o
obj-$(USE_GPT)-$(CFG_RH850) += Gpt_tauj.o
obj-$(USE_GPT)-$(CFG_TMS570) += Gpt_tms570.o
obj-$(USE_GPT)-$(CFG_JACINTO) += Gpt_jacinto.o
inc-$(USE_GPT)-$(if $(CFG_JACINTO)$(CFG_TMS570)$(CFG_RH850),y) +=  $(ROOTDIR)/drivers/Gpt
vpath-$(USE_GPT)-$(if $(CFG_JACINTO)$(CFG_TMS570)$(CFG_RH850),y) +=  $(ROOTDIR)/drivers/Gpt
