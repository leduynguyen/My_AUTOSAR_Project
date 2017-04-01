

CC = $(GHS_BIN)/ccarm
LD = $(GHS_BIN)/ccarm.exe
AS = $(GHS_BIN)/asarm.exe

cflags-y += --gnu_asm
cflags-y += -thumb -fhard -e Reset_Handler

ASFLAGS += -cpu=$(GHS_TARGET)
ASFLAGS += -dwarf2


