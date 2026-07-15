/* CProjectile - the in-battle projectile (shot) object: the sibling of CMobile,
 * the thing every weapon fires. Reconstructed from InitProjectile (0x454dc0),
 * SimulateProjectileFrame (0x455cc0) and the shot spawners
 * (SpawnPrimaryShot/SpawnSuperShot/SpawnItemProjectile). See src/cxx/README.md.
 *
 * CONFIRMED (from the binary):
 *  - The base object is 0x3f9c bytes; allocated by the shot spawners
 *    (operator_new(0x3f9c)) and constructed by InitProjectile(this, 0x186a2).
 *    Per-weapon subtypes are larger (0x3fa0 / 0x40a8 / 0x4940 / 0x4838 / 0x41cc
 *    / 0x42d8 / 0x494c ...): a thin per-type ctor (e.g. FUN_00468860) calls
 *    InitProjectile then swaps in its own vtable (e.g. 0x555dac) - the same
 *    pattern as the 16 CMobile subclasses.
 *  - Single base vtable at 0x555c34 (dumped: 13 slots). NOT related to CMobile's
 *    vtable (0x555c68, 8 slots) - the two are separate, adjacent vtables that
 *    only reuse two shared method implementations as slots: 0x461c60
 *    (acquire-handle, slots 1/9) and 0x429800 (no-op, slots 4/12). CProjectile
 *    does NOT share a base class with CMobile.
 *  - Most of the object (from +0x54, spaced 0x224) is ~29 CValueGuard cells plus
 *    GuardedBools - the anti-cheat-protected position/velocity/damage/timing
 *    state (same treatment as CMobile). They are left as padding here until the
 *    guard fields are individually mapped.
 *
 * GUESSED: the vtable-only slots (3/7/8/10/11) and the shared no-ops. CONFIRMED:
 * slot 0 (dtor), slot 2 (AnimateProjectileTick), slot 5 (SimulateProjectileFrame),
 * slot 6 (DetonateProjectile). Interior fields between the named ones are unmapped
 * (guard cells / padding).
 */
#ifndef GB_CXX_PROJECTILE_H
#define GB_CXX_PROJECTILE_H

#include "gb_common.h"

#pragma pack(push, 1)
/* The battle projectile. Declaration order of the virtuals IS the confirmed base
 * vtable order (0x555c34, 13 slots). */
class CProjectile {
public:
    /* slot 0 +0x00: scalar-deleting destructor 0x455550 (-> real dtor 0x455570,
     * then conditional operator_delete). */
    virtual ~CProjectile();
    /* slot 1 +0x04: 0x461c60 (shared) - RENAMED from v1_AcquireHandle
     * (2026-07-15): angr-confirmed (see ButtonWidget.cpp's SetState, the
     * same underlying function at the same address) this is the generic
     * named-state string resolver, not a handle-acquire op - `this` (ECX)
     * and a needle string (stack arg) were BOTH dropped from the original
     * 0-arg declaration. Looks up `name` in the table at this+0x1c
     * (m_texture) via FindStringNoCase, records the match in
     * m_state/m_unk20/m_unk28/m_unk2c/m_unk34. See Projectile.cpp for the
     * inlined implementation (same "don't call the shared ResolveNamedState
     * symbol" reasoning as CButtonWidget::SetState). */
    virtual void v1_SetState(const char *name);
    /* slot 2 +0x08: 0x48f1c0 = AnimateProjectileTick - per-frame animate tick:
     * dispatches slot 6 (Detonate), then advances the sprite animation
     * (AdvanceSpriteAnimation), bumping a small frame counter (+0x3b44) and
     * firing a replay event when it reaches 5. */
    virtual void AnimateProjectileTick();
    /* slot 3 +0x0c: 0x458690 (vtable-only; Ghidra has not defined it). */
    virtual void v3();
    /* slot 4 +0x10: 0x429800 (shared) - no-op (`return;`). */
    virtual void v4_NoOp();
    /* slot 5 +0x14: 0x455cc0 = SimulateProjectileFrame (CONFIRMED) - the per-frame
     * ballistics/state update: physics helpers, guard-protected fields, replay
     * events 0xf002/0xf003. No spawn/render calls.
     * CORRECTED (2026-07-12, cxx/Projectile.cpp): takes a real second
     * argument - Ghidra's own fresh decompile shows it consumed throughout
     * as `in_stack_00000004` (never resolved into the formal parameter
     * list), used as a per-step time/delta value in the ballistic stepping
     * loop. The zero-arg declaration here was wrong; DetonateProjectile's
     * `SimulateFrame();` call (slot-5 dispatch, this header's own earlier
     * comment) is therefore ALSO missing this argument - not fixed there
     * yet, flagged as follow-up. */
    virtual void SimulateFrame(int stepDelta);
    /* slot 6 +0x18: 0x4572b0 = DetonateProjectile - impact/detonation handler:
     * operator_new(0x3fbc) + InitProjectile a child blast object (vtable
     * 0x55658c), scans the object list for terrain (0x186aa marker), computes
     * the crater (FloatToInt64), spawns damage particles (FUN_00432320),
     * RegisterActiveObject + AcquireSoundChannel, then rescrambles a guard. */
    virtual void DetonateProjectile();
    /* slot 7 +0x1c: 0x458850 (vtable-only). */
    virtual void v7();
    /* slot 8 +0x20: 0x40ca00 - RENAMED from v8 (2026-07-15): confirmed the
     * same address as CButtonWidget's slot 0 (Delete -
     * DeletePoisonedBaseObject, see ButtonWidget.h/.cpp), a shared
     * scalar-deleting destructor thunk reused across unrelated classes.
     * Real signature drops `shouldFree` (this + 1 stack arg, __thiscall) -
     * was declared 0-arg. */
    virtual void *v8_Delete(int shouldFree);
    /* slot 9 +0x24: 0x461c60 (shared, same rename/arg-fix as slot 1 above). */
    virtual void v9_SetState(const char *name);
    /* slot 10 +0x28: 0x458ae0 (vtable-only). */
    virtual void v10();
    /* slot 11 +0x2c: 0x458b00 (vtable-only). */
    virtual void v11();
    /* slot 12 +0x30: 0x429800 (shared) - no-op. */
    virtual void v12_NoOp();

    /* ---- data members (confirmed offsets; interior gaps are guard cells /
     * unmapped padding) ---- */
    u32 m_ctorArg0;      /* +0x04: InitProjectile's param_3 (owner/shot arg) */
    u32 m_ctorArg1;      /* +0x08: InitProjectile's param_1 (type/owner arg) */
    u8  m_pad0c[0xc];    /* +0x0c */
    u32 m_spriteId;      /* +0x18: primary sprite/animation set id (spawners set 6000+shot) */
    u32 m_texture;       /* +0x1c: projectile texture handle (FindPreloadedTextureByName) */
    /* +0x20..0x37 (was one opaque m_pad20[0x18] blob): split 2026-07-15,
     * confirmed via the v1_SetState/v9_SetState angr trace (0x461c60) -
     * these are the same found-flag/state/inverse-flag fields
     * CButtonWidget documents at the same offsets (ButtonWidget.h). +0x30
     * remains an unmapped gap (untouched by 0x461c60). */
    u8  m_unk20;         /* +0x20: found flag, set by v1/v9 SetState */
    u8  m_unk21[3];      /* +0x21 padding */
    u32 m_state;         /* +0x24: matched index, set by v1/v9 SetState */
    u32 m_unk28;         /* +0x28: reset to 0 on a successful SetState match */
    u32 m_unk2c;         /* +0x2c: reset to 0 on a successful SetState match */
    u8  m_unk30[4];       /* +0x30: untouched by SetState - unmapped */
    u32 m_unk34;         /* +0x34: inverse-found flag, set by v1/v9 SetState */
    u32 m_lifetime;      /* +0x38: spawner sets m_spriteId + 100 */
    u8  m_flags;         /* +0x3c: low 3 bits = a per-shot tag (retaddr & 7) */
    /* +0x3d..0x3f8f: mostly ~29 CValueGuard cells (0x224 stride from +0x54) and
     * GuardedBools - the guarded projectile state; plus the blast/flame effect
     * sprite-name strings (blast name at +0x3813). Left as padding. */
    u8  m_pad3d[0x3f53];
    u32 m_subtype;       /* +0x3f90: shot subtype / blast frame set (spawners set 0..7, 0xff) */
    u32 m_field3f94;     /* +0x3f94: spawner's param_12 (a per-shot value) */
    u8  m_pad3f98[4];    /* +0x3f98..0x3f9b - tail padding to the confirmed 0x3f9c size */
};
#pragma pack(pop)

#endif /* GB_CXX_PROJECTILE_H */
