/* CJewel - the collectible that sits on the terrain and chain-detonates when
 * a blast reaches it, discovered and evidenced during the 2026-08-19 battle
 * entity-registry audit (commits ce98d5e / 12201a8 / 56c5662).
 *
 * TIER-1 COVERAGE PROMOTION: every slot of vtable 0x555fdc is ported and none
 * is uncarved (tools/vtable_census.py --coverage), and the whole spawn / hit
 * / damage chain around it is now named, so this file turns that evidence
 * into a declared class.
 *
 * ABI: the SAME flat 5-slot active-object vtable as CButtonWidget
 * (ButtonWidget.h), the effects (Effects.h) and the weather hazards
 * (Hazards.h) - [scalar-deleting dtor, ResolveNamedState, Tick, Draw,
 * NoOpMethod].  Like those it is NOT a CWidget or CProjectile relative; it
 * only SHARES the three stock slot implementations (0x461c60 / 0x429800).
 *
 *   CJewel  0x2298 bytes  ctor InitJewel (0x477bb0)  vtable 0x555fdc
 *     Delete 0x4780c0 DeleteJewel      Tick 0x479ba0 TickJewelFrame
 *     Draw   0x47a960 RenderJewel      slot 4 NoOpMethod
 *     spawner SpawnJewel (0x438410), sprite "jewel%d", state "normal"
 *
 * CLASS ID.  InitJewel stamps 100006 at +0x4 INLINE - it does not delegate to
 * InitProjectile - which is why the guard block is based at +0x38 rather than
 * the projectile base's +0x40.  See the entity-registry notes.
 *
 * LAYOUT.  After the active-object header the body is three consecutive
 * 0x224-byte CValueGuard cells, the anti-cheat treatment of the jewel's whole
 * state:
 *     +0x38   type      (SpawnJewel's param_3; also picks the "jewel%d"
 *                        sprite and a 300/200/peek switch)
 *     +0x25c  X         (SpawnJewel's param_2, `x % g_nCameraBoundX`)
 *     +0x480  Y
 * RenderJewel independently corroborates this trio: its own 2026-08-13
 * dropped-cell note records reading +0x25c/+0x480/+0xaf0 and +0x38 and
 * remarks that "the offsets differ from the usual mobile-cell family - this
 * object is a different class", which is exactly right.  +0xaf0 is a fourth
 * cell (+0x480 + 0x224 * 3) whose meaning is not established.
 *
 * The GuardedBool and per-cell interior mapping is not done, so the body
 * stays an opaque m_raw tail with the documented offsets above - sizeof() is
 * what the assert pins (checked in cxx_selftest.cpp).
 */
#ifndef GB_CXX_JEWEL_H
#define GB_CXX_JEWEL_H

#include "gb_common.h"

#pragma pack(push, 1)

class CJewel {
public:
    virtual void *Delete(int shouldFree);    /* 0x4780c0 - scalar-deleting dtor */
    virtual void SetState(const char *name); /* 0x461c60 - ResolveNamedState (shared) */
    virtual int Tick();                      /* 0x479ba0 - TickJewelFrame */
    virtual void Draw();                     /* 0x47a960 - RenderJewel */
    virtual void NoOp();                     /* 0x429800 - NoOpMethod */

    u8 m_raw[0x2298 - 4];   /* +0x04 class id 100006; CValueGuard cells at
                             * +0x38 type / +0x25c X / +0x480 Y (see header) */
};
GB_STATIC_ASSERT(sizeof(CJewel) == 0x2298, jewel_size);

#pragma pack(pop)

#endif /* GB_CXX_JEWEL_H */
