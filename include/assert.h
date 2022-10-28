#pragma once

#ifndef NDEBUG
#define assert(condition) _assert(bool)
#else
#define assert(condition) ((void)0)
#endif

#define static_assert _Static_assert
