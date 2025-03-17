#ifndef RLIMIT_H
#define RLIMIT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int64_t rlimit_value_t;

typedef enum {
  rlimit_open_files = 1,
} rlimit_resource_t;

static const rlimit_value_t rlimit_no_limit = -1;
static const rlimit_value_t rlimit_infer = -2;

int
rlimit_get(rlimit_resource_t resource, rlimit_value_t *result);

int
rlimit_set(rlimit_resource_t resource, rlimit_value_t value);

#ifdef __cplusplus
}
#endif

#endif // HEX_H
