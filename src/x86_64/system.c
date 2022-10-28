#ifdef __x86_64__

#include "arcadeos/system.h"

void halt(void) {
  for (;;) {
    __asm__("hlt");
  }
}

static void map_page(void *addr, void *vaddr, uint8_t flags) {
  uint64_t pdindex = ((uint64_t)vaddr) >> 27;
  uint64_t ptindex = ((uint64_t)vaddr) >> 12 & 0x03ff;
  uint64_t *pd = (uint64_t *)0xfffff000;
  uint64_t *pt = ((uint64_t *)0xffc00000) + (0x400 * pdindex);
  pt[ptindex] = ((uint64_t)addr | (flags & 0xfff) | 0x01);
}

void identity_map(void *ptr, size_t len) {
  for (; len > 0; len -= 4096, ptr += 4096) {
    map_page(ptr, ptr, 0b110);
  }
}

#endif
