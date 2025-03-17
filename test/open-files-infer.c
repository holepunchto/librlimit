#include <assert.h>
#include <stdio.h>

#include "../include/rlimit.h"

int
main() {
  int e;
  e = rlimit_set(rlimit_open_files, rlimit_infer);
  assert(e == 0);

  rlimit_value_t limit;
  e = rlimit_get(rlimit_open_files, &limit);
  assert(e == 0);

  printf("limit=%lld\n", limit);
}
