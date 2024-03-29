#pragma once

// TODO

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

typedef int8_t int_fast8_t;
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;

typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;

typedef int64_t intmax_t;

typedef int64_t intptr_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef uint8_t uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;

typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

typedef uint64_t uintmax_t;

typedef uint64_t uintptr_t;

#define INT8_WIDTH 8
#define INT16_WIDTH 16
#define INT32_WIDTH 32
#define INT64_WIDTH 64

#define INT_FAST8_WIDTH INT8_WIDTH
#define INT_FAST16_WIDTH INT16_WIDTH
#define INT_FAST32_WIDTH INT32_WIDTH
#define INT_FAST64_WIDTH INT64_WIDTH

#define INT_LEAST8_WIDTH INT8_WIDTH
#define INT_LEAST16_WIDTH INT16_WIDTH
#define INT_LEAST32_WIDTH INT32_WIDTH
#define INT_LEAST64_WIDTH INT64_WIDTH

#define INTPTR_WIDTH INT64_WIDTH
#define INTMAX_WIDTH INT64_WIDTH

#define INT8_MIN (-128)
#define INT16_MIN (-32768)
#define INT32_MIN (-2147483647 - 1)
#define INT64_MIN (-9223372036854775807LL - 1)

#define INT_FAST8_MIN INT8_MIN
#define INT_FAST16_MIN INT16_MIN
#define INT_FAST32_MIN INT32_MIN
#define INT_FAST64_MIN INT64_MIN

#define INT_LEAST8_MIN INT8_MIN
#define INT_LEAST16_MIN INT16_MIN
#define INT_LEAST32_MIN INT32_MIN
#define INT_LEAST64_MIN INT64_MIN

#define INTPTR_MIN INT64_MIN
#define INTMAX_MIN INT64_MIN

#define INT8_MAX 127
#define INT16_MAX 32767
#define INT32_MAX 2147483647
#define INT64_MAX 9223372036854775807LL

#define INT_FAST8_MAX INT8_MAX
#define INT_FAST16_MAX INT16_MAX
#define INT_FAST32_MAX INT32_MAX
#define INT_FAST64_MAX INT64_MAX

#define INT_LEAST8_MAX INT8_MAX
#define INT_LEAST16_MAX INT16_MAX
#define INT_LEAST32_MAX INT32_MAX
#define INT_LEAST64_MAX INT64_MAX

#define INTPTR_MAX INT64_MAX
#define INTMAX_MAX INT64_MAX

#define UINT8_WIDTH 8
#define UINT16_WIDTH 16
#define UINT32_WIDTH 32
#define UINT64_WIDTH 64

#define UINT_FAST8_WIDTH UINT8_WIDTH
#define UINT_FAST16_WIDTH UINT16_WIDTH
#define UINT_FAST32_WIDTH UINT32_WIDTH
#define UINT_FAST64_WIDTH UINT64_WIDTH

#define UINT_LEAST8_WIDTH UINT8_WIDTH
#define UINT_LEAST16_WIDTH UINT16_WIDTH
#define UINT_LEAST32_WIDTH UINT32_WIDTH
#define UINT_LEAST64_WIDTH UINT64_WIDTH

#define UINTPTR_WIDTH UINT64_WIDTH
#define UINTMAX_WIDTH UINT64_WIDTH

#define UINT8_MAX 0xFF
#define UINT16_MAX 0xFFFF
#define UINT32_MAX 0xFFFFFFFF
#define UINT64_MAX 0xFFFFFFFFFFFFFFFFull

#define UINT_FAST8_MAX UINT8_MAX
#define UINT_FAST16_MAX UINT16_MAX
#define UINT_FAST32_MAX UINT32_MAX
#define UINT_FAST64_MAX UINT64_MAX

#define UINT_LEAST8_MAX UINT8_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define UINT_LEAST64_MAX UINT64_MAX

#define UINTPTR_MAX UINT64_MAX
#define UINTMAX_MAX UINT64_MAX

#define INT8_C(val) (INT_LEAST8_MAX - INT_LEAST8_MAX + (val))
#define INT16_C(val) (INT_LEAST16_MAX - INT_LEAST16_MAX + (val))
#define INT32_C(val) (INT_LEAST32_MAX - INT_LEAST32_MAX + (val))
#define INT64_C(val) (INT_LEAST64_MAX - INT_LEAST64_MAX + (val))

#define UINT8_C(val) (UINT_LEAST8_MAX - UINT_LEAST8_MAX + (val))
#define UINT16_C(val) (UINT_LEAST16_MAX - UINT_LEAST16_MAX + (val))
#define UINT32_C(val) (UINT_LEAST32_MAX - UINT_LEAST32_MAX + (val))
#define UINT64_C(val) (UINT_LEAST64_MAX - UINT_LEAST64_MAX + (val))

#define INTMAX_C(val) (INTMAX_MAX - INTMAX_MAX + (val))
#define UINTMAX_C(val) (INTMAX_MAX - INTMAX_MAX + (val))
