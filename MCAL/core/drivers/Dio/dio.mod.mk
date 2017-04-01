#Dio
inc-$(USE_DIO) += $(ROOTDIR)/drivers/Dio

obj-$(USE_DIO) += Dio.o
obj-$(USE_DIO) += Dio_Lcfg.o