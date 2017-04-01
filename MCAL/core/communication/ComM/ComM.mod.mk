# ComM
obj-$(USE_COMM) += ComM.o
obj-$(USE_COMM) += ComM_Cfg.o
inc-$(USE_COMM) += $(ROOTDIR)/communication/ComM
vpath-$(USE_COMM) += $(ROOTDIR)/communication/ComM
vpath-y += $(ROOTDIR)/communication/ComM
inc-$(USE_COMM) += $(ROOTDIR)/communication/ComM