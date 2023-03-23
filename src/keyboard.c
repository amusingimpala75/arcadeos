#include "arcadeos/input.h"

#include "arcadeos/serial.h"

#include "stdio.h"

static const uint8_t ACK = 0xFA;
static const uint8_t RESEND = 0xFE;

static const uint16_t PORT = 0x60;

static void send(const uint8_t i) {
  outb(PORT, i);
  uint8_t stat = inb(PORT);
  while (1) {
    printf("%llx\n", (uint64_t)stat);
    if (stat == ACK)
      return;
    else if (stat == RESEND)
      outb(PORT, i);
    stat = inb(PORT);
  }
}

void set_leds(const bool scroll_lock, const bool num_lock,
              const bool caps_lock) {
  uint8_t val = ((caps_lock ? 1 : 0) << 2) | ((num_lock ? 1 : 0) << 1) |
                (scroll_lock ? 1 : 0);
  send(0xED);
  send(val);
}

bool is_key_pressed(const enum keys key) { return false; }
