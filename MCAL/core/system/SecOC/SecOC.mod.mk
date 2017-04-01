#SecOC
obj-$(USE_SECOC) += SecOC.o
obj-$(USE_SECOC) += SecOC_Cfg.o
inc-$(USE_SECOC) += $(ROOTDIR)/system/SecOC
vpath-$(USE_SECOC) += $(ROOTDIR)/system/SecOC