.section .text
.global _start

_start:
    // Configurar a pilha (stack pointer)
    mov sp, #0x80000
    bl kernel_main
infinite_loop:
    b infinite_loop
