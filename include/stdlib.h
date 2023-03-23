#pragma once

// TODO

#include "stddef.h"

#define MALLOC(type) ((type)malloc(sizeof(type)))
#define MALLOC_A(type, count) ((type *)malloc(sizeof(type) * (count)))

#define FREE(ptr)                                                              \
  do {                                                                         \
    free(ptr);                                                                 \
    ptr = NULL;                                                                \
  } while (0)

void *malloc(size_t size);
void *calloc(size_t num, size_t size);
void *realloc(void *ptr, size_t new_size);
void free(void *ptr);
void free_sized(void *ptr, size_t size);
void free_aligned_sized(void *ptr, size_t alignement, size_t size);
void *aligned_alloc(size_t alignment, size_t size);
