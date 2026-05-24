#include "STM32F401XX.h"
#include "STM32F401_SPI.h"
#include <string.h>

#define COMMAND_LED_CTRL  0x50
#define LED_PIN 9
#define LED_ON  1

SPI_Handle_t SPI2Handle;

uint8_t txBuffer[32];
uint8_t rxBuffer[32];

volatile uint8_t spiTxDone = 0;
volatile uint8_t spiRxDone = 0;

/* Delay */
void delay(void)
{
	for(uint32_t i = 0; i < 500000/2; i++);
}

/* Button Init */
void GPIO_BUTTON_ENABLE(void)
{
	GPIO_Handle_t GPIOBTN;

	GPIOBTN.pGPIOx = GPIOA;
	GPIOBTN.GPIO_config.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBTN.GPIO_config.GPIO_PinNumber = GPIO_PIN_0;
	GPIOBTN.GPIO_config.GPIO_Pinpupdcontrol = GPIO_PIN_PU;
	GPIOBTN.GPIO_config.GPIO_PinSpeed = GPIO_SPEED_FAST;

	GPIO_PLLCLK_Init(GPIOA, ENABLE);
	GPIO_Init(&GPIOBTN);
}

/* SPI GPIO */
void SPI2_GPIO_Init(void)
{
	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_config.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_config.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_config.GPIO_PinOptype = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_config.GPIO_Pinpupdcontrol = GPIO_NO_PUPD;
	SPIPins.GPIO_config.GPIO_PinSpeed = GPIO_SPEED_FAST;

	SPIPins.GPIO_config.GPIO_PinNumber = GPIO_PIN_13;
	GPIO_Init(&SPIPins);

	SPIPins.GPIO_config.GPIO_PinNumber = GPIO_PIN_15;
	GPIO_Init(&SPIPins);

	SPIPins.GPIO_config.GPIO_PinNumber = GPIO_PIN_14;
	GPIO_Init(&SPIPins);

	SPIPins.GPIO_config.GPIO_PinNumber = GPIO_PIN_12;
	GPIO_Init(&SPIPins);
}

/* SPI Init */
void SPI2_Init(void)
{
	SPI2Handle.pSPIX = SPI2;
	SPI2Handle.SPIConfig.deviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPIConfig.busConfig = SPI_BUS_CONFIG_FD;
	SPI2Handle.SPIConfig.sclkSpeed = SPI_CLOCKDIV8;
	SPI2Handle.SPIConfig.dff = SPI_DFF_8BIT;
	SPI2Handle.SPIConfig.cpol = SPI_CPOL_LOW;
	SPI2Handle.SPIConfig.cpha = SPI_CPHA_LOW;
	SPI2Handle.SPIConfig.ssm = SPI_SSM_DI;

	SPI_Init(&SPI2Handle);
}

/* SPI IRQ */
void SPI2_IRQHandler(void)
{
	SPI_IRQHandle(&SPI2Handle);
}

/* Callback */
void SPI_ApplicationEventCallBack(SPI_Handle_t *pSPIHandle,uint8_t AppEv)
{
	if(AppEv == SPI_EVENT_TX_CMPLT)
	{
		spiTxDone = 1;
	}
	else if(AppEv == SPI_EVENT_RX_CMPLT)
	{
		spiRxDone = 1;
	}
}

int main(void)
{
	GPIO_BUTTON_ENABLE();
	SPI2_GPIO_Init();
	SPI2_Init();

	// Enable NSS output
	SPI_SSOE_Config(SPI2, ENABLE);

	// Enable SPI IRQ in NVIC (SPI2 = IRQ 36)
	SPI_IRQCONFIG(36, ENABLE);

	while(1)
	{
		while(!GPIO_Read_Pin(GPIOA, GPIO_PIN_0));
		delay();

		SPI_Peripheralcontrol(SPI2, ENABLE);

		/* Prepare data */
		txBuffer[0] = COMMAND_LED_CTRL;
		txBuffer[1] = LED_PIN;
		txBuffer[2] = LED_ON;

		spiTxDone = 0;

		/* Start interrupt TX */
		SPI_Send_data_IT(&SPI2Handle, txBuffer, 3);

		/* Wait for completion */
		while(!spiTxDone);

		/* Optional receive */
		spiRxDone = 0;
		SPI_Receive_data_IT(&SPI2Handle, rxBuffer, 1);

		while(!spiRxDone);

		while(SPI_getflag_status(SPI2, SPI_BUSY_FLAG));

		SPI_Peripheralcontrol(SPI2, DISABLE);
	}
}
