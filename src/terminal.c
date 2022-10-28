#include "arcadeos/terminal.h"
#include "limine.h"

static void setup_put_string(const char *, size_t);

static void (*put_string)(const char *, size_t) = &setup_put_string;

static struct limine_terminal *terminal;
static struct limine_terminal_response *response;

static void actual_put_string(const char *string, size_t len) {
  response->write(terminal, string, len);
}

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST, .revision = 0};

static void setup_put_string(const char *string, size_t len) {
  response = terminal_request.response;
  if (!response || response->terminal_count < 1)
    return;
  terminal = response->terminals[0];
  put_string = &actual_put_string;
  put_string(string, len);
}

void print(const char *string, size_t len) { put_string(string, len); }

void println(const char *string, size_t len) {
  put_string(string, len);
  put_string("\n", 1);
}
