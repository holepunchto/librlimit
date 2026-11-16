#ifndef RLIMIT_H
#define RLIMIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#if defined(_WIN32)
#if defined(RLIMIT_BUILDING)
#define RLIMIT_EXPORT __declspec(dllexport)
#elif defined(RLIMIT_SHARED)
#define RLIMIT_EXPORT __declspec(dllimport)
#else
#define RLIMIT_EXPORT
#endif
#elif defined(__GNUC__)
#define RLIMIT_EXPORT __attribute__((visibility("default")))
#else
#define RLIMIT_EXPORT
#endif

typedef int64_t rlimit_value_t;

typedef enum {
  rlimit_open_files = 1,
} rlimit_resource_t;

static const rlimit_value_t rlimit_no_limit = -1;
static const rlimit_value_t rlimit_infer = -2;

RLIMIT_EXPORT int
rlimit_get(rlimit_resource_t resource, rlimit_value_t *result);

RLIMIT_EXPORT int
rlimit_set(rlimit_resource_t resource, rlimit_value_t value);

#ifdef __cplusplus
}
#endif

#endif // HEX_H
