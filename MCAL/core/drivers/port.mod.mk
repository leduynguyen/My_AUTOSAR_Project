#port
obj-$(USE_PORT) += Port.o
obj-$(USE_PORT) += Port_Lcfg.o
obj-$(USE_PORT) += Port_PBcfg.o
obj-$(USE_PORT)-$(CFG_RH850) += Port_regfinder.o
obj-$(CFG_ARM_CM3_STM32)-$(USE_PORT) += stm32f10x_gpio.o