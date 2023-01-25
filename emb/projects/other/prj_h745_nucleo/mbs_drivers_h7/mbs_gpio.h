#ifndef MBS_GPIO_H_
#define MBS_GPIO_H_

extern const uint32_t Get_Pull[];
extern const uint32_t Get_Type[];
extern const uint32_t Get_OutputType[];
extern const GPIO_TypeDef *Get_GPIO_Port[];
extern const uint32_t Get_GPIO_Pin[];

#define PORT_SIZE 4
#define INPUT LL_GPIO_MODE_INPUT
#define OUTPUT LL_GPIO_MODE_OUTPUT

#define GPIO_PULL(Pin_Pull) Get_Pull[Pin_Pull]
#define GPIO_TYPE(Pin_Type) Get_Type[Pin_Type]
#define GPIO_OUTPUT_TYPE(Pin_OutputType) Get_OutputType[Pin_OutputType]
#define GPIO_PORT(Number) (GPIO_TypeDef *)Get_GPIO_Port[Number]
#define GPIO_PIN(Number) Get_GPIO_Pin[Number]
#define GPIO_PORT_BY_PIN(Pin_Number) (GPIO_TypeDef *)Get_GPIO_Port[((Pin_Number) >> PORT_SIZE)]
#define GPIO_PIN_BY_PIN(Pin_Number) Get_GPIO_Pin[(Pin_Number) - (((Pin_Number) >> PORT_SIZE) << PORT_SIZE)]
#define GPIO_PORT_NUMBER(Pin_Number) ((Pin_Number) >> PORT_SIZE)
#define IS_NEED_GPIO_PORT(Pin_Number) (1 << ((Pin_Number) >> PORT_SIZE))
#define Get_Bit_State(Value, Count) (((Value) & (1 << (Count))) >> (Count))

void MBS_GPIO_INIT(short Pin_Number, uint32_t Pin_Type, uint32_t Pin_OutputType, uint32_t Pin_Pull, uint32_t Pin_Value);

#define RCC_AHB4Periph_GPIOx(NUM)	(1UL << NUM)

void *GPIO_getPort(char PortNum);
void GPIO_PeriphEnable(char PortNum);
void *GPIO_init(short Type, short OutputType, short Pull, unsigned short *Bit, short Value);
void GPIO_writeBits(GPIO_TypeDef * Port, uint32_t Mask, uint32_t Data);

#endif
