#Ethernet
obj-$(USE_ETHSM) += EthSM_Cfg.o
obj-$(USE_ETHSM) += EthSM.o
vpath-$(USE_ETHSM) += $(ROOTDIR)/communication/EthSM
inc-$(USE_ETHSM) += $(ROOTDIR)/communication/EthSM
