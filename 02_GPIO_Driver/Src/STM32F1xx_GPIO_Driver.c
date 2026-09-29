/*
 * STM32F1xx_GPIO_Driver.c
 * Bare-metal GPIO Driver Source Implementation
 */

#include "STM32F1xx_GPIO_Driver.h"

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi) {
    if (EnorDi == ENABLE) {
        if (pGPIOx == GPIOA)      { GPIOA_PCLK_EN(); }
        else if (pGPIOx == GPIOB) { GPIOB_PCLK_EN(); }
        else if (pGPIOx == GPIOC) { GPIOC_PCLK_EN(); }
        else if (pGPIOx == GPIOD) { GPIOD_PCLK_EN(); }
        else if (pGPIOx == GPIOE) { GPIOE_PCLK_EN(); }
    } else {
        if (pGPIOx == GPIOA)      { GPIOA_PCLK_DI(); }
        else if (pGPIOx == GPIOB) { GPIOB_PCLK_DI(); }
        else if (pGPIOx == GPIOC) { GPIOC_PCLK_DI(); }
        else if (pGPIOx == GPIOD) { GPIOD_PCLK_DI(); }
        else if (pGPIOx == GPIOE) { GPIOE_PCLK_DI(); }
    }
}

void GPIO_Init(GPIO_Handle_t *pGPIOHandle) {
    // Enable port clock
    GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

    uint8_t pin = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
    uint8_t shift = (pin % 8) * 4; // Each pin uses 4 bits in CRL/CRH

    // Select CRL (pins 0-7) or CRH (pins 8-15)
    volatile uint32_t *pCR = (pin <= 7) ? &pGPIOHandle->pGPIOx->CRL : &pGPIOHandle->pGPIOx->CRH;

    // Clear current 4-bit configuration
    *pCR &= ~(0x0F << shift);

    /* ---------------- INPUT & INTERRUPT MODES ---------------- */
    if ((pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_PIN_IP) ||
        (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode > 4))
    {
        // Set input type in CRL/CRH
        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl == GPIO_IN_AL) {
            *pCR |= (0x00 << shift); // Analog
        }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl == GPIO_IN_FL) {
            *pCR |= (0x04 << shift); // Floating input
        }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl == GPIO_IN_PU) {
            *pCR |= (0x08 << shift); // Input with pull-up/pull-down
            pGPIOHandle->pGPIOx->ODR |= (1 << pin); // Set ODR bit for Pull-Up
        }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl == GPIO_IN_PD) {
            *pCR |= (0x08 << shift); // Input with pull-up/pull-down
            pGPIOHandle->pGPIOx->ODR &= ~(1 << pin); // Clear ODR bit for Pull-Down
        }

        // Setup EXTI if an interrupt mode was specified
        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode > 4) {
            AFIO_PCLK_EN();

            if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_PIN_IP_RT) {
                EXTI->RTSR |= (1 << pin);
                EXTI->FTSR &= ~(1 << pin);
            }
            else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_PIN_IP_FT) {
                EXTI->FTSR |= (1 << pin);
                EXTI->RTSR &= ~(1 << pin);
            }
            else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_PIN_IP_FRT) {
                EXTI->RTSR |= (1 << pin);
                EXTI->FTSR |= (1 << pin);
            }

            // Route port pin to EXTI line in AFIO->EXTICR
            uint8_t index = pin / 4;
            uint8_t exti_shift = (pin % 4) * 4;
            uint8_t port_code = 0;

            if (pGPIOHandle->pGPIOx == GPIOA)      { port_code = 0; }
            else if (pGPIOHandle->pGPIOx == GPIOB) { port_code = 1; }
            else if (pGPIOHandle->pGPIOx == GPIOC) { port_code = 2; }
            else if (pGPIOHandle->pGPIOx == GPIOD) { port_code = 3; }
            else if (pGPIOHandle->pGPIOx == GPIOE) { port_code = 4; }

            AFIO->EXTICR[index] &= ~(0x0F << exti_shift);
            AFIO->EXTICR[index] |= (port_code << exti_shift);

            // Unmask EXTI line
            EXTI->IMR |= (1 << pin);
        }
    }
    /* ---------------- OUTPUT MODES ---------------- */
    else {
        uint8_t cnf = 0;
        uint8_t speed = 0;

        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_OP_PP)        { cnf = 0x0; }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_OP_OD)   { cnf = 0x1; }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_OPAF_PP) { cnf = 0x2; }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_OPAF_OD) { cnf = 0x3; }

        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed == GPIO_PIN_OP10)     { speed = 0x1; }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed == GPIO_PIN_OP02) { speed = 0x2; }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed == GPIO_PIN_OP50) { speed = 0x3; }

        uint8_t config_val = (cnf << 2) | speed;
        *pCR |= (config_val << shift);
    }
}

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx) {
    if (pGPIOx == GPIOA)      { RCC->APB2RSTR |= (1 << 2); RCC->APB2RSTR &= ~(1 << 2); }
    else if (pGPIOx == GPIOB) { RCC->APB2RSTR |= (1 << 3); RCC->APB2RSTR &= ~(1 << 3); }
    else if (pGPIOx == GPIOC) { RCC->APB2RSTR |= (1 << 4); RCC->APB2RSTR &= ~(1 << 4); }
    else if (pGPIOx == GPIOD) { RCC->APB2RSTR |= (1 << 5); RCC->APB2RSTR &= ~(1 << 5); }
    else if (pGPIOx == GPIOE) { RCC->APB2RSTR |= (1 << 6); RCC->APB2RSTR &= ~(1 << 6); }
}

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {
    return (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
}

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx) {
    return (uint16_t)(pGPIOx->IDR);
}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value) {
    if (Value == GPIO_PIN_SET) {
        pGPIOx->ODR |= (1 << PinNumber);
    } else {
        pGPIOx->ODR &= ~(1 << PinNumber);
    }
}

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value) {
    pGPIOx->ODR = Value;
}

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {
    pGPIOx->ODR ^= (1 << PinNumber);
}

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi) {
    if (EnorDi == ENABLE) {
        if (IRQNumber <= 31) {
            *NVIC_ISER0 |= (1 << IRQNumber);
        } else if (IRQNumber > 31 && IRQNumber < 64) {
            *NVIC_ISER1 |= (1 << (IRQNumber % 32));
        } else if (IRQNumber >= 64 && IRQNumber < 96) {
            *NVIC_ISER2 |= (1 << (IRQNumber % 32));
        }
    } else {
        if (IRQNumber <= 31) {
            *NVIC_ICER0 |= (1 << IRQNumber);
        } else if (IRQNumber > 31 && IRQNumber < 64) {
            *NVIC_ICER1 |= (1 << (IRQNumber % 32));
        } else if (IRQNumber >= 64 && IRQNumber < 96) {
            *NVIC_ICER2 |= (1 << (IRQNumber % 32));
        }
    }
}

void IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority) {
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_shift = IRQNumber % 4;

    // STM32 implements upper 4 bits of priority byte field
    uint32_t shift_amount = (iprx_shift * 8) + 4;

    volatile uint32_t *pNVIC_IPR = (volatile uint32_t *)NVIC_PR_BASE_ADDR;

    *(pNVIC_IPR + iprx) &= ~(0x0F << shift_amount);
    *(pNVIC_IPR + iprx) |= (IRQPriority << shift_amount);
}

void GPIO_IRQHandling(uint8_t PinNumber) {
    if (EXTI->PR & (1 << PinNumber)) {
        // Clear pending interrupt flag by writing 1
        EXTI->PR |= (1 << PinNumber);
    }
}
