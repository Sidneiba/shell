/* linker.ld */
ENTRY(_start)

SECTIONS {
    . = 0x80000; /* Endereço inicial para Raspberry Pi 3 no QEMU */
    .text : {
        *(.text)
    }
    .rodata : {
        *(.rodata)
    }
    .data : {
        *(.data)
    }
    .bss : {
        *(.bss)
    }
    . = ALIGN(8);
}
