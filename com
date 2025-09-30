#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>

void buffer_init(void);
int buffer_get(char *c);
void buffer_put(char c);

#endif
