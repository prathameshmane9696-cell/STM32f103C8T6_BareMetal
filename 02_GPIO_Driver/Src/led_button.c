/*
 * led_button.c
 * Polling GPIO Example: Toggles PA1 LED on PA2 button press
 */

#include "STM32F1xx_GPIO_Driver.h"
#include "STM32F103C8T6.h"

#define PRESSED 1

// Simple software delay loop for button debouncing
void delay(void) {
    for (volatile uint32_t i = 0; i < 300000; i++);
}

int main(void) {
    GPIO_Handle_t LED;
    GPIO_Handle_t BTN;

    /* ---- LED Setup (PA1 - Output Push-Pull) ---- */
    LED.pGPIOx = GPIOA;
    LED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
    LED.GPIO_PinConfig.GPIO_PinMode = GPIO_OP_PP;
    LED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_OP50;
    GPIO_Init(&LED);

    /* ---- Button Setup (PA2 - Input with Pull-Down) ---- */
    BTN.pGPIOx = GPIOA;
    BTN.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    BTN.GPIO_PinConfig.GPIO_PinMode = GPIO_PIN_IP;
    BTN.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_IN_PD; // Internal pull-down
    GPIO_Init(&BTN);

    /* ---- Main Event Loop ---- */
    while (1) {
        // Read input pin PA2
        if (GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_2) == PRESSED) {
            GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_1); // Toggle LED state
            delay(); // Debounce delay to prevent multiple triggers on a single press
        }
    }

    return 0;
}
