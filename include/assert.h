#pragma once

/*
assert(expression)
- if NDEBUG is defined, then evaluates to ((void)0)
- otherwise test expression, aborting if the condition is false
 */
#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
#define assert(condition)                                                      \
  if (!(condition)) {                                                          \
    fprintf(stderr, "Assertion failed: %s, function %s, file %s, line %s.\n",  \
            (condition), __func__, __file__, __line__);                        \
    abort();                                                                   \
  }
#endif

#define static_assert _Static_assert
