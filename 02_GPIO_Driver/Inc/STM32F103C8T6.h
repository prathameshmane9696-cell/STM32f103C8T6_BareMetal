/*
 * STM32F103C8T6.h
 * Device Header File - Register Definitions & Base Addresses
 */

#ifndef INC_STM32F103C8T6_H_
#define INC_STM32F103C8T6_H_

#include <stdint.h>

#define __vo volatile

/******************************************************************************/
/*                        Processor Core Specifics (NVIC)                      */
/******************************************************************************/

/* ARM Cortex-M3 NVIC Interrupt Set-Enable Registers */
#define NVIC_ISER0          ((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1          ((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2          ((__vo uint32_t*)0xE000E108)

/* ARM Cortex-M3 NVIC Interrupt Clear-Enable Registers */
#define NVIC_ICER0          ((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1          ((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2          ((__vo uint32_t*)0xE000E188)

/* Priority Register Base Address */
#define NVIC_PR_BASE_ADDR   ((__vo uint32_t*)0xE000E400)

/* NVIC EXTI Position Definitions */
#define IRQ_NO_EXTI0        6
#define IRQ_NO_EXTI1        7
#define IRQ_NO_EXTI2        8
#define IRQ_NO_EXTI3        9
#define IRQ_NO_EXTI4        10
#define IRQ_NO_EXTI9_5      23
#define IRQ_NO_EXTI15_10    40

/******************************************************************************/
/*                         Memory Map Base Addresses                          */
/******************************************************************************/

#define FLASH_BASEADDR      0x08000000U
#define SRAM_BASEADDR       0x20000000U

#define PERIPH_BASEADDR     0x40000000U
#define APB1_BASEADDR       PERIPH_BASEADDR
#define APB2_BASEADDR       (PERIPH_BASEADDR + 0x00010000U)
#define AHB_BASEADDR        (PERIPH_BASEADDR + 0x00020000U)

#define RCC_BASEADDR        (AHB_BASEADDR + 0x1000U)

/* APB2 Peripherals */
#define AFIO_BASEADDR       (APB2_BASEADDR + 0x0000U)
#define EXTI_BASEADDR       (APB2_BASEADDR + 0x0400U)
#define GPIOA_BASEADDR      (APB2_BASEADDR + 0x0800U)
#define GPIOB_BASEADDR      (APB2_BASEADDR + 0x0C00U)
#define GPIOC_BASEADDR      (APB2_BASEADDR + 0x1000U)
#define GPIOD_BASEADDR      (APB2_BASEADDR + 0x1400U)
#define GPIOE_BASEADDR      (APB2_BASEADDR + 0x1800U)

/******************************************************************************/
/*                       Peripheral Register Structures                        */
/******************************************************************************/

typedef struct {
    volatile uint32_t CRL;   /* 0x00: Config Low  (Pins 0..7)  */
    volatile uint32_t CRH;   /* 0x04: Config High (Pins 8..15) */
    volatile uint32_t IDR;   /* 0x08: Input Data Register      */
    volatile uint32_t ODR;   /* 0x0C: Output Data Register     */
    volatile uint32_t BSRR;  /* 0x10: Bit Set/Reset Register   */
    volatile uint32_t BRR;   /* 0x14: Bit Reset Register       */
    volatile uint32_t LCKR;  /* 0x18: Port Lock Register       */
} GPIO_RegDef_t;

typedef struct {
    volatile uint32_t EVCR;       /* 0x00: Event Control Register         */
    volatile uint32_t MAPR;       /* 0x04: AF Remap & Debug Config        */
    volatile uint32_t EXTICR[4]; /* 0x08 - 0x14: EXTI Configuration Regs */
    volatile uint32_t MAPR2;      /* 0x1C: AF Remap Register 2            */
} AFIO_RegDef_t;

typedef struct {
    volatile uint32_t CR;         /* 0x00: Clock Control Register        */
    volatile uint32_t CFGR;       /* 0x04: Clock Config Register         */
    volatile uint32_t CIR;        /* 0x08: Clock Interrupt Register      */
    volatile uint32_t APB2RSTR;   /* 0x0C: APB2 Reset Register           */
    volatile uint32_t APB1RSTR;   /* 0x10: APB1 Reset Register           */
    volatile uint32_t AHBENR;     /* 0x14: AHB Clock Enable Register     */
    volatile uint32_t APB2ENR;    /* 0x18: APB2 Clock Enable Register    */
    volatile uint32_t APB1ENR;    /* 0x1C: APB1 Clock Enable Register    */
    volatile uint32_t BDCR;       /* 0x20: Backup Domain Control         */
    volatile uint32_t CSR;        /* 0x24: Control/Status Register       */
} RCC_RegDef_t;

typedef struct {
    volatile uint32_t IMR;   /* 0x00: Interrupt Mask Register */
    volatile uint32_t EMR;   /* 0x04: Event Mask Register     */
    volatile uint32_t RTSR;  /* 0x08: Rising Trigger Register */
    volatile uint32_t FTSR;  /* 0x0C: Falling Trigger Reg     */
    volatile uint32_t SWIER; /* 0x10: Software Interrupt Reg  */
    volatile uint32_t PR;    /* 0x14: Pending Register        */
} EXTI_RegDef_t;

/******************************************************************************/
/*                        Peripheral Base Pointer Macros                       */
/******************************************************************************/

#define GPIOA   ((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB   ((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC   ((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD   ((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE   ((GPIO_RegDef_t *)GPIOE_BASEADDR)

#define RCC     ((RCC_RegDef_t *)RCC_BASEADDR)
#define AFIO    ((AFIO_RegDef_t *)AFIO_BASEADDR)
#define EXTI    ((EXTI_RegDef_t *)EXTI_BASEADDR)

/******************************************************************************/
/*                           Clock Enable Macros                              */
/******************************************************************************/

#define GPIOA_PCLK_EN() (RCC->APB2ENR |= (1 << 2))
#define GPIOB_PCLK_EN() (RCC->APB2ENR |= (1 << 3))
#define GPIOC_PCLK_EN() (RCC->APB2ENR |= (1 << 4))
#define GPIOD_PCLK_EN() (RCC->APB2ENR |= (1 << 5))
#define GPIOE_PCLK_EN() (RCC->APB2ENR |= (1 << 6))

#define GPIOA_PCLK_DI() (RCC->APB2ENR &= ~(1 << 2))
#define GPIOB_PCLK_DI() (RCC->APB2ENR &= ~(1 << 3))
#define GPIOC_PCLK_DI() (RCC->APB2ENR &= ~(1 << 4))
#define GPIOD_PCLK_DI() (RCC->APB2ENR &= ~(1 << 5))
#define GPIOE_PCLK_DI() (RCC->APB2ENR &= ~(1 << 6))

#define AFIO_PCLK_EN()  (RCC->APB2ENR |= (1 << 0))

#define ENABLE   1
#define DISABLE  0
#define SET      ENABLE
#define RESET    DISABLE
#define GPIO_PIN_SET   SET
#define GPIO_PIN_RESET RESET

#endif /* INC_STM32F103C8T6_H_ */
