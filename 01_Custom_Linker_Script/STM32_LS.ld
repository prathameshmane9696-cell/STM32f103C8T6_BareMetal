ENTRY(reset_handler) 

MEMORY {
    FLASH(rx)  : ORIGIN = 0x08000000, LENGTH = 64K  
    SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS {
    .text : {
        . = ALIGN(4);
        *(.isr_section)    
        *(.text)
        *(.text*)          /*  Wildcard: Captures minor code sub-blocks safely */
        *(.rodata)
        *(.rodata*)        /*  Wildcard: Captures long strings/constants safely */
        . = ALIGN(4);
        _etext = . ;  
    } > FLASH

    .data : {
        . = ALIGN(4);
        _sdata = . ;
        *(.data)
        *(.data*)          /* Wildcard: Captures global sub-variables safely */
        . = ALIGN(4);
        _edata = . ;
    } > SRAM AT> FLASH

    _sidata = LOADADDR(.data);

    .bss : {
        . = ALIGN(4);
        _sbss = . ;
        *(.bss)
        *(.bss*)           /*  Wildcard: Captures uninitialized sub-spaces safely */
        *(COMMON)
        . = ALIGN(4);
        _ebss = . ;
    } > SRAM
}
