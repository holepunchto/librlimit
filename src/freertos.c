#include <stdint.h>

#include "../include/rlimit.h"

// There are no processes and so no resource limits, which leaves every resource
// unlimited. A limit can't be imposed either, as nothing would enforce it.
int
rlimit_get(rlimit_resource_t resource, rlimit_value_t *result) {
  switch (resource) {
  case rlimit_open_files:
    *result = rlimit_no_limit;

    return 0;
  default:
    return -1;
  }
}

int
rlimit_set(rlimit_resource_t resource, rlimit_value_t value) {
  switch (resource) {
  case rlimit_open_files:
    return value == rlimit_no_limit || value == rlimit_infer ? 0 : -1;
  default:
    return -1;
  }
}
