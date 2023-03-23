#pragma once

#include "stdbool.h"

enum keys {
  key_q,
  key_w,
  key_e,
  key_r,
  key_t,
  key_y,
  key_u,
  key_i,
  key_o,
  key_p,
  key_a,
  key_s,
  key_d,
  key_f,
  key_g,
  key_h,
  key_j,
  key_k,
  key_l,
  key_z,
  key_x,
  key_c,
  key_v,
  key_b,
  key_n,
  key_m,
  key_1,
  key_2,
  key_3,
  key_4,
  key_5,
  key_6,
  key_7,
  key_8,
  key_9,
  key_0,
};

bool is_key_pressed(const enum keys);
void set_leds(const bool scroll_lock, const bool num_lock,
              const bool caps_lock);
