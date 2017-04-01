
# ARCH defines
ARCH=armv7_ar
ARCH_FAM=arm
ARCH_MCU=armv7_ar

#
# CFG (y/n) macros
# 

CFG=ARM ARMV7_AR ARM_GIC ZYNQ
# Add our board  
CFG+=BRD_ZYNQ_ZC702 OS_SYSTICK2

CFG+=TIMER_GLOBAL
CFG+=HW_FLOAT
CFG+=THUMB
CFG+=TIMER


# What buildable modules does this board have, 
# default or private

# MCAL
MOD_AVAIL+=ADC DIO MCU PORT PWM GPT ICU WDG SPI
# Additional
MOD_AVAIL+=RAMLOG
# Required modules
MOD_USE += MCU
#
# Extra defines 
#

# Default cross compiler
DEFAULT_CROSS_COMPILE = /opt/arm-none-eabi/bin/arm-none-eabi-

