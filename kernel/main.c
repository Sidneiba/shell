// kernel/main.c
#include "../include/console.h"
#include "../include/uart.h"
#include "../include/shell.h"

void kernel_main(void) {
    uart_init();
    console_init();
    shell_loop();
}
