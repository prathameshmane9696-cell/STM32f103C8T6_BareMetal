/*
 * led_toggle.c
 * Target: STM32F103C8T6 (Blue Pill)
 * Description: Toggle Onboard LED on PC13
 */

#include "STM32F103C8T6.h"
#include "STM32F1xx_GPIO_Driver.h"

// Simple Software Delay Loop
void delay(void)
{
    for (volatile uint32_t i = 0; i < 300000; i++);
}

int main(void)
{
    GPIO_Handle_t GpioLed;

    // Configure PC13 for Onboard LED
    GpioLed.pGPIOx = GPIOC;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;   // Corrected to Pin 13
    GpioLed.GPIO_PinConfig.GPIO_PinMode   = GPIO_OP_PP;       // Corrected to Push-Pull
    GpioLed.GPIO_PinConfig.GPIO_PinSpeed  = GPIO_PIN_OP10;    // Output Speed 2MHz/10MHz
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_IN_FL;  // Floating/No-pull for output

    // Initialize Port C Pin 13
    GPIO_Init(&GpioLed);

    while (1)
    {
        GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_NO_13);          // Corrected to Pin 13
        delay();
    }

    return 0;
}
