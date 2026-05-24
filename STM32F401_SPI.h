#ifndef STM32F401_SPI_H_
#define STM32F401_SPI_H_

#include "STM32F401XX.h"
#include "STM32F401_GPIO.h"

/*=========================
SPI_MODES_STRUCTURE
==========================*/
typedef struct
{
    uint8_t deviceMode;     // Master or Slave
    uint8_t busConfig;      // Full-duplex, Half-duplex, Simplex RX
    uint8_t sclkSpeed;      // Baud rate
    uint8_t dff;            // Data frame format (8/16 bit)
    uint8_t cpol;           // Clock polarity
    uint8_t cpha;           // Clock phase
    uint8_t ssm;            // Software slave management
} SPI_Config_t;

/*=========================
SPI_Handle_STRUCTURE
==========================*/
typedef struct
{
	SPI_RegDef_t *pSPIX;  // This Holds the base address of SPIx (X:0,1,2) peripheral
	SPI_Config_t  SPIConfig;
	uint8_t * pTxBuffer;  // to store the app ,Tx buffer address
	uint8_t * pRxBuffer;  // to store the app ,RX buffer
	uint32_t TxLen;       // to store Tx length
	uint32_t RxLen;       // to store Rx length
	uint8_t TxState;      // to store Tx State
	uint8_t RxState;      // to store Rx state
} SPI_Handle_t;

/*=========================
SPI_device modes
==========================*/
#define SPI_DEVICE_MODE_MASTER  1
#define SPI_DEVICE_MODE_SLAVE   0

/*=========================
SPI_BUS_CONFIG
==========================*/
#define SPI_BUS_CONFIG_FD               1
#define SPI_BUS_CONFIG_HD               2
#define SPI_BUS_CONFIG_SIMPLEX_TXONLY   3
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY   4

/*=========================
SPI_APPLICATION_STATES
==========================*/
#define SPI_READY         0
#define SPI_BUSY_IN_RX    1
#define SPI_BUSY_IN_TX    2


/*=========================
POSSIBLE SPI_APPLICATION_EVENTS
==========================*/

#define SPI_EVENT_TX_CMPLT 1
#define SPI_EVENT_RX_CMPLT 2
#define SPI_EVENT_OVR_ERR  3
#define SPI_EVENT_CRC_ERR  4


/*=========================
SPI_SCLK_SPEED
==========================*/
#define SPI_CLOCKDIV2    0
#define SPI_CLOCKDIV4    1
#define SPI_CLOCKDIV8    2
#define SPI_CLOCKDIV16   3
#define SPI_CLOCKDIV32   4
#define SPI_CLOCKDIV64   5
#define SPI_CLOCKDIV128  6
#define SPI_CLOCKDIV256  7

/*=========================
SPI_DFF
==========================*/
#define SPI_DFF_8BIT   0  // 8-bit data frame
#define SPI_DFF_16BIT  1  // 16-bit data frame

/*=========================
SPI_CPOL
==========================*/
#define SPI_CPOL_HIGH  1
#define SPI_CPOL_LOW   0

/*=========================
SPI_CPHA
==========================*/
#define SPI_CPHA_HIGH  1
#define SPI_CPHA_LOW   0

/*=========================
SPI_SSM
==========================*/
#define SPI_SSM_EN   1
#define SPI_SSM_DI   0

/*=========================
SPI_REG_RESET_MACROS
==========================*/
#define SPI1_REG_RESET()   do{ RCC->APB2RSTR |= (1<<12); RCC->APB2RSTR &= ~(1<<12); }while(0)
#define SPI2_REG_RESET()   do{ RCC->APB1RSTR |= (1<<14); RCC->APB1RSTR &= ~(1<<14); }while(0)
#define SPI3_REG_RESET()   do{ RCC->APB1RSTR |= (1<<15); RCC->APB1RSTR &= ~(1<<15); }while(0)
#define SPI4_REG_RESET()   do{ RCC->APB2RSTR |= (1<<13); RCC->APB2RSTR &= ~(1<<13); }while(0)

/*=========================
SPI_related status flags
==========================*/
#define SPI_TXE_FLAG  (1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG (1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG (1 << SPI_SR_BSY)
// attribute macro
#define __weak __attribute__((weak))
/*=========================
SPI_API's
==========================*/

/* PERIPHERAL CLOCK */
void SPI_PLLCLK_Init(SPI_RegDef_t *pSPIx, uint8_t ENorDI);

/* INITIALIZE AND DEINITIALIZE THE SPI */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/* SEND AND RECEIVE DATA */
void SPI_Send_data(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len);
void SPI_Recieve_data(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t len);

uint8_t SPI_Send_data_IT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t len);
uint8_t SPI_Recieve_data_IT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t len);

/* SPI INTERRUPT HANDLING */
void SPI_IRQCONFIG(uint8_t IRQNumber, uint8_t IRQENorDI);
void SPI_IRPriority(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandle(SPI_Handle_t *pSPIHandle);

/* OTHER PERIPHERAL CONTROL APIs */
void SPI_Peripheralcontrol(SPI_RegDef_t *pSPIx, uint8_t ENorDI);
void SPI_SSI_Config(SPI_RegDef_t *pSPIx, uint8_t ENorDI);
void SPI_SSOE_Config(SPI_RegDef_t *pSPIx, uint8_t ENorDI);
uint8_t SPI_getflag_status(SPI_RegDef_t *pSPIx, uint32_t flagname);
void SPI_ClearOVRFLag(SPI_RegDef_t * pSPIx);
void SPI_CloseTransmission(SPI_Handle_t * pSPIHandle);
void SPI_CloseReception(SPI_Handle_t * pSPIHandle);
//Application callback
void SPI_ApplicationEventCallBack(SPI_Handle_t * pSPIHandle,uint8_t AppEv);
#endif /* STM32F401_SPI_H_ */
