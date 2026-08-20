/* CProjectile - the in-battle projectile (shot) object: the sibling of CMobile,
 * the thing every weapon fires. Reconstructed from InitProjectile (0x454dc0),
 * SimulateProjectileFrame (0x455cc0) and the shot spawners
 * (SpawnPrimaryShot/SpawnSuperShot/SpawnItemProjectile). See src/cxx/README.md.
 *
 * CONFIRMED (from the binary):
 *  - The base object is 0x3f9c bytes; allocated by the shot spawners
 *    (operator_new(0x3f9c)) and constructed by InitProjectile(this, 0x186a2).
 *    Per-weapon subtypes are larger (0x3fa0 / 0x40a8 / 0x4940 / 0x4838 / 0x41cc
 *    / 0x42d8 / 0x494c ...): a thin per-type ctor (e.g. InitShot2_Bullet1) calls
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
 * The per-weapon subclasses themselves are tabulated in
 * docs/projectile_classes.md - every vtable in this family, the class it
 * belongs to, and which function fills each of its Delete/Animate/Simulate/
 * Detonate/Explode slots.  Classes there were identified only from slots
 * UNIQUE to one vtable; the table also lists the ones that cannot be
 * identified and why.
 *
 * GUESSED: the vtable-only slots (3/7/8/10/11) and the shared no-ops. CONFIRMED:
 * slot 0 (dtor), slot 2 (AnimateProjectileTick), slot 5 (SimulateProjectileFrame),
 * slot 6 (DetonateProjectile). Interior fields between the named ones are unmapped
 * (guard cells / padding).
 *
 * VTABLE LENGTH (2026-08-16, from dumping every per-weapon projectile vtable
 * with tools/projectile_class_map.py): the concrete per-weapon classes are
 * 8-slot vtables (slots 0-7), each immediately followed by the NEXT class's
 * vtable (e.g. 0x5560d0 is followed at 0x5560f0 by mobile type 9's vtable),
 * so the "13 slots" read above at 0x555c34 spans into 0x555c54 = [0x40ca00
 * dtor, 0x461c60, 0x458ae0, 0x458b00, 0x429800], a separate 5-slot class -
 * slots 8-12 below are therefore that neighbour's, not CProjectile's.  The
 * sixteen SUPER-SHOT classes (SpawnSuperShot's cases) alone carry a 9th
 * slot: a post-detonation effect the slot-6 override dispatches after
 * marking the projectile dead (`param_1[5] = 1; (**(code **)(*param_1 +
 * 0x20))()`), e.g. 0x4837e0 spawns the eight "ssflame8" flames of bullet 8.
 * The 49 per-weapon overrides of slots 2/5/6/8 were renamed that day to
 * <Animate|Simulate|Detonate|Explode><Shot1|Shot2|PrimaryShot|SuperShot|
 * ItemShot>_Bullet<N> (N = SpawnXxx case + 1 = the bulletN texture number,
 * Shot1/Shot2 = weapon index 0/1, PrimaryShot = one class for both) and
 * live under src/battle/.
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
    /* slot 3 +0x0c: 0x458690 - fresh angr disassembly (2026-07-15, no prior
     * decompile existed). 0-arg __thiscall, void return (confirmed - real
     * signature, no fix needed). Publishes several guard-cell values into a
     * g_clientContext-relative per-slot tracking array indexed by
     * m_ctorArg1, gated on a global table pointer at g_clientContext+0x20b94
     * (whole function is a no-op if that's null); does 2 BST lookups via
     * 0x455b60 (unnamed - a tree walk against the same sprite/frame
     * registry root FindSpriteFrame/DrawButtonWidget use) keyed on
     * m_spriteId/m_lifetime and a newly-discovered field at this+0x30
     * (inside what was m_unk30 - likely a per-shot sprite/frame cache key,
     * unconfirmed). GUESSED name/role - the specific purpose of the
     * per-slot tracking array isn't confirmed, only its shape. See
     * Projectile.cpp for the full derivation and the exact global offsets. */
    virtual void PublishProjectileTrackingState();
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
    /* slot 7 +0x1c: 0x458850 = IsProjectileInBounds - CARVED and NAMED
     * 2026-08-19 (src/battle/IsProjectileInBounds.c); the highest-leverage
     * uncarved slot in the tree, referenced by FORTY vtables.  The
     * 2026-07-15 angr pass had the shape right - a bool return with two
     * distinct exits, 0 stack args, an ANDed guarded window check - but
     * recorded "cell targets not resolvable" for the first two comparisons
     * and left the role GUESSED.  Both targets are plain g_clientContext
     * offsets, 0x6a9b78 and 0x6a9d9c, and they, 0x6a9fc0 and 0x6aa1e4 are
     * CONSECUTIVE 0x224-byte CValueGuard cells - a guarded quadruple of
     * WORLD BOUNDS, compared against this projectile's own X (+0xf54) and
     * Y (+0x1178) cells.  That makes the role confirmed rather than guessed:
     * the projectile is in bounds while
     *     boundsLeft <= x < boundsRight  &&  -1000 <= y < boundsBottom.
     * The two object cells are the same pair DetonateProjectile,
     * ApplyBlastDamage and the terrain column scans use. */
    virtual bool IsProjectileInBounds();
    /* slot 8 +0x20: 0x40ca00 - RENAMED from v8 (2026-07-15): confirmed the
     * same address as CButtonWidget's slot 0 (Delete -
     * DeletePoisonedBaseObject, see ButtonWidget.h/.cpp), a shared
     * scalar-deleting destructor thunk reused across unrelated classes.
     * Real signature drops `shouldFree` (this + 1 stack arg, __thiscall) -
     * was declared 0-arg. */
    virtual void *v8_Delete(int shouldFree);
    /* slot 9 +0x24: 0x461c60 (shared, same rename/arg-fix as slot 1 above). */
    virtual void v9_SetState(const char *name);
    /* slot 10 +0x28: 0x458ae0 - RENAMED from v10 (2026-07-15, fresh angr
     * disassembly, no prior decompile existed - confident rename, not just
     * a guess): a max-lifetime auto-expiry tick. Confirmed via cross-
     * reference against DetonateProjectile's already-committed
     * `pCVar9->m_pad0c[8] = '\x01'` writes (the same this+0x14 field this
     * function force-sets once a counter at this+0x40 exceeds a limit at
     * this+0x44 - both currently inside the unmapped m_pad3d guard-cell
     * region). 0-arg __thiscall, void return - matches the prior
     * declaration exactly, no signature fix needed.
     * KNOWN CONFLICT (flagged, not resolved): this also accumulates the
     * counter into this+0x3c - the SAME offset Projectile.h documents as
     * m_flags (u8, "low 3 bits = a per-shot tag", set once by InitProjectile
     * and read as a small tag value by DetonateProjectile's
     * FUN_00432320/ApplyBlastDamage calls), but reads/writes it here as a full
     * accumulating DWORD. Both behaviors are real and angr-confirmed at the
     * same address; not reconciled here - see Projectile.cpp for how this
     * is written (raw offset arithmetic, not through the m_flags member, to
     * stay honest about the ambiguity). */
    virtual void TickLifetimeExpiry();
    /* slot 11 +0x2c: 0x458b00 - fresh angr disassembly (2026-07-15, no prior
     * decompile existed). 0-arg __thiscall, void return (confirmed - real
     * signature, no fix needed). Computes a camera-relative screen position
     * twice with constants differing by exactly +/-1 (298/399 vs 297/400 -
     * a classic drop-shadow/outline double-draw offset pattern) from
     * m_lifetime (+0x38) and the this+0x3c field (see slot 10's comment -
     * same conflicted offset), against two not-yet-named camera globals in
     * the g_clientContext+0x6a7710/+0x6a7714 family (same cluster as the
     * g_nCameraX/g_nCameraScrollX globals already named in
     * DetonateProjectile, just not these two specific ones), then issues 2
     * draw-style calls (0x4eb640/0x4eb720, not identified anywhere else in
     * the tree) passing a constant mode/color index and a new 16-bit field
     * at this+0x48 (inside what was m_pad3d) whose content (value? string
     * pointer? sprite index?) is unconfirmed. GUESSED name/role - the
     * "draw twice at adjacent camera-relative offsets" shape is solid, the
     * exact content being drawn is not confirmed. */
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
