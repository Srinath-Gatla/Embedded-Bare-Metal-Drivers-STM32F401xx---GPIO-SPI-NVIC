# Embedded-Bare-Metal-Drivers-STM32F401xx---GPIO-SPI-NVIC

A clean, well-structured **bare-metal driver library** for the **STM32F401RET6TR* (and STM32F401xx series) microcontrollers.

---

## 📋 Overview

This repository contains low-level **register-based drivers** written from scratch for STM32F401xx. It includes drivers for GPIO and SPI with proper interrupt support.

### Supported Peripherals
- **GPIO** (Input, Output, Alternate Function, External Interrupts)
- **SPI** (Master/Slave, Polling + Interrupt mode)
- **RCC** (Clock Control)
- **NVIC** & **EXTI** (Interrupt System)

---

## ✨ Features

- Modular and educational code structure
- Full **Interrupt-driven SPI** (Non-blocking)
- Complete **GPIO Interrupt** support (Rising, Falling, Both edges)
- Proper peripheral clock enabling/disabling
- Software Slave Management (SSM) support
- Weak application callback implementation
- Well-commented code

---

## 🛠 Hardware Configuration

- **MCU**: STM32F401CCU6 (Black Pill)
- **SPI2 Pins**:
  - SCK  → PB13
  - MOSI → PB15
  - MISO → PB14
  - NSS  → PB12
- **User Button** → PA0 (Pull-up enabled)

---

## 🧪 Example Application

The `main.c` demonstrates:
- Button press detection on PA0
- SPI Master communication using **interrupts**
- Sending command to control LED on slave device
- TX + RX using interrupt mode

---

## 📁 Project Structure

STM32F401_BareMetal_Drivers/
├── STM32F401XX.h
├── STM32F401_GPIO.h
├── STM32F401_GPIO.c
├── STM32F401_SPI.h
├── STM32F401_SPI.c
├── main.c
└── README.md

---

## 🚀 How to Use

1. Copy all files into your project folder
2. Add startup file (`startup_stm32f401xx.s`) and linker script
3. Build using STM32CubeIDE, Keil uVision, or ARM GCC
4. Flash the code
5. Press the button on PA0 to send SPI data

---

## 📌 Key API Examples

### GPIO Initialization
```c
GPIO_Handle_t btn;
btn.pGPIOx = GPIOA;
btn.GPIO_config.GPIO_PinNumber = GPIO_PIN_0;
btn.GPIO_config.GPIO_PinMode = GPIO_MODE_IN;
btn.GPIO_config.GPIO_Pinpupdcontrol = GPIO_PIN_PU;
GPIO_Init(&btn);
SPI_Send_data_IT(&SPI2Handle, txBuffer, 3);
SPI_Receive_data_IT(&SPI2Handle, rxBuffer, 1);
```
### SPI Interrupt Mode
```c
CSPI_Send_data_IT(&SPI2Handle, txBuffer, 3);
SPI_Receive_data_IT(&SPI2Handle, rxBuffer, 1);
```

### Application Callback
```C
void SPI_ApplicationEventCallBack(SPI_Handle_t *pSPIHandle, uint8_t AppEv)
{
    if(AppEv == SPI_EVENT_TX_CMPLT)
        spiTxDone = 1;
}
```
### 🎯 Future Enhancements

I2C Driver (header already present)
USART Driver
DMA support for SPI
Timer, ADC, PWM


### 📜 License
MIT License - Feel free to use and modify.

### 👨‍💻 Author
Srinath
Embedded Systems Developer
