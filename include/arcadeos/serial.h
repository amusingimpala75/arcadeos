#pragma once

#include "stddef.h"
#include "stdint.h"

void serial_write_string(const char *, size_t len);
int init_serial(void);

#ifdef __x86_64__
inline void outb(const uint16_t port, const uint8_t val) {
  __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}
inline uint8_t inb(const uint16_t port) {
  uint8_t ret;
  __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}
#endif
