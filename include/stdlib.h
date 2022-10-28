#pragma once

#include "stddef.h"

void *malloc(size_t size);
void *calloc(size_t num, size_t size);
void *realloc(void *ptr, size_t new_size);
void free(void *ptr);
void free_sized(void *ptr, size_t size);
void free_aligned_sized(void *ptr, size_t alignement, size_t size);
void *aligned_alloc(size_t alignment, size_t size);
