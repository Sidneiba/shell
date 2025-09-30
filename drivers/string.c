// drivers/string.c
#include <string.h>
#include <stddef.h>

char *strchr(const char *s, int c) {
    while (*s != (char)c) {
        if (*s == '\0') return NULL;
        s++;
    }
    return (char *)s;
}

char *strtok(char *str, const char *delim) {
    static char *next = NULL;
    char *start;

    if (str) next = str;
    if (!next) return NULL;

    while (*next && strchr(delim, *next)) next++;
    start = next;
    if (*next == '\0') {
        next = NULL;
        return start;
    }

    while (*next && !strchr(delim, *next)) next++;
    if (*next) {
        *next = '\0';
        next++;
    } else {
        next = NULL;
    }
    return start;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    while (n && *s1 && (*s1 == *s2)) {
        s1++;
        s2++;
        n--;
    }
    if (n == 0) return 0;
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

size_t strlen(const char *s) {
    size_t len = 0;
    while (*s++) len++;
    return len;
}

char *strncpy(char *dest, const char *src, size_t n) {
    size_t i;
    for (i = 0; i < n && src[i]; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return dest;
}

void *memset(void *s, int c, size_t n) {
    unsigned char *p = (unsigned char *)s;
    while (n--) {
        *p++ = (unsigned char)c;
    }
    return s;
}

char *strncat(char *dest, const char *src, size_t n) {
    size_t dest_len = strlen(dest);
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + i] = '\0';
    return dest;
}
