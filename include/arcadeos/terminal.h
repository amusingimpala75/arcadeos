#pragma once

#include "stddef.h"
#include "stdint.h"

enum int_print_format { INT_PRINT_HEX, INT_PRINT_DEC, INT_PRINT_BIN };

void println(const char *, const size_t);
void print(const char *, const size_t);
void sprint(const char *);
void sprintln(const char *);
size_t ulprint(const uint64_t, const enum int_print_format);
size_t ulprintln(const uint64_t, const enum int_print_format);

void terminal_refresh(void);

void initialize_terminal(void);
