#include "arcadeos/system.h"

#include "arcadeos/terminal.h"

#include "assert.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

#include "limine.h"

static volatile struct limine_smbios_request req = {.id = LIMINE_SMBIOS_REQUEST,
                                                    .revision = 0};

struct entry {
  char str[4];
  uint8_t checksum;
  uint8_t len;
  uint8_t major;
  uint8_t minor;
  uint16_t max_struct_size;
  uint8_t revision;
  char formatted[5];
  char str2[5];
  uint8_t checksum2;
  uint16_t table_len;
  uint32_t addr;
  uint16_t count;
  uint8_t unused;
} __attribute__((packed)) * smbios_entry;

struct header {
  uint8_t type;
  uint8_t length;
  uint16_t handle;
} __attribute__((packed));

struct bios_header_v1 {
  struct header base;
  uint8_t str_vendor_name;
  uint8_t str_version;
  uint16_t start_addr_seg;
  uint8_t str_release_date;
  uint8_t rom_size;
  struct characteristics {
    bool reserved : 1;
    bool reserved1 : 1;
    bool unknown : 1;
    bool is_unsupported : 1;
    bool isa_support : 1;
    bool mca_support : 1;
    bool eisa_support : 1;
    bool pci_support : 1;
    bool pcmcia_support : 1;
    bool plug_play_support : 1;
    bool apm_support : 1;
    bool upgradeable : 1;
    bool shadowing : 1;
    bool vl_vesa_support : 1;
    bool escd_support : 1;
    bool boot_cd_support : 1;
    bool select_boot_support : 1;
    bool rom_socketed : 1;
    bool boot_pcmcia : 1;
    bool edd_support : 1;
    bool nec_floppy_support : 1;
    bool toshiba_floppy_support : 1;
    bool k360_floppy_support : 1;
    bool m1_2_floppy_support : 1;
    bool k720_floppy_support : 1;
    bool m2_88_floppy_support : 1;
    bool print_screen_support : 1;
    bool keyboard_8042_support : 1;
    bool serial_support : 1;
    bool printer_support : 1;
    bool cga_mono_support : 1;
    bool nec_pc98 : 1;
    uint16_t bios_reserved : 16;
    uint16_t system_reserved : 16;
  } __attribute__((packed)) characteristics;
} __attribute__((packed));

static_assert(sizeof(struct characteristics) == sizeof(uint64_t),
              "Incorrect size of bios header characteristics");

struct bios_header_v2_4 {
  struct bios_header_v1 base;
  struct bios_ext_b1 {
    bool acpi_support : 1;
    bool usb_legacy_support : 1;
    bool agp_support : 1;
    bool i20_boot_support : 1;
    bool ls_120_boot_support : 1;
    bool atapi_zip_boot_support : 1;
    bool boot_1394_support : 1;
    bool smart_batteru_support : 1;
  } __attribute__((packed)) ext1;
  struct bios_ext_b2 {
    bool bios_boot_spec_support : 1;
    bool function_key_network_support : 1;
    bool targeted_content_distribution : 1;
    bool uefi_support : 1;
    bool is_virt : 1;
    bool manufacturing_mode_support : 1;
    bool manufacturing_mode : 1;
    bool reserved : 1;
  } __attribute__((packed)) ext2;
  uint8_t bios_major;
  uint8_t bios_minor;
  uint8_t firmware_major;
  uint8_t firmware_minor;
  uint16_t extended_rom_size;
} __attribute__((packed));

static_assert(sizeof(struct bios_ext_b1) + sizeof(struct bios_ext_b2) ==
                  sizeof(uint16_t),
              "Incorrect size of bios extensions header info");

/* static const char *str_from_tbl(struct header *header, size_t index) { */
/*   const char *tbl = (const char *)(((uint8_t *)header) + header->length); */
/*   size_t len = strlen(tbl); */
/*   size_t ind = 0; */
/*   while (ind < index) { */
/*     tbl += len; */
/*     len = strlen(tbl); */
/*     ind++; */
/*   } */
/*   return tbl; */
/* } */

void print_smbios_info(void) {
  printf("======== Printing SMBIOS info ========\n");
  struct limine_smbios_response *resp = req.response;
  if (resp == NULL)
    printf("[WARN] smbios information not found");

  smbios_entry = resp->entry_32 == NULL ? resp->entry_64 : resp->entry_32;
  if (smbios_entry == NULL)
    panic("Got SMBIOS response but both the 64-bit and 32-bit pointers were "
          "null!");

  // validate_smbios();
  printf("[WARN] SMBIOS not implemented yet.\n");

  printf("======== SMBIOS info printed ========\n\n");
}
