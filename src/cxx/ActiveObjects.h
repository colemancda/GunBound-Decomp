/* The active-object container (PLAN.md Phase 5.1) - the key->intrusive-
 * list registry every screen's sprites/widgets register with (storage
 * DAT_00ea0e18, header at DAT_00ea0e1c; primed per-screen by
 * LoadSpriteSet, swept by the per-tick GC).
 *
 * Only the piece every state OnExit needs is modeled so far: the
 * bucket walk + destroy-all. The identical inlined copy appears in
 * Title (0x4e53a0), Logo1 (0x443430), Logo2 (0x4432c0) and Loading
 * (0x43eff0) - clearly an inline helper (or macro) in the original
 * source, so it is one here too; MSVC 7.1 re-inlines it at /O2 into
 * the same shape. */
#ifndef GB_CXX_ACTIVEOBJECTS_H
#define GB_CXX_ACTIVEOBJECTS_H

#include "gb_common.h"

extern "C" {
extern unsigned char DAT_00ea0e18;  /* container storage */
extern unsigned int  DAT_00ea0e1c;  /* container header (bucket list at +0x1c) */
}

/* Walk the sorted bucket list to `key`; if present, run every
 * registered object's vtable-slot-0 destructor with free=1 and reset
 * the bucket's intrusive list to empty. Buckets are ordered, so the
 * walk bails as soon as it passes `key`.
 *
 * Node layout (from the raw ports): [1] key, [3]/[4] intrusive list
 * head/next, [7] next bucket. Object call is really __thiscall; kept
 * in the raw ports' code* shape until the element class is
 * reconstructed. */
__forceinline void ActiveObjects_DestroyBucket(unsigned int key)
{
    unsigned int **bucket = *(unsigned int ***)(DAT_00ea0e1c + 0x1c);
    unsigned int k = (unsigned int)bucket[1];
    if (key < k) {
        return;                     /* sorted list already past the key */
    }
    while (k != key) {
        bucket = (unsigned int **)bucket[7];
        k = (unsigned int)bucket[1];
        if (key < k) {
            return;
        }
    }
    unsigned int **node = (unsigned int **)bucket[4];
    while (node != bucket) {
        unsigned int **obj = (unsigned int **)*node;
        node = (unsigned int **)node[4];
        ((void (__cdecl *)(int))*obj)(1);
    }
    bucket[3] = (unsigned int *)bucket;
    bucket[4] = (unsigned int *)bucket;
}

#endif /* GB_CXX_ACTIVEOBJECTS_H */
