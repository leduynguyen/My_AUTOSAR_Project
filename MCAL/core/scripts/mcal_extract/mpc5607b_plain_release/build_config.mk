
# ARCH defines
ARCH=mpc55xx
ARCH_FAM=ppc
ARCH_MCU=mpc5606b

# CFG (y/n) macros
CFG=PPC E200Z0 MPC55XX MPC560X MPC560XB MPC5606B BRD_MPC5606B_XPC560B
CFG+=MCU_ARC_CONFIG
CFG+=CREATE_SREC


ifneq ($(COMPILER),gcc)
CFG+=VLE
endif
# What buildable modules does this board have, 
# default or private

# Memory + Peripherals
MOD_AVAIL+=ADC DIO CAN GPT MCU PORT PWM FLS SPI
# Required modules
MOD_USE += MCU

# Default cross compiler
COMPILER?=ghs
DEFAULT_CROSS_COMPILE = /opt/powerpc-eabispe/bin/powerpc-eabispe-
DEFAULT_CW_COMPILE= /c/devtools/Freescale/cw_mpc5xxx_2.10
DEFAULT_DIAB_COMPILE = /c/devtools/WindRiver/diab/5.9.3.0/WIN32
DEFAULT_GHS_COMPILE = /c/devtools/ghs/comp_201314p

# Defines
def-y += SRAM_SIZE=0x18000

# Software floating point, PowerPC No Small-Data ELF EABI Object Format
DIAB_TARGET?=-tPPCE200Z0VFS:simple
GHS_TARGET?=ppc560xb

