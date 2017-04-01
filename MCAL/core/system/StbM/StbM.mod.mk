#StbM
inc-$(USE_STBM) += $(ROOTDIR)/system/StbM
inc-$(USE_STBM) += $(ROOTDIR)/include/rte
vpath-$(USE_STBM) += $(ROOTDIR)/system/StbM
obj-$(USE_STBM) += StbM.o
obj-$(USE_STBM) += StbM_Cfg.o
