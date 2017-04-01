#CAL
obj-$(USE_CAL) += Cal_Mac.o
obj-$(USE_CAL) += Cal_Cfg.o
inc-$(USE_CAL) += $(ROOTDIR)/system/Cal
vpath-$(USE_CAL) += $(ROOTDIR)/system/Cal