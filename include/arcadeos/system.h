#pragma once

#include "stddef.h"
#include "stdint.h"

_Noreturn void halt(void);
_Noreturn void panic(const char *message);
void identity_map(void *ptr, size_t size);

void initialize_malloc(void);
void setup_rsdp(void);
void print_smbios_info(void);
void arch_specific_setup(void);

uint64_t boot_time(void);
