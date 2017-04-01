#FrTp
obj-$(USE_FRTP) += FrTp.o
obj-$(USE_FRTP) += FrTp_PBcfg.o
obj-$(USE_FRTP) += FrTp_Lcfg.o
vpath-$(USE_FRTP) += $(ROOTDIR)/communication/FrTp
inc-$(USE_FRTP) += $(ROOTDIR)/communication/FrTp
