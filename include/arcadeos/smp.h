#pragma once

#include "stdbool.h"
#include "stdint.h"

uint64_t cpu_count(void);
void dispatch(void (*task)(void), bool *success_monitor);

void spin_until(bool *);

typedef volatile int mutex_t;
// TODO: use queue instead of just racing for the lock
void acquire_mutex(mutex_t *);
void release_mutex(mutex_t *);

void initialize_smp(void);
