
# ARCH defines
ARCH=mpc55xx
ARCH_FAM=ppc
ARCH_MCU=spc560b54

# CFG (y/n) macros
CFG=PPC E200Z0 MPC55XX MPC560X MPC560XB SPC560B54 BRD_SPC560B54_SPC56XXMM
CFG+=MCU_ARC_CONFIG
CFG+=CREATE_SREC


ifneq ($(COMPILER),gcc)
CFG+=VLE
endif
# What buildable modules does this board have, 
# default or private

# Memory + Peripherals
MOD_AVAIL+=ADC DIO CAN GPT MCU PORT PWM FLS SPI ICU OCU
# Required modules
MOD_USE += MCU

# Default cross compiler
COMPILER?=diab
DEFAULT_CROSS_COMPILE = /opt/powerpc-eabispe/bin/powerpc-eabispe-
DEFAULT_CW_COMPILE= /c/devtools/Freescale/cw_mpc5xxx_2.10
DEFAULT_DIAB_COMPILE = /c/devtools/WindRiver/diab/5.9.3.0/WIN32
DEFAULT_GHS_COMPILE = /c/devtools/ghs/comp_201314p

# Defines
def-y += SRAM_SIZE=0x10000

# Software floating point, PowerPC No Small-Data ELF EABI Object Format
DIAB_TARGET?=-tPPCE200Z0VFS:simple
GHS_TARGET?=ppc560xb

