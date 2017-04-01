

CC = $(GHS_BIN)/ccrh850
LD = $(GHS_BIN)/ccrh850.exe

cflags-y += --gnu_asm
# Don't allocate small data.
cflags-y += -no_allocate_ep 
cflags-y += -notda

AS = $(GHS_BIN)/ease850
ASFLAGS += -cpu=rh850g3m
