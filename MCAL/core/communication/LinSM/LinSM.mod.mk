#LinSM
obj-$(USE_LINSM) += LinSM_Lcfg.o
obj-$(USE_LINSM) += LinSM_Cfg.o
obj-$(USE_LINSM) += LinSM.o

vpath-$(USE_LINSM) += $(ROOTDIR)/communication/LinSM