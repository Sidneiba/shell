// include/buffer.h
#ifndef BUFFER_H
#define BUFFER_H

void buffer_init(void);
void buffer_write(char *buf, int size);
char buffer_read(void);

#endif
