// kernel/shell.c
#include "../include/console.h"
#include "../include/uart.h"
#include "../include/shell.h"
#include <string.h>
#include <stddef.h>

#define MAX_INPUT 128
#define MAX_ARGS  8
#define MAX_HISTORY 10

static char history[MAX_HISTORY][MAX_INPUT];
static int history_count = 0;
static int history_pos = -1;

static int parse_command(char *input, char *argv[], int max_args) {
    int argc = 0;
    char *token = strtok(input, " ");
    while (token && argc < max_args - 1) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    argv[argc] = NULL;
    return argc;
}

static void shell_execute(int argc, char *argv[]) {
    if (argc == 0) return;

    if (argc > 0 && history_count < MAX_HISTORY) {
        char cmd[MAX_INPUT];
        memset(cmd, 0, MAX_INPUT);
        for (int i = 0; i < argc; i++) {
            strncat(cmd, argv[i], MAX_INPUT - strlen(cmd) - 1);
            strncat(cmd, " ", MAX_INPUT - strlen(cmd) - 1);
        }
        strncpy(history[history_count], cmd, MAX_INPUT - 1);
        history[history_count][MAX_INPUT - 1] = '\0';
        history_count++;
        history_pos = history_count;
    }

    if (strcmp(argv[0], "help") == 0) {
        console_write("Comandos disponiveis:\n");
        console_write(" help      - mostra esta mensagem\n");
        console_write(" clear     - limpa a tela\n");
        console_write(" echo ...  - repete o texto\n");
        console_write(" ls        - lista arquivos (fake)\n");
        console_write(" cat <arq> - mostra conteudo (fake)\n");
        console_write(" reboot    - reinicia (placeholder)\n");
        console_write(" edit      - editor simples (Ctrl+D para sair)\n");
        console_write(" save      - salvar estado (nao implementado)\n");
        console_write(" set       - configurar (nao implementado)\n");
        console_write(" show      - exibir (nao implementado)\n");
    }
    else if (strcmp(argv[0], "clear") == 0) {
        console_write("\033[2J\033[H");
    }
    else if (strcmp(argv[0], "echo") == 0) {
        for (int i = 1; i < argc; i++) {
            console_write(argv[i]);
            console_write(" ");
        }
        console_write("\n");
    }
    else if (strcmp(argv[0], "ls") == 0) {
        console_write("Arquivos simulados:\n");
        console_write(" boot.cfg\n kernel.img\n hello.txt\n");
    }
    else if (strcmp(argv[0], "cat") == 0) {
        if (argc < 2) {
            console_write("Uso: cat <arquivo>\n");
        } else if (strcmp(argv[1], "hello.txt") == 0) {
            console_write("Conteudo de hello.txt:\n");
            console_write("Ola, mundo do kernel!\n");
        } else {
            console_write("Arquivo nao encontrado: ");
            console_write(argv[1]);
            console_write("\n");
        }
    }
    else if (strcmp(argv[0], "reboot") == 0) {
        console_write("Reiniciando (nao implementado)...\n");
    }
    else if (strcmp(argv[0], "edit") == 0) {
        console_write("Editor simples (digite texto, Ctrl+D para sair):\n");
        char buffer[MAX_INPUT];
        int pos = 0;
        while (1) {
            char c = uart_getc();
            if (c == 4) { // Ctrl+D
                buffer[pos] = '\0';
                console_write("\nTexto digitado: ");
                console_write(buffer);
                console_write("\n");
                break;
            } else if (c == 127 || c == '\b') {
                if (pos > 0) {
                    pos--;
                    console_write("\b \b");
                    buffer[pos] = '\0';
                }
            } else if (pos < MAX_INPUT - 1) {
                buffer[pos++] = c;
                console_putc(c);
            }
        }
    }
    else if (strcmp(argv[0], "save") == 0) {
        console_write("Salvando estado (nao implementado)...\n");
    }
    else if (strcmp(argv[0], "set") == 0) {
        console_write("Configurando (nao implementado)...\n");
    }
    else if (strcmp(argv[0], "show") == 0) {
        console_write("Exibindo (nao implementado)...\n");
    }
    else {
        console_write("Comando nao reconhecido: ");
        console_write(argv[0]);
        console_write("\n");
    }
}

void shell_loop(void) {
    char input[MAX_INPUT];
    char *argv[MAX_ARGS];
    int pos = 0;
    int cursor_pos = 0;

    console_write("Bem-vindo ao Shell++!\n");
    console_write("> ");

    while (1) {
        char c = uart_getc();

        if (c == '\r' || c == '\n') {
            input[pos] = '\0';
            console_write("\n");

            int argc = parse_command(input, argv, MAX_ARGS);
            shell_execute(argc, argv);

            pos = 0;
            cursor_pos = 0;
            input[0] = '\0';
            console_write("> ");
        }
        else if (c == 127 || c == '\b') {
            if (pos > 0 && cursor_pos > 0) {
                pos--;
                cursor_pos--;
                for (int i = cursor_pos; i < pos; i++) {
                    input[i] = input[i + 1];
                }
                input[pos] = '\0';
                console_write("\b \b");
                console_write(&input[cursor_pos]);
                for (int i = cursor_pos; i < pos; i++) {
                    console_write("\b");
                }
            }
        }
        else if (c == '\033') {
            char seq[2];
            seq[0] = uart_getc();
            seq[1] = uart_getc();

            if (seq[0] == '[') {
                if (seq[1] == 'A' && history_pos > 0) {
                    history_pos--;
                    while (pos > 0) {
                        console_write("\b \b");
                        pos--;
                    }
                    cursor_pos = 0;
                    strncpy(input, history[history_pos], MAX_INPUT - 1);
                    input[MAX_INPUT - 1] = '\0';
                    pos = strlen(input);
                    cursor_pos = pos;
                    console_write(input);
                } else if (seq[1] == 'B' && history_pos < history_count - 1) {
                    history_pos++;
                    while (pos > 0) {
                        console_write("\b \b");
                        pos--;
                    }
                    cursor_pos = 0;
                    strncpy(input, history[history_pos], MAX_INPUT - 1);
                    input[MAX_INPUT - 1] = '\0';
                    pos = strlen(input);
                    cursor_pos = pos;
                    console_write(input);
                } else if (seq[1] == 'C' && cursor_pos < pos) {
                    console_putc(input[cursor_pos]);
                    cursor_pos++;
                } else if (seq[1] == 'D' && cursor_pos > 0) {
                    console_write("\b");
                    cursor_pos--;
                }
            }
        }
        else {
            if (pos < MAX_INPUT - 1 && cursor_pos <= pos) {
                for (int i = pos; i > cursor_pos; i--) {
                    input[i] = input[i - 1];
                }
                input[cursor_pos] = c;
                pos++;
                cursor_pos++;
                input[pos] = '\0';
                console_write(&input[cursor_pos - 1]);
                for (int i = cursor_pos; i < pos; i++) {
                    console_write("\b");
                }
            }
        }
    }
}
