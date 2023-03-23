#include "string.h"
#include "stdint.h"
#include "stdlib.h"
// TODO: add tests

char *strcpy(char *restrict dest, const char *restrict src) {
  char *ret = dest;
  while (*src != '\0') {
    *(dest++) = *(src++);
  }
  *dest = '\0';
  return ret;
}

char *strncpy(char *restrict dest, const char *restrict src, size_t count) {
  size_t index = 0;
  while (src[index] != '\0' && index < count) {
    dest[index] = src[index];
    index++;
  }
  if (index < count) {
    dest[index] = '\0';
  }
  return dest;
}

char *strcat(char *restrict dest, const char *restrict src) {
  char *ret = dest;
  while (*dest != '\0')
    dest++;
  *(dest) = 'a'; // make non-null
  strcpy(dest, src);
  return ret;
}

char *strncat(char *restrict dest, const char *restrict src, size_t count) {
  char *ret = dest;
  while (*dest != '\0')
    dest++;
  *(dest) = 'a';
  strncpy(dest, src, count);
  return ret;
}

char *strdup(const char *src) {
  char *ret = MALLOC_A(char, strlen(src) + 1);
  if (ret == NULL)
    return NULL;
  return strcpy(ret, src);
}

size_t strlen(const char *string) {
  size_t length = 0;
  while (string[length++] != '\0')
    ;
  return length - 1;
}

size_t strnlen_s(const char *src, size_t size) {
  size_t length = 0;
  while (src[length++] != '\0' && length <= size)
    ;
  return length;
}

int strcmp(const char *lhs, const char *rhs) {
  while (*lhs == *rhs && *lhs != NULL) {
    lhs++;
    rhs++;
  }
  return *lhs - *rhs;
}

int strncmp(const char *lhs, const char *rhs, size_t count) {
  size_t index = 0;
  while (*lhs == *rhs && *lhs != NULL && index < count) {
    lhs++;
    rhs++;
    index++;
  }
  return *lhs - *rhs;
}

int memcmp(const void *lhs, const void *rhs, size_t count) {
  while (*((uint8_t *)lhs) == *((uint8_t *)rhs) && count > 0) {
    lhs++;
    rhs++;
    count--;
  }
  if (count == 0)
    return 0;
  return *((uint8_t *)lhs) - *((uint8_t *)rhs);
}

void *memset(void *dest, int ch, size_t count) {
  uint8_t *ptr = (uint8_t *)dest;
  while (count-- > 0) {
    *(ptr++) = (uint8_t)ch;
  }
  return dest;
}

void *memcpy(void *restrict dest, const void *restrict src, size_t count) {
  void *ret = dest;
  while (count-- > 0) {
    *((uint8_t *)dest++) = *((uint8_t *)src++);
  }
  return ret;
}
