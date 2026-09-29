/*
 * STM32F1xx_GPIO_Driver.h
 * GPIO Driver Header File - Public APIs & Configuration Structures
 */

#ifndef INC_STM32F1XX_GPIO_DRIVER_H_
#define INC_STM32F1XX_GPIO_DRIVER_H_

#include "STM32F103C8T6.h"

/* Physical Pin Definitions */
#define GPIO_PIN_NO_0   0
#define GPIO_PIN_NO_1   1
#define GPIO_PIN_NO_2   2
#define GPIO_PIN_NO_3   3
#define GPIO_PIN_NO_4   4
#define GPIO_PIN_NO_5   5
#define GPIO_PIN_NO_6   6
#define GPIO_PIN_NO_7   7
#define GPIO_PIN_NO_8   8
#define GPIO_PIN_NO_9   9
#define GPIO_PIN_NO_10  10
#define GPIO_PIN_NO_11  11
#define GPIO_PIN_NO_12  12
#define GPIO_PIN_NO_13  13
#define GPIO_PIN_NO_14  14
#define GPIO_PIN_NO_15  15

/* Pin Operational Modes */
#define GPIO_PIN_IP     0  /* Standard Input */
#define GPIO_OP_PP      1  /* Output Push-Pull */
#define GPIO_OP_OD      2  /* Output Open-Drain */
#define GPIO_OPAF_PP    3  /* Alternate Function Push-Pull */
#define GPIO_OPAF_OD    4  /* Alternate Function Open-Drain */

/* External Interrupt Modes */
#define GPIO_PIN_IP_RT  5  /* Interrupt Rising Edge Trigger */
#define GPIO_PIN_IP_FT  6  /* Interrupt Falling Edge Trigger */
#define GPIO_PIN_IP_FRT 7  /* Interrupt Rising & Falling Edge Trigger */

/* Input Configurations */
#define GPIO_IN_AL      0  /* Analog Mode */
#define GPIO_IN_FL      1  /* Floating Input */
#define GPIO_IN_PU      2  /* Internal Pull-Up */
#define GPIO_IN_PD      3  /* Internal Pull-Down */

/* Output Maximum Speed Options */
#define GPIO_PIN_OP10   1  /* 10 MHz Max Speed */
#define GPIO_PIN_OP02   2  /* 2 MHz Max Speed  */
#define GPIO_PIN_OP50   3  /* 50 MHz Max Speed */

/* Pin Configuration Structure */
typedef struct {
    uint8_t GPIO_PinNumber;      /* Pin 0 to 15 */
    uint8_t GPIO_PinMode;        /* Pin operating mode */
    uint8_t GPIO_PinSpeed;       /* Output speed */
    uint8_t GPIO_PinPuPdControl; /* Pull-up / Pull-down / Floating selection */
    uint8_t GPIO_PinAltFunMode;  /* Alternate function selection */
} GPIO_PinConfig_t;

/* Pin Handle Structure */
typedef struct {
    GPIO_RegDef_t *pGPIOx;           /* Base address of the GPIO port */
    GPIO_PinConfig_t GPIO_PinConfig; /* Active pin configuration settings */
} GPIO_Handle_t;

/******************************************************************************/
/*                            Driver Public APIs                              */
/******************************************************************************/

/* Peripheral Clock Management */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/* Initialization & De-Initialization */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/* Data Read & Write Interfaces */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/* Interrupt Management & Interrupt Handlers */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* INC_STM32F1XX_GPIO_DRIVER_H_ */
