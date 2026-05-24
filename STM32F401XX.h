#ifndef STM32F401XX_H_
#define STM32F401XX_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

#define __VO volatile
/* ==========================
   PROCESSOR SPECIFIC DETAILS FOR THE ARM CORTEX M4 REGISTERS for ISER registers
   ========================== */
#define NVIC_ISER0 (uint32_t *)0xE000E100
#define NVIC_ISER1 (uint32_t *)0xE000E104
#define NVIC_ISER2 (uint32_t *)0xE000E10C
/* ==========================
   PROCESSOR SPECIFIC DETAILS FOR THE ARM CORTEX M4 REGISTERS for ISER registers
   ========================== */
#define NVIC_ICER0 (uint32_t *)0xE000E180
#define NVIC_ICER1 (uint32_t *)0xE000E184
#define NVIC_ICER2 (uint32_t *)0xE000E18C
/* ==========================
   PROCESSOR SPECIFIC DETAILS FOR THE ARM CORTEX M4 REGISTERS for IPR registers
   ========================== */
#define NVIC_IPR   (uint32_t *)0xE000E400
#define NO_PR_BITS_IMPLEMENTED  4
/* ==========================
   MEMORY BASE ADDRESSES
   ========================== */

#define FLASH_BASE_ADDRESS      0x08000000U
#define SRAM1_BASE_ADDRESS      0x20000000U
#define SRAM2_BASE_ADDRESS      0x2001C000U
#define ROM_BASE_ADDRESS        0x1FFF0000U

#define PERIPH_BASE_ADDRESS     0x40000000U
#define AHB1_BASE_ADDRESS       0x40020000U
#define AHB2_BASE_ADDRESS       0x50000000U
#define APB1_BASE_ADDRESS       PERIPH_BASE_ADDRESS
#define APB2_BASE_ADDRESS       0x40010000U


/* ==========================
   AHB1 PERIPHERALS
   ========================== */

#define GPIOA_BASE_ADDRESS      (AHB1_BASE_ADDRESS + 0x0000)
#define GPIOB_BASE_ADDRESS      (AHB1_BASE_ADDRESS + 0x0400)
#define GPIOC_BASE_ADDRESS      (AHB1_BASE_ADDRESS + 0x0800)
#define GPIOD_BASE_ADDRESS      (AHB1_BASE_ADDRESS + 0x0C00)
#define GPIOE_BASE_ADDRESS      (AHB1_BASE_ADDRESS + 0x1000)
#define GPIOH_BASE_ADDRESS      (AHB1_BASE_ADDRESS + 0x1C00)

#define RCC_BASE_ADDRESS        (AHB1_BASE_ADDRESS + 0x3800)


/* ==========================
   APB1 PERIPHERALS
   ========================== */

#define I2C1_BASE_ADDRESS       (APB1_BASE_ADDRESS + 0x5400)
#define I2C2_BASE_ADDRESS       (APB1_BASE_ADDRESS + 0x5800)
#define I2C3_BASE_ADDRESS       (APB1_BASE_ADDRESS + 0x5C00)

#define SPI2_BASE_ADDRESS       (APB1_BASE_ADDRESS + 0x3800)
#define SPI3_BASE_ADDRESS       (APB1_BASE_ADDRESS + 0x3C00)

#define USART2_BASE_ADDRESS     (APB1_BASE_ADDRESS + 0x4400)


/* ==========================
   APB2 PERIPHERALS
   ========================== */

#define SPI1_BASE_ADDRESS       (APB2_BASE_ADDRESS + 0x3000)
#define SPI4_BASE_ADDRESS       (APB2_BASE_ADDRESS + 0x3400)

#define USART1_BASE_ADDRESS     (APB2_BASE_ADDRESS + 0x1000)
#define USART6_BASE_ADDRESS     (APB2_BASE_ADDRESS + 0x1400)

#define EXTI_BASE_ADDRESS       (APB2_BASE_ADDRESS + 0x3C00)
#define SYSCFG_BASE_ADDRESS     (APB2_BASE_ADDRESS + 0x3800)
#define GPIO_BASE_ADDR_CODE(x)    ((x == GPIOA) ? 0 : \
                                   ((x == GPIOB) ? 1 : \
                                   ((x == GPIOC) ? 2 : \
                                   ((x == GPIOD) ? 3 : \
                                   ((x == GPIOE) ? 4 : \
                                   ((x == GPIOH) ? 5 : 0))))))  /* Default to 0 */
/* ==========================
   EXTI Priorities
   ========================== */
#define IRQ_EXTI_0       6
#define IRQ_EXTI_1       7
#define IRQ_EXTI_2       8
#define IRQ_EXTI_3       9
#define IRQ_EXTI_4       10
#define IRQ_EXTI_9_5     23
#define IRQ_EXTI_15_10   40
#define IRQ_EXTI_16      1
#define IRQ_EXTI_17      41
#define IRQ_EXTI_18      42
#define IRQ_EXTI_21      20
#define IRQ_EXTI_22      21
/* ==========================
   EXTI Priorities
   ========================== */

#define NVIC_IRQ_PRIO0   0
#define NVIC_IRQ_PRIO1   1
#define NVIC_IRQ_PRIO2   2
#define NVIC_IRQ_PRIO3   3
#define NVIC_IRQ_PRIO4   4
#define NVIC_IRQ_PRIO5   5
#define NVIC_IRQ_PRIO6   6
#define NVIC_IRQ_PRIO7   7
#define NVIC_IRQ_PRIO8   8
#define NVIC_IRQ_PRIO9   9
#define NVIC_IRQ_PRIO10  10
#define NVIC_IRQ_PRIO11  11
#define NVIC_IRQ_PRIO12  12
#define NVIC_IRQ_PRIO13  13
#define NVIC_IRQ_PRIO14  14
#define NVIC_IRQ_PRIO15  15

/* ==========================
   GPIO REGISTER STRUCTURE
   ========================== */

typedef struct
{
    __VO uint32_t MODER;
    __VO uint32_t OTYPER;
    __VO uint32_t OSPEEDR;
    __VO uint32_t PUPDR;
    __VO uint32_t IDR;
    __VO uint32_t ODR;
    __VO uint32_t BSRR;
    __VO uint32_t LCKR;
    __VO uint32_t AFR[2];

} GPIO_RegDef_t;

/* ==========================
   SPI Register Structure
   ========================== */

typedef struct
{
	__VO uint32_t CR1;
	__VO uint32_t CR2;
	__VO uint32_t SR;
	__VO uint32_t DR;
	__VO uint32_t CRCPR;
	__VO uint32_t RXCRCR;
	__VO uint32_t TXCRCR;
	__VO uint32_t I2SCFGR;
	__VO uint32_t I2SPR;
}SPI_RegDef_t;

/* ==========================
   SYSCFG REGISTER STRUCTURE
   ========================== */
typedef struct
{
	__VO uint32_t MEMRMP;           // Offset 0x00
	__VO uint32_t PMC;              // Offset 0x04
	__VO uint32_t EXTICR[4];        // Offsets 0x08, 0x0C, 0x10, 0x14
	uint32_t RESERVED0[2];          // Offsets 0x18, 0x1C (reserved space)
	__VO uint32_t CMPCR;            // Offset 0x20

} SYSCFG_RegDef_t;
/* ==========================
   RCC REGISTER STRUCTURE
   ========================== */

typedef struct
{
    __VO uint32_t CR;
    __VO uint32_t PLLCFGR;
    __VO uint32_t CFGR;
    __VO uint32_t CIR;

    __VO uint32_t AHB1RSTR;
    __VO uint32_t AHB2RSTR;
    __VO uint32_t RESERVED0[2];

    __VO uint32_t APB1RSTR;
    __VO uint32_t APB2RSTR;
    __VO uint32_t RESERVED1[2];

    __VO uint32_t AHB1ENR;
    __VO uint32_t AHB2ENR;
    __VO uint32_t RESERVED2[2];

    __VO uint32_t APB1ENR;
    __VO uint32_t APB2ENR;

    __VO uint32_t AHB1LPENR;
    __VO uint32_t AHB2LPENR;
    __VO uint32_t RESERVED3[2];

    __VO uint32_t APB1LPENR;
    __VO uint32_t APB2LPENR;
    __VO uint32_t RESERVED4[2];

    __VO uint32_t BDCR;
    __VO uint32_t CSR;
    __VO uint32_t RESERVED5[2];

    __VO uint32_t SSCGR;
    __VO uint32_t PLLI2SCFGR;
    __VO uint32_t RESERVED6;
    __VO uint32_t DCKCFGR;

} RCC_RegDef_t;

/* ==========================
   EXTI REGISTER STRUCTURE
   ========================== */
typedef struct
{
	__VO uint32_t IMR;
	__VO uint32_t EMR;
	__VO uint32_t RTSR;
	__VO uint32_t FTSR;
	__VO uint32_t SWIER;
	__VO uint32_t PR;
}EXTI_RegDef_t;
/* ==========================
   PERIPHERAL DEFINITIONS
   ========================== */

#define GPIOA   ((GPIO_RegDef_t*) GPIOA_BASE_ADDRESS)
#define GPIOB   ((GPIO_RegDef_t*) GPIOB_BASE_ADDRESS)
#define GPIOC   ((GPIO_RegDef_t*) GPIOC_BASE_ADDRESS)
#define GPIOD   ((GPIO_RegDef_t*) GPIOD_BASE_ADDRESS)
#define GPIOE   ((GPIO_RegDef_t*) GPIOE_BASE_ADDRESS)
#define GPIOH   ((GPIO_RegDef_t*) GPIOH_BASE_ADDRESS)

#define RCC     ((RCC_RegDef_t*) RCC_BASE_ADDRESS)
#define EXTI    ((EXTI_RegDef_t*) EXTI_BASE_ADDRESS)
#define SYSCFG  ((SYSCFG_RegDef_t *)SYSCFG_BASE_ADDRESS)

#define SPI1    ((SPI_RegDef_t *)SPI1_BASE_ADDRESS)
#define SPI2    ((SPI_RegDef_t *)SPI2_BASE_ADDRESS)
#define SPI3    ((SPI_RegDef_t *)SPI3_BASE_ADDRESS)
#define SPI4    ((SPI_RegDef_t *)SPI4_BASE_ADDRESS)
/* ==========================
   CLOCK ENABLE MACROS
   ========================== */

#define GPIOA_PCLK_EN()   (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()   (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()   (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()   (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()   (RCC->AHB1ENR |= (1 << 4))
#define GPIOH_PCLK_EN()   (RCC->AHB1ENR |= (1 << 7))

#define GPIOA_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOH_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 7))

/* ==========================
   I2C CLOCK ENABLE MACROS
   ========================== */

#define I2C1_PCLK_EN()    (RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()    (RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()    (RCC->APB1ENR |= (1 << 23))

#define I2C1_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 23))

/* ==========================
   SPI CLOCK ENABLE MACROS
   ========================== */

#define SPI1_PCLK_EN()    (RCC->APB2ENR |= (1 << 12))
#define SPI4_PCLK_EN()    (RCC->APB2ENR |= (1 << 13))

#define SPI2_PCLK_EN()    (RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()    (RCC->APB1ENR |= (1 << 15))

#define SPI1_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 12))
#define SPI4_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 13))

#define SPI2_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 15))

/* ==========================
   USART CLOCK ENABLE MACROS
   ========================== */

#define USART1_PCLK_EN()   (RCC->APB2ENR |= (1 << 4))
#define USART6_PCLK_EN()   (RCC->APB2ENR |= (1 << 5))

#define USART2_PCLK_EN()   (RCC->APB1ENR |= (1 << 17))

#define USART1_PCLK_DI()   (RCC->APB2ENR &= ~(1 << 4))
#define USART6_PCLK_DI()   (RCC->APB2ENR &= ~(1 << 5))

#define USART2_PCLK_DI()   (RCC->APB1ENR &= ~(1 << 17))

/* ==========================
   SYSCFG CLOCK ENABLE MACROS
   ========================== */

#define SYSCFG_PCLK_EN()   (RCC->APB2ENR |= (1 << 14))
#define SYSCFG_PCLK_DI()   (RCC->APB2ENR &= ~(1 << 14))

/* ==========================
   GENERIC MACROS
   ========================== */

#define ENABLE      1
#define DISABLE     0

#define SET         ENABLE
#define RESET       DISABLE

#define GPIO_PIN_SET    SET
#define GPIO_PIN_RESET  RESET

#define FLAG_RESET RESET
#define FLAG_SET   SET

/*=========================
SPI_CR1 Register bits and macro representation
 ==========================*/
#define SPI_CR1_BIDIMODE 15
#define SPI_CR1_BIDIOE   14
#define SPI_CR1_CRCEN    13
#define SPI_CR1_CRCNEXT  12
#define SPI_CR1_DFF      11
#define SPI_CR1_RXONLY   10
#define SPI_CR1_SSM      9
#define SPI_CR1_SSI      8
#define SPI_CR1_LSBFIRST 7
#define SPI_CR1_SPE      6
#define SPI_CR1_BR3_5    3
#define SPI_CR1_MSTR     2
#define SPI_CR1_CPOL     1
#define SPI_CR1_CPHA     0

/*=========================
SPI_CR2 Register bits and macro representation
 ==========================*/
#define SPI_CR2_TXEIE    7
#define SPI_CR2_RXNEIE   6
#define SPI_CR2_ERRIE    5
#define SPI_CR2_FRF      4
#define SPI_CR2_SSOE     2
#define SPI_CR2_TXDMAEN  1
#define SPI_CR2_RXDMAEN  0

/*=========================
SPI_SR Register bits and macro representation
 ==========================*/
#define SPI_SR_RXNE     0   // Receive buffer not empty
#define SPI_SR_TXE      1   // Transmit buffer empty
#define SPI_SR_CHSIDE   2   // Channel side (I2S mode)
#define SPI_SR_UDR      3   // Underrun flag
#define SPI_SR_CRCERR   4   // CRC error flag
#define SPI_SR_MODF     5   // Mode fault
#define SPI_SR_OVR      6   // Overrun flag
#define SPI_SR_BSY      7   // Busy flag
#define SPI_SR_FRE      8   // Frame format error (TI mode)

#endif /* STM32F401XX_H_ */
