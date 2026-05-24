#ifndef STM32F401_GPIO_H_
#define STM32F401_GPIO_H_

#include "STM32F401XX.h"

/*********************************************************************
 * GPIO Configuration Structure
 *********************************************************************/
typedef struct
{
    uint8_t GPIO_PinNumber;        /* Possible values: GPIO_PIN_0 to GPIO_PIN_15 */
    uint8_t GPIO_PinMode;          /* Possible values: @GPIO_PIN_MODES */
    uint8_t GPIO_PinSpeed;         /* Possible values: @GPIO_PIN_SPEED */
    uint8_t GPIO_Pinpupdcontrol;      /* Possible values: @GPIO_PUPD */
    uint8_t GPIO_PinOptype;        /* Possible values: @GPIO_OUTPUT_TYPES */
    uint8_t GPIO_PinAltFunMode;    /* Possible values: 0–15 */
} GPIO_Config_t;

/*********************************************************************
 * GPIO Handle Structure
 *********************************************************************/
typedef struct
{
    GPIO_RegDef_t *pGPIOx;         /* Holds base address of GPIO port */
    GPIO_Config_t GPIO_config;     /* Holds GPIO pin configuration */
} GPIO_Handle_t;

/*********************************************************************
 * GPIO PIN NUMBERS
 *********************************************************************/
#define GPIO_PIN_0        0
#define GPIO_PIN_1        1
#define GPIO_PIN_2        2
#define GPIO_PIN_3        3
#define GPIO_PIN_4        4
#define GPIO_PIN_5        5
#define GPIO_PIN_6        6
#define GPIO_PIN_7        7
#define GPIO_PIN_8        8
#define GPIO_PIN_9        9
#define GPIO_PIN_10       10
#define GPIO_PIN_11       11
#define GPIO_PIN_12       12
#define GPIO_PIN_13       13
#define GPIO_PIN_14       14
#define GPIO_PIN_15       15

/*********************************************************************
 * GPIO PIN MODES
 *********************************************************************/
#define GPIO_MODE_IN        0
#define GPIO_MODE_OUT       1
#define GPIO_MODE_ALTFN     2
#define GPIO_MODE_ANALOG    3
#define GPIO_MODE_IT_FT     4
#define GPIO_MODE_IT_RT     5
#define GPIO_MODE_IT_RFT    6

/*********************************************************************
 * GPIO OUTPUT TYPES
 *********************************************************************/
#define GPIO_OP_TYPE_PP     0
#define GPIO_OP_TYPE_OD     1

/*********************************************************************
 * GPIO SPEED
 *********************************************************************/
#define GPIO_SPEED_LOW      0
#define GPIO_SPEED_MEDIUM   1
#define GPIO_SPEED_FAST     2
#define GPIO_SPEED_HIGH     3

/*********************************************************************
 * GPIO PULL-UP / PULL-DOWN
 *********************************************************************/
#define GPIO_NO_PUPD        0
#define GPIO_PIN_PU         1
#define GPIO_PIN_PD         2

/*********************************************************************
 * GPIO RESET MACROS
 *********************************************************************/
#define GPIOA_REG_RESET()  do{ (RCC->AHB1RSTR |= (1 << 0)); \
                               (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)

#define GPIOB_REG_RESET()  do{ (RCC->AHB1RSTR |= (1 << 1)); \
                               (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)

#define GPIOC_REG_RESET()  do{ (RCC->AHB1RSTR |= (1 << 2)); \
                               (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)

#define GPIOD_REG_RESET()  do{ (RCC->AHB1RSTR |= (1 << 3)); \
                               (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)

#define GPIOE_REG_RESET()  do{ (RCC->AHB1RSTR |= (1 << 4)); \
                               (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)

#define GPIOH_REG_RESET()  do{ (RCC->AHB1RSTR |= (1 << 7)); \
                               (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)

/*********************************************************************
 * API PROTOTYPES
 *********************************************************************/

/* Peripheral Clock */
void GPIO_PLLCLK_Init(GPIO_RegDef_t *pGPIOx, uint8_t ENorDI);

/* Init & DeInit */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/* Data Read */
uint8_t GPIO_Read_Pin(GPIO_RegDef_t *pGPIOx, uint8_t pinnumber);
uint16_t GPIO_Read_Port(GPIO_RegDef_t *pGPIOx);

/* Data Write */
void GPIO_Write_Pin(GPIO_RegDef_t *pGPIOx, uint8_t pinnumber, uint8_t Value);
void GPIO_Write_Port(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_Toggle_Pin(GPIO_RegDef_t *pGPIOx, uint8_t pinnumber);

/* Interrupt Handling */
void GPIO_IRQCONFIG(uint8_t IRQNumber, uint8_t IRQENorDI);
void GPIO_IRPriority(uint8_t IRQNumber,uint32_t IRQPriority);
void GPIO_IRQHandle(uint8_t pinnumber);

#endif /* STM32F401_GPIO_H_ */
