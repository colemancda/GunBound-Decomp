/* The detonation-effect objects: CFlameEffect / CSuperFlameEffect /
 * CRiderEffect - the small transient sprites the weapon detonations spawn
 * (flame plumes, the parachuting "rider"), discovered and evidenced during
 * the 2026-08-17 CValueGuard effect-family audit (commits cbc8a15/da6a9b3).
 *
 * These are FLAT active-object classes on the same 5-slot vtable ABI as
 * CButtonWidget (ButtonWidget.h) - [scalar-deleting dtor, ResolveNamedState,
 * Tick, Draw, NoOpMethod] - registered via RegisterActiveObject for
 * per-frame tick/draw, and every one begins with the ActiveObjectNode
 * header (ActiveObjects.h).  They are NOT CWidget or CProjectile relatives;
 * like CButtonWidget they only SHARE three slot implementations with other
 * classes (0x40ca00 / 0x461c60 / 0x429800).
 *
 * CONFIRMED (per class, from the ctor field writes + the spawner pokes +
 * the vtable dumps read with the corrected 5-slot length - the 13-slot
 * read overruns into the NEXT class's vtable, see Projectile.h's 2026-08-16
 * note on exactly this trap):
 *
 *   CFlameEffect       0x54 bytes  ctor 0x471af0  vtable 0x555ef0
 *     Tick 0x471c70 (TickFlameEffect.c)  Draw 0x471d00 (DrawFlameEffect.c)
 *     spawner SpawnFlameEffect (0x4372f0), animation "flame"
 *   CSuperFlameEffect  0x54 bytes  ctor 0x47e940  vtable 0x5560bc
 *     Tick 0x471c70 (SHARED with CFlameEffect)  Draw 0x47ead0
 *     (DrawSuperFlameEffect.c)
 *     spawner SpawnSuperFlameEffect (0x4373c0), animation "flame"
 *   CRiderEffect       0x48 bytes  ctor 0x4a2780  vtable 0x5564bc
 *     Tick 0x4a2920 (TickRiderEffect.c)  Draw 0x4a2a00
 *     (DrawRiderEffect.c)
 *     spawner SpawnRiderEffect (0x42bb10), texture "rider"
 *
 * The four slot bodies Ghidra never carved (they were reachable only
 * through these vtables) were hand-ported from disassembly 2026-08-18:
 * src/battle/DrawFlameEffect.c / DrawSuperFlameEffect.c /
 * TickRiderEffect.c / DrawRiderEffect.c, with PROGRESS.csv rows added.
 * Their sprite-cache blitters (FUN_00471b40 / FUN_0047e990 /
 * FUN_004a27d0) had their EAX sprite-key parameter promoted at the same
 * time - the new Draw ports are their only callers.
 *
 * CONVENTION NOTE: the ctors receive the object in EAX (operator_new's
 * return used directly - Ghidra's in_EAX), not ECX; the spawners call them
 * immediately after new.  The C++ ctors below are therefore
 * layout-documenting, not yet byte-verified (same gating as the rest of
 * PLAN.md Phase 1).
 *
 * GUESSED: the class names (from the animation/texture names) and the
 * semantics of fields the ctor zeroes but nothing traced yet reads
 * (m_unk15/m_unk20/m_unk28/m_unk2c).
 */
#ifndef GB_CXX_EFFECTS_H
#define GB_CXX_EFFECTS_H

#include "gb_common.h"

#pragma pack(push, 1)

/* --------------------------------------------------------------------------
 * CFlameEffect - one flame plume of a detonation.  SpawnFlameEffect fills
 * x/y, the direction/owner word, a random start phase (rand % the guarded
 * frame divisor DAT_00e9bed8), the texture handle for its param_6 name, and
 * then SetState("flame").
 * ------------------------------------------------------------------------ */
class CFlameEffect {
public:
    CFlameEffect()
        : m_layer(190000), m_unk0c(0), m_unk10(0), m_dead(0), m_unk15(0),
          m_spriteBase(-1), m_texture(0), m_unk20(0), m_state(-1),
          m_unk28(0), m_unk2c(0), m_unk40(0), m_animPhase(0),
          m_width(0x10), m_height(0x80)
    {}

    /* SLOT 0 +0x00: shared scalar-deleting dtor (see ButtonWidget.h). */
    virtual void *Delete(int shouldFree);        /* 0x40ca00 - DeletePoisonedBaseObject */
    /* SLOT 1 +0x04: shared named-state resolver; the spawner calls it with
     * "flame" to start the animation. */
    virtual void SetState(const char *name);     /* 0x461c60 - ResolveNamedState */
    /* SLOT 2 +0x08: per-frame tick - advances the sprite animation, copies
     * the animation-finished flag (+0x34) into m_dead so the registry
     * prunes the object, and steps m_animPhase by 5 (when the fast-forward
     * byte ctx+0x45578 is set) or 2, modulo the guarded frame divisor
     * DAT_00e9bed8; returns the whole-frames advanced. */
    virtual int Tick();                          /* 0x471c70 - TickFlameEffect.c */
    /* SLOT 3 +0x0c: draw - publishes {x, y, phase} into the per-slot flame
     * tables (ctx+0x21644/0x21654) and blits the group sheet cell. */
    virtual void Draw();                         /* 0x471d00 - DrawFlameEffect.c */
    /* SLOT 4 +0x10: shared no-op. */
    virtual void NoOp();                         /* 0x429800 - NoOpMethod */

    /* ActiveObjectNode header (after the vptr the compiler emits at +0x00) */
    u32 m_layer;        /* +0x04: layer key 190000 */
    u32 m_id;           /* +0x08: id within the layer (set at registration) */
    u32 m_unk0c;        /* +0x0c: innerPrev (intrusive list) */
    u32 m_unk10;        /* +0x10: innerNext */
    u8  m_dead;         /* +0x14: prune flag - set when the animation ends */
    u8  m_unk15;        /* +0x15 */
    u8  m_pad16[2];     /* +0x16 */
    int m_spriteBase;   /* +0x18: ctor -1; spawner writes its param_5 */
    u32 m_texture;      /* +0x1c: FindPreloadedTextureByName handle */
    u8  m_unk20;        /* +0x20 */
    u8  m_pad21[3];     /* +0x21 */
    int m_state;        /* +0x24: ctor -1 (named-state index, via slot 1) */
    u32 m_unk28;        /* +0x28 */
    u32 m_unk2c;        /* +0x2c */
    u32 m_unk30;        /* +0x30 */
    u8  m_finished;     /* +0x34: animation-finished, read by Tick */
    u8  m_pad35[3];     /* +0x35 */
    int m_x;            /* +0x38: spawner param_3 */
    int m_y;            /* +0x3c: spawner param_4 */
    u32 m_unk40;        /* +0x40 */
    int m_animPhase;    /* +0x44: rand-seeded, stepped mod DAT_00e9bed8 */
    int m_width;        /* +0x48: ctor 0x10 */
    int m_height;       /* +0x4c: ctor 0x80 */
    u8  m_flags;        /* +0x50: spawner param_1 (randomize-phase toggle) */
    u8  m_pad51[3];     /* +0x51 */
};
GB_STATIC_ASSERT(sizeof(CFlameEffect) == 0x54, flameeffect_size);

/* --------------------------------------------------------------------------
 * CSuperFlameEffect - the SuperShot detonations' flame variant.  Identical
 * layout and shared Tick; its own class only for the ctor (which does NOT
 * preset m_layer - the spawner supplies it) and its own Draw.  Spawner
 * additionally caps its param_2 at <4.
 * ------------------------------------------------------------------------ */
class CSuperFlameEffect {
public:
    virtual void *Delete(int shouldFree);        /* 0x40ca00 */
    virtual void SetState(const char *name);     /* 0x461c60 */
    virtual int Tick();                          /* 0x471c70 - shared with CFlameEffect */
    virtual void Draw();                         /* 0x47ead0 - DrawSuperFlameEffect.c */
    virtual void NoOp();                         /* 0x429800 */

    u32 m_layer;        /* +0x04: NOT set by the ctor (spawner's job) */
    u32 m_id;           /* +0x08 */
    u32 m_unk0c;        /* +0x0c */
    u32 m_unk10;        /* +0x10 */
    u8  m_dead;         /* +0x14 */
    u8  m_unk15;        /* +0x15 */
    u8  m_pad16[2];
    int m_spriteBase;   /* +0x18: ctor -1 */
    u32 m_texture;      /* +0x1c */
    u8  m_unk20;        /* +0x20 */
    u8  m_pad21[3];
    int m_state;        /* +0x24: ctor -1 */
    u32 m_unk28;        /* +0x28 */
    u32 m_unk2c;        /* +0x2c */
    u32 m_unk30;        /* +0x30 */
    u8  m_finished;     /* +0x34 */
    u8  m_pad35[3];
    int m_x;            /* +0x38 */
    int m_y;            /* +0x3c */
    u32 m_unk40;        /* +0x40 */
    int m_animPhase;    /* +0x44 */
    int m_width;        /* +0x48: ctor 0x10 */
    int m_height;       /* +0x4c: ctor 0x80 */
    u8  m_flags;        /* +0x50 */
    u8  m_pad51[3];
};
GB_STATIC_ASSERT(sizeof(CSuperFlameEffect) == 0x54, superflameeffect_size);

/* --------------------------------------------------------------------------
 * CRiderEffect - the falling "rider" decoration.  SpawnRiderEffect places
 * it at (x, min(y, g_nCameraBoundY-0x26)), picks facing from the screen
 * half, and stores its param_3 into m_animPhase (over the ctor's 1000).
 * ------------------------------------------------------------------------ */
class CRiderEffect {
public:
    CRiderEffect()
        : m_layer(0x186a7), m_unk0c(0), m_unk10(0), m_dead(0), m_unk15(0),
          m_spriteBase(-1), m_texture(0), m_unk20(0), m_state(-1),
          m_unk28(0), m_unk2c(0), m_x(0), m_y(0), m_facing(0),
          m_targetY(1000)
    {}

    virtual void *Delete(int shouldFree);        /* 0x40ca00 */
    virtual void SetState(const char *name);     /* 0x461c60 - called with the
                                                    anim right after the
                                                    "rider" texture lookup */
    virtual int Tick();                          /* 0x4a2920 - TickRiderEffect.c */
    virtual void Draw();                         /* 0x4a2a00 - DrawRiderEffect.c */
    virtual void NoOp();                         /* 0x429800 */

    u32 m_layer;        /* +0x04: layer key 0x186a7 (100007 - the projectile
                           id space, cf. 0x186aa in the sim tree walks) */
    u32 m_id;           /* +0x08 */
    u32 m_unk0c;        /* +0x0c */
    u32 m_unk10;        /* +0x10 */
    u8  m_dead;         /* +0x14 */
    u8  m_unk15;        /* +0x15 */
    u8  m_pad16[2];
    int m_spriteBase;   /* +0x18: ctor -1 */
    u32 m_texture;      /* +0x1c: the "rider" texture handle */
    u8  m_unk20;        /* +0x20 */
    u8  m_pad21[3];
    int m_state;        /* +0x24: ctor -1 */
    u32 m_unk28;        /* +0x28 */
    u32 m_unk2c;        /* +0x2c */
    u32 m_unk30;        /* +0x30 */
    u32 m_unk34;        /* +0x34 */
    int m_x;            /* +0x38: spawn x */
    int m_y;            /* +0x3c: spawn y, clamped to g_nCameraBoundY-0x26 */
    u8  m_facing;       /* +0x40: g_nCameraBoundX/2 < x */
    u8  m_pad41[3];
    int m_targetY;      /* +0x44: descent target (ctor 1000; spawner param_3) -
                           NOT an anim phase: TickRiderEffect falls to it, then
                           drifts sideways */
};
GB_STATIC_ASSERT(sizeof(CRiderEffect) == 0x48, ridereffect_size);

#pragma pack(pop)

#endif /* GB_CXX_EFFECTS_H */
