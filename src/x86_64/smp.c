#ifdef __x86_64__
#include "arcadeos/smp.h"

void acquire_mutex(mutex_t *mutex) {
  while (!__sync_bool_compare_and_swap(mutex, 0, 1)) {
    __asm__("pause");
  }
}

void spin_until(bool *val) {
  while (!*val) {
    __asm__("pause");
  }
}
#endif
