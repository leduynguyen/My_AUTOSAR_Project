#RamTst
obj-$(USE_RAMTST) += RamTst.o
obj-$(USE_RAMTST) += RamTst_Cfg.o
inc-$(USE_RAMTST) += $(ROOTDIR)/memory/RamTst
vpath-$(USE_RAMTST) += $(ROOTDIR)/memory/RamTst