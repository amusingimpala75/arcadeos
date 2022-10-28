#include "arcadeos/system.h"
#include "stdbool.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"

typedef struct memory_block {
  struct memory_block *local_prev; // only changed when block size changes
  struct memory_block *next_free;
  struct memory_block *prev_free;
  size_t len;
  bool has_next;
  bool free;
} memory_block_t;

static memory_block_t *freed = NULL;

static memory_block_t *next(memory_block_t *block) {
  return (memory_block_t *)(((uint8_t *)(block + 1)) + block->len);
}

static memory_block_t *block_at_addr(void *ptr) {
  return ((memory_block_t *)ptr) - 1;
}

static void *base;
static size_t size;

static bool is_managed(void *ptr) {
  return ptr >= base && ((uint64_t)ptr) <= ((uint64_t)base) + size;
}

void initialize_malloc(void *ptr, size_t len) {
  freed = ptr;
  freed->local_prev = NULL;
  freed->has_next = false;
  freed->len = len;
  freed->free = true;
  freed->next_free = NULL;
  freed->prev_free = NULL;
  base = ptr;
  size = len;
}

void *malloc(size_t size) {
  if (size == 0)
    return NULL; // malformed request
  if (freed == NULL)
    return NULL; // out of memory
  memory_block_t *block = freed;
  while (block->len != size && block->len < size + sizeof(memory_block_t)) {
    if (!block->has_next)
      return NULL; // no spaces availiable, no merging to do as that is done
                   // elsewhere
    block = next(block);
  }
  // current block is large enough
  size_t new_size = block->len - size - sizeof(memory_block_t);
  block->len = size;

  // setup new block
  memory_block_t *new = next(block);
  new->has_next = block->has_next;
  new->len = new_size;
  new->local_prev = block;
  new->free = true;
  new->prev_free = NULL;

  block->has_next = true;
  block->free = false;
  if (block == freed) {
    new->next_free = freed->next_free;
    freed = new;
  }
  if (block->next_free != NULL)
    block->next_free->prev_free = new;
  if (block->prev_free != NULL)
    block->prev_free->next_free = new;
  return ((memory_block_t *)block + 1);
}

void *calloc(size_t num, size_t size) {
  void *ptr = malloc(num * size);
  if (ptr == NULL)
    return NULL;
  memset(ptr, '\0', num * size);
  return ptr;
}

void *realloc(void *ptr, size_t size) {
  if (ptr == NULL)
    return malloc(size);
  else if (!is_managed(ptr))
    return NULL;
  else if (size == 0) {
    free(ptr);
    return NULL;
  }
  size_t required = size - block_at_addr(ptr)->len;
  size_t available = next(block_at_addr(ptr))->len + sizeof(memory_block_t);
  if (required == available || required + sizeof(memory_block_t) <= available) {
    // TODO: expand allocation
  }
  void *new = malloc(size);
  if (new == NULL)
    return NULL;
  memcpy(new, ptr, block_at_addr(ptr)->len);
  return new;
}

void free(void *ptr) {
  if (!is_managed(ptr))
    return;
  memory_block_t *block = block_at_addr(ptr);
  block->free = true;
  block->next_free = freed;
  block->next_free->prev_free = block;
  block->prev_free = NULL;
  freed = block;

  if (block->has_next && next(block)->free) {
    memory_block_t *next_block = next(block);
    if (next_block->prev_free != NULL)
      next_block->prev_free->next_free = next_block->next_free;
    if (next_block->next_free != NULL)
      next_block->next_free->prev_free = next_block->prev_free;
    block->len += sizeof(memory_block_t) + next_block->len;
    if (block->next_free == next_block) {
      block->next_free = next_block->next_free;
      if (next_block->next_free != NULL)
        next_block->next_free->prev_free = block;
    }
  }
  if (block->local_prev != NULL && block->local_prev->free) {
    block->local_prev->len += block->len + sizeof(memory_block_t);
    if (block->prev_free != NULL)
      block->prev_free->next_free = block->next_free;
    if (block->next_free != NULL)
      block->next_free->prev_free = block->prev_free;
    if (block->local_prev->next_free == block)
      block->local_prev->next_free = block->next_free;
  }
}

void free_sized(void *ptr, size_t size) { free(ptr); }
