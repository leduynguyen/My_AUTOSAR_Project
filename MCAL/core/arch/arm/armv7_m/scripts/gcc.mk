
# prefered version
CC_VERSION=4.1.2
# ARMv7, Thumb-2, little endian, soft-float. 
cflags-$(CFG_ARMV7_M) += -march=armv7-m
cflags-$(CFG_ARMV7E_M) += -march=armv7e-m

cflags-$(CFG_ARM_CM3) += -mcpu=cortex-m3
cflags-$(CFG_ARM_CM4) += -mcpu=cortex-m4

ifeq ($(CFG_HW_FLOAT),y) 
cflags-$(CFG_ARMV7E_M) += -mfloat-abi=hard -mfpu=fpv4-sp-d16
else
cflags-y += -mfloat-abi=soft
endif

cflags-$(CFG_THUMB) += -mthumb 

cflags-y 	+= -ggdb
cflags-y 	+= -gdwarf-2
cflags-y 	+= -nostdlib
ldflags-y += --allow-multiple-definition

ifeq ($(CFG_JAC6_IPC),y)
# Get Cortex-M like types..
cflags-y += -Dxdc_target_types__=ti/targets/std.h
cflags-y += -D__TMS470__ 
endif

cflags-y += -ffunction-sections

lib-y   	+= -lgcc -lc
asflags-$(CFG_ARM_CM3) += -mcpu=cortex-m3
asflags-$(CFG_ARM_CM4) += -mcpu=cortex-m4
asflags-$(CFG_THUMB) += -mthumb 

#ifeq ($(CFG_JAC6_IPC),y)
#lib-y   	+= -lm -static $(ROOTDIR)/$(ARCH_PATH-y)/drivers_jacinto/libipc-vayu.aem3
#endif

ifeq ($(CFG_HW_FLOAT),y)  
asflags-$(CFG_HW_FLOAT)	+= -mfloat-abi=hard -mfpu=fpv4-sp-d16
else
cflags-y += -mfloat-abi=soft
endif

ASFLAGS += $(asflags-y) 
 
