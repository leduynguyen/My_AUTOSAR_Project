# IO Hardware Abstraction
vpath-$(USE_IOHWAB) += $(ROOTDIR)/system/IoHwAb
obj-$(USE_IOHWAB) += IoHwAb_Digital.o
obj-$(USE_IOHWAB) += IoHwAb_Analog.o
obj-$(USE_IOHWAB) += IoHwAb_Pwm.o