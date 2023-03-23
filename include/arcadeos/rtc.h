#pragma once

#include "stdint.h"

typedef struct time {
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  uint8_t month;
  uint8_t year;
} time_t;

void get_time(time_t *);
