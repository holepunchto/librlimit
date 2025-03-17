#include <stdint.h>
#include <sys/resource.h>

#include "../include/rlimit.h"

static inline int
rlimit__to_system_resource(rlimit_resource_t resource) {
  switch (resource) {
  case rlimit_open_files:
    return RLIMIT_NOFILE;
  default:
    return -1;
  }
}

int
rlimit_get(rlimit_resource_t resource, rlimit_value_t *result) {
  int err;

  struct rlimit limit;
  err = getrlimit(rlimit__to_system_resource(resource), &limit);
  if (err < 0) return -1;

  if (limit.rlim_cur == RLIM_INFINITY) {
    *result = rlimit_no_limit;
  } else {
    *result = limit.rlim_cur;
  }

  return 0;
}

int
rlimit_set(rlimit_resource_t resource, rlimit_value_t value) {
  int err;

  struct rlimit limit;
  err = getrlimit(rlimit__to_system_resource(resource), &limit);
  if (err < 0) return -1;

  if (limit.rlim_cur == limit.rlim_max) {
    if (value == rlimit_no_limit && limit.rlim_cur == RLIM_INFINITY) return 0;

    if (value == rlimit_infer) return 0;

    if (value == limit.rlim_cur) return 0;

    return -1;
  }

  if (value == rlimit_no_limit) {
    limit.rlim_cur = RLIM_INFINITY;

    err = setrlimit(rlimit__to_system_resource(resource), &limit);
    if (err < 0) return -1;

    return 0;
  }

  if (value == rlimit_infer) {
    rlim_t min = limit.rlim_cur;
    rlim_t max = 1 << 20;

    if (limit.rlim_max != RLIM_INFINITY) {
      min = limit.rlim_max;
      max = limit.rlim_max;
    }

    do {
      limit.rlim_cur = min + (max - min) / 2;

      if (setrlimit(rlimit__to_system_resource(resource), &limit)) {
        max = limit.rlim_cur;
      } else {
        min = limit.rlim_cur;
      }
    } while (min + 1 < max);

    return 0;
  }

  err = setrlimit(rlimit__to_system_resource(resource), &limit);
  if (err < 0) return -1;

  return 0;
}
