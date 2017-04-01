
# prefered version
#CC_VERSION=4.4.5
# ARMv7, Thumb-2, little endian, soft-float. 

#cflags-y 	+= -mthumb -mcpu=cortex-r4 -mbig-endian
cflags-$(CFG_BIG_ENDIAN)	+= -mthumb -march=armv7-r -mbig-endian -mfloat-abi=hard -mfpu=vfpv3-d16
cflags-$(CFG_LITTLE_ENDIAN)	+= -mthumb -march=armv7-a -mfloat-abi=hard -mfpu=vfpv3-d16
cflags-y 	+= -gdwarf-2

ldflags-$(CFG_FS_RAM) += --allow-multiple-definition

lib-y += -lgcc -lc -lm 
ifeq ($(CFG_TMS570),y)
lib-$(CFG_ARM_CR4)   	+= $(ROOTDIR)/$(ARCH_PATH-y)/drivers/F021/F021_API_CortexR4_BE_V3D16.lib
lib-$(CFG_ARM_CR5)   	+= $(ROOTDIR)/$(ARCH_PATH-y)/drivers/F021_L2FMC/F021_API_CortexR4_BE_L2FMC_V3D16.lib
endif

#ASFLAGS 	+= -mthumb -march=armv7-r -mbig-endian -mfloat-abi=hard -mfpu=vfpv3-d16
asflags-y += -mthumb
asflags-$(CFG_BIG_ENDIAN) += -march=armv7-r -mbig-endian -mfloat-abi=hard -mfpu=vfpv3-d16
asflags-$(CFG_LITTLE_ENDIAN) += -march=armv7-a -mfloat-abi=hard -mfpu=vfpv3-d16

LDFLAGS     += 

libpath-$(CFG_BIG_ENDIAN) +=-L/opt/arm-none-eabi/lib/gcc/arm-none-eabi/4.8.2/thumb/be/armv7-r/fpu_hard/vfpv3-d16
libpath-$(CFG_BIG_ENDIAN) +=-L/opt/arm-none-eabi/arm-none-eabi/lib/thumb/be/armv7-r/fpu_hard/vfpv3-d16
