/*
 * main.c
 * LED Toggle using EXTI0 Interrupt on STM32F103C8T6
 */

#include "STM32F1xx_GPIO_Driver.h"
#include "STM32F103C8T6.h"

// Software delay for simple switch debouncing
void delay(void)
{
    for (volatile uint32_t i = 0; i < 300000; i++);
}

/**
 * @brief  Interrupt Service Routine for EXTI Line 0 (Pin 0)
 */
void EXTI0_IRQHandler(void)
{
    // Clear pending flag on Pin 0 so we don't re-trigger continuously
    GPIO_IRQHandling(GPIO_PIN_NO_0);

    // Debounce delay
    delay();

    // Toggle LED on PA1
    GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_1);
}

int main(void)
{
    GPIO_Handle_t LED;
    GPIO_Handle_t BTN;

    /* ---- LED Setup (PA1 Output) ---- */
    LED.pGPIOx = GPIOA;
    LED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
    LED.GPIO_PinConfig.GPIO_PinMode   = GPIO_OP_PP;     // Push-Pull Output
    LED.GPIO_PinConfig.GPIO_PinSpeed  = GPIO_PIN_OP50;  // 50 MHz Speed

    GPIO_Init(&LED);

    /* ---- Button Setup (PA0 EXTI Input) ---- */
    BTN.pGPIOx = GPIOA;
    BTN.GPIO_PinConfig.GPIO_PinNumber     = GPIO_PIN_NO_0;
    BTN.GPIO_PinConfig.GPIO_PinMode       = GPIO_PIN_IP_RT; // Rising Edge Interrupt
    BTN.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_IN_PD;     // Internal Pull-Down

    GPIO_Init(&BTN);

    /* ---- NVIC Setup ---- */
    // Enable EXTI0 line in NVIC
    GPIO_IRQInterruptConfig(IRQ_NO_EXTI0, ENABLE);

    // Set interrupt priority
    IRQPriorityConfig(IRQ_NO_EXTI0, 15);

    while (1)
    {
        // Event handling driven entirely by ISR
    }

    return 0;
}
