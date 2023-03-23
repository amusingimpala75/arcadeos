#include "arcadeos/framebuffer.h"
#include "arcadeos/input.h"
#include "arcadeos/rsdp.h"
#include "arcadeos/rtc.h"
#include "arcadeos/serial.h"
#include "arcadeos/smp.h"
#include "arcadeos/system.h"
#include "arcadeos/terminal.h"

#include "limine.h"

#include "math.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <time.h>

// TODO: INPUT and PCIE
// TODO: interrupts, filesystem, elfs, graphics, etc.
// TODO: Triple buffering, proper kpanic

// limine TODO: stack size (maybe), HHDM (definitely), terminal callback
// (definitely), entry point (yes, so I can simplify
// linker.ld), kernel file / modules (maybe at some point), rsdp (yes), smbios
// (possibly), efi sys table (possibly), kernel addr (yes), device tree blob
// (soon)
static void kmain(void);

static volatile struct limine_bootloader_info_request bootloader_info_req = {
    .id = LIMINE_BOOTLOADER_INFO_REQUEST, .revision = 0};

#ifdef __x86_64__
static volatile struct limine_5_level_paging_request lvl5_req = {
    .id = LIMINE_5_LEVEL_PAGING_REQUEST, .revision = 0};
static void lvl5_warn(void) {
  if (lvl5_req.response == NULL)
    printf("WARNING: Couldn't enable 5 level paging.\n\n");
}
#endif

static void print_bootloader_info(void) {
  struct limine_bootloader_info_response *resp = bootloader_info_req.response;
  if (resp == NULL)
    panic("Didn't get bootloader info");
  printf("Booted with %s (version %s)\n", resp->name, resp->version);

  uint64_t bt = boot_time();
  printf("Current Time: %llu\n\n", bt);
}

// multithread initialization?
void pre_kmain(void) {
  init_serial();
  initialize_terminal();

  initialize_malloc();
  initialize_smp();

  arch_specific_setup();

  print_bootloader_info();
  initialize_framebuffer();

  setup_rsdp();

#ifdef __x86_64__
  lvl5_warn();
#endif

  // TODO: print boot time (requires RTC)

  printf("======== Calling kmain ========\n");
  kmain();
  printf("======== Exiting without Errors ========\n");
  halt();
}

// static uint64_t time = 1;

// static uint64_t lfsr = 0xACE1u;
// static uint64_t bit;
//
// static uint64_t rand() {
//   bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ^ (lfsr >> 7)
//   ^
//          (lfsr >> 8)) &
//         1;
//   return lfsr = (lfsr >> 1) | (bit << 32);
// }
//
// static uint64_t abs(int64_t i) {
//   if (i < 0)
//     return -i;
//   return i;
// }

// static uint32_t pixel_color(uint64_t x, uint64_t y) {
//    return (time * 2) << 16 | x << 8 | y;
//    const uint8_t val = 0xff;
//   uint8_t n = rand() % 256;
//   uint8_t n = ((256 * abs((int64_t)x - framebuffer_width() / 2)) /
//               framebuffer_width()) +
//              ((256 * abs((int64_t)y - framebuffer_height() / 2)) /
//               framebuffer_height());
//   uint64_t above = y == 0 ? y : y - 1;
//   if (get_pixel(x, y) >> 16 == val || get_pixel(x, above) >> 16 == val) {
//     n = val;
//   }
//   return n << 16 | n << 8 | n;
//  const uint8_t c = time % 2 == 0 ? 0 : 255;
//  return c << 16 | c << 8 | c;
//}

// static void graphics_test(void) {
//   size_t fb_max_x = framebuffer_width();
//   size_t fb_max_y = framebuffer_height();
//   while (true) {
//     for (size_t y = 0; y < fb_max_y; y++) {
//       for (size_t x = 0; x < fb_max_x; x++) {
//         put_pixel(x, y, pixel_color(x, y));
//       }
//     }
//     time++;
//     swap_buffer();
//     write_to_screen();
//     if (time > 200)
//       break;
//   }
// }

static void some_task(void) {
  printf("do something\n");
  printf("task done!\n");
}

static void kmain(void) {
  set_leds(true, true, true);
  char *str = MALLOC_A(char, strlen("Hello, ") + strlen("World!") + 1);
  str[0] = '\0';
  strcat(str, "Hello, ");
  strcat(str, "World!");
  printf("%s\n", str);
  FREE(str);
  // graphics_test();
  // terminal_refresh();
  printf("testing base-n printing: \n");
  printf("\tbase-2: ");
  ulprintln(123, INT_PRINT_BIN);
  printf("\tbase-10: %llu\n", (uint64_t)123);
  printf("\tbase-16: %llx\n", (uint64_t)123);

  printf("format plus %s %llu\n", "arg", (uint64_t)5);

  time_t time = {0};
  get_time(&time);
  printf("The time is: %llu:%llu:%llu UTC\n", (uint64_t)time.hours,
         (uint64_t)time.minutes, (uint64_t)time.seconds);

  bool done = false;
  printf("requesting task...\n");
  dispatch(some_task, &done);
  printf("waiting for task to complete...\n");
  spin_until(&done);
  printf("Done\n");
}
