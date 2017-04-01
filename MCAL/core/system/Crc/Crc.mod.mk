#Crc
obj-$(USE_CRC) += Crc.o
obj-$(USE_CRC) += Crc_8.o
obj-$(USE_CRC) += Crc_16.o
obj-$(USE_CRC) += Crc_32.o
obj-$(USE_CRC) += Crc_32P4.o
inc-$(USE_CRC) += $(ROOTDIR)/system/Crc
vpath-$(USE_CRC) += $(ROOTDIR)/system/Crc
