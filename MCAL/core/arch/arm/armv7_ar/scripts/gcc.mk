
# prefered version
CC_VERSION=4.8.2

# vfpv3-d16

# ARMv7, Thumb-2, little endian, soft-float.
# -mthumb 
 
cflags-$(CFG_HW_FLOAT)	+= -mfloat-abi=hard -mfpu=vfpv3
cflags-$(CFG_SOFT_FLOAT)+= -mfloat-abi=softfp -mfpu=vfpv3
cflags-$(CFG_THUMB) += -mthumb 


cflags-y 	+= -march=armv7-a 
#cflags-y 	+= -ggdb
cflags-y 	+= -gdwarf-2
#cflags-y 	+= -mtpcs-frame

cflags-y += -ffunction-sections

lib-y   	+= -lgcc -lc -lm
asflags-$(CFG_THUMB) +=  -mthumb
asflags-$(CFG_HW_FLOAT)	+= -mfloat-abi=hard -mfpu=vfpv3

ASFLAGS 	+= $(asflags-y) -march=armv7-a


 

LDFLAGS     += 