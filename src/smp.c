#include "arcadeos/smp.h"

#include "arcadeos/system.h"
#include "arcadeos/terminal.h"

#include "limine.h"

#include "stdbool.h"
#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"

static volatile struct limine_smp_request smp_req = {.id = LIMINE_SMP_REQUEST,
                                                     .revision = 0};

static struct limine_smp_response *smp_resp = NULL;

struct arcadeos_proc_status {
  bool busy;
  bool *write_on_completion;
  void (*task)(void);
};

// TODO: validate the bootstrapping processor is always id 0
static void setup_processor(struct limine_smp_info *info) {
  struct arcadeos_proc_status *status =
      malloc(sizeof(struct arcadeos_proc_status));
  info->extra_argument = (uint64_t)status;
  if (status == NULL)
    panic("malloc error setting up co-processors!");
  status->write_on_completion = NULL;
  status->task = NULL;
  status->busy = info->processor_id == 0;
  printf("ID: %llx\n", (uint64_t)info->processor_id);
#ifdef __x86_64__
  printf("\tLocal APIC ID: %llx\n", info->lapic_id);
#endif
}

void initialize_smp(void) {
  printf("======== Initializing SMP ========\n");
  if (!(smp_resp = smp_req.response))
    panic("Failure bootstrapping secondary processors");
  // print lapic/mpidr
  printf("Found %llu CPUs.\n", smp_resp->cpu_count);

  for (uint64_t i = 0; i < smp_resp->cpu_count; i++) {
    setup_processor(smp_resp->cpus[i]);
  }
  printf("======== SMP Initialized ========\n\n");
}

static void run_task(struct limine_smp_info *info) {
  struct arcadeos_proc_status *status =
      (struct arcadeos_proc_status *)info->extra_argument;
  status->task();
  *status->write_on_completion = true;
  status->busy = false;
  while (1) {
  }
}

bool dispatch_impl(void (*task)(void), bool *success_monitor) {
  if (smp_resp->cpu_count == 1) {
    task();
    *success_monitor = true;
    return true;
  }
  uint64_t i = 0;
  struct arcadeos_proc_status *status = NULL;
  bool found = false;
  for (; i < smp_resp->cpu_count; i++) {
    status = (struct arcadeos_proc_status *)smp_resp->cpus[i]->extra_argument;
    if (!status->busy) {
      found = true;
      break;
    }
  }
  if (!found)
    return false;
  *success_monitor = false;
  status->write_on_completion = success_monitor;
  status->task = task;
  status->busy = true;
  smp_resp->cpus[i]->goto_address = &run_task;
  return true;
}

void dispatch(void (*task)(void), bool *success_monitor) {
  while (!dispatch_impl(task, success_monitor))
    ;
}

void release_mutex(mutex_t *mutex) { *mutex = 0; }
