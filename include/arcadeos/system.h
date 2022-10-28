#pragma once

#include "stddef.h"

void halt(void);
void initialize_malloc(void *base, size_t size);
void identity_map(void *ptr, size_t size);
