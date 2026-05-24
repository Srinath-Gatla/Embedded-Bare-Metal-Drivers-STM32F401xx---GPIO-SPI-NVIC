#include "STM32F401_GPIO.h"
// Initalize the GPIO pin
void GPIO_Init(GPIO_Handle_t * pGPIOHandle)
{
	    uint32_t temp = 0;
	    // enable the peripheral clock
	    GPIO_PLLCLK_Init(pGPIOHandle->pGPIOx,ENABLE);

	    // Configure GPIO mode (MODER)
	    if(pGPIOHandle->GPIO_config.GPIO_PinMode <= GPIO_MODE_ANALOG)
	    {
	        temp = (pGPIOHandle->GPIO_config.GPIO_PinMode << (2 * pGPIOHandle->GPIO_config.GPIO_PinNumber));
	        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_config.GPIO_PinNumber));
	        pGPIOHandle->pGPIOx->MODER |= temp;
	    }
	    // ⚠️ ONLY configure EXTI for interrupt modes
	    else if(pGPIOHandle->GPIO_config.GPIO_PinMode >= GPIO_MODE_IT_FT)
	    {
	        // Enable SYSCFG clock FIRST
	        SYSCFG_PCLK_EN();

	        // Configure trigger edge
	        if(pGPIOHandle->GPIO_config.GPIO_PinMode == GPIO_MODE_IT_FT) {
	            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_config.GPIO_PinNumber);
	            EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_config.GPIO_PinNumber);
	        }
	        else if(pGPIOHandle->GPIO_config.GPIO_PinMode == GPIO_MODE_IT_RT) {
	            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_config.GPIO_PinNumber);
	            EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_config.GPIO_PinNumber);
	        }
	        else if(pGPIOHandle->GPIO_config.GPIO_PinMode == GPIO_MODE_IT_RFT) {
	            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_config.GPIO_PinNumber);
	            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_config.GPIO_PinNumber);
	        }

	        // Map EXTI line to GPIO port (use |= to preserve other pins in same register)
	        uint8_t temp1 = pGPIOHandle->GPIO_config.GPIO_PinNumber / 4;
	        uint8_t temp2 = pGPIOHandle->GPIO_config.GPIO_PinNumber % 4;
	        uint8_t portcode = GPIO_BASE_ADDR_CODE(pGPIOHandle->pGPIOx);

	        SYSCFG->EXTICR[temp1] &= ~(0xF << (temp2 * 4));  // Clear first
	        SYSCFG->EXTICR[temp1] |= (portcode << (temp2 * 4));  // Then set

	        // Enable interrupt mask for THIS pin only
	        EXTI->IMR |= (1 << pGPIOHandle->GPIO_config.GPIO_PinNumber);  // ✅ Fixed: (1 << pin)
	    }

    // SPEED
    temp = (pGPIOHandle->GPIO_config.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_config.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_config.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;

    // OUTPUT TYPE
    temp = (pGPIOHandle->GPIO_config.GPIO_PinOptype << pGPIOHandle->GPIO_config.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_config.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER |= temp;

    // PULL UP / PULL DOWN
    temp = (pGPIOHandle->GPIO_config.GPIO_Pinpupdcontrol << (2 * pGPIOHandle->GPIO_config.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_config.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR |= temp;
}
void GPIO_DeInit(GPIO_RegDef_t * pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}
	else if(pGPIOx ==GPIOB)
	{
		GPIOB_REG_RESET();
	}
	else if(pGPIOx ==GPIOC)
	{
		GPIOC_REG_RESET();
	}
	else if(pGPIOx ==GPIOD)
	{
		GPIOD_REG_RESET();
	}
	else if(pGPIOx ==GPIOE)
	{
		GPIOE_REG_RESET();
	}
	else if(pGPIOx ==GPIOH)
	{
		GPIOH_REG_RESET();
	}
}
// API to initialize the clock
void GPIO_PLLCLK_Init(GPIO_RegDef_t * pGPIOx, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}

	}
	else
	{

		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}
		else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}

	}
}
// API for read and write the programs
uint16_t  GPIO_Read_Port(GPIO_RegDef_t * pGPIOx)
{
	return (pGPIOx->IDR);
}
uint8_t GPIO_Read_Pin(GPIO_RegDef_t * pGPIOx,uint8_t pinnumber)
{
	uint16_t value;
	value= (uint8_t) (pGPIOx->IDR >> pinnumber) & 0x1;
	return value;
}
void GPIO_Write_Port(GPIO_RegDef_t * pGPIOx,uint16_t value)
{
	pGPIOx->ODR=value;
}
void GPIO_Write_Pin(GPIO_RegDef_t * pGPIOx,uint8_t pinnumber,uint8_t value)
{
	if(value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1<<pinnumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1<<pinnumber);
	}
}
//API for Toggling Output Pin
void GPIO_Toggle_Outputpin(GPIO_RegDef_t * pGPIOx, uint8_t pinnumber)
{
	pGPIOx->ODR ^= (1<<pinnumber);
}
// API for Interrupt handler
void GPIO_IRQCONFIG(uint8_t IRQNumber, uint8_t IRQENorDI)
{
    if(IRQENorDI == ENABLE)
    {
        if(IRQNumber <= 31)
        {
            *NVIC_ISER0 |= (1 << IRQNumber);  // ✅ Fixed
        }
        else if(IRQNumber >= 32 && IRQNumber < 64)
        {
            *NVIC_ISER1 |= (1 << (IRQNumber % 32));  // ✅ Fixed
        }
        else if(IRQNumber >= 64 && IRQNumber < 96)
        {
            *NVIC_ISER2 |= (1 << (IRQNumber % 64));  // ✅ Fixed
        }
    }
    else
    {
        if(IRQNumber <= 31)
        {
            *NVIC_ICER0 |= (1 << IRQNumber);
        }
        else if(IRQNumber >= 32 && IRQNumber < 64)
        {
            *NVIC_ICER1 |= (1 << (IRQNumber % 32));
        }
        else if(IRQNumber >= 64 && IRQNumber < 96)
        {
            *NVIC_ICER2 |= (1 << (IRQNumber % 64));
        }
    }
}
void GPIO_IRPriority(uint8_t IRQNumber,uint32_t IRQPriority)
{
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;
    uint8_t shift_section = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
    *(NVIC_IPR + iprx) |= (IRQPriority << shift_section);
}
void GPIO_IRQHandle(uint8_t pinnumber)
{
	if(EXTI->PR & (1<<pinnumber))
	{
		EXTI->PR |= (1<<pinnumber);
	}
}
