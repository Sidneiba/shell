// drivers/uart.c
#include "../include/uart.h"

#define UART0_BASE 0x09000000
#define UART0_DR   (UART0_BASE + 0x00) // Data Register
#define UART0_FR   (UART0_BASE + 0x18) // Flag Register

#define UART_FR_TXFF (1 << 5) // TX FIFO full
#define UART_FR_RXFE (1 << 4) // RX FIFO empty

void uart_init(void) {
    // No QEMU, UART geralmente já vem configurada
}

void uart_putc(char c) {
    while (*(volatile unsigned int *)UART0_FR & UART_FR_TXFF) {
        ; // Espera até haver espaço no FIFO de transmissão
    }
    *(volatile char *)UART0_DR = c;
}

void uart_puts(const char *s) {
    while (*s) {
        uart_putc(*s++);
    }
}

char uart_getc(void) {
    while (*(volatile unsigned int *)UART0_FR & UART_FR_RXFE) {
        ; // Espera até ter dados no FIFO de recepção
    }
    return *(volatile char *)UART0_DR;
}
