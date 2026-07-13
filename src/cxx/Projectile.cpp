/* CProjectile methods - promoted from the raw C ports under src/battle/
 * (DestroyProjectile 0x455570, AnimateProjectileTick 0x48f1c0). See
 * Projectile.h and src/cxx/README.md.
 *
 * Only these two methods are promoted so far - SimulateProjectileFrame
 * (0x455cc0, ~660 lines) and DetonateProjectile (0x4572b0, ~610 lines)
 * are large enough to be their own follow-up unit of work, and
 * InitProjectile (0x454dc0) is the ~29-guard-cell constructor body,
 * whose individual field offsets are not yet mapped to real names (see
 * Projectile.h's "left as padding" note) - promoting it faithfully means
 * preserving the exact same raw offsets, not inventing a cleaner layout.
 *
 * Both ports below keep the SAME register-passed-cell-pointer gap the
 * raw C already had: DestroyProjectile's ScrambleChecksumGuardBytes/
 * TreeLowerBound calls and AnimateProjectileTick's PeekPacketChecksumBool/
 * PeekPacketChecksumState/EncodeOutgoingPacketField calls never show a
 * cell argument in Ghidra's decompile (the real cell pointer arrives via
 * a register Ghidra didn't resolve, same class of issue as Widget.cpp's
 * asm-capture shims) - rather than invent an unverified register capture,
 * these stay exactly as free-function calls with the same argument shape
 * the raw port had. Byte-verify before trusting this beyond "same
 * behavior as the raw C, now living on the class."
 *
 * score.sh status (2026-07-12):
 *  - AnimateProjectileTick: 3200/4500 - a real but partial match, likely
 *    limited by the same unresolved cell-pointer gap above.
 *  - ~CProjectile (dtor): 39655/39600 (worse than max - essentially no
 *    byte match). Root cause found: DestroyProjectile.c's `local_4`
 *    (written before every one of the 29 checks, never read in the
 *    visible C) plus the `unaff_FS_OFFSET`/`puStack_8` frame push at the
 *    top is real MSVC SEH scaffolding (a `_except_handler3`-style
 *    exception-registration record with `local_4` as the per-block
 *    unwind-state marker) - the original genuinely wraps this destructor
 *    body in `__try`/`__finally`. This port strips that scaffolding
 *    entirely (same accepted tradeoff as other SEH-bearing functions in
 *    this tree - see src/README.md), which accounts for a real size gap
 *    (compiled here: 0x340 bytes vs. the original's 0x5e8) on top of the
 *    already-known cell-pointer gap. Reproducing real `__try`/`__finally`
 *    to close this is unstarted follow-up work, not attempted here.
 *  - DetonateProjectile: 155950/129800 (also worse than max). Built from a
 *    FRESH Ghidra decompile rather than the stale src/battle/
 *    DetonateProjectile.c raw port - see that method's own header comment
 *    for the two concrete bugs this fixed (RegisterActiveObject's dropped
 *    4 args, InitProjectile's call-site argument order). Compiled size
 *    (0xf04) is proportionally close to the original (0x1322, ~78%),
 *    unlike the destructor's structural mismatch - this poor score is
 *    accumulated noise from ~45 unresolved guard-cell call targets across
 *    a function this size, the same category of gap already documented
 *    above, not a structural-shape problem. SEH also stripped, same
 *    tradeoff as the destructor.
 *
 * FIXED (2026-07-13): the `iStack_ab0` uninitialized-read bug noted below
 * is now resolved. Root cause CONFIRMED (not just suspected) by reading
 * src/network/EncodeChecksumDeltaShr.c and its siblings' own raw C: each
 * writes `*(byte*)(out+0x220) = 0; *(u32*)(out+0x14) = 0;` into its own
 * `out` parameter - exactly CValueGuard's `activeFlag` (+0x220) and
 * `tableHandle` (+0x14) offsets. So `out` is a full 0x224-byte
 * `CValueGuard`-shaped LOCAL scratch cell, not a 20-byte buffer - and
 * Ghidra's `iStack_ab0`/`uStack_8a4` (etc.) locals this file used to
 * declare separately are just that same local's `.tableHandle`/
 * `.activeFlag` fields, split off because only those sub-fields get read
 * back later. Confirmed identically across EncodeChecksumDeltaShr,
 * EncodeChecksumPairDiff, EncodeChecksumDeltaAdd, EncodeChecksumPairSum,
 * EncodeChecksumNegate - all five raw C files show the same two writes.
 * Fix applied below: `auStack_ac4`/`auStack_8a0` are now real
 * `CValueGuard` locals (matching `auStack_67c`/`auStack_458`/
 * `auStack_234`, which were ALREADY correctly declared as 548 = 0x224
 * bytes by Ghidra) instead of undersized byte arrays + disconnected
 * trailer locals - the guard checks now read `.tableHandle` off the
 * SAME object the Encode* call already wrote into, no longer
 * uninitialized. This also unblocks a future SimulateProjectileFrame
 * retry (previously abandoned over this exact ambiguity, see git log).
 * score.sh after this fix: 156085/129800 - essentially unchanged from
 * 155950/129800 before, as expected: this was a correctness fix (real
 * UB removed), not a byte-match fix - the score gap is still dominated
 * by the ~45 unresolved cell-target calls and stripped SEH documented
 * above, unrelated to this bug. */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include "Projectile.h"
#include "ValueGuard.h"

extern "C" {
void ScrambleChecksumGuardBytes(void);
void TreeLowerBound(void *scratch);
void AdvanceSpriteAnimation(void);
void FUN_004585e0(void);
char PeekPacketChecksumBool(void);
int PeekPacketChecksumState(void);
void EncodeOutgoingPacketField(unsigned int value);
extern CRITICAL_SECTION DAT_005a9068; /* the guard family's shared lock, defined in ValueGuard.cpp */

/* DetonateProjectile's extra dependencies. Declared locally (not added to
 * functions.h) since several of these have a WRONG signature there today
 * (e.g. functions.h's RegisterActiveObject()/CalculateAngleFromDelta()
 * take zero params, matching the raw C's buggy call sites, not the real
 * shape Ghidra's fresh decompile shows) - fixing functions.h globally is
 * out of scope here. */
char PeekPacketChecksumBool_5(int, unsigned int, int, int, unsigned int, int);
void *operator_new(unsigned int size);
void InitProjectile(void *thisArg, int type);
char CheckGuardedBoolAnd(int cond);
void EmitChecksumSum(void *cell);
int EncodeChecksumDeltaShr(void *cell, void *out, int shift);
char PacketChecksumLessThan(void *cell, int value);
void QueueOutgoingPacketField(unsigned int value);
unsigned int EncodeChecksumDeltaDiv(int cell, void *out, int div);
unsigned int EncodeChecksumPairDiff(int cell, void *out, unsigned int a);
unsigned int EncodeChecksumPairSum(int cell, void *out, unsigned int a);
char CompareChecksumPair(void *cellA, unsigned int cellB);
void ScrubChecksumGuard(void *cell);
unsigned int EncodeChecksumNegate(void *cell, void *out);
void EncodeChecksumState(unsigned int value);
void SetGuardedBool(int value);
char PacketChecksumGreaterEqual(void *cell, unsigned int value);
char CheckBothGuardedBools(void);
void SyncOutgoingChecksumField(int arg1, void *cell);
void FUN_00436070(void *base, unsigned int a, void *b);
void FUN_0043af40(unsigned int a, void *b, int c, void *d, int e, unsigned int f, unsigned char g);
void FUN_00431d90(unsigned char a, int b, int c, unsigned int d, unsigned int e, unsigned int f,
                   unsigned int g, unsigned int h);
char FUN_004e4fe0(void *base, void *a, void *b, int c, int d, int e);
int CalculateAngleFromDelta_2(int dx, int dy);
int FloatToInt64_0(void);
void *RegisterActiveObject_4(void *a, void *b, void *c, void *d);
void FUN_00432320(unsigned char a, int b, int c, unsigned int d, unsigned int e, unsigned int f,
                   unsigned int g, unsigned int h, unsigned int i);
unsigned int FUN_004ac4d0(void);
int FUN_004ac400(void);
char PeekChecksumStateUnderLock(void *out);
void ApplyCraterExcavation(unsigned int a, void *b, unsigned int c, unsigned int d, unsigned int e,
                            void *f, unsigned int g, unsigned int h);
void RebuildTerrainColumnCache(void *base);
void FUN_00450eb0(void *a, unsigned int b, void *c, int d, int e, int f);
void FUN_00436ac0(unsigned int a, unsigned int b);
void FUN_004372f0(int a, void *b, unsigned int c, unsigned int d, void *e);
void FUN_00437150(unsigned int a, unsigned int b, int c, unsigned int d);
char InitChecksumSeed(void);
char CompareChecksumExceeds(void *cellA, void *cellB);
void AcquireSoundChannel(int a);
int _rand(void);

extern int g_clientContext;             /* _DAT_005b3484 */
extern unsigned char DAT_006a7708;      /* address anchors: only ever used as    */
extern unsigned char DAT_006a773c;      /* "&DAT_xxx + g_clientContext" bases -  */
extern unsigned char DAT_006a7758;      /* declared as 1-byte so that arithmetic */
extern unsigned char DAT_006a7f70;      /* on them matches the raw port exactly. */
extern unsigned char DAT_006a7f8c;
extern unsigned char DAT_006a7f74;
extern int g_nCameraBoundX, g_nCameraBoundY, g_nCameraX, g_nCameraY;
extern int g_nCameraScrollX, g_nCameraScrollY;
extern unsigned char DAT_006a7734, DAT_006a7736, DAT_006a7f6c;
extern int DAT_006a770c, DAT_006a772c, DAT_006a7730, DAT_006a7750, DAT_006a7754;
extern unsigned char DAT_005f3768, DAT_005f376c;
extern void *PTR_FUN_0055658c;
}

/* 0x455570 DestroyProjectile, vtable slot 0. Releases the object's 29
 * CValueGuard/GuardedBool cells whose registry handle is still live (scans
 * the same field offsets InitProjectile wrote), highest offset first, then
 * swaps in the "being destroyed" vtable. Field offsets AND control-flow
 * shape are copied verbatim from the raw port (29 unrolled if-blocks, not
 * a loop) - MSVC 7.1 does not codegen a hand-written loop the same as its
 * own unrolled original, so a loop+table version scored essentially zero
 * match (39480/39600) before this rewrite. `scratch` is a fresh 8-byte
 * stack buffer, exactly like the raw port's `local_14` - NOT `this`. */
CProjectile::~CProjectile()
{
    unsigned int *self = reinterpret_cast<unsigned int *>(this);
    unsigned char scratch[8];

    if (self[0xf60] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xed7] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xe4d] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xd80] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xcf7] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xc6b] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xbe2] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xb59] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xad0] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0xa47] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x9be] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x935] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x8ac] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x823] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x79a] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x710] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x687] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x5fe] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x575] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x4ec] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x463] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x3da] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x34b] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x2c2] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x239] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x1b0] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x127] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x9e]  != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (self[0x15]  != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
}

/* 0x48f1c0 AnimateProjectileTick, vtable slot 2. Per-frame animate tick:
 * dispatch DetonateProjectile (was a manual vtable-slot-6 call in the raw
 * port - now a real virtual call, the same operation), advance the sprite
 * animation, then bump the +0x3b44 frame counter and fire a replay event
 * (EncodeOutgoingPacketField) once it reaches 5. */
void CProjectile::AnimateProjectileTick()
{
    DetonateProjectile();
    FUN_004585e0();
    AdvanceSpriteAnimation();
    if (PeekPacketChecksumBool() != 0) {
        EnterCriticalSection(&DAT_005a9068);
        EncodeOutgoingPacketField(PeekPacketChecksumState() + 1);
        LeaveCriticalSection(&DAT_005a9068);
    }
    unsigned int *frameCounter = reinterpret_cast<unsigned int *>(
        reinterpret_cast<char *>(this) + 0x3b44);
    unsigned int next = *frameCounter + 1;
    *frameCounter = next;
    if (next == 5) {
        EnterCriticalSection(&DAT_005a9068);
        EncodeOutgoingPacketField(PeekPacketChecksumState());
        LeaveCriticalSection(&DAT_005a9068);
    }
}

/* 0x4572b0 DetonateProjectile, vtable slot 6. Impact/detonation handler:
 * built from a FRESH Ghidra decompile (not the stale src/battle/
 * DetonateProjectile.c raw port), because the raw port has real bugs
 * relative to the current decompile - notably RegisterActiveObject's call
 * site: the raw port calls it with ZERO args, but the fresh decompile
 * shows 4 (`punk`, `unaff_EDI`, `unaff_ESI`, `unaff_EBP`). EDI/ESI/EBP are
 * callee-saved and never reassigned anywhere else in this function, so
 * they are genuine incoming register-passed parameters (Ghidra's
 * "unaff_REG" naming for a register whose function-entry value survives
 * untouched) - captured via inline asm as the first statement, same
 * technique as Widget.cpp's asm-capture shims. `punk` is NOT a register
 * capture - it's set to the literal 8 mid-function and never reassigned
 * before the RegisterActiveObject call, so it's threaded through as a
 * real local.
 *
 * The apparent `while (true) { ... }` dead code after the unconditional
 * `goto LAB_004579de;` is NOT a raw-port artifact - Ghidra's OWN current
 * decompile reproduces the exact same shape (verified live), so this is
 * an inherent decompiler-structuring quirk on the real control flow, not
 * a bug to "fix". Preserved as-is per this project's standing rule to
 * trust a fresh decompile's structure over inventing a "more correct" one.
 *
 * Known gaps (same class as ~CProjectile / AnimateProjectileTick):
 *  - The ~45 PeekPacketChecksumState/EncodeOutgoingPacketField/
 *    PeekPacketChecksumBool calls never show a resolvable guard-cell
 *    target in EITHER the raw port or this fresh decompile - kept as
 *    free-function calls with the same argument shape both already had.
 *  - SEH (__try/__finally) scaffolding stripped, same tradeoff as the
 *    destructor - expect a real, not-yet-measured score gap from this.
 *  - The many DAT_006a77xx/g_nCamera* globals are camera/terrain-state
 *    address anchors reached via "&DAT_xxx + g_clientContext" - copied
 *    verbatim, not independently re-derived or renamed here.
 *  - Several extern helpers below (RegisterActiveObject_4,
 *    CalculateAngleFromDelta_2, etc.) are declared locally with a
 *    best-guess signature matching this call site, suffixed to avoid
 *    colliding with functions.h's existing (differently-shaped, and in
 *    at least RegisterActiveObject's case demonstrably wrong) declarations -
 *    reconciling functions.h globally is out of scope here. */
void CProjectile::DetonateProjectile()
{
    void *capturedEdi, *capturedEsi, *capturedEbp;
    __asm {
        mov capturedEdi, edi
        mov capturedEsi, esi
        mov capturedEbp, ebp
    }

    CProjectile *self = this;
    CProjectile *pCVar9;
    int *piVar18;
    int iVar5, iVar6, iVar10, iVar11, iVar12, iVar14;
    unsigned int uVar8, uVar13, uVar16;
    char cVar4;
    bool bVar2, bVar3, bVar17, bVar20;
    void *punk = 0;
    unsigned int *apuStack_ad0[2];
    void *puStack_af4;
    CValueGuard auStack_ac4, auStack_8a0;
    CValueGuard auStack_67c, auStack_458, auStack_234;
    unsigned int local_ae8;
    unsigned int uStack_adc, uVar21, uVar22, uVar23, uVar24;
    void *local_ad4;
    CProjectile *pCStack_ac8, *pCStack_ad8;
    CValueGuard *puVar15;

    EnterCriticalSection(&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    iVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar6 + iVar5);
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    iVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar6 + iVar5);
    LeaveCriticalSection(&DAT_005a9068);
    punk = (void *)8;
    /* was a manual vtable slot-5 (+0x14) call - now a real virtual call.
     * SimulateFrame's true 2nd arg (see Projectile.h) isn't visible at
     * THIS call site either (DetonateProjectile's own raw decompile shows
     * a bare no-stack-arg call) - passing 0 is a placeholder, not a
     * verified value; flagged in Projectile.h as follow-up. */
    SimulateFrame(0);
    cVar4 = PeekPacketChecksumBool();
    if (cVar4 == '\0') {
        EncodeChecksumDeltaShr(self->m_pad3d + 3, &auStack_ac4, 8);
        EnterCriticalSection(&DAT_005a9068);
        uVar8 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(uVar8);
        LeaveCriticalSection(&DAT_005a9068);
        if (auStack_ac4.tableHandle != 0) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(apuStack_ad0);
            self = pCStack_ad8;
        }
        EncodeChecksumDeltaShr(self->m_pad3d + 0x227, &auStack_ac4, 8);
        EnterCriticalSection(&DAT_005a9068);
        uVar8 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(uVar8);
        LeaveCriticalSection(&DAT_005a9068);
        pCVar9 = self;
        if (auStack_ac4.tableHandle != 0) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(apuStack_ad0);
            pCVar9 = pCStack_ad8;
        }
        cVar4 = CheckGuardedBoolAnd(*reinterpret_cast<int *>(pCVar9->m_pad3d + 0xf0b) != 0);
        if (cVar4 == '\0') {
            EmitChecksumSum(pCVar9->m_pad3d + 0xab7);
            EmitChecksumSum(pCVar9->m_pad3d + 0xcdb);
        } else {
            EnterCriticalSection(&DAT_005a9068);
            uVar13 = PeekPacketChecksumState();
            LeaveCriticalSection(&DAT_005a9068);
            if ((int)((uVar13 ^ (int)uVar13 >> 0x1f) - ((int)uVar13 >> 0x1f)) < 200) {
                cVar4 = PacketChecksumLessThan(pCVar9->m_pad3d + 0x44b, 0);
                uVar8 = cVar4 == '\0' ? 200 : 0xffffff38;
                QueueOutgoingPacketField(uVar8);
            }
            uVar8 = EncodeChecksumDeltaDiv(*reinterpret_cast<int *>(pCVar9->m_pad3d + 0xf0b) + 0x25c,
                                            &auStack_67c, 4);
            uVar8 = EncodeChecksumPairDiff(*reinterpret_cast<int *>(pCVar9->m_pad3d + 0xf0b) + 0x38,
                                            &auStack_458, uVar8);
            bVar2 = false;
            bVar20 = false;
            cVar4 = CompareChecksumPair(pCVar9->m_pad3d + 0xf17, uVar8);
            if (cVar4 == '\0') {
                uVar8 = EncodeChecksumDeltaDiv(*reinterpret_cast<int *>(pCVar9->m_pad3d + 0xf0b) + 0x25c,
                                                &auStack_8a0, 4);
                uVar8 = EncodeChecksumPairSum(*reinterpret_cast<int *>(pCVar9->m_pad3d + 0xf0b) + 0x38,
                                               &auStack_ac4, uVar8);
                bVar2 = true;
                bVar20 = true;
                cVar4 = CompareChecksumPair(reinterpret_cast<void *>(uVar8), *reinterpret_cast<unsigned int *>(pCVar9->m_pad3d + 0xf17));
                bVar3 = cVar4 == '\0';
            } else {
                bVar3 = true;
            }
            if (bVar20) ScrubChecksumGuard(&auStack_ac4);
            if (bVar2) ScrubChecksumGuard(&auStack_8a0);
            ScrubChecksumGuard(&auStack_458);
            ScrubChecksumGuard(&auStack_67c);
            if (bVar3) {
                iVar5 = *reinterpret_cast<int *>(pCVar9->m_pad3d + 0xf13) + 1;
                *reinterpret_cast<int *>(pCVar9->m_pad3d + 0xf13) = iVar5;
                if (iVar5 < 3) {
                    uVar8 = EncodeChecksumNegate(pCVar9->m_pad3d + 0x44b, &auStack_234);
                    EncodeChecksumState(uVar8);
                    ScrubChecksumGuard(&auStack_234);
                } else {
                    SetGuardedBool(0);
                }
            }
        }
        EnterCriticalSection(&DAT_005a9068);
        iVar5 = PeekPacketChecksumState();
        LeaveCriticalSection(&DAT_005a9068);
        if (iVar5 < 0) {
        LAB_004583d9:
            pCVar9->m_pad0c[8] = '\x01';
            cVar4 = PeekPacketChecksumBool();
            if (cVar4 != '\0' && InitChecksumSeed() == '\0') {
                iVar5 = *reinterpret_cast<int *>(*reinterpret_cast<int *>(g_clientContext + 0x621e4) + 0x24);
                uVar8 = (iVar5 == 5) ? 2u : (iVar5 == 6 ? 0x19u : uVar8);
                QueueOutgoingPacketField(uVar8);
                iVar5 = g_clientContext;
                if (*reinterpret_cast<int *>(&DAT_005f3768 + g_clientContext) != 0) {
                    *reinterpret_cast<unsigned int *>(&DAT_005f3768 + g_clientContext) = 5;
                    *reinterpret_cast<unsigned int *>(&DAT_005f376c + iVar5) = 0;
                }
            }
        } else {
            iVar5 = *reinterpret_cast<int *>(&g_nCameraBoundX + g_clientContext);
            EnterCriticalSection(&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            LeaveCriticalSection(&DAT_005a9068);
            if (iVar5 <= iVar6 ||
                PacketChecksumGreaterEqual(self->m_pad3d + 0x113b,
                                            *reinterpret_cast<unsigned int *>(&g_nCameraBoundY + g_clientContext)) != '\0' ||
                PacketChecksumLessThan(self->m_pad3d + 0x113b, 0xfffffc18) != '\0')
                goto LAB_004583d9;
        }
        cVar4 = CheckBothGuardedBools();
        if (cVar4 != '\0') {
            EnterCriticalSection(&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            LeaveCriticalSection(&DAT_005a9068);
            EnterCriticalSection(&DAT_005a9068);
            iVar10 = PeekPacketChecksumState();
            LeaveCriticalSection(&DAT_005a9068);
            iVar5 = g_clientContext;
            piVar18 = reinterpret_cast<int *>(&DAT_006a7708 + g_clientContext);
            cVar4 = PeekPacketChecksumBool();
            if (cVar4 == '\0' && (&DAT_006a7758)[iVar5] != 0) {
                if ((&DAT_006a7736)[iVar5] == 1 &&
                    ((uVar13 = iVar6 - g_nCameraY, uVar16 = (int)uVar13 >> 0x1f,
                      200 < (int)((uVar13 ^ uVar16) - uVar16)) ||
                     (uVar13 = iVar10 - g_nCameraX, uVar16 = (int)uVar13 >> 0x1f,
                      300 < (int)((uVar13 ^ uVar16) - uVar16)))) {
                    (&DAT_006a7736)[iVar5] = 0;
                }
                iVar11 = (399 < iVar10) ? iVar10 : 400;
                iVar12 = g_nCameraBoundX - 400;
                if (iVar11 <= iVar12 && iVar10 < 400) iVar12 = 400;
                else if (iVar11 <= iVar12) iVar12 = iVar10;
                iVar10 = (-0x15 < iVar6) ? iVar6 : -0x14;
                iVar11 = g_nCameraBoundY - 0x104;
                if (iVar10 <= iVar11 && -0x15 < iVar6) iVar11 = iVar6;
                else if (iVar10 <= iVar11) iVar11 = -0x14;
                iVar6 = *piVar18 - iVar12;
                g_nCameraScrollY = iVar11;
                if ((DAT_006a770c - iVar11) * (DAT_006a770c - iVar11) + iVar6 * iVar6 < 40000 &&
                    (DAT_006a7734 == 1 || DAT_006a7f6c == 0)) {
                    g_nCameraX = iVar12;
                    *piVar18 = iVar12;
                    g_nCameraY = iVar11;
                    DAT_006a770c = iVar11;
                }
                if (DAT_006a7734 == 0 && DAT_006a7f6c == 1 && DAT_006a7736 == 0) {
                    iVar6 = DAT_006a7730;
                    iVar10 = (iVar12 <= iVar6) ? iVar12 : iVar6;
                    iVar14 = DAT_006a772c;
                    if (iVar14 <= iVar10 && iVar12 <= iVar6) iVar14 = iVar12;
                    else if (iVar14 <= iVar10) iVar14 = iVar6;
                    g_nCameraScrollX = iVar14;
                }
                if (DAT_006a7734 == 1) {
                    g_nCameraScrollX = iVar12;
                    g_nCameraScrollY = iVar11;
                }
            }
        }
        goto LAB_004585ba;
    }
    SyncOutgoingChecksumField(self->m_ctorArg1, self->m_pad3d + 0x113b);
    cVar4 = PeekPacketChecksumBool();
    if (cVar4 != '\0') {
        char *pcVar7;
        EnterCriticalSection(&DAT_005a9068);
        iVar5 = PeekPacketChecksumState();
        LeaveCriticalSection(&DAT_005a9068);
        if (-1 < iVar5 && iVar5 < *reinterpret_cast<int *>(&g_nCameraBoundX + g_clientContext)) {
            pcVar7 = reinterpret_cast<char *>(*reinterpret_cast<int *>(&DAT_006a773c + g_clientContext) + iVar5);
            puStack_af4 = (void *)0;
            if (0 < *reinterpret_cast<int *>(&g_nCameraBoundY + g_clientContext)) {
                do {
                    if (*pcVar7 != '\0') goto LAB_004573fa;
                    pcVar7 += *reinterpret_cast<int *>(&g_nCameraBoundX + g_clientContext);
                    puStack_af4 = reinterpret_cast<void *>(reinterpret_cast<int>(puStack_af4) + 1);
                } while (reinterpret_cast<int>(puStack_af4) < *reinterpret_cast<int *>(&g_nCameraBoundY + g_clientContext));
            }
        }
        puStack_af4 = reinterpret_cast<void *>(0x2710);
    LAB_004573fa:
        EnterCriticalSection(&DAT_005a9068);
        uVar8 = PeekPacketChecksumState();
        LeaveCriticalSection(&DAT_005a9068);
        FUN_00436070(&DAT_006a7f70 + g_clientContext, uVar8, puStack_af4);
        local_ae8 = 1;
        if (0 < (int)self->m_field3f94) local_ae8 = self->m_field3f94;
        EnterCriticalSection(&DAT_005a9068);
        uVar8 = PeekPacketChecksumState();
        LeaveCriticalSection(&DAT_005a9068);
        EnterCriticalSection(&DAT_005a9068);
        iVar5 = PeekPacketChecksumState();
        LeaveCriticalSection(&DAT_005a9068);
        EnterCriticalSection(&DAT_005a9068);
        local_ad4 = reinterpret_cast<void *>(PeekPacketChecksumState());
        LeaveCriticalSection(&DAT_005a9068);
        EnterCriticalSection(&DAT_005a9068);
        uStack_adc = PeekPacketChecksumState();
        LeaveCriticalSection(&DAT_005a9068);
        FUN_0043af40(uStack_adc, puStack_af4, 0, local_ad4, iVar5 / (int)local_ae8, uVar8, self->m_flags);
        EnterCriticalSection(&DAT_005a9068);
        uVar8 = PeekPacketChecksumState();
        LeaveCriticalSection(&DAT_005a9068);
        EnterCriticalSection(&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection(&DAT_005a9068);
        uVar24 = 0;
        uVar23 = 2;
        uVar22 = 0xff;
        uVar21 = 0;
        PeekPacketChecksumBool_5(0, uVar8, 0xff, 2, 0, 0);
        FUN_00431d90(self->m_flags, 7, 0, uVar21, uVar8, uVar22, uVar23, uVar24);
    }
    EnterCriticalSection(&DAT_005a9068);
    pCVar9 = reinterpret_cast<CProjectile *>(PeekPacketChecksumState());
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    iVar5 = g_clientContext;
    pCStack_ac8 = reinterpret_cast<CProjectile *>(self->m_ctorArg1);
    uStack_adc = uVar8;
    local_ad4 = pCVar9;
    EnterCriticalSection(&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    if (iVar6 == 4) {
        puStack_af4 = operator_new(0x3fbc);
        apuStack_ad0[0] = reinterpret_cast<unsigned int *>(puStack_af4);
        if (puStack_af4 == 0) {
            puStack_af4 = 0;
        } else {
            InitProjectile(pCStack_ac8, (int)puStack_af4);
            *reinterpret_cast<void **>(puStack_af4) = PTR_FUN_0055658c;
            reinterpret_cast<unsigned int *>(puStack_af4)[0xfe7] = 0xffffffff;
        }
        iVar6 = *reinterpret_cast<int *>(*reinterpret_cast<int *>(&DAT_006a7f8c + g_clientContext) + 0x1c);
        uVar13 = *reinterpret_cast<unsigned int *>(iVar6 + 4);
        while (uVar13 < 0x186ab) {
            if (uVar13 == 0x186aa) {
                piVar18 = *reinterpret_cast<int **>(iVar6 + 0x10);
                bVar20 = true;
                if (piVar18[2] == 0) goto LAB_00457675;
                break;
            }
            iVar6 = *reinterpret_cast<int *>(iVar6 + 0x1c);
            uVar13 = *reinterpret_cast<unsigned int *>(iVar6 + 4);
        }
    }
    goto LAB_004579de;
    while (true) {
        piVar18 = reinterpret_cast<int *>(piVar18[4]);
        bVar20 = piVar18[2] == 0;
        if (!bVar20) break;
    LAB_00457675:
        if (bVar20) {
            apuStack_ad0[0] = reinterpret_cast<unsigned int *>(piVar18[0xf]);
            iVar6 = piVar18[0xe];
            iVar10 = CalculateAngleFromDelta_2(reinterpret_cast<int>(pCVar9) - reinterpret_cast<int>(apuStack_ad0[0]), iVar6);
            iVar11 = FloatToInt64_0();
            iVar12 = FloatToInt64_0();
            iVar12 = reinterpret_cast<int>(apuStack_ad0[0]) - iVar12;
            (*reinterpret_cast<void (**)(void *)>(*piVar18 + 4))(reinterpret_cast<void *>(0x553b90));
            piVar18[0x11] = iVar10;
            apuStack_ad0[0] = reinterpret_cast<unsigned int *>(&DAT_006a7f74 + iVar5);
            cVar4 = PeekPacketChecksumBool();
            if (cVar4 == '\0') {
                auStack_8a0.activeFlag = 0;
                auStack_8a0.tableHandle = 0;
                EncodeOutgoingPacketField(0);
                auStack_ac4.activeFlag = 0;
                auStack_ac4.tableHandle = 0;
                EncodeOutgoingPacketField(0);
                SyncOutgoingChecksumField((int)pCStack_ac8->m_pad0c + 4, &auStack_ac4);
                EnterCriticalSection(&DAT_005a9068);
                PeekPacketChecksumState();
                LeaveCriticalSection(&DAT_005a9068);
                EnterCriticalSection(&DAT_005a9068);
                uVar8 = PeekPacketChecksumState();
                LeaveCriticalSection(&DAT_005a9068);
                iVar5 = self->m_field3f94;
                uVar21 = 0;
                uVar22 = 0xff;
                uVar23 = 100;
                uVar24 = 0;
                PeekPacketChecksumBool_5(uVar8, 0, 100, 0xff, iVar5, 0);
                FUN_00432320(self->m_flags, 1, 1, uVar8, uVar21, uVar23, uVar22, iVar5, uVar24);
                ScrubChecksumGuard(&auStack_ac4);
                puVar15 = &auStack_8a0;
                goto LAB_0045793d;
            } else {
                cVar4 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext, &uStack_adc, &local_ad4, 2, 1, 1);
                if (cVar4 != '\0') {
                    auStack_ac4.activeFlag = 0;
                    auStack_ac4.tableHandle = 0;
                    EncodeOutgoingPacketField(0);
                    auStack_8a0.activeFlag = 0;
                    auStack_8a0.tableHandle = 0;
                    EncodeOutgoingPacketField(0);
                    QueueOutgoingPacketField(uStack_adc);
                    QueueOutgoingPacketField(reinterpret_cast<unsigned int>(local_ad4));
                    SyncOutgoingChecksumField((int)pCStack_ac8->m_pad0c + 4, &auStack_8a0);
                    iVar5 = self->m_field3f94;
                    uVar21 = 0;
                    uVar22 = 0xff;
                    uVar23 = 100;
                    uVar24 = 0;
                    PeekChecksumStateUnderLock(&auStack_8a0);
                    uVar8 = PeekChecksumStateUnderLock(&auStack_ac4);
                    PeekPacketChecksumBool_5(uVar8, uVar21, uVar23, uVar22, iVar5, uVar24);
                    FUN_00432320(self->m_flags, 1, 1, uVar8, uVar21, uVar23, uVar22, iVar5, uVar24);
                    ScrubChecksumGuard(&auStack_8a0);
                    puVar15 = &auStack_ac4;
                LAB_0045793d:
                    ScrubChecksumGuard(puVar15);
                    goto LAB_00457940;
                }
            }
        LAB_00457940:
            reinterpret_cast<unsigned int *>(puStack_af4)[0xfea] = iVar6 - iVar11;
            reinterpret_cast<unsigned int *>(puStack_af4)[0xfeb] = iVar12;
            reinterpret_cast<unsigned int *>(puStack_af4)[0xfec] = uStack_adc;
            reinterpret_cast<unsigned int *>(puStack_af4)[0xfed] = reinterpret_cast<unsigned int>(local_ad4);
            reinterpret_cast<unsigned int *>(puStack_af4)[0xfee] = iVar10;
            uVar8 = FUN_004ac4d0();
            reinterpret_cast<unsigned int *>(puStack_af4)[0xfe9] = uVar8;
            iVar5 = FUN_004ac400();
            reinterpret_cast<unsigned int *>(puStack_af4)[0xfe8] = iVar5 * self->m_field3f94;
            cVar4 = PeekPacketChecksumBool();
            if (cVar4 == '\0') {
                RegisterActiveObject_4(punk, capturedEdi, capturedEsi, capturedEbp);
            } else {
                (*reinterpret_cast<void (**)(int)>(puStack_af4))(1);
            }
            break;
        }
    }
LAB_004579de:
    pCStack_ad8->m_pad0c[8] = '\x01';
    EnterCriticalSection(&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    uVar21 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    apuStack_ad0[0] = reinterpret_cast<unsigned int *>(PeekPacketChecksumState());
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    uVar22 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    uVar23 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    uVar24 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    local_ad4 = reinterpret_cast<void *>(PeekPacketChecksumState());
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    uStack_adc = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    reinterpret_cast<int &>(pCStack_ac8) = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    ApplyCraterExcavation(uStack_adc, local_ad4, uVar24, uVar23, uVar22, apuStack_ad0[0], uVar21, uVar8);
    RebuildTerrainColumnCache(&DAT_006a7708 + g_clientContext);
    EnterCriticalSection(&DAT_005a9068);
    pCVar9 = pCStack_ad8;
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    apuStack_ad0[0] = reinterpret_cast<unsigned int *>(PeekPacketChecksumState());
    LeaveCriticalSection(&DAT_005a9068);
    FUN_00450eb0(apuStack_ad0[0], uVar8, pCVar9, 1, 0, 0);
    EnterCriticalSection(&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    uVar21 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    FUN_00436ac0(uVar21, uVar8);
    EnterCriticalSection(&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    apuStack_ad0[0] = reinterpret_cast<unsigned int *>(PeekPacketChecksumState());
    LeaveCriticalSection(&DAT_005a9068);
    FUN_004372f0(static_cast<int>(pCVar9->m_ctorArg1), apuStack_ad0[0], uVar8,
                 *reinterpret_cast<unsigned int *>(pCVar9->m_pad3d + 0x3857), pCVar9->m_pad3d + 0x385b);
    EnterCriticalSection(&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    uVar21 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    uVar22 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    FUN_00437150(uVar22, uVar21, 0x3c, uVar8);
    iVar5 = g_clientContext;
    cVar4 = PeekPacketChecksumBool();
    if (cVar4 != '\x01') {
        iVar6 = DAT_006a7750;
        if (iVar6 < 0x10) iVar6 = 0xf;
        DAT_006a7750 = iVar6;
        iVar6 = DAT_006a7754;
        if (iVar6 < 0xb) iVar6 = 10;
        DAT_006a7754 = iVar6;
    }
    cVar4 = PeekPacketChecksumBool();
    if (cVar4 == '\0') AcquireSoundChannel(0);
    cVar4 = PeekPacketChecksumBool();
    if (cVar4 != '\0' && InitChecksumSeed() == '\0') {
        EnterCriticalSection(&DAT_005a9068);
        uVar8 = PeekPacketChecksumState();
        LeaveCriticalSection(&DAT_005a9068);
        QueueOutgoingPacketField(uVar8);
        iVar5 = g_clientContext;
        if (*reinterpret_cast<int *>(&DAT_005f3768 + g_clientContext) != 0) {
            *reinterpret_cast<unsigned int *>(&DAT_005f3768 + g_clientContext) = 5;
            *reinterpret_cast<unsigned int *>(&DAT_005f376c + iVar5) = 0;
        }
    }
    EnterCriticalSection(&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    cVar4 = CheckGuardedBoolAnd(iVar5 < iVar6);
    if (cVar4 != '\0') {
        EnterCriticalSection(&DAT_005a9068);
        uVar8 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(uVar8);
        LeaveCriticalSection(&DAT_005a9068);
    }
    EnterCriticalSection(&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    if (iVar5 < 0) {
        EnterCriticalSection(&DAT_005a9068);
        iVar5 = PeekPacketChecksumState();
        LeaveCriticalSection(&DAT_005a9068);
        if (iVar5 < 1) goto LAB_00457e68;
    LAB_00457eb4:
        cVar4 = PeekPacketChecksumBool();
        if (cVar4 == '\0') SetGuardedBool(1);
    } else {
    LAB_00457e68:
        EnterCriticalSection(&DAT_005a9068);
        iVar5 = PeekPacketChecksumState();
        LeaveCriticalSection(&DAT_005a9068);
        if (0 < iVar5) {
            EnterCriticalSection(&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection(&DAT_005a9068);
            if (iVar5 < 0) goto LAB_00457eb4;
        }
    }
    EnterCriticalSection(&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    if (iVar6 <= iVar5 ||
        CompareChecksumPair(pCStack_ad8->m_pad3d + 0x3b0b, reinterpret_cast<unsigned int>(pCStack_ad8->m_pad3d + 0x3d2f)) == '\0') {
        EnterCriticalSection(&DAT_005a9068);
        iVar5 = PeekPacketChecksumState();
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection(&DAT_005a9068);
        if (iVar5 <= iVar6 ||
            CompareChecksumExceeds(pCStack_ad8->m_pad3d + 0x3b0b, pCStack_ad8->m_pad3d + 0x3d2f) == '\0' ||
            *reinterpret_cast<int *>(pCStack_ad8->m_pad3d + 0x3b07) < 6)
            goto LAB_004585ba;
    }
    {
        unsigned char *pbVar19 = reinterpret_cast<unsigned char *>(g_clientContext + 0x62143);
        unsigned char bVar1, bVar15;
        EnterCriticalSection(&DAT_005a9068);
        iVar6 = _rand();
        *pbVar19 = static_cast<unsigned char>(iVar6);
        iVar6 = _rand();
        bVar1 = *pbVar19;
        *reinterpret_cast<unsigned char *>(g_clientContext + 0x62144) = static_cast<unsigned char>(iVar6);
        bVar15 = 1 << (bVar1 & 7);
        bVar15 = (~bVar15 & static_cast<unsigned char>(iVar6)) | bVar15;
        *reinterpret_cast<unsigned char *>(g_clientContext + 0x62144) = bVar15;
        *reinterpret_cast<unsigned char *>(g_clientContext + 0x62145) = bVar1 + bVar15 - 0x34;
        LeaveCriticalSection(&DAT_005a9068);
    }
LAB_004585ba:
    return;
}
