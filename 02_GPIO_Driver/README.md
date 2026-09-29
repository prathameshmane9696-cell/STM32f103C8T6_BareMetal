# Bare-Metal STM32F103 GPIO Driver & EXTI Framework

A modular, register-level GPIO driver and hardware interrupt framework for the ARM Cortex-M3 (STM32F103C8T6 "Blue Pill") microcontroller. Built entirely from scratch using C without relying on vendor HAL/LL abstractions or auto-generated code.

## 📁 Directory Structure

```
02_GPIO_Driver/
├── Inc/
│   ├── STM32F103C8T6.h            # Microcontroller memory map & peripheral register definitions
│   └── STM32F1xx_GPIO_Driver.h    # Driver APIs, configuration structures, & macros
└── Src/
    ├── STM32F1xx_GPIO_Driver.c    # Low-level driver implementation routines
    ├── led_toggle.c               # Application 1: Basic output pin toggling
    ├── led_button.c               # Application 2: LED toggle using button
    └── led_buttonIRQ.c            # Application 3: Asynchronous EXTI & NVIC hardware interrupts

```

## 🛠️ Key Capabilities & Driver Features

* **Register-Level Memory Mapping:** Peripheral base addresses (`RCC`, `GPIOA-GPIOG`, `AFIO`, `EXTI`, `NVIC`) mapped directly using standard C structures according to the STM32F103 reference manual (RM0008).

* **Configurable GPIO Modes:** Supports Output Push-Pull, Output Open-Drain, Input Analog, Input Floating, and Input Pull-Up/Pull-Down modes.

* **Driver APIs Implemented:**

  * `GPIO_Init(...)` / `GPIO_DeInit(...)`

  * `GPIO_ReadFromInputPin(...)` / `GPIO_ReadFromInputPort(...)`

  * `GPIO_WriteToOutputPin(...)` / `GPIO_WriteToOutputPort(...)`

  * `GPIO_ToggleOutputPin(...)`

  * `GPIO_IRQConfig(...)` / `GPIO_IRQHandling(...)`

* **Asynchronous Hardware Interrupts:** Integrated EXTI line selection via `AFIO_EXTICR`, configurable edge detection (Rising/Falling/Both), and NVIC interrupt mask control via `NVIC_ISER`.

* **Atomic Pending Flag Clearing:** Interrupt service routine handling (`EXTI_IRQHandler`) with atomic clearing of pending register bits (`EXTI_PR`) to prevent continuous re-entry loops.

## 

|  | 
 | ----- | 

##  
