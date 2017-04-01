
# prefered version
CC_VERSION=4.8.2
SELECT_CLIB?=CLIB_DNK
ifeq ($(SELECT_CLIB),CLIB_NEWLIB)
CFG_CLIB_NEWLIB=y
else
CFG_CLIB_DNK=y
endif
#SELECT_CLIB=CLIB_DNK


cflags-y += -DSELECT_CLIB=$(SELECT_CLIB)

inc-y += $(dir $(CROSS_COMPILE))../tricore/include/machine
inc-y += $(dir $(CROSS_COMPILE))../lib/gcc/tricore/4.6.4/include
inc-y += $(dir $(CROSS_COMPILE))../bsp/tricore/TriBoard-TC29xB/h
#cc_inc_path

#libpath-y += -L$(dir $(CROSS_COMPILE))../tricore/lib/

cflags-y += -mtc161
cflags-y += -fdata-sections
cflags-y += -fshort-double
#cflags-y += -finline-is-always-inline commented out due to build problem for ADPM
lib-$(CFG_CLIB_NEWLIB) 	+= -lgcc
lib-$(CFG_CLIB_NEWLIB) 	+= -lc
lib-$(CFG_CLIB_NEWLIB) 	+= -lm

def-$(CFG_CLIB_DNK) += _ALLOW_KEYWORD_MACROS

lib-$(CFG_CLIB_DNK) += -ldnk_c

lib-y   	+= -lgcc
asflags += -mtc161 
asflags += --gdwarf-2

ASFLAGS += $(asflags-y)

libpath-y += -L$(dir $(CROSS_COMPILE))../tricore/lib/tc161/short-double
LDFLAGS   += --allow-multiple-definition --cref --oformat=elf32-tricore --mcpu=tc161 --mem-holes --extmap="a"

