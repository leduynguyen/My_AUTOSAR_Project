# NvM
obj-$(USE_NVM) += NvM.o
obj-$(USE_NVM) += NvM_Cfg.o
inc-$(USE_NVM) += $(ROOTDIR)/memory/NvM
vpath-$(USE_NVM) += $(ROOTDIR)/memory/NvM