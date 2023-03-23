#pragma once

#include "stddef.h"
#include "stdint.h"

size_t framebuffer_width(void);
size_t framebuffer_height(void);
void put_pixel(const uint64_t x, const uint64_t y, const uint32_t color);
uint32_t get_pixel(const uint64_t x, const uint64_t y);

void swap_buffer(void);
void write_to_screen(void);

void initialize_framebuffer(void);
