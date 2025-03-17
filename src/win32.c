#include <stdint.h>
#include <windows.h>

#include "../include/rlimit.h"

static inline int
rlimit_get__open_files(rlimit_value_t *result) {
  int res = _getmaxstdio();
  if (res < 0) return -1;

  *result = (rlimit_value_t) res;

  return 0;
}

int
rlimit_get(rlimit_resource_t resource, rlimit_value_t *result) {
  switch (resource) {
  case rlimit_open_files:
    return rlimit_get__open_files(result);
  default:
    return -1;
  }
}

static inline int
rlimit_set__open_files(rlimit_value_t value) {
  if (value == rlimit_no_limit) return -1;

  if (value == rlimit_infer) value = 8192;

  if (value < 32 || value > 8192) return -1;

  int res = _setmaxstdio((int) value);
  if (res < 0) return -1;

  return 0;
}

int
rlimit_set(rlimit_resource_t resource, rlimit_value_t value) {
  switch (resource) {
  case rlimit_open_files:
    return rlimit_set__open_files(value);
  default:
    return -1;
  }
}
