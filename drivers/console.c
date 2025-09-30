// drivers/console.c
#include "../include/console.h"
#include "../include/uart.h"

void console_init(void) {
    uart_init(); // Inicializa UART
}

void console_putc(char c) {
    uart_putc(c); // Escreve caractere na UART
}

void console_write(const char *str) {
    while (*str) {
        console_putc(*str++);
    }
}
