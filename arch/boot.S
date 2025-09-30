// arch/boot.S
.section .text
.global _start

_start:
    // Configurar stack pointer
    ldr     x0, =0x100000  // Ajustado para 1MB após 0x80000
    mov     sp, x0

    // Chamar kernel_main
    bl      kernel_main

    // Loop infinito caso kernel_main retorne
hang:
    wfe
    b       hang
