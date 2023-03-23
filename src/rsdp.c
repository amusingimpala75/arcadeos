#include "arcadeos/rsdp.h"

#include "stdio.h"
#include "string.h"

#include "arcadeos/system.h"
#include "arcadeos/terminal.h"
#include "limine.h"

static volatile struct limine_rsdp_request req = {.id = LIMINE_RSDP_REQUEST,
                                                  .revision = 0};

struct rsdp_desc {
  char signature[8];
  uint8_t checksum;
  char oem_id[6];
  uint8_t revision;
  uint32_t rsdt_addr;
} __attribute__((packed)) * desc;

static void validate_rsdp(void) {
  uint8_t *rsdp_bytes = (uint8_t *)desc;

  size_t sum = 0;

  for (size_t i = 0; i < sizeof(struct rsdp_desc) / sizeof(uint8_t); i++) {
    sum += *(rsdp_bytes++);
  }

  sum %= UINT8_MAX + 1;

  if (sum != 0)
    panic("rsdp checksum invalid!");

  if (memcmp(desc->signature, "RSD PTR ", 8) != 0) {
    char sig[9] = {0};
    memcpy(sig, desc->signature, 8);
    printf("[ERROR] rsdp signature: \"%s\"\n", sig);
    panic("rsdp signature invalid!");
  }
}

void setup_rsdp(void) {

  printf("======== Setting up RSDP ========\n");

  const struct limine_rsdp_response *resp = req.response;

  if (resp == NULL)
    panic("Could not read rsdp!");

  desc = resp->address;

  validate_rsdp();
  if (desc->revision >= 2) {
  }

  printf("RSDP valid!\n");

  printf("OEM id: %s\n", desc->oem_id);

  printf("[WARN] rsdp not implemented yet!\n");

  printf("======== RSDP setup complete ========\n\n");
}
