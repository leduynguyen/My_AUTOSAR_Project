obj-y += CDD_EthTrcv.o
obj-$(USE_CDDETHTRCV) += CddEthTrcv_Cfg.o
inc-y +=   $(ROOTDIR)/Cdd/EthTrcv/src
vpath-y += $(ROOTDIR)/Cdd/EthTrcv/src
