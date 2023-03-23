#include "arcadeos/framebuffer.h"

#include "arcadeos/smp.h"
#include "arcadeos/terminal.h"
#include "limine.h"

#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

static volatile struct limine_framebuffer_request request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST, .revision = 1};

static struct limine_framebuffer *framebuffer = NULL;
static bool loaded = false;

// automate copying of ready buffer with interrupts
bool need_to_copy = false; // set true when buffers swapped, false when
// copied to screen
static uint32_t *fb_ready = NULL;
static uint32_t *fb_writing = NULL;

void initialize_framebuffer(void) {
  printf("======== Initializing Framebuffer ========\n");
  struct limine_framebuffer_response *resp = request.response;
  if (resp == NULL || resp->framebuffer_count < 1) {
    printf("Could not load framebuffer\n");
    return;
  }
  framebuffer = resp->framebuffers[0];
  const size_t fb_size =
      framebuffer->bpp / 8 * framebuffer->height * framebuffer->width;

  if (!(fb_ready = malloc(fb_size)) || !(fb_writing = malloc(fb_size)))
    return;

  loaded = true;
  printf("Framebuffer Height: %llu\n", framebuffer->height);
  printf("Framebuffer Width: %llu\n", framebuffer->width);
  printf("======== Framebuffer Initialized ========\n\n");
}

static mutex_t mut_internal;
static mutex_t mut_visible;

void swap_buffer(void) {
  if (!loaded)
    return;
  acquire_mutex(&mut_internal);
  uint32_t *t = fb_ready;
  fb_ready = fb_writing;
  fb_writing = t;
  release_mutex(&mut_internal);

  acquire_mutex(&mut_visible);
  need_to_copy = true;
  release_mutex(&mut_visible);
}

void write_to_screen(void) {
  if (!need_to_copy || !loaded)
    return;
  acquire_mutex(&mut_visible);
  for (uint64_t y = 0; y < framebuffer->height; y++) {
    for (uint64_t x = 0; x < framebuffer->width; x++) {
      ptrdiff_t diff = y * framebuffer->pitch + x * framebuffer->bpp / 8;
      *(uint32_t *)(framebuffer->address + diff) = *(fb_ready + diff);
    }
  }
  need_to_copy = false;
  release_mutex(&mut_visible);
}

size_t framebuffer_width(void) {
  if (!loaded)
    return 0;
  return framebuffer->width;
}

size_t framebuffer_height(void) {
  if (!loaded)
    return 0;
  return framebuffer->height;
}

void put_pixel(const uint64_t x, const uint64_t y, const uint32_t color) {
  if (!loaded)
    return;
  uint32_t *pixel =
      fb_ready + y * framebuffer->pitch + x * framebuffer->bpp / 8;
  acquire_mutex(&mut_internal);
  *pixel = color;
  release_mutex(&mut_internal);
}

uint32_t get_pixel(const uint64_t x, const uint64_t y) {
  if (!loaded)
    return 0;
  acquire_mutex(&mut_visible);
  uint32_t val = *((uint32_t *)(framebuffer->address + y * framebuffer->pitch +
                                x * framebuffer->bpp / 8));
  release_mutex(&mut_visible);
  return val;
}
