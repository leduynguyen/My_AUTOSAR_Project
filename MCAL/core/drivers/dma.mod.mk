#DMA
obj-$(USE_DMA) += Dma.o
obj-$(USE_DMA) += Dma_Cfg.o
inc-$(USE_DMA) += $(ROOTDIR)/$(ARCH_PATH-y)/drivers
