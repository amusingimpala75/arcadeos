#include "arcadeos/system.h"
#include "arcadeos/terminal.h"
#include "limine.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"

static const char *msg = "Hello, World";

static volatile struct limine_memmap_request memmap = {
    .id = LIMINE_MEMMAP_REQUEST, .revision = 0};

static void as_binary(char buffer[64], uint64_t number) {
  for (uint64_t i = 0; i < 64; i++) {
    if ((~0b1 << i) & number)
      buffer[i] = '1';
    else
      buffer[i] = '0';
  }
}

// TODO: interrupts, filesystem, userspace elfs, graphics, etc.
void pre_kmain(void) {
  println(msg, strlen(msg));
  struct limine_memmap_response *resp = memmap.response;
  char buffer[64] = {0};
  if (resp == NULL) {
    halt();
  }
  println("Got memmap response", strlen("got memmap response"));
  void *ptr = NULL;
  size_t len = 0;
  for (uint64_t i = 0; i < resp->entry_count; i++) {
    if (resp->entries[i]->type != LIMINE_MEMMAP_USABLE)
      continue;
    if (resp->entries[i]->length > len) {
      len = resp->entries[i]->length;
      ptr = (void *)resp->entries[i]->base;
    }
  }
  if (ptr == NULL)
    halt();
  identity_map(ptr, len);
  initialize_malloc(ptr, len);

  println("initialized malloc", strlen("initialized malloc"));
  volatile char *str = malloc(strlen("Hello, ") + strlen("World!") + 1);
  str[0] = '\0';
  strcat(str, "Hello, ");
  strcat(str, "World!");
  println(str, strlen(str));
  free(str);
  while (1) {
    volatile void *ptr = malloc(256);
    volatile void *ptr2 = malloc(256);
    if (!ptr || !ptr2)
      break;
    free(ptr2);
    free(ptr);
    println("debug", 5);
  }
  // println("Exhausted heap", strlen("exhausted heap"));
  halt();
}
