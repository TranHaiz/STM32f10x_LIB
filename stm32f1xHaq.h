#ifndef STM32F1X_H_
#define STM32F1X_H_

//--------------------------------------------
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
//--------------------------------------------
#define ENABLE 1
#define DISABLE 0
#define HIGH 1
#define LOW 0
//--------------------------------------------
#define FLASH_BASE            ((uint32_t)0x08000000) /*!< FLASH base address in the alias region */
#define SRAM_BASE             ((uint32_t)0x20000000) /*!< SRAM base address in the alias region */
#define PERIPH_BASE           ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */

#define SRAM_BB_BASE          ((uint32_t)0x22000000) /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE        ((uint32_t)0x42000000) /*!< Peripheral base address in the bit-band region */

#define FSMC_R_BASE           ((uint32_t)0xA0000000) /*!< FSMC registers base address */

/*!< Peripheral memory map */
#define RCC_BASE 0x40021000UL
#define RCC_CFGR        (*(volatile unsigned int *)(RCC_BASE + 0x04))
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)

#define GPIOA_BASE 0x40010800UL
#define GPIOB_BASE 0x40010C00UL
#define GPIOC_BASE 0x40011000UL
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)

#define ADC1_BASE             (APB2PERIPH_BASE + 0x2400)
#define ADC2_BASE             (APB2PERIPH_BASE + 0x2800)

#define USART1_BASE           (APB2PERIPH_BASE + 0x3800)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE           (APB1PERIPH_BASE + 0x4800)
#define UART4_BASE            (APB1PERIPH_BASE + 0x4C00)
#define UART5_BASE            (APB1PERIPH_BASE + 0x5000)
//--------------------------------------------
typedef struct {
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_TypeDef;

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
		volatile uint32_t APB1ENR;
		volatile uint32_t BDCR;
} RCC_TypeDef;

typedef struct
{
  volatile uint32_t SR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMPR1;
  volatile uint32_t SMPR2;
  volatile uint32_t JOFR1;
  volatile uint32_t JOFR2;
  volatile uint32_t JOFR3;
  volatile uint32_t JOFR4;
  volatile uint32_t HTR;
  volatile uint32_t LTR;
  volatile uint32_t SQR1;
  volatile uint32_t SQR2;
  volatile uint32_t SQR3;
  volatile uint32_t JSQR;
  volatile uint32_t JDR1;
  volatile uint32_t JDR2;
  volatile uint32_t JDR3;
  volatile uint32_t JDR4;
  volatile uint32_t DR;
} ADC_TypeDef;
typedef struct
{
  volatile uint16_t SR;
  uint16_t  RESERVED0;
  volatile uint16_t DR;
  uint16_t  RESERVED1;
  volatile uint16_t BRR;
  uint16_t  RESERVED2;
  volatile uint16_t CR1;
  uint16_t  RESERVED3;
  volatile uint16_t CR2;
  uint16_t  RESERVED4;
  volatile uint16_t CR3;
  uint16_t  RESERVED5;
  volatile uint16_t GTPR;
  uint16_t  RESERVED6;
} USART_TypeDef;
//--------------------------------------------
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long*)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //ngo ra
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //ngo vao

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)   

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //ngo ra
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //ngo vao

#define RCC_GPIOA_EN (RCC->APB2ENR |= (1<<2))
#define RCC_GPIOB_EN (RCC->APB2ENR |= (1<<3))
#define RCC_GPIOC_EN (RCC->APB2ENR |= (1<<4))
#define RCC_GPIOD_EN (RCC->APB2ENR |= (1<<5))
#define RCC_GPIOE_EN (RCC->APB2ENR |= (1<<6))
#define RCC_GPIOF_EN (RCC->APB2ENR |= (1<<7))
#define RCC_GPIOG_EN (RCC->APB2ENR |= (1<<8))
//------------------------------------------------------
//mode
#define MODE_INPUT_ANALOG 0
#define MODE_INPUT_FLOAT 1
#define MODE_INPUT 2

#define MODE_OUTPUT_PUSH_PULL 0
#define MODE_OUTPUT_OPEN_DRAIN 1
#define MODE_OUTPUT_ALT_PUSH_PULL 2
#define MODE_OUTPUT_ALT_OPEN_DRAIN 3
//io_speed
#define INPUT 0
#define OUTPUT_LOW_SPEED 2
#define OUTPUT_MEDIUM_SPEED 1
#define OUTPUT_HIGH_SPEED 3
//pull
#define NO_PULL 0
#define PULL_UP 1
#define PULL_DOWN 2
//ADC channel
#define ADC_Channel_0                               ((uint8_t)0x00)
#define ADC_Channel_1                               ((uint8_t)0x01)
#define ADC_Channel_2                               ((uint8_t)0x02)
#define ADC_Channel_3                               ((uint8_t)0x03)
#define ADC_Channel_4                               ((uint8_t)0x04)
#define ADC_Channel_5                               ((uint8_t)0x05)
#define ADC_Channel_6                               ((uint8_t)0x06)
#define ADC_Channel_7                               ((uint8_t)0x07)
#define ADC_Channel_8                               ((uint8_t)0x08)
#define ADC_Channel_9                               ((uint8_t)0x09)
#define ADC_Channel_10                              ((uint8_t)0x0A)
#define ADC_Channel_11                              ((uint8_t)0x0B)
#define ADC_Channel_12                              ((uint8_t)0x0C)
#define ADC_Channel_13                              ((uint8_t)0x0D)
#define ADC_Channel_14                              ((uint8_t)0x0E)
#define ADC_Channel_15                              ((uint8_t)0x0F)
#define ADC_Channel_16                              ((uint8_t)0x10)
#define ADC_Channel_17                              ((uint8_t)0x11)
//USART channel
typedef enum {
	Pins_PA9PA10,	//USART1
	Pins_PB6PB7,	////USART1
	Pins_PA2PA3,	//USART2
	Pins_PD5PD6,	//USART2
	Pins_PB10PB11,	//USART3
	Pins_PC10PC11,	//USART3//UART4
	Pins_PD8PD9,	//USART3
	Pins_PA0PA1,	//UART4
	Pins_PC12PD2,	//UART5
	Pins_PC6PC7,	//USART6
	Pins_PG14PG9,	//USART6
	Pins_PB8PE7,	//UART7
	Pins_PF7PF6,	//UART7
	Pins_PE1PE0		//UART8
} Pins_USART;
//-----------------------------------------------------------------
#define GPIOA 							((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB 							((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC 							((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define RCC 								((RCC_TypeDef *) RCC_BASE)
#define RCC_APB1ENR 				( RCC_BASE+ 0x1C )
#define RCC_APB2ENR 				(RCC_BASE+ 0x18 )
#define ADC1                ((ADC_TypeDef *) ADC1_BASE)
#define ADC2                ((ADC_TypeDef *) ADC2_BASE)
#define USART1              ((USART_TypeDef *) USART1_BASE)
#define USART2              ((USART_TypeDef *) USART2_BASE)
#define USART3              ((USART_TypeDef *) USART3_BASE)
#define UART4               ((USART_TypeDef *) UART4_BASE)
#define UART5               ((USART_TypeDef *) UART5_BASE)
//-----------------------------------------------------------------
//GPIO
void GPIO_INIT(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t speed, uint8_t mode, uint8_t pull);
void GPIO_WRITE(GPIO_TypeDef* GPIOx,uint8_t pin,uint8_t state);
uint8_t GPIO_READ(GPIO_TypeDef* GPIOx,uint8_t pin);
void GPIO_TOGGLE(GPIO_TypeDef* GPIOx,uint8_t pin);
//ADC
void ADCx_init(ADC_TypeDef* ADCx, uint8_t channel);
uint16_t ADCx_read(ADC_TypeDef* ADCx, uint8_t channel);
uint16_t ADC_avg(ADC_TypeDef* ADCx,uint8_t channel, uint16_t sample);
//USART
void UARTx_init(USART_TypeDef *USARTx,Pins_USART Pinx,uint32_t Baud);
void USARTx_WRITE(USART_TypeDef *USARTx,unsigned char data);
#endif
