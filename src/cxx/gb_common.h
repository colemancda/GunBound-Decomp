/* Shared basics for the C++ reconstruction layer (src/cxx/README.md).
 * MSVC 7.1 C++ mode - predates <cstdint> and static_assert. */
#ifndef GB_CXX_COMMON_H
#define GB_CXX_COMMON_H

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    s8;
typedef signed short   s16;
typedef signed int     s32;

/* C++03-compatible compile-time assert: instantiating a negative-size
 * array is a hard error. Message discipline: name the check in `what`. */
#define GB_STATIC_ASSERT(cond, what) \
    typedef char gb_static_assert_##what[(cond) ? 1 : -1]

/* Field-offset check that works on these non-POD (vtable-bearing)
 * classes under MSVC 7.1. Standard offsetof is UB on non-PODs, but this
 * null-object form is the customary decomp-project idiom and MSVC
 * evaluates it as a constant. */
#define GB_OFFSETOF(T, m) ((unsigned)&(((T *)0)->m))

#endif /* GB_CXX_COMMON_H */
