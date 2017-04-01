
/*
 * Generator version: 5.0.1
 * AUTOSAR version:   4.1.2
 */

#include "Port.h"
#include "stm32f10x_gpio.h"



const uint32 remaps[] = {

	GPIO_Remap2_CAN1
};


const GpioPinCnfMode_Type GPIOConf[] =
{
  /*GPIOA*/
  {
	.GpioPinCnfMode_0 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_1 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_2 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_3 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_4 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_5 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_6 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_7 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_8 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_9 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_10 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_11 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_12 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_13 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_14 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_15 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
  },
  /*GPIOB*/
  {
	.GpioPinCnfMode_0 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_1 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_2 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_3 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_4 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_5 = GPIO_INPUT_MODE | GPIO_INPUT_PULLUP_CNF,
	.GpioPinCnfMode_6 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_7 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_8 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_9 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_10 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_11 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_12 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_13 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_14 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_15 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
  },
  /*GPIOC*/
  {
	.GpioPinCnfMode_0 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_1 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_2 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_3 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_4 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_5 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_6 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_7 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_8 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_9 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_10 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_11 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_12 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_13 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_14 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_15 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
  },
  /*GPIOD*/
  {
	.GpioPinCnfMode_0 = GPIO_INPUT_MODE | GPIO_INPUT_PULLUP_CNF,
	.GpioPinCnfMode_1 = GPIO_OUTPUT_10MHz_MODE | GPIO_ALT_PUSHPULL_CNF,
	.GpioPinCnfMode_2 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_3 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_4 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_5 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_6 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_7 = GPIO_OUTPUT_10MHz_MODE | GPIO_OUTPUT_PUSHPULL_CNF,
	.GpioPinCnfMode_8 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_9 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_10 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_11 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_12 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_13 = GPIO_OUTPUT_10MHz_MODE | GPIO_OUTPUT_PUSHPULL_CNF,
	.GpioPinCnfMode_14 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_15 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
  },
  /*GPIOE*/
  {
	.GpioPinCnfMode_0 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_1 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_2 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_3 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_4 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_5 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_6 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_7 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_8 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_9 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_10 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_11 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_12 = GPIO_INPUT_MODE | GPIO_INPUT_PULLUP_CNF,
	.GpioPinCnfMode_13 = GPIO_INPUT_MODE | GPIO_INPUT_PULLUP_CNF,
	.GpioPinCnfMode_14 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_15 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
  },
  /*GPIOF*/
  {
	.GpioPinCnfMode_0 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_1 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_2 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_3 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_4 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_5 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_6 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_7 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_8 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_9 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_10 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_11 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_12 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_13 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_14 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_15 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
  },
  /*GPIOG*/
  {
	.GpioPinCnfMode_0 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_1 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_2 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_3 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_4 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_5 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_6 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_7 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_8 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_9 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_10 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_11 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_12 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_13 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_14 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
	.GpioPinCnfMode_15 = GPIO_INPUT_MODE | GPIO_FLOATING_INPUT_CNF, /* Not configured */
  },
};

const GpioPinOutLevel_Type GPIOOutConf[] =
{
  /*GPIOA*/
  {
	.GpioPinOutLevel_0 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_1 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_2 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_3 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_4 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_5 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_6 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_7 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_8 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_9 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_10 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_11 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_12 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_13 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_14 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_15 = GPIO_OUTPUT_LOW,
  },
  /*GPIOB*/
  {
	.GpioPinOutLevel_0 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_1 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_2 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_3 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_4 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_5 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_6 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_7 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_8 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_9 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_10 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_11 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_12 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_13 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_14 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_15 = GPIO_OUTPUT_LOW,
  },
  /*GPIOC*/
  {
	.GpioPinOutLevel_0 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_1 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_2 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_3 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_4 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_5 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_6 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_7 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_8 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_9 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_10 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_11 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_12 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_13 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_14 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_15 = GPIO_OUTPUT_LOW,
  },
  /*GPIOD*/
  {
	.GpioPinOutLevel_0 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_1 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_2 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_3 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_4 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_5 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_6 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_7 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_8 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_9 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_10 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_11 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_12 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_13 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_14 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_15 = GPIO_OUTPUT_LOW,
  },
  /*GPIOE*/
  {
	.GpioPinOutLevel_0 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_1 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_2 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_3 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_4 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_5 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_6 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_7 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_8 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_9 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_10 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_11 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_12 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_13 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_14 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_15 = GPIO_OUTPUT_LOW,
  },
  /*GPIOF*/
  {
	.GpioPinOutLevel_0 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_1 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_2 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_3 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_4 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_5 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_6 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_7 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_8 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_9 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_10 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_11 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_12 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_13 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_14 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_15 = GPIO_OUTPUT_LOW,
  },
  /*GPIOG*/
  {
	.GpioPinOutLevel_0 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_1 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_2 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_3 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_4 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_5 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_6 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_7 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_8 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_9 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_10 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_11 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_12 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_13 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_14 = GPIO_OUTPUT_LOW,
	.GpioPinOutLevel_15 = GPIO_OUTPUT_LOW,
  },
};


const Port_ConfigType PortConfigData =
{
	.padCnt = 7,
	.padConfig = GPIOConf,
	.outConfig = GPIOOutConf,

	.remapCount = sizeof(remaps) / sizeof(uint32),
	.remaps = &remaps[0]
};



