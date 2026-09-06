\# STM32F103 Bare-Metal Bootstrapping \& Build System



A bare-metal C project template for the STM32F103 (ARM Cortex-M3) microcontroller, developed from scratch without vendor HAL libraries or STM32CubeMX auto-generated code.



\## Key Technical Highlights



\* \*\*Custom Linker Script (`STM32\_LS.ld`):\*\* 

&#x20; \* Configures target memory regions (`FLASH` and `SRAM`).

&#x20; \* Maps memory sections (`.isr\_section`, `.text`, `.data`, `.bss`) with strict 4-byte boundary alignment.

&#x20; \* Explicitly defines section load addresses (`\_sidata`) and boundary symbols (`\_sdata`, `\_edata`, `\_sbss`, `\_ebss`).



\* \*\*Bare-Metal Startup Routine (`STM32\_startup.c`):\*\* 

&#x20; \* Constructs the ARM Cortex-M3 exception and interrupt vector table in C.

&#x20; \* Configures weak-aliased default interrupt handlers (`Default\_Handler`).

&#x20; \* Implements `reset\_handler` to manually relocate initialized global variables (`.data`) from Flash (LMA) to RAM (VMA) and zero-initialize uninitialized data (`.bss`).



\* \*\*Cross-Platform Toolchain Configuration (`Makefile`):\*\*

&#x20; \* Configured for `arm-none-eabi-gcc` with GNU11 standard and `-nostdlib` flags.

&#x20; \* Generates ELF binaries (`final.elf`) and memory allocation map logs (`final.map`).

&#x20; \* Includes OS auto-detection for cross-platform build cleanup on Windows and Linux systems.



\## Repository Structure



\* `main.c` – Minimal application entry point for build validation.

\* `STM32\_startup.c` – Vector table array and C startup sequence (`reset\_handler`).

\* `STM32\_LS.ld` – Linker script controlling memory placement and section boundary symbols.

\* `Makefile` – Custom build system orchestration file.

\* `final.map` – Linker-generated symbol map file showing absolute section allocation.



\## How to Build



1\. \*\*Compile \& Link:\*\*

&#x20;  ```bash

&#x20;  make

Clean Output Artifacts:



Bash

make clean

Requirements

ARM GNU Toolchain (arm-none-eabi-gcc)



GNU Make

