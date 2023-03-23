#ifdef __x86_64__

#include "arcadeos/rtc.h"

#include "arcadeos/serial.h"

#include "stdbool.h"
#include "stdint.h"
#include "string.h"

static const uint8_t NMI_disable_bit = 1; // TODO undisable NMI

static inline uint8_t read_register(uint8_t reg) {
  outb(0x70, (NMI_disable_bit << 7) | reg);
  return inb(0x71);
}

static uint8_t get_updating_flag(void) {
  outb(0x70, (NMI_disable_bit << 7) | 0x0a);
  return inb(0x71) & 0x80;
}

static void read_time(time_t *time) {
  while (get_updating_flag())
    ;
  time->seconds = read_register(0x00);
  time->minutes = read_register(0x02);
  time->hours = read_register(0x04);
  time->month = read_register(0x08);
  time->year = read_register(0x09);
}

static bool time_equal(time_t *first, time_t *second) {
  return memcmp(first, second, sizeof(time_t)) == 0;
}

void get_time(time_t *time) {
  time_t extra = {0};
  read_time(&extra);
  read_time(time);
  if (!time_equal(time, &extra)) {
    get_time(time);
    return;
  }
  uint8_t regb = inb(0x0b);

  if (!(regb & 0x04)) {
    time->seconds = (time->seconds & 0x0F) + ((time->seconds / 16) * 10);
    time->minutes = (time->minutes & 0x0F) + ((time->minutes / 16) * 10);
    time->hours = ((time->hours & 0x0F) + (((time->hours & 0x70) / 16) * 10)) |
                  (time->hours & 0x80);
    time->month = (time->month & 0x0F) + ((time->month / 16) * 10);
    time->year = (time->year & 0x0F) + ((time->year / 16) * 10);
  }
}

#endif
