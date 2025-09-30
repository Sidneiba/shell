#include "../include/shell.h"
#include "../include/uart.h"  // Ajuste o caminho se necessário

void shell_loop(void) {
    uart_puts("Bem-vindo ao shell!\n");
    while (1) {
        uart_puts("> ");
        char input[256] = {0};
        int i = 0;
        char c;
        while ((c = uart_getc()) != '\n' && i < 255) {
            input[i++] = c;
            uart_putc(c);
        }
        uart_puts("\n");
        uart_puts("Voce digitou: ");
        uart_puts(input);
        uart_puts("\n");
    }
}
