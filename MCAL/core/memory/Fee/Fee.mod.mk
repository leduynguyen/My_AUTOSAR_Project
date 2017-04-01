# Fee
obj-$(USE_FEE) += Fee.o
obj-$(USE_FEE) += Fee_Cfg.o
inc-$(USE_FEE) += $(ROOTDIR)/memory/Fee
vpath-$(USE_FEE) += $(ROOTDIR)/memory/Fee