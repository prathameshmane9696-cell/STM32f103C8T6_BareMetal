# STM32F103 Bare-Metal Bootstrapping & Build System

A bare-metal C project template for the STM32F103 (ARM Cortex-M3) microcontroller, developed completely from scratch without vendor HAL libraries or STM32CubeMX auto-generated code.

---

## Key Technical Highlights

* **Custom Linker Script (`STM32_LS.ld`):** 
  * Configures target memory regions (`FLASH` and `SRAM`).
  * Maps memory sections (`.text`, `.data`, `.bss`) with strict 4-byte boundary alignment.
  * Explicitly defines section load addresses (`_sidata`) and boundary symbols (`_sdata`, `_edata`, `_sbss`, `_ebss`).

* **Bare-Metal Startup Routine (`STM32_startup.c`):** 
  * Constructs the ARM Cortex-M3 exception and peripheral interrupt vector table in C.
  * Configures weak-aliased default interrupt handlers (`Default_Handler`).
  * Implements `reset_handler` to manually relocate initialized global variables (`.data`) from Flash (LMA) to RAM (VMA) and zero-initialize uninitialized data (`.bss`).

* **Cross-Platform Toolchain Configuration (`Makefile`):**
  * Configured for `arm-none-eabi-gcc` with GNU11 standard and `-nostdlib` flags.
  * Generates ELF binaries (`final.elf`) and memory allocation map logs (`final.map`).
  * Includes OS auto-detection for cross-platform build cleanup on Windows and Linux systems.

---

## Repository Structure

* `main.c` – Application entry point for build validation.
* `STM32_startup.c` – Exception vector table array and C startup sequence (`reset_handler`).
* `STM32_LS.ld` – Linker script controlling memory placement and section boundary symbols.
* `Makefile` – Custom build system orchestration file.
* `final.map` – Linker-generated symbol map file showing absolute section allocation.

---

## How to Build

1. **Compile & Link:**
   ```bash
   make
