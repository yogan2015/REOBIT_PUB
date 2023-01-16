#include "main.h"
#ifdef STM32H7xx_LL_GPIO_H
#include "mbs_gpio.h"

const uint32_t Get_Pull[] = {
		LL_GPIO_PULL_NO,
		LL_GPIO_PULL_UP,
		LL_GPIO_PULL_DOWN,
		LL_GPIO_PULL_NO
};

const uint32_t Get_Type[] = {
		LL_GPIO_MODE_INPUT,
		LL_GPIO_MODE_OUTPUT
};

const uint32_t Get_OutputType[] = {
		LL_GPIO_OUTPUT_PUSHPULL,
		LL_GPIO_OUTPUT_OPENDRAIN
};

const GPIO_TypeDef *Get_GPIO_Port[] = {
		GPIOA,
		GPIOB,
		GPIOC,
		GPIOD,
		GPIOE,
		GPIOF,
		GPIOG,
		GPIOH,
		GPIOI
};

const uint32_t Get_GPIO_Pin[] = {
		LL_GPIO_PIN_0,
		LL_GPIO_PIN_1,
		LL_GPIO_PIN_2,
		LL_GPIO_PIN_3,
		LL_GPIO_PIN_4,
		LL_GPIO_PIN_5,
		LL_GPIO_PIN_6,
		LL_GPIO_PIN_7,
		LL_GPIO_PIN_8,
		LL_GPIO_PIN_9,
		LL_GPIO_PIN_10,
		LL_GPIO_PIN_11,
		LL_GPIO_PIN_12,
		LL_GPIO_PIN_13,
		LL_GPIO_PIN_14,
		LL_GPIO_PIN_15
};

void MBS_GPIO_INIT(short Pin_Number, uint32_t Pin_Type, uint32_t Pin_OutputType, uint32_t Pin_Pull, uint32_t Pin_Value)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	if(Pin_Type == INPUT)
	{
		GPIO_InitStruct.Pin = GPIO_PIN_BY_PIN(Pin_Number);
		GPIO_InitStruct.Mode = GPIO_TYPE(Pin_Type);
		GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
		LL_GPIO_Init(GPIO_PORT_BY_PIN(Pin_Number), &GPIO_InitStruct);
	}
	else if(Pin_Type == OUTPUT)
	{
		if(Pin_Value)
		{
			LL_GPIO_SetOutputPin(GPIO_PORT_BY_PIN(Pin_Number), GPIO_PIN_BY_PIN(Pin_Number));
		}
		else
		{
			LL_GPIO_ResetOutputPin(GPIO_PORT_BY_PIN(Pin_Number), GPIO_PIN_BY_PIN(Pin_Number));
		}

		GPIO_InitStruct.Pin = GPIO_PIN_BY_PIN(Pin_Number);
		GPIO_InitStruct.Mode = GPIO_TYPE(Pin_Type);
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.OutputType = GPIO_OUTPUT_TYPE(Pin_OutputType);
		GPIO_InitStruct.Pull = GPIO_PULL(Pin_Pull);
		LL_GPIO_Init(GPIO_PORT_BY_PIN(Pin_Number), &GPIO_InitStruct);
	}
}

extern void DelayUsecs(unsigned long usecs);

void *GPIO_getPort(char PortNum)
{
	switch(PortNum)
	{
		case 0:  return (void *)GPIOA;
		case 1:  return (void *)GPIOB;
		case 2:  return (void *)GPIOC;
		case 3:  return (void *)GPIOD;
		case 4:  return (void *)GPIOE;
		case 5:  return (void *)GPIOF;
		case 6:  return (void *)GPIOG;
		case 7:  return (void *)GPIOH;
		case 8:  return (void *)GPIOI;
		case 9:  return (void *)GPIOJ;
		case 10:  return (void *)GPIOK;
	}
	return (void *)0;
}

void GPIO_PeriphEnable(char PortNum)
{
	LL_AHB4_GRP1_EnableClock(RCC_AHB4Periph_GPIOx(PortNum));
}

void *GPIO_init(short Type, short OutputType, short Pull, unsigned short *Bit, short Value)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_TypeDef *GPIOx;
	uint16_t PortNum;
	uint16_t BitMask;

	PortNum = (uint16_t)*Bit >> 4;
	BitMask = 1U << (*Bit & 0xF);

	GPIOx = (GPIO_TypeDef *)GPIO_getPort(PortNum);
	if (GPIOx)
	{
		GPIO_PeriphEnable(PortNum);

		GPIO_InitStruct.Pin = BitMask;
		GPIO_InitStruct.Mode = Type ? LL_GPIO_MODE_OUTPUT : LL_GPIO_MODE_INPUT;
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.OutputType = OutputType ? LL_GPIO_OUTPUT_OPENDRAIN : LL_GPIO_OUTPUT_PUSHPULL;
		if(Type)
		{
			GPIO_InitStruct.Pull = Get_Pull[Pull];
			if (Value) LL_GPIO_SetOutputPin(GPIOx, BitMask) ;
			else LL_GPIO_ResetOutputPin(GPIOx, BitMask);
		}
		else
		{
			GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
		}
		LL_GPIO_Init(GPIOx, &GPIO_InitStruct);

		*Bit = (short)BitMask;
	}

	return ((void *)GPIOx);
}

void GPIO_writeBits(GPIO_TypeDef * Port, uint32_t Mask, uint32_t Data)
{
	LL_GPIO_WriteOutputPort(
								Port,
								(
									(LL_GPIO_ReadOutputPort(Port) & (~Mask))
								|
									(Data & Mask)
								)
							);
}

#endif
