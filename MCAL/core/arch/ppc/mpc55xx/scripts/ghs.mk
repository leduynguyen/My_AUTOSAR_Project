
AS = $(GHS_BIN)/asppc
CC = $(GHS_BIN)/ccppc
LD = $(GHS_BIN)/ccppc.exe

ifeq ($(CFG_SPE),y)
cflags-y += -SPE
else
cflags-y += -noSPE
endif
def-y += CFG_SPE_INIT

cflags-y += -bigendian
cflags-y += --gnu_asm

cflags-$(CFG_VLE) += -vle
ldflags-$(CFG_VLE) += -vle

ASFLAGS += -cpu=$(GHS_TARGET)