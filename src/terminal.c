#include "arcadeos/terminal.h"

#include "arcadeos/serial.h"
#include "arcadeos/smp.h"

#include "limine.h"

#include "stdbool.h"
#include "string.h"

static struct limine_terminal *terminal;
static struct limine_terminal_response *response;

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST, .revision = 0};
static bool loaded = false;

void initialize_terminal(void) {
  response = terminal_request.response;
  if (!response || response->terminal_count < 1)
    return;
  terminal = response->terminals[0];
  loaded = true;
}

void terminal_refresh(void) {
  response->write(terminal, NULL, LIMINE_TERMINAL_FULL_REFRESH);
}

static mutex_t mut;

void print(const char *string, const size_t len) {
  acquire_mutex(&mut);
#ifdef DEBUG_BUILD
  serial_write_string(string, len);
#endif
  if (loaded) {
    response->write(terminal, string, len);
  }
  release_mutex(&mut);
}

void println(const char *string, const size_t len) {
  acquire_mutex(&mut);
#ifdef DEBUG_BUILD
  serial_write_string(string, len);
  serial_write_string("\n", 1);
#endif
  if (loaded) {
    response->write(terminal, string, len);
    response->write(terminal, "\n", 1);
  }
  release_mutex(&mut);
}

void sprint(const char *str) { print(str, strlen(str)); }

void sprintln(const char *str) {
  print(str, strlen(str));
  print("\n", 1);
}

static void swap(char *buffer, const uint64_t length) {
  uint8_t index = 0;
  while (index < length / 2) {
    const char t = buffer[index];
    buffer[index] = buffer[length - (index + 1)];
    buffer[length - (index + 1)] = t;
    index++;
  }
}

#define U_AS_BASE_N(base, digit_conversion)                                    \
  static void u_as_base_##base(char buffer[21], uint64_t number) {             \
    uint8_t index = 0;                                                         \
    while (number > 0) {                                                       \
      buffer[index++] = (digit_conversion)(number % (base));                   \
      number /= (base);                                                        \
    }                                                                          \
    swap(buffer, index);                                                       \
  }

static char u_as_binary(const uint8_t n) {
  if (n == 0)
    return '0';
  if (n == 1)
    return '1';
  return '@';
}
U_AS_BASE_N(2, &u_as_binary)

static char u_as_decimal(const uint8_t n) {
  if (n >= 0 && n <= 9)
    return '0' + n;
  return '@';
}
U_AS_BASE_N(10, &u_as_decimal)

static char u_as_hexidecimal(const uint8_t number) {
  if (number >= 0 && number <= 9)
    return '0' + number;
  if (number >= 10 && number <= 15)
    return 'A' + (number - 10);
  return '@';
}
U_AS_BASE_N(16, &u_as_hexidecimal);

// TODO proper mutex locking here
// TODO fix printing '0'
size_t ulprint(const uint64_t val, const enum int_print_format format) {
  char buffer[20 + 1] = {0};
  size_t len = 0;
  switch (format) {
  case INT_PRINT_HEX:
    u_as_base_16(buffer, val);
    print("0x", 2);
    len += 2;
    break;
  case INT_PRINT_DEC:
    u_as_base_10(buffer, val);
    break;
  case INT_PRINT_BIN:
    u_as_base_2(buffer, val);
    print("0b", 2);
    len += 2;
    break;
  default:
    u_as_base_16(buffer, format);
    sprint("Unrecognized int format type: 0x");
    sprintln(buffer);
    return 0;
  }
  len += strlen(buffer);
  print(buffer, len);
  return len;
}

size_t ulprintln(const uint64_t val, const enum int_print_format format) {
  const size_t len = ulprint(val, format);
  print("\n", 1);
  return len + 1;
}
