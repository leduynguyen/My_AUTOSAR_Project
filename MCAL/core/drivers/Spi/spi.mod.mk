#SPI
obj-$(USE_SPI) += Spi.o
obj-$(USE_SPI)-$(CFG_ZYNQ) += Spi_zynq.o
obj-$(USE_SPI) += Spi_Lcfg.o
obj-$(USE_SPI)-$(CFG_TMS570) += Spi_Hw.o
obj-$(USE_SPI)-$(CFG_TMS570) += Spi_Dlc.o
obj-$(USE_SPI)-$(CFG_TMS570LS12X) += Spi_DlcDma.o
obj-$(USE_SPI)-$(CFG_TMS570LS1114) += Spi_DlcDma.o
obj-$(USE_SPI)-$(CFG_TMS570) += Spi_Irq.o
obj-$(USE_SPI)-$(CFG_MPC55XX) += Spi_dspi.o
obj-$(USE_SPI)-$(CFG_JACINTO) += Spi_jacinto.o
obj-$(USE_SPI)-$(CFG_RH850) += Spi_csih.o
vpath-$(USE_SPI)-$(if $(CFG_MPC55XX)$(CFG_ZYNQ)$(CFG_JACINTO)$(CFG_RH850),y) += $(ROOTDIR)/drivers/Spi
inc-$(USE_SPI)-$(if $(CFG_MPC55XX)$(CFG_ZYNQ)$(CFG_JACINTO)$(CFG_RH850),y) += $(ROOTDIR)/drivers/Spi
