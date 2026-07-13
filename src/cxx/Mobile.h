/* CMobile - the in-battle "mobile" (tank) object and its 16 concrete
 * subclasses. Reconstruction of the mobile factory documented in
 * ARCHITECTURE.md ("the battle mobile object" struct-size anchor); see
 * src/cxx/README.md for conventions and confidence levels.
 *
 * CONFIRMED (from the binary):
 *  - The object is 0xd1d4 (53,716) bytes; allocated by CreateMobile (0x42b0b0)
 *    via operator_new + base ctor InitMobile (0x458b80).
 *  - Single-inheritance hierarchy: one base vtable at 0x555c68 (dumped: 8
 *    slots) + 16 concrete subclass vtables (one per mobileType 0..0xF), each
 *    overriding ONLY slot 0 (the scalar-deleting destructor) and slot 7 (the
 *    per-type "main action"); type 13 additionally overrides slot 5. Slots
 *    1-6 are shared across all types. The 16 vtable addresses and their slot
 *    0/7 overrides were dumped from the binary (see the table below).
 *  - Slot 6 is 0x45f910 (HandleFireInput, shared by every mobile). Slot 4 is
 *    a no-op (0x429800). Base slot 7 is CGameState_NoOpVirtual_B (0x4fdef0),
 *    so the base mobile does nothing on its main action - every real mobile
 *    overrides it.
 *  - The named field offsets below (from InitMobile / CreateMobile /
 *    HandleFireInput).
 *
 * GUESSED: all slot names except HandleFireInput; the canonical mobile NAME
 * for each type id (Armor/Mage/Nak/...) is NOT mapped - the 16 subclasses
 * differ only by behaviour (vtable), and neither the binary strings nor
 * characterdata.dat carry a type->name table (see ARCHITECTURE.md /
 * FILEFORMATS.md). Interior fields between the named ones are unmapped
 * (padding).
 */
#ifndef GB_CXX_MOBILE_H
#define GB_CXX_MOBILE_H

#include "gb_common.h"

/* The 16 mobile type ids, indexed identically by CreateMobile's factory
 * switch AND by characterdata.dat's 16 stat records. Names are unknown, so
 * these stay numeric.
 *
 *   type -> concrete vtable  (slot0 = ~dtor, slot7 = MainAction; both
 *                             per-type. * = type 13 also overrides slot5)
 *     0  0x555af8   4  0x556264   8  0x555d34   12  0x555f18
 *     1  0x556230   5  0x555c14   9  0x5560f0   13  0x555e54 *
 *     2  0x5562a8   6  0x556448  10  0x555f7c   14  0x556038
 *     3  0x5566a0   7  0x5561ec  11  0x556640   15  0x555d54
 *   default (out-of-range) -> type 0's vtable (0x555af8).
 *
 * The 16 subclasses carry NO extra data members (all 0xd1d4 bytes, identical
 * layout); they exist purely to swap the vtable, so they are represented here
 * by this table rather than 16 redundant empty subclass declarations. */
enum MobileType {
    MOBILE_TYPE_00 = 0,  MOBILE_TYPE_01, MOBILE_TYPE_02, MOBILE_TYPE_03,
    MOBILE_TYPE_04,      MOBILE_TYPE_05, MOBILE_TYPE_06, MOBILE_TYPE_07,
    MOBILE_TYPE_08,      MOBILE_TYPE_09, MOBILE_TYPE_10, MOBILE_TYPE_11,
    MOBILE_TYPE_12,      MOBILE_TYPE_13, MOBILE_TYPE_14, MOBILE_TYPE_15,
    MOBILE_TYPE_COUNT = 16
};

#pragma pack(push, 1)
/* The battle mobile. Declaration order of the virtuals IS the confirmed base
 * vtable order (0x555c68, 8 slots). */
class CMobile {
public:
    /* slot 0 +0x00: scalar-deleting destructor. Base 0x45a540 (-> base dtor
     * body 0x45a560, then conditional free); every subclass overrides with
     * its own (e.g. type 0 = 0x44e8f0). */
    virtual ~CMobile();
    /* slot 1 +0x04: 0x461c60 (shared) - acquires a handle: if +0x1c != 0,
     * +0x24 = FindStringNoCase(), sets the +0x20 active flag / +0x34 fail flag. */
    virtual void v1_AcquireHandle();
    /* slot 2 +0x08: 0x461ca0 = SimulateMobileFrame (shared) - the per-frame
     * mobile tick: runs the anti-cheat guard checks, reads the fire
     * angle/power CValueGuards (0x243/0x2cc int-index = byte 0x90c/0xb30),
     * advances sprite animation, records replay events, updates the
     * color/AI counters. Dispatches to several other vtable slots. */
    virtual void v2_SimulateFrame();
    /* slot 3 +0x0c: 0x462900 = RenderMobile (shared) - the mobile draw pass:
     * blits the tank sprite via BlitSpriteAttached (0x45b730) / BlitSpriteDirect
     * (0x45b900) - direct (non-RLE) sprite copies clipped to the 128x128 tile -
     * draws the aim/trajectory markers (BlitRLESprite), and sprintf's a "%d,%d"
     * coordinate overlay drawn digit-by-digit; populates the per-slot
     * turn-display array. (The +0x90c fire-angle field is fed through the
     * FUN_004ead90/70 = (x+90)/360 and x/360 helpers, then FloatToInt64.) */
    virtual void v3_Render();
    /* slot 4 +0x10: 0x429800 (shared) - no-op (`return;`). */
    virtual void v4_NoOp();
    /* slot 5 +0x14: 0x45c6e0 = ComputeMobileGroundY (shared; type 13 overrides
     * -> 0x46cbb0) - queries the terrain height below the mobile via
     * FindGroundHeightAtColumn (0x4e4340, a downward column scan of the terrain
     * bitmap for the first solid pixel), guard-verified, and returns it. */
    virtual int v5_ComputeGroundY();
    /* slot 6 +0x18: 0x45f910 = HandleFireInput (shared) - decides a fire
     * attempt's outcome and emits the 0x8403 Fire action; reads the fire
     * angle/power CValueGuard objects at byte 0x90c / 0xb30 (see below). CONFIRMED. */
    virtual void HandleFireInput();
    /* slot 7 +0x1c: the per-type MAIN action = the weapon-fire dispatcher,
     * `(this, animEvent, subType)`. Base = CGameState_NoOpVirtual_B (0x4fdef0,
     * no-op); every subclass overrides it with its own weapon set (type 0 =
     * Mobile00_MainAction 0x44e920). It switch()es on the animation event and,
     * at the fire frame, reads the fire angle/power guards (+0x90c/+0xb30) and
     * position, then spawns the projectile via the shared shot-spawners
     * (SpawnPrimaryShot / SpawnItemProjectile / SpawnSuperShot) and acquires/releases the
     * firing sound channel (AcquireSoundChannel 0x4ee9b0, handle at +0xb0a4).
     * This is where the 16 mobiles' distinct behaviour lives; only type 0 is
     * named so far. */
    virtual void MainAction();

    /* Per-type slot-7 overrides. Each of the 16 mobile types installs its
     * own weapon-fire dispatcher in vtable slot 7; the base MainAction above
     * is the no-op every type replaces. These are NOT extra virtuals on the
     * base class - they're the concrete slot-7 implementations, declared as
     * plain members here (the 16 subclasses share CMobile's layout, so no
     * subclass type is needed - see the class-header note). Only type 0 is
     * reconstructed so far; the other 15 remain raw. Signature is
     * (this, animEvent, subType). */
    void Mobile00_MainAction(int animEvent, int subType);  /* 0x44e920 */

    /* ---- data members (confirmed offsets; interior gaps are unmapped) ---- */
    u32  m_idBase;             /* +0x4: InitMobile seeds 0x186a1 (100001) - id/health base */
    u32  m_owner;              /* +0x8: InitMobile arg (owner/slot index passed to the ctor) */
    u8   m_padc[0xc];
    u32  m_spriteId;           /* +0x18: CreateMobile: mobileType + 5000 (primary sprite id) */
    u32  m_tankTexture;        /* +0x1c: CreateMobile: tank%d texture handle; also the +0x1c handle v1() polls */
    u8   m_pad20[0x34];
    u32  m_avataTexture;       /* +0x54: CreateMobile: avata texture handle */
    /* The "fire angle" / "fire power" are NOT scalars here. HandleFireInput
     * accesses them as `param_1 + 0x243` / `+0x2cc` on an int* (Ghidra
     * type-propagation, 2026), i.e. BYTE offsets 0x90c / 0xb30, and passes them
     * to the CValueGuard encoders (EncodeChecksumDeltaSub / ScrubChecksumGuard)
     * - each is a 0x224-byte anti-cheat guard object, not a u8. (An earlier
     * draft placed u8 m_fireAngle/m_firePower at 0x243/0x2cc, mistaking the
     * int-INDEX for a byte offset; corrected to padding.) Most of CMobile is
     * such guard objects; they are left as padding until CValueGuard is modeled. */
    u8   m_pad58[0x8ac];
    u32  m_spriteId2;          /* +0x904: CreateMobile: mobileType + 0x13ec (5100+type) - secondary sprite id */
    u8   m_pad908[0xa50d];
    char m_name[0xd];          /* +0xae15: CreateMobile copies the player name here (0xD stride; 2nd string at +0xae22) */
    u8   m_padae22[0x11ce];
    u32  m_type13Field;        /* +0xbff0: set to 2 by the type-13 ctor FUN_0046cb60 (0 for other types) */
    u8   m_padbff4[0x11e0];    /* tail padding to the confirmed 0xd1d4 size */
};
#pragma pack(pop)

#endif /* GB_CXX_MOBILE_H */
