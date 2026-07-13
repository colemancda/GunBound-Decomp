/* CMobile methods - promoted from the raw C ports under src/battle/.
 * See Mobile.h and src/cxx/README.md.
 *
 * Started with the shared base-vtable methods that are genuinely
 * CMobile-specific. NOT promoted as real bodies (they stay shared free
 * functions / vtable slots): slot 1 (ResolveNamedState 0x461c60 - a
 * generic named-state resolver reused by ButtonWidget/CProjectile too,
 * see src/registry/ResolveNamedState.c), slot 4 (the shared no-op
 * 0x429800), and slot 7 (base MainAction = the no-op 0x4fdef0 every
 * subclass overrides).
 *
 * The base destructor (slot 0 body, 0x45a560) is DELIBERATELY not promoted
 * here. It's 89 near-identical unrolled guard-cell scrubs (`if
 * (this[idx] != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(); }`)
 * plus two things that cannot be faithfully reproduced from C++ source:
 * (1) an `_eh_vector_destructor_iterator_(this+0xb728, 0x224, 4,
 * ScrubChecksumGuard)` CRT array-destruct helper - MSVC only emits that
 * for a real `CValueGuard[4]` member with a destructor, not from a hand
 * loop; and (2) explicit vtable-pointer writes (base vtable 0x555c68 on
 * entry, a poison vtable 0x55752c on exit) that fight the compiler's own
 * dtor-generated vptr writes. With SEH also stripped it would score ~0
 * (cf. CProjectile's equivalent dtor at worse-than-max), so it's 97 lines
 * of unfaithful bulk with no reconstruction insight - skipped on purpose.
 * Promoted so far: v5 ComputeMobileGroundY and v3 RenderMobile (below).
 * The remaining base methods with real logic (v2 SimulateMobileFrame
 * 0x461ca0, slot 6 HandleFireInput 0x45f910) are larger follow-up units,
 * each its own careful pass.
 *
 * The guard-cell ABI used throughout is the one confirmed for CProjectile
 * (see src/cxx/PLAN.md's "Encode family" note and Projectile.cpp): the
 * checksum "Encode*" functions' `out` parameter is a full 0x224-byte
 * CValueGuard local, and Ghidra's small `<20-byte buffer>` + adjacent
 * `<int handle>` local pairs are one CValueGuard split into its head and
 * its `.tableHandle` (+0x14) field. Windows SEH (__try/__finally)
 * scaffolding is stripped, same documented tradeoff as the rest of this
 * tree - so byte scores here are expected to be dominated by that plus
 * the unresolved register-passed args (e.g. FindGroundHeightAtColumn's
 * column coordinate arrives in a register Ghidra never resolved). */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include "Mobile.h"
#include "ValueGuard.h"

extern "C" {
void ScrambleChecksumGuardBytes(void);
void ScrubChecksumGuard(void *cell);
void TreeLowerBound(void *scratch);
int  PeekPacketChecksumState(void);
int  PeekChecksumStateUnderLock(void *cell);
char PeekPacketChecksumBool(void);
unsigned int EncodeChecksumDeltaDiv(void *cell, void *out, int div);
unsigned int EncodeChecksumPairDiff(void *cell, void *out, unsigned int a);
unsigned int EncodeChecksumDeltaAdd(void *cell, void *out, int delta);
unsigned int EncodeChecksumDeltaSub(void *cell, void *out, unsigned int v);
unsigned int EncodeChecksumPairSum(void *cell, void *out, void *b);
unsigned int EncodeChecksumDeltaMul(void *cell, void *out, int m);
unsigned int EncodeChecksumNegate(void *cell, void *out);
int  FindGroundHeightAtColumn(void);   /* 0x4e4340 - column arg arrives in a register (dropped) */
extern CRITICAL_SECTION DAT_005a9068;  /* the guard family's shared lock, defined in ValueGuard.cpp */

/* RenderMobile's additional dependencies. The Blit / Draw / FillRect calls
 * all drop most of their real (register-passed) coordinate/handle args in
 * Ghidra's decompile - kept with the exact argument shape the decompile
 * shows (documented gap, same as elsewhere in this tree). GBFillRect is the
 * game's own 2-int sprite-fill primitive (Ghidra labelled it "FillRect");
 * renamed here only to avoid colliding with <windows.h>'s FillRect - the
 * name is irrelevant to the score (it compiles to an external-call reloc). */
void BlitSpriteDirect(int a, int b);
unsigned int BlitSpriteAttached(unsigned int spriteId, unsigned int tex, int pos, int layer);
void BlitRLESprite(int a, int b);
void DrawSprite(void);
void GBFillRect(int a, int b);
void FUN_004ead90(void);               /* (x+90)/360 angle helper */
void FUN_004ead70(void);               /* x/360 angle helper */
int  FloatToInt64(void);
char CheckGuardedBoolAnd(int cond);
unsigned int PacketChecksumEquals(void *cell, int v);
char PacketChecksumNotEquals(void *cell, int v);
char CompareChecksumPair(void *cellA, unsigned int cellB);
void FUN_004eb7a0(int a, int b, int c);
int  _sprintf(char *buf, const char *fmt, int a, int b);

extern int g_clientContext;            /* _DAT_005b3484 */
extern unsigned char g_nCameraX, g_nCameraY;  /* 1-byte: used only as &sym + g_clientContext ctx bases (see Projectile.cpp) */
extern int DAT_00793530, DAT_0056df30, DAT_00793534, DAT_0056df34;  /* on-screen clip bounds */
extern unsigned char DAT_00e9bed8;     /* a guard cell (address-of taken) */
extern unsigned char DAT_00796aa0;     /* a guard cell (address-of taken) */
extern unsigned char DAT_0056d468;     /* color/palette table base */
extern const char s___d__d__00555c88[];/* "%d,%d" */
}

/* 0x45c6e0 ComputeMobileGroundY, vtable slot 5 (shared; type 13 overrides
 * with 0x46cbb0). Queries the terrain height directly below the mobile:
 * decodes the fire-angle/power guard cells (m_pad908 + 4 = byte 0x90c and
 * + 0x228 = byte 0xb30, the documented fire-angle/power CValueGuards; the
 * + 0x670 cell = byte 0xf78 feeds the column divisor), scans the terrain
 * bitmap via FindGroundHeightAtColumn, and cross-checks the result against
 * a re-decoded copy (the anti-cheat "compute it twice and compare" idiom -
 * if the two agree it trusts the value, else it re-probes at +1). Returns
 * the ground Y. Guard cells local_678/454/230 are CValueGuard locals;
 * their .tableHandle drives the post-use scrub. */
int CMobile::v5_ComputeGroundY()
{
    unsigned char scratch[8];              /* local_688 - TreeLowerBound scratch */
    CValueGuard g678, g454, g230;
    unsigned char *pbVar1 = this->m_pad908 + 0x670;
    unsigned char *pbVar2 = this->m_pad908 + 0x228;
    unsigned int uVar3;
    int iVar4, iVar5, iVar6;
    int local_680;
    unsigned char *local_67c;

    uVar3 = EncodeChecksumDeltaDiv(pbVar1, &g678, 2);
    EncodeChecksumPairDiff(pbVar2, &g454, uVar3);
    EnterCriticalSection(&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    EnterCriticalSection(&DAT_005a9068);
    local_67c = this->m_pad908 + 4;        /* column x - passed to FindGroundHeightAtColumn via register */
    (void)local_67c;
    PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    local_680 = FindGroundHeightAtColumn();
    if (g454.tableHandle != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (g678.tableHandle != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }

    uVar3 = EncodeChecksumDeltaDiv(pbVar1, &g454, 2);
    EncodeChecksumPairDiff(pbVar2, &g678, uVar3);
    EnterCriticalSection(&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    bool bVar7 = local_680 == iVar4;
    if (g678.tableHandle != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }
    if (g454.tableHandle != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }

    iVar4 = local_680;
    if (bVar7) {
        EncodeChecksumPairDiff(pbVar2, &g678, reinterpret_cast<unsigned int>(pbVar1));
        EnterCriticalSection(&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection(&DAT_005a9068);
        EnterCriticalSection(&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection(&DAT_005a9068);
        iVar5 = FindGroundHeightAtColumn();
        if (g678.tableHandle != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }

        EncodeChecksumPairDiff(pbVar2, &g678, reinterpret_cast<unsigned int>(pbVar1));
        EnterCriticalSection(&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection(&DAT_005a9068);
        if (g678.tableHandle != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }

        iVar4 = local_680;
        if (iVar5 == iVar6) {
            EncodeChecksumDeltaAdd(pbVar2, &g678, 1);
            EnterCriticalSection(&DAT_005a9068);
            PeekPacketChecksumState();
            LeaveCriticalSection(&DAT_005a9068);
            EnterCriticalSection(&DAT_005a9068);
            PeekPacketChecksumState();
            LeaveCriticalSection(&DAT_005a9068);
            iVar4 = FindGroundHeightAtColumn();
            if (g678.tableHandle != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }

            EncodeChecksumDeltaAdd(pbVar2, &g230, 1);
            EnterCriticalSection(&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection(&DAT_005a9068);
            if (g230.tableHandle != 0) { ScrambleChecksumGuardBytes(); TreeLowerBound(scratch); }

            if (iVar4 == iVar5) {
                iVar4 = PeekChecksumStateUnderLock(pbVar2);
            }
        }
    }
    return iVar4;
}

/* 0x462900 RenderMobile, vtable slot 3 (shared). The mobile draw pass.
 * Faithful translation of a fresh Ghidra decompile. Two rendering modes:
 *   - checksum-bool == 0 (not the local/active mobile): if the mobile is
 *     in state 2 and owned by the polled slot, blit a pair of shadow
 *     sprites (BlitSpriteDirect) and return.
 *   - else (the local mobile): blit the tank body + turret
 *     (BlitSpriteAttached) into the per-slot turn-display array
 *     (g_clientContext + ((owner&7)+0x154c)*0x18), then - when the mobile
 *     is visible, on-screen (clip-bounds check) and not a spectator - draw
 *     the aim/power gauge (FillRect bars driven by the +0x6060/+0x66cc
 *     guard cells) and the "%d,%d" coordinate overlay, digit-by-digit via
 *     DrawSprite.
 * The fire angle/power are read from the CValueGuard cells at m_pad908+4
 * (0x90c) / +0x228 (0xb30); the +0x59f0 cell feeds the turret angle through
 * FUN_004ead90/70 ((x+90)/360, x/360) + FloatToInt64. Camera-relative
 * screen position uses g_nCameraX/Y as ctx-relative arena fields
 * (&sym + g_clientContext, see the declaration note above).
 *
 * Known gaps (score expected poor, same family as ComputeMobileGroundY):
 * SEH stripped; every Blit / Draw / FillRect / FUN_004ead call drops its
 * register-passed coordinate/handle args in Ghidra's decompile and is kept
 * with that same argument shape; FindGroundHeightAtColumn-style register
 * inputs unresolved. */
void CMobile::v3_Render()
{
    unsigned char *pbVar1;
    int *piVar2;
    unsigned char bVar3;
    char cVar4;
    unsigned int uVar5;
    int iVar6;
    unsigned int uVar7;
    unsigned int uVar8;
    int iVar9;
    int iVar10;
    int iVar11;
    unsigned int uVar12;
    unsigned char *pbVar13;
    char *pcVar14;
    unsigned int uVar15;
    int iVar16;
    bool bVar17;
    unsigned int local_930;
    unsigned int local_928;
    char local_91c[128];
    unsigned char local_89c[0x224];
    unsigned char local_678[0x224];
    unsigned char local_454[0x224];
    unsigned char local_230[0x224];

    uVar7 = this->m_owner;
    uVar5 = uVar7 >> 2 & 1;
    iVar6 = *reinterpret_cast<int *>(g_clientContext + 0x1fe1c + uVar5 * 4);
    iVar11 = *reinterpret_cast<int *>(g_clientContext + 0x1fe24 + uVar5 * 4);
    cVar4 = PeekPacketChecksumBool();
    iVar9 = g_clientContext;
    if (cVar4 == '\0') {
        EnterCriticalSection(&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection(&DAT_005a9068);
        if (iVar6 == 2) {
            EnterCriticalSection(&DAT_005a9068);
            uVar7 = PeekPacketChecksumState();
            LeaveCriticalSection(&DAT_005a9068);
            if ((this->m_owner & 7) == uVar7) {
                iVar6 = *reinterpret_cast<int *>(g_clientContext + 0x1fe2c);
                iVar11 = *reinterpret_cast<int *>(g_clientContext + 0x1fe30);
                if (iVar6 != 0) {
                    BlitSpriteDirect(iVar6, iVar11);
                    BlitSpriteDirect(iVar11 / 2 + iVar6, iVar11);
                }
            }
        }
    } else {
        uVar5 = this->m_owner >> 2 & 1;
        uVar15 = (uVar7 & 3) / 2;
        iVar16 = (uVar7 & 1) * 2;
        uVar7 = (*reinterpret_cast<int *>(this->m_pad20 + 4) == 0xe) ? 0xffffffffu : this->m_spriteId;
        BlitSpriteAttached(uVar7, *reinterpret_cast<unsigned int *>(this->m_pad58 + 0x10),
                           (*reinterpret_cast<int *>(g_clientContext + 0x1fe4c + uVar5 * 4) * (int)uVar15 + iVar16) * 0x80 +
                           *reinterpret_cast<int *>(g_clientContext + 0x1fe44 + uVar5 * 4), iVar11);
        uVar7 = this->m_owner >> 2 & 1;
        uVar5 = (*reinterpret_cast<int *>(this->m_pad20 + 4) == 0xe) ? 0xffffffffu : this->m_spriteId;
        uVar7 = BlitSpriteAttached(uVar5, *reinterpret_cast<unsigned int *>(this->m_pad58 + 0x10),
                                   (*reinterpret_cast<int *>(iVar9 + 0x1fe5c + uVar7 * 4) * (int)uVar15 + iVar16) * 0x80 +
                                   *reinterpret_cast<int *>(iVar9 + 0x1fe54 + uVar7 * 4), iVar11);
        *reinterpret_cast<unsigned int *>(iVar9 + ((this->m_owner & 7) + 0x154c) * 0x18) = uVar7 & 0xff;
        if (iVar6 != 0 && this->m_pad908[0xa50c] == 0 &&
            (cVar4 = PeekPacketChecksumBool(), cVar4 != '\x01')) {
            cVar4 = PeekPacketChecksumBool();
            iVar9 = g_clientContext;
            if (cVar4 != '\0') {
                *reinterpret_cast<unsigned char *>((this->m_owner & 7) + 0x1fe94 + g_clientContext) = 0;
            }
            *reinterpret_cast<unsigned int *>(iVar9 + 0x1fe6c + (this->m_owner & 7) * 4) = 1;
            if (*reinterpret_cast<int *>(this->m_pad20 + 4) == 0xe) {
                *reinterpret_cast<unsigned int *>(iVar9 + 0x1fe6c + (this->m_owner & 7) * 4) = 0;
            }
            cVar4 = PeekPacketChecksumBool();
            iVar9 = g_clientContext;
            if (cVar4 != '\0') {
                *reinterpret_cast<unsigned int *>(g_clientContext + 0x1fe6c + (this->m_owner & 7) * 4) = 2;
            }
            pbVar13 = this->m_pad908 + 4;
            *reinterpret_cast<unsigned char *>((this->m_owner & 7) + 0x1fe8c + iVar9) = 1;
            uVar8 = PeekChecksumStateUnderLock(pbVar13);
            *reinterpret_cast<unsigned int *>(g_clientContext + 0x1ff0c + (this->m_owner & 7) * 0x18) = uVar8;
            uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x228);
            *reinterpret_cast<unsigned int *>(g_clientContext + 0x1ff10 + (this->m_owner & 7) * 0x18) = uVar8;
            if (*reinterpret_cast<int *>(this->m_pad20 + 4) == 0xd) {
                iVar9 = 0;
            } else {
                iVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x1794);
                iVar9 = -iVar9;
            }
            *reinterpret_cast<int *>(g_clientContext + 0x1ff14 + (this->m_owner & 7) * 0x18) = iVar9;
            uVar7 = PacketChecksumEquals(this->m_pad908 + 0x134c, 1);
            iVar9 = g_clientContext;
            *reinterpret_cast<unsigned int *>(g_clientContext + 0x1ff18 + (this->m_owner & 7) * 0x18) = uVar7 & 0xff;
            if (*reinterpret_cast<int *>(iVar9 + 0x1ff14 + (this->m_owner & 7) * 0x18) < 0) {
                piVar2 = reinterpret_cast<int *>(iVar9 + 0x1ff14 + (this->m_owner & 7) * 0x18);
                iVar9 = PeekChecksumStateUnderLock(&DAT_00e9bed8);
                *piVar2 = *piVar2 + iVar9;
            }
            iVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x1124);
            iVar9 = g_clientContext;
            *reinterpret_cast<unsigned int *>(g_clientContext + 0x1ff1c + (this->m_owner & 7) * 0x18) =
                *reinterpret_cast<unsigned int *>(&DAT_0056d468 + (iVar10 * 0x1e + *reinterpret_cast<int *>(this->m_pad20 + 4)) * 4);
            BlitSpriteDirect(((int)uVar15 * iVar11 + iVar16) * 0x80 + iVar6, iVar11);
            if (*reinterpret_cast<int *>(iVar9 + 0x1fe34 + (this->m_owner >> 2 & 1) * 4) != 0) {
                uVar7 = this->m_owner >> 2 & 1;
                iVar6 = *reinterpret_cast<int *>(iVar9 + 0x1fe3c + uVar7 * 4);
                BlitSpriteDirect((iVar6 * (int)uVar15 + iVar16) * 0x80 + *reinterpret_cast<int *>(iVar9 + 0x1fe34 + uVar7 * 4), iVar6);
            }
            cVar4 = CheckGuardedBoolAnd(*reinterpret_cast<int *>(this->m_pad20 + 4) != 0xe);
            iVar6 = g_clientContext;
            if (cVar4 != '\0') {
                *reinterpret_cast<unsigned int *>(g_clientContext + 0x227a8) = 1;
                uVar8 = EncodeChecksumNegate(this->m_pad908 + 0x59f0, local_89c);
                uVar8 = EncodeChecksumDeltaAdd(reinterpret_cast<void *>(uVar8), local_678, 0x5a);
                PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
                FUN_004ead90();
                uVar8 = FloatToInt64();
                uVar8 = EncodeChecksumDeltaAdd(pbVar13, local_454, (int)uVar8);
                uVar8 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
                *reinterpret_cast<unsigned int *>(g_clientContext + 0x227ac) = uVar8;
                ScrubChecksumGuard(local_454);
                ScrubChecksumGuard(local_678);
                ScrubChecksumGuard(local_89c);
                uVar8 = EncodeChecksumNegate(this->m_pad908 + 0x59f0, local_454);
                uVar8 = EncodeChecksumDeltaAdd(reinterpret_cast<void *>(uVar8), local_678, 0x5a);
                PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
                FUN_004ead70();
                uVar8 = FloatToInt64();
                uVar8 = EncodeChecksumDeltaSub(this->m_pad908 + 0x228, local_89c, uVar8);
                uVar8 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
                *reinterpret_cast<unsigned int *>(g_clientContext + 0x227b0) = uVar8;
                ScrubChecksumGuard(local_89c);
                ScrubChecksumGuard(local_678);
                ScrubChecksumGuard(local_454);
                iVar6 = g_clientContext;
                *reinterpret_cast<unsigned int *>(g_clientContext + 0x227b4) = *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x272);
                *reinterpret_cast<int *>(iVar6 + 0x227b8) = *reinterpret_cast<int *>(this->m_padae22 + 0x276) << 0x18;
                *reinterpret_cast<unsigned int *>(iVar6 + 0x227bc) = *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x27e);
            }
            uVar8 = EncodeChecksumDeltaSub(pbVar13, local_454, *reinterpret_cast<unsigned int *>(&g_nCameraX + iVar6));
            uVar8 = EncodeChecksumDeltaAdd(reinterpret_cast<void *>(uVar8), local_678, 400);
            uVar8 = EncodeChecksumDeltaSub(reinterpret_cast<void *>(uVar8), local_89c, 0x29);
            iVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
            ScrubChecksumGuard(local_89c);
            ScrubChecksumGuard(local_678);
            ScrubChecksumGuard(local_454);
            uVar8 = EncodeChecksumDeltaSub(this->m_pad908 + 0x228, local_454, *reinterpret_cast<unsigned int *>(&g_nCameraY + g_clientContext));
            uVar8 = EncodeChecksumDeltaAdd(reinterpret_cast<void *>(uVar8), local_678, 0x10e);
            uVar8 = EncodeChecksumDeltaAdd(reinterpret_cast<void *>(uVar8), local_89c, 0x26);
            iVar11 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
            ScrubChecksumGuard(local_89c);
            ScrubChecksumGuard(local_678);
            ScrubChecksumGuard(local_454);
            if (500 < iVar11) {
                iVar9 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                iVar11 = iVar11 - iVar9;
            }
            if (DAT_00793530 <= iVar6 + 0x53 && iVar6 <= DAT_0056df30 &&
                DAT_00793534 <= iVar11 + 0x1f && iVar11 <= DAT_0056df34) {
                uVar8 = EncodeChecksumDeltaSub(pbVar13, local_678, *reinterpret_cast<unsigned int *>(&g_nCameraX + g_clientContext));
                uVar8 = EncodeChecksumDeltaAdd(reinterpret_cast<void *>(uVar8), local_89c, 400);
                PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
                ScrubChecksumGuard(local_89c);
                ScrubChecksumGuard(local_678);
                if (*reinterpret_cast<char *>(g_clientContext + 0x45122) == '\0') {
                    iVar9 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(g_clientContext + 0x3b49c));
                    bVar17 = *reinterpret_cast<int *>(this->m_padae22 + 10) == iVar9;
                } else {
                    bVar17 = *reinterpret_cast<unsigned int *>(this->m_padae22 + 10) ==
                             (unsigned int)*reinterpret_cast<unsigned char *>(g_clientContext + 0x3b6c0);
                }
                if (*reinterpret_cast<int *>(this->m_pad20 + 4) != 0xe &&
                    (cVar4 = PacketChecksumNotEquals(reinterpret_cast<void *>(g_clientContext + 0x45354), 3), cVar4 != '\0')) {
                    FUN_004eb7a0(iVar6 + 1, 0x4e, 5);
                    GBFillRect(0x4c, 0x2965);
                    pbVar13 = this->m_pad908 + 0x64a8;
                    pbVar1 = this->m_pad908 + 0x5e3c;
                    uVar8 = EncodeChecksumPairSum(pbVar1, local_230, pbVar13);
                    iVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
                    if (0 < iVar6) {
                        uVar8 = EncodeChecksumPairSum(pbVar1, local_454, pbVar13);
                        local_928 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
                    } else {
                        local_928 = 1;
                    }
                    uVar8 = EncodeChecksumDeltaMul(this->m_pad908 + 0x6060, local_678, 0x4c);
                    uVar8 = EncodeChecksumDeltaDiv(reinterpret_cast<void *>(uVar8), local_89c, (int)local_928);
                    uVar8 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
                    ScrubChecksumGuard(local_89c);
                    ScrubChecksumGuard(local_678);
                    if (0 < iVar6) {
                        ScrubChecksumGuard(local_454);
                    }
                    ScrubChecksumGuard(local_230);
                    uVar12 = EncodeChecksumPairSum(pbVar1, local_89c, pbVar13);
                    uVar12 = EncodeChecksumDeltaDiv(reinterpret_cast<void *>(uVar12), local_230, 3);
                    cVar4 = CompareChecksumPair(this->m_pad908 + 0x6060, uVar12);
                    ScrubChecksumGuard(local_230);
                    ScrubChecksumGuard(local_89c);
                    GBFillRect(uVar8, (-(unsigned int)(cVar4 != '\0') & 0x5af7) + 0x65a9);
                    uVar8 = EncodeChecksumPairSum(pbVar1, local_454, pbVar13);
                    iVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
                    if (0 < iVar6) {
                        uVar8 = EncodeChecksumPairSum(pbVar1, local_678, pbVar13);
                        uVar8 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
                    } else {
                        uVar8 = 1;
                    }
                    uVar12 = EncodeChecksumDeltaMul(this->m_pad908 + 0x66cc, local_89c, 0x4c);
                    uVar8 = EncodeChecksumDeltaDiv(reinterpret_cast<void *>(uVar12), local_230, (int)uVar8);
                    uVar12 = 0x21d8;
                    uVar8 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
                    GBFillRect(uVar8, uVar12);
                    ScrubChecksumGuard(local_230);
                    ScrubChecksumGuard(local_89c);
                    if (0 < iVar6) {
                        ScrubChecksumGuard(local_678);
                    }
                    ScrubChecksumGuard(local_454);
                }
                pbVar13 = this->m_padae22;
                if (this->m_padae22[0] == 0) {
                    DrawSprite();
                    BlitRLESprite(iVar11 + 10, 0);
                    BlitRLESprite(iVar11 + 9, (-(unsigned int)bVar17 & 0x517) + 0xfae8);
                } else {
                    do {
                        bVar3 = *pbVar13;
                        pbVar13 = pbVar13 + 1;
                    } while (bVar3 != 0);
                    iVar6 = *reinterpret_cast<int *>(this->m_padae22 + 0x12);
                    if (0x3e6 < iVar6) { iVar6 = 999; }
                    iVar9 = *reinterpret_cast<int *>(this->m_padae22 + 0xe);
                    if (0x3e6 < iVar9) { iVar9 = 999; }
                    _sprintf(local_91c, s___d__d__00555c88, iVar9, iVar6);
                    pcVar14 = local_91c;
                    local_930 = 0;
                    do {
                        cVar4 = *pcVar14;
                        pcVar14 = pcVar14 + 1;
                    } while (cVar4 != '\0');
                    if (pcVar14 != local_91c + 1) {
                        do {
                            DrawSprite();
                            local_930 = local_930 + 1;
                            pcVar14 = local_91c;
                            do {
                                cVar4 = *pcVar14;
                                pcVar14 = pcVar14 + 1;
                            } while (cVar4 != '\0');
                        } while (local_930 < (unsigned int)((int)pcVar14 - (int)(local_91c + 1)));
                    }
                    BlitRLESprite(iVar11 + 8, 0);
                    iVar6 = (-(unsigned int)bVar17 & 0x517) + 0xfae8;
                    BlitRLESprite(iVar11 + 7, iVar6);
                    DrawSprite();
                    BlitRLESprite(iVar11 + 0x15, 0);
                    BlitRLESprite(iVar11 + 0x14, iVar6);
                }
            }
        }
    }
}
