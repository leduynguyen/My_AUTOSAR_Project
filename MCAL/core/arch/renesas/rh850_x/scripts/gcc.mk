

cflags-y += -mv850e3v5
cflags-y 	+= -gdwarf-2

cflags-y 	+= -mtda=0
cflags-y 	+= -msda=0
cflags-y 	+= -mzda=0

cflags-$(CFG_RH850F1L) += -msoft-float

ASFLAGS += -mv850e3v5

lib-y   	+= -lgcc -lc -lm
