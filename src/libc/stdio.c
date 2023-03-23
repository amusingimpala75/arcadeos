#include "stdio.h"

#include "stdarg.h"
#include "stdbool.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"

#include "arcadeos/terminal.h"

static void swap(char *buffer, const uint64_t length) {
  uint8_t index = 0;
  while (index < length / 2) {
    char t = buffer[index];
    buffer[index] = buffer[length - (index + 1)];
    buffer[length - (index + 1)] = t;
    index++;
  }
}

#define U_AS_BASE_N(base, digit_conversion)                                    \
  static void u_as_base_##base(char buffer[21], uint64_t number) {             \
    if (number == 0) {                                                         \
      buffer[0] = '0';                                                         \
      return;                                                                  \
    }                                                                          \
    uint8_t index = 0;                                                         \
    while (number > 0) {                                                       \
      buffer[index++] = (digit_conversion)(number % (base));                   \
      number /= (base);                                                        \
    }                                                                          \
    swap(buffer, index);                                                       \
  }

// TODO fix error because buffer to short for large binary num
// static char u_as_binary(uint8_t n) {
//  if (n == 0)
//    return '0';
//  if (n == 1)
//    return '1';
//  return '@';
// }
// U_AS_BASE_N(2, &u_as_binary)

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

struct length_change {
  int64_t str_len;  // output string delta length for format
  uint64_t ind_jmp; // format string index extra jump
};

static struct length_change length_change(const char *fmt, va_list args) {
  switch (fmt[0]) {
  case '%': {
    const struct length_change lc = {.str_len = -1, .ind_jmp = 1};
    return lc;
  }
  case 's': {
    const char *str = va_arg(args, const char *);
    const struct length_change lc = {.str_len = -2 + strlen(str) + 1,
                                     .ind_jmp = 1};
    // TODO why +1? without it free at end of
    // function crashes because buffer stack-smash, but why?
    return lc;
  }
  case 'l':
    if (fmt[1] == 'l') {
      void (*itoa)(char buf[21], uint64_t n) = NULL;
      if (fmt[2] == 'u')
        itoa = &u_as_base_10;
      else if (fmt[2] == 'x')
        itoa = &u_as_base_16;
      else
        goto error;
      const uint64_t n = va_arg(args, uint64_t);
      char buf[21] = {0};
      itoa(buf, n);
      const struct length_change lc = {.str_len = -3 + strlen(buf) + 1,
                                       .ind_jmp = 3};
      return lc;
    }
  default:
  error:
    sprint("unknown format: ");
    println(&fmt[0], 1);
    const struct length_change lc = {.str_len = 0, .ind_jmp = 0};
    return lc;
  }
}

struct formatting_jump {
  uint64_t fmt_jmp;
  uint64_t out_jmp;
};

static struct formatting_jump process_format(const char *fmt, char *out,
                                             va_list args) {
  switch (fmt[0]) {
  case '%': {
    out[0] = '%';
    const struct formatting_jump fj = {.fmt_jmp = 1, .out_jmp = 1};
    return fj;
  }
  case 's': {
    const char *str = va_arg(args, const char *);
    strcat(out, str);
    const struct formatting_jump fj = {.fmt_jmp = 1, .out_jmp = strlen(str)};
    return fj;
  }
  case 'l':
    if (fmt[1] == 'l') {
      void (*itoa)(char buf[21], uint64_t n);
      if (fmt[2] == 'u')
        itoa = &u_as_base_10;
      else if (fmt[2] == 'x') {
        itoa = &u_as_base_16;
        strcat(out, "0x");
      } else
        goto error;
      uint64_t n = va_arg(args, uint64_t);
      char buf[21] = {0};
      itoa(buf, n);
      strcat(out, buf);
      const struct formatting_jump fj = {
          .fmt_jmp = 3, .out_jmp = strlen(buf) + (fmt[2] == 'x' ? 2 : 0)};
      return fj;
    }
  default:
  error:
    out[0] = fmt[0];
    const struct formatting_jump fj = {.fmt_jmp = 0, .out_jmp = 1};
    return fj;
  }
}

// TODO actually be standards conforming
int printf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);

  const size_t initial_length = strlen(fmt) + 1;
  size_t new_length = initial_length;
  for (size_t i = 0; i < new_length; i++) {
    if (fmt[i] == '%' && i + 1 < new_length) {
      struct length_change lc = length_change(&fmt[i + 1], args);
      new_length += lc.str_len;
      i += lc.ind_jmp;
    }
  }
  va_start(args, fmt);
  char *str = MALLOC_A(char, new_length + 1);
  if (!str) {
    sprint("Malloc error, skipping formatting\n");
    sprint(fmt);
    return -1;
  }
  memset(str, '\0', new_length + 1);
  size_t initial_size = strlen(fmt);
  for (size_t i = 0, j = 0; i < initial_size; i++) {
    if (fmt[i] == '%' && i < new_length - 2) {
      const struct formatting_jump fj =
          process_format(&fmt[i + 1], &str[j], args);
      i += fj.fmt_jmp;
      j += fj.out_jmp;
    } else {
      str[j] = fmt[i];
      j++;
    }
  }
  sprint(str);
  FREE(str);
  return 0;
}
