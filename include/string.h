#pragma once

#include "stddef.h"

char *strcpy(char *restrict dest, const char *restrict src);
// strcpy_s
char *strncpy(char *restrict dest, const char *restrict src, size_t count);
// strncpy_s
char *strcat(char *restrict dest, const char *restrict src);
// strcat_s
char *strncat(char *restrict dest, const char *restrict src, size_t count);
// strncat_s
size_t strxfrm(char *restrict dest, const char *restrict src, size_t count);
char *strdup(const char *src);
char *strndup(const char *src, size_t size);
size_t strlen(const char *str);
size_t strnlen_s(const char *str, size_t size);
int strcmp(const char *lhs, const char *rhs);
int strncmp(const char *lhs, const char *rhs, size_t count);
int strcoll(const char *lhs, const char *rhs);
char *strchr(const char *str, int ch);
char *strrchr(const char *str, int ch);
size_t strspn(const char *dest, const char *src);
char *strpbrk(const char *dest, const char *breakset);
char *strstr(const char *str, const char *substr);
char *strtok(char *restrict str, const char *restrict delim);
// strtok_c
void *memchr(const void *ptr, int ch, size_t count);
int memcmp(const void *lhs, const void *rhs, size_t count);
void *memset(void *dest, int ch, size_t count);
void *memset_explicit(void *dest, int ch, size_t count);
// memset_s
void *memcpy(void *restrict dest, const void *restrict src, size_t count);
// memcpy_s
void *memmove(void *dest, const void *src, size_t count);
// memmove_s
void *memccpy(void *restrict dest, const void *restrict src, int ch,
              size_t count);
char *strerror(int errnum);
// strerror_s
// strerrorlen_s
