
# prefered version
CC_VERSION=4.1.2

# No smalldata
ppc_common-y	+= -msdata=none

gcc_version := $(word 3,$(shell ${CROSS_COMPILE}gcc --version))
gcc_split = $(subst ., ,$(gcc_version))

#### Select floating point and CPU #### 
# - Assume that CFG_VLE uses a the VLE version of GCC

# 32-bit 
ppc_common-$(CFG_SPE_FPU_SCALAR_SINGLE) += -mfloat-gprs=single -mhard-float
# GCC can't emit some instructions here but it should be ok.
ppc_common-$(CFG_EFPU) += -mfloat-gprs=single -mhard-float
#ppc_common-$(CFG_SPE) +=  -mspe=yes

ifeq ($(CFG_SPE),y)
ppc_common-y += -mspe
else
# mcpu=8540 will generate spe instructions by default
ppc_common-y += -mno-spe   
endif

ppc_common-y += -frounding-math -fsignaling-nans 

# default to softfloat
ifeq ($(findstring $(CFG_SPE_FPU_SCALAR_SINGLE)$(CFG_EFPU)$(CFG_E200Z0)$(CFG_E200Z3),y),)
ppc_common-y += -msoft-float
endif

ppc_common-$(CFG_E200Z0)-$(CFG_VLE) += -mcpu=e200z0
ppc_common-$(CFG_E200Z3)-$(CFG_VLE) += -mcpu=e200z3
ppc_common-$(CFG_E200Z4D)-$(CFG_VLE) += -mcpu=e200z3
ppc_common-$(CFG_E200Z4)-$(CFG_VLE) += -mcpu=e200z3

ppc_common-$(CFG_VLE) += -mno-eabi

ifeq ($(CFG_VLE),)
ppc_common-y    += -mcpu=8540
endif
ppc_common-y 	+= -mmultiple
ppc_common-y 	+= -mstrict-align
ppc_common-y 	+= -gdwarf-2
ppc_common-y   += -D_PPC

cflags-$(CFG_MPC55XX) 	+= -B$(prefix)/libexec/gcc:/opt
cflags-$(CFG_MPC55XX) += $(ppc_common-y) $(ppc_common-y-y) 

lib-y   	+= -lgcc -lc -lm
#LDFLAGS += -te500v1

asflags-$(CFG_SPE) += -mspe
asflags-$(CFG_VLE) += -mvle
asflags-y += -me500
asflags-y += -mregnames
 
ASFLAGS += $(asflags-y)


