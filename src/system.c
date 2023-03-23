#include "arcadeos/system.h"

#include "arcadeos/terminal.h"
#include "limine.h"

#include "stdio.h"

void panic(const char *message) {
  printf("%s\n", message);
  halt();
}

static volatile struct limine_boot_time_request boot_time_req = {
    .id = LIMINE_BOOT_TIME_REQUEST, .revision = 0};

uint64_t boot_time(void) {
  struct limine_boot_time_response *resp = boot_time_req.response;
  if (resp == NULL)
    panic("Could not get boot time");
  return resp->boot_time;
}
