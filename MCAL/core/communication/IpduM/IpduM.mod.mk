# IpduM
obj-$(USE_IPDUM) += IpduM.o
obj-$(USE_IPDUM) += IpduM_PbCfg.o
inc-$(USE_IPDUM) += $(ROOTDIR)/communication/IpduM
vpath-$(USE_IPDUM) += $(ROOTDIR)/communication/IpduM
