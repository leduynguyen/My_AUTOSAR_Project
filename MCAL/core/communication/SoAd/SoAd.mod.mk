# SoAd
obj-$(USE_SOAD) += SoAd_Cfg.o
obj-$(USE_SOAD) += SoAd.o
inc-$(USE_SOAD) += $(ROOTDIR)/communication/SoAd
inc-$(USE_SOAD) += $(ROOTDIR)/communication/SoAd
vpath-$(USE_SOAD) += $(ROOTDIR)/communication/SoAd