#ifndef IO_H
#define IO_H

void console_init(void);
void console_write(const char *str);
void console_write_char(char c);
char console_read(void);

#endif
