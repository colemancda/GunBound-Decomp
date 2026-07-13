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
 * All four base-vtable methods with real logic are now promoted (below):
 * v2 SimulateMobileFrame, v3 RenderMobile, v5 ComputeMobileGroundY, and
 * slot 6 HandleFireInput. The CMobile base class is complete apart from the
 * deliberately-skipped destructor.
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

/* SimulateMobileFrame's additional dependencies. */
char PacketChecksumLessThan(void *cell, int v);
char PacketChecksumGreaterEqual(void *cell, unsigned int v);
char PacketChecksumLessEqual(void *cell, int v);
char PacketChecksumGreaterThan(void *cell, int v);
void QueueOutgoingPacketField(unsigned int v);
void AddToPacketChecksum(int v);
void SubFromPacketChecksum(int v);
void AdvanceSpriteAnimation(void);
void FUN_0045cb50(void);
char FUN_0043c820(void);
void FUN_0045ba50(CMobile *self);
void FUN_0045ed80(void);
void FUN_00436cd0(unsigned int a, unsigned int b);
unsigned short FUN_0045d360(int a);
void FUN_0041f200(int a);
char ChecksumPairDiffers(void *a, void *b);
unsigned int EncodeChecksumDeltaMod(void *cell, void *out, int m);
void EncodeChecksumState(void *cell);
void EmitChecksumSum(void *cell);
void EmitChecksumDiff(void *cell);
void EmitChecksumMod(void *cell);
void EncodeDecrementedChecksum(void);
void AcquireSoundChannel(int a);
void ResolveNamedState(int *arg);
int  DecodeGuardedBool(void);
void SetGuardedBool(int v);
void QueueBroadcastEvent(unsigned int event);
void BroadcastQueuedEvent(void);

extern int DAT_005b3424;               /* second per-connection base (distinct from g_clientContext) */
extern unsigned char g_nCameraBoundX, g_nCameraBoundY;  /* 1-byte ctx bases (&sym + g_clientContext) */
extern unsigned char DAT_005f3768;     /* 1-byte ctx base */
extern unsigned char DAT_006a7758;     /* 1-byte ctx base (byte-indexed) */
extern unsigned int  DAT_007934e4;     /* shared overlay EDIT control singleton (holds an address) */
extern unsigned char DAT_007a7644;     /* animated cursor object (address taken) */
extern unsigned char g_abBroadcastEventBuffer;
extern unsigned int  g_dwBroadcastEventCursor;
extern const char s_normal_00552230[], s_wnormal_00553618[], s_wmove_00555ca0[];
extern unsigned char DAT_00553f90, DAT_00555c90;

/* HandleFireInput's additional dependencies. */
void EncodeOutgoingPacketField(unsigned int v);
char CompareChecksumExceeds(void *cell, unsigned int other);
void FUN_004eeae0(void);
void FUN_0040b030(void);
char FUN_0040b450(void *cell, unsigned int v);
void FUN_0043c860(void *base, int *self);
char FUN_0041eaa0(int a, short b);
char FUN_0045ec30(void);
void FUN_0043d6d0(void);
void FUN_00464060(void);
void ClampCursorToRect(void);
void InvokeWidget(int a);
int  _rand(void);
unsigned long timeGetTime2(void);   /* winmm timeGetTime; renamed to dodge the <mmsystem.h> proto */

extern char DAT_007933b8;
extern int  DAT_00e52838, DAT_00e5283c;   /* fire-gesture state (-1000 / 0 / 1000) */
extern char DAT_007934c4;
extern unsigned char DAT_006a6481;         /* ctx-indexed */
extern unsigned char DAT_006a64a4, DAT_006a64a8, DAT_006a64ac; /* ctx bases */
extern unsigned char DAT_005f2f40;         /* ctx-indexed */
extern int  DAT_005b3438;                  /* _DAT_005b3438 */
extern unsigned char DAT_00e52868;         /* indexed by DAT_00e52e68 */
extern int  DAT_00e52e68;
extern unsigned char DAT_00794bf0, DAT_00e9ba40; /* guard cells (address taken) */
extern unsigned char DAT_00553bcc, DAT_00551cb1;
extern unsigned char DAT_00e9aacd, DAT_00e9aace;
extern unsigned char DAT_006a7f70;         /* ctx base */
extern const char s_unmove_00555c98[];
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

/* 0x461ca0 SimulateMobileFrame, vtable slot 2 (shared). The mobile's
 * per-frame tick. Faithful translation of a fresh Ghidra decompile,
 * preserving its exact control flow (including the cross-branch gotos
 * LAB_0046205f / LAB_004622bc that the original's shared move/state-name
 * tails produce). Outline:
 *   - dispatch the attached input/AI sub-object (m_pad20+0x18 vtable slot 2)
 *   - if alive & active: clamp the fire angle to [0, boundX); run the
 *     turn-timer/ready sub-object (m_padbff4+6) and, when it expires, latch
 *     the per-slot ready state into the client-context arena and zero it;
 *     fire the HandleFireInput (slot 6) and MainAction (slot 7) virtuals
 *   - decide the movement animation state name (normal / wnormal / wmove /
 *     DAT_00553f90) from the position-delta guard cells (m_pad908+4 vs
 *     +0xcdc, speed via +0x4264/+0x5e3c/+0x6060/+0x7e58), emitting the
 *     move packet fields
 *   - pulse the damage-flash color channels (m_padae22 +0x272.. RGBA)
 *   - handle the fall-off-map / out-of-bounds death (camera-bound checks),
 *     the fire-sound channel, and the 0x8402 fire broadcast event
 *   - apply the small self-correcting drift on the aim guards and record
 *     this frame's position into m_padbff4+0x2b0/0x2b4 for next-frame delta.
 *
 * vtable slot calls are done as raw indirect __thiscall dispatches through
 * the vptr (`*(int*)this`), because the header's slot signatures (no args)
 * don't match how slots 1/7 are actually invoked here (with a state-name
 * string / two ints) - matching the decompile's `(**(code**)(vptr+N))(...)`
 * exactly. Same known gaps as the other CMobile methods: SEH stripped;
 * many checksum/packet helpers drop register-passed args; g_nCameraBoundX/Y
 * and DAT_005f3768 are ctx-relative arena fields (&sym + g_clientContext);
 * DAT_005b3424 is a second per-connection base.
 *
 * score.sh: 110987/82300 - OVER max, the least byte-faithful of the CMobile
 * methods (RenderMobile/ComputeGroundY both scored under max). This is a
 * divergence artifact, not a known logic bug: it's by far the most
 * vtable-dispatch-heavy method, and the __fastcall+dummy-EDX trick emits a
 * spurious EDX load before each of the ~11 indirect calls, on top of the
 * stripped SEH state machine (uStack_4 ran states 0..0xe) and very high
 * branch density. Compiled size (798 instrs) still tracks the original
 * (0xc50 bytes); the translation is line-for-line faithful with the
 * decompile's exact control flow (gotos preserved). Recovering the real
 * __thiscall dispatch (no dummy EDX) and the SEH frame would be needed to
 * close the gap - not attempted. */
void CMobile::v2_SimulateFrame()
{
    /* MSVC 7.1 forbids explicit __thiscall on pointer typedefs (C4234), so
     * these vtable slots are dispatched via the standard __fastcall +
     * dummy-EDX trick: __thiscall passes `this` in ECX and args on the
     * stack, which __fastcall(this, edxDummy, args...) reproduces
     * (this->ECX, dummy->EDX, args->stack). Adds a harmless EDX load vs the
     * original; semantically exact. VtVoid (no args) needs no dummy. */
    typedef void (__fastcall *VtStr)(CMobile *, int, const void *);
    typedef void (__fastcall *VtAb)(CMobile *, int, unsigned int, unsigned int);
    typedef void (__fastcall *VtVoid)(CMobile *);

    unsigned char *pbVar1;
    unsigned char *pbVar12;
    bool bVar2 = false;
    bool bVar3;
    int iVar4;
    char cVar5;
    unsigned char bVar6;
    unsigned short uVar7;
    int iVar8;
    unsigned int uVar9;
    unsigned int uVar10;
    int iVar11;
    const char *pcVar13;
    unsigned int uVar14;
    unsigned char auStack_454[0x224];
    unsigned char auStack_230[0x224];

    /* dispatch the attached input/AI sub-object's slot 2 */
    {
        int sub = *reinterpret_cast<int *>(this->m_pad20 + 0x18);
        (*reinterpret_cast<void (**)()>(sub + 8))();
    }
    cVar5 = PeekPacketChecksumBool();
    if (cVar5 == '\x01') goto LAB_004628db;
    cVar5 = PeekPacketChecksumBool();
    if (cVar5 == '\0') {
        AdvanceSpriteAnimation();
        return;
    }
    cVar5 = PeekPacketChecksumBool();
    if (cVar5 == '\0') {
        cVar5 = PacketChecksumLessThan(this->m_pad908 + 4, 0);
        if (cVar5 != '\0') {
            QueueOutgoingPacketField(0);
        }
        cVar5 = PacketChecksumGreaterEqual(this->m_pad908 + 4,
                                           *reinterpret_cast<unsigned int *>(&g_nCameraBoundX + g_clientContext));
        if (cVar5 != '\0') {
            QueueOutgoingPacketField(*reinterpret_cast<int *>(&g_nCameraBoundX + g_clientContext) - 1);
        }
    }
    FUN_0045cb50();
    if (this->m_padbff4[6] != 0 && (cVar5 = FUN_0043c820(), cVar5 == '\0')) {
        (*reinterpret_cast<VtStr *>(*reinterpret_cast<int *>(this) + 4))(this, 0, this->m_padbff4 + 6);
        iVar11 = *reinterpret_cast<int *>(DAT_005b3424 + 0x10a0);
        iVar8 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(g_clientContext + 0x3b49c));
        iVar4 = g_clientContext;
        if (iVar11 == iVar8) {
            *reinterpret_cast<unsigned int *>(*reinterpret_cast<int *>(g_clientContext + 0x621e0) + 0xb0b0) = 3;
        } else {
            if (*reinterpret_cast<char *>(g_clientContext + 0x4590c + iVar11) != *reinterpret_cast<char *>(g_clientContext + 0x3b6c0)) {
                *reinterpret_cast<unsigned int *>(*reinterpret_cast<int *>(g_clientContext + 0x621e0) + 0xb0b0) = 1;
            }
            if (*reinterpret_cast<char *>(*reinterpret_cast<int *>(DAT_005b3424 + 0x10a0) + 0x4590c + iVar4) ==
                *reinterpret_cast<char *>(iVar4 + 0x3b6c0)) {
                *reinterpret_cast<unsigned int *>(*reinterpret_cast<int *>(iVar4 + 0x621e0) + 0xb0b0) = 2;
            }
        }
        pbVar12 = this->m_padbff4 + 6;
        for (iVar11 = 0x20; iVar11 != 0; iVar11 = iVar11 - 1) {
            pbVar12[0] = 0; pbVar12[1] = 0; pbVar12[2] = 0; pbVar12[3] = 0;
            pbVar12 = pbVar12 + 4;
        }
    }
    cVar5 = PeekPacketChecksumBool();
    if (cVar5 != '\0') {
        (*reinterpret_cast<VtVoid *>(*reinterpret_cast<int *>(this) + 0x18))(this);
    }
    FUN_0045ba50(this);
    AdvanceSpriteAnimation();
    if (this->m_pad20[0x14] != 0) {
        FUN_0045ed80();
    }
    (*reinterpret_cast<VtAb *>(*reinterpret_cast<int *>(this) + 0x1c))(
        this, 0, *reinterpret_cast<unsigned int *>(this->m_pad20 + 4), *reinterpret_cast<unsigned int *>(this->m_pad20 + 0xc));
    cVar5 = PeekPacketChecksumBool();
    if (cVar5 == '\x01') goto LAB_004628db;
    cVar5 = PeekPacketChecksumBool();
    if (cVar5 == '\0' && *reinterpret_cast<int *>(this->m_pad20 + 4) != 0xd &&
        (cVar5 = PeekPacketChecksumBool(), cVar5 != '\0')) {
        pbVar12 = this->m_pad908 + 0xcdc;
        pbVar1 = this->m_pad908 + 4;
        cVar5 = ChecksumPairDiffers(pbVar1, pbVar12);
        if (cVar5 == '\0') {
            if (*reinterpret_cast<int *>(this->m_pad20 + 4) != 1 && *reinterpret_cast<int *>(this->m_pad20 + 4) != 3)
                goto LAB_004622cf;
            uVar9 = EncodeChecksumDeltaDiv(this->m_pad908 + 0x5e3c, auStack_454, 3);
            cVar5 = CompareChecksumPair(this->m_pad908 + 0x6060, uVar9);
            ScrubChecksumGuard(auStack_454);
            if (cVar5 == '\0') {
                pcVar13 = s_normal_00552230;
                goto LAB_004622bc;
            }
            (*reinterpret_cast<VtStr *>(*reinterpret_cast<int *>(this) + 4))(this, 0, s_wnormal_00553618);
        } else {
            cVar5 = CompareChecksumPair(pbVar12, reinterpret_cast<unsigned int>(pbVar1));
            if (cVar5 == '\0') {
                QueueOutgoingPacketField(1);
                uVar9 = EncodeChecksumPairDiff(pbVar1, auStack_454, reinterpret_cast<unsigned int>(pbVar12));
                uVar10 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar9));
                if ((int)((uVar10 ^ (int)uVar10 >> 0x1f) - ((int)uVar10 >> 0x1f)) < 3 ||
                    ((cVar5 = PacketChecksumGreaterEqual(pbVar1, *reinterpret_cast<int *>(&g_nCameraBoundX + g_clientContext) - 2),
                      cVar5 != '\0' && *reinterpret_cast<int *>(&g_nCameraBoundX + g_clientContext) != 2))) {
                    bVar2 = true;
                } else {
                    bVar2 = false;
                }
                ScrubChecksumGuard(auStack_454);
                if (!bVar2) {
                    if (*reinterpret_cast<int *>(this->m_pad20 + 4) != 1 && *reinterpret_cast<int *>(this->m_pad20 + 4) != 3) {
                        uVar9 = EncodeChecksumDeltaDiv(this->m_pad908 + 0x5e3c, auStack_454, 3);
                        cVar5 = CompareChecksumPair(this->m_pad908 + 0x6060, uVar9);
                        ScrubChecksumGuard(auStack_454);
                        if (cVar5 == '\0') {
                            (*reinterpret_cast<VtStr *>(*reinterpret_cast<int *>(this) + 4))(this, 0, &DAT_00553f90);
                        } else {
                            (*reinterpret_cast<VtStr *>(*reinterpret_cast<int *>(this) + 4))(this, 0, s_wmove_00555ca0);
                        }
                    }
                    uVar9 = EncodeChecksumDeltaMul(this->m_pad908 + 0x4264, auStack_454, 2);
                    iVar11 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar9));
                    AddToPacketChecksum(0x96 - iVar11);
                    ScrubChecksumGuard(auStack_454);
                    uVar9 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                    uVar9 = EncodeChecksumDeltaDiv(this->m_pad908 + 0x7e58, auStack_454, uVar9);
                    EmitChecksumSum(reinterpret_cast<void *>(uVar9));
                    goto LAB_0046205f;
                }
                EncodeChecksumState(pbVar12);
                uVar9 = EncodeChecksumDeltaDiv(this->m_pad908 + 0x5e3c, auStack_454, 3);
            } else {
                QueueOutgoingPacketField(0);
                uVar9 = EncodeChecksumPairDiff(pbVar1, auStack_454, reinterpret_cast<unsigned int>(pbVar12));
                uVar10 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar9));
                if ((int)((uVar10 ^ (int)uVar10 >> 0x1f) - ((int)uVar10 >> 0x1f)) < 3 ||
                    ((cVar5 = PacketChecksumLessEqual(pbVar1, 1), cVar5 != '\0' &&
                      (cVar5 = PacketChecksumLessEqual(pbVar12, 1), cVar5 != '\0')))) {
                    bVar2 = true;
                } else {
                    bVar2 = false;
                }
                ScrubChecksumGuard(auStack_454);
                if (!bVar2) {
                    if (*reinterpret_cast<int *>(this->m_pad20 + 4) != 1 && *reinterpret_cast<int *>(this->m_pad20 + 4) != 3) {
                        uVar9 = EncodeChecksumDeltaDiv(this->m_pad908 + 0x5e3c, auStack_454, 3);
                        cVar5 = CompareChecksumPair(this->m_pad908 + 0x6060, uVar9);
                        ScrubChecksumGuard(auStack_454);
                        if (cVar5 == '\0') {
                            (*reinterpret_cast<VtStr *>(*reinterpret_cast<int *>(this) + 4))(this, 0, &DAT_00553f90);
                        } else {
                            (*reinterpret_cast<VtStr *>(*reinterpret_cast<int *>(this) + 4))(this, 0, s_wmove_00555ca0);
                        }
                    }
                    uVar9 = EncodeChecksumDeltaMul(this->m_pad908 + 0x4264, auStack_454, 2);
                    iVar11 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar9));
                    AddToPacketChecksum(0x96 - iVar11);
                    ScrubChecksumGuard(auStack_454);
                    uVar9 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                    uVar9 = EncodeChecksumDeltaDiv(this->m_pad908 + 0x7e58, auStack_454, uVar9);
                    EmitChecksumDiff(reinterpret_cast<void *>(uVar9));
                LAB_0046205f:
                    ScrubChecksumGuard(auStack_454);
                    uVar9 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                    EmitChecksumMod(reinterpret_cast<void *>(uVar9));
                    goto LAB_004622cf;
                }
                EncodeChecksumState(pbVar12);
                uVar9 = EncodeChecksumDeltaDiv(this->m_pad908 + 0x5e3c, auStack_454, 3);
            }
            cVar5 = CompareChecksumPair(this->m_pad908 + 0x6060, uVar9);
            ScrubChecksumGuard(auStack_454);
            if (cVar5 == '\0') {
                (*reinterpret_cast<VtStr *>(*reinterpret_cast<int *>(this) + 4))(this, 0, s_normal_00552230);
            } else {
                pcVar13 = s_wnormal_00553618;
            LAB_004622bc:
                (*reinterpret_cast<VtStr *>(*reinterpret_cast<int *>(this) + 4))(this, 0, pcVar13);
            }
        }
        QueueOutgoingPacketField(0);
    }
LAB_004622cf:
    cVar5 = PeekPacketChecksumBool();
    if (cVar5 != '\0') {
        iVar11 = PeekChecksumStateUnderLock(&DAT_00e9bed8);
        *reinterpret_cast<int *>(this->m_padae22 + 0x272) = (*reinterpret_cast<int *>(this->m_padae22 + 0x272) + 9) % iVar11;
        iVar11 = *reinterpret_cast<int *>(this->m_padae22 + 0x276) + *reinterpret_cast<int *>(this->m_padae22 + 0x27a);
        *reinterpret_cast<int *>(this->m_padae22 + 0x276) = iVar11;
        if (0xfe < iVar11) {
            this->m_padae22[0x276] = 0xff; this->m_padae22[0x277] = 0; this->m_padae22[0x278] = 0; this->m_padae22[0x279] = 0;
            this->m_padae22[0x27a] = 0xf0; this->m_padae22[0x27b] = 0xff; this->m_padae22[0x27c] = 0xff; this->m_padae22[0x27d] = 0xff;
        }
        if (*reinterpret_cast<int *>(this->m_padae22 + 0x276) < 0x30) {
            this->m_padae22[0x276] = 0x2f; this->m_padae22[0x277] = 0; this->m_padae22[0x278] = 0; this->m_padae22[0x279] = 0;
            this->m_padae22[0x27a] = 0x10; this->m_padae22[0x27b] = 0; this->m_padae22[0x27c] = 0; this->m_padae22[0x27d] = 0;
        }
        iVar11 = (*reinterpret_cast<int *>(this->m_padae22 + 0x27e) << 2) / 5;
        *reinterpret_cast<int *>(this->m_padae22 + 0x27e) = iVar11;
        if (iVar11 < 0xc0) {
            this->m_padae22[0x27e] = 0xc0; this->m_padae22[0x27f] = 0; this->m_padae22[0x280] = 0; this->m_padae22[0x281] = 0;
        }
    }
    pbVar12 = this->m_pad908 + 0x82bc;
    cVar5 = PacketChecksumGreaterThan(pbVar12, 0);
    if (cVar5 != '\0' && (cVar5 = PeekPacketChecksumBool(), cVar5 == '\x01') &&
        (cVar5 = PeekPacketChecksumBool(), cVar5 == '\x01') &&
        *reinterpret_cast<int *>(&DAT_005f3768 + g_clientContext) != 1 &&
        *reinterpret_cast<int *>(&DAT_005f3768 + g_clientContext) != 2) {
        EncodeDecrementedChecksum();
        uVar9 = EncodeChecksumDeltaMod(pbVar12, auStack_454, 0x14);
        cVar5 = PacketChecksumEquals(reinterpret_cast<void *>(uVar9), 0);
        if (cVar5 == '\0' ||
            (cVar5 = PeekPacketChecksumBool(), cVar5 == '\0') ||
            (cVar5 = PeekPacketChecksumBool(), cVar5 == '\0') ||
            (cVar5 = PeekPacketChecksumBool(), cVar5 == '\0') ||
            (cVar5 = PacketChecksumNotEquals(pbVar12, 0), cVar5 == '\0')) {
            bVar2 = false;
        } else {
            bVar2 = true;
        }
        ScrubChecksumGuard(auStack_454);
        if (bVar2) {
            AcquireSoundChannel(0);
        }
    }
    bVar2 = false;
    cVar5 = PacketChecksumEquals(pbVar12, 0);
    if (cVar5 != '\0' && (cVar5 = PeekPacketChecksumBool(), cVar5 == '\x01')) {
        QueueOutgoingPacketField(0xffffffff);
        cVar5 = PacketChecksumNotEquals(this->m_pad908 + 0x6f5c, 0);
        if (cVar5 != '\0') {
            *reinterpret_cast<unsigned char *>(DAT_007934e4 + 8) = 1;
        }
        ResolveNamedState(reinterpret_cast<int *>(&DAT_007a7644));
        uVar9 = DecodeGuardedBool();
        cVar5 = CheckGuardedBoolAnd(uVar9);
        if (cVar5 != '\0' && (cVar5 = PeekPacketChecksumBool(), cVar5 != '\0') &&
            (cVar5 = PeekPacketChecksumBool(), cVar5 != '\0')) {
            QueueBroadcastEvent(0x8402);
            uVar7 = (unsigned short)PeekChecksumStateUnderLock(this->m_pad908 + 4);
            *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar7;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
            uVar7 = (unsigned short)PeekChecksumStateUnderLock(this->m_pad908 + 0x228);
            *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar7;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
            bVar6 = (unsigned char)PacketChecksumEquals(this->m_pad908 + 0x134c, 1);
            (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = bVar6;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
            BroadcastQueuedEvent();
            SetGuardedBool(0);
            SetGuardedBool(0);
            QueueBroadcastEvent(0xc301);
            (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 1;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
            uVar7 = FUN_0045d360(1);
            *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar7;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
            FUN_0041f200(0);
            BroadcastQueuedEvent();
        }
    }
    cVar5 = PacketChecksumGreaterEqual(this->m_pad908 + 0x228,
                                       *reinterpret_cast<unsigned int *>(&g_nCameraBoundY + g_clientContext));
    if (cVar5 != '\0' && (cVar5 = PeekPacketChecksumBool(), cVar5 == '\x01') &&
        ((cVar5 = PacketChecksumEquals(reinterpret_cast<void *>(g_clientContext + 0x45354), 1), cVar5 != '\0') ||
         (cVar5 = PacketChecksumEquals(reinterpret_cast<void *>(g_clientContext + 0x45354), 3), cVar5 != '\0'))) {
        (*reinterpret_cast<VtStr *>(*reinterpret_cast<int *>(this) + 4))(this, 0, &DAT_00555c90);
        QueueOutgoingPacketField(5);
        uVar10 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(g_clientContext + 0x3b49c));
        iVar11 = g_clientContext;
        if (this->m_owner == uVar10) {
            *reinterpret_cast<unsigned char *>(DAT_005b3424 + 0x93) = 1;
            (&DAT_006a7758)[iVar11] = 0;
        }
        this->m_pad908[0xa50c] = 1;
        SetGuardedBool(0);
        SetGuardedBool(1);
    }
    cVar5 = CheckGuardedBoolAnd(*reinterpret_cast<int *>(this->m_pad20 + 4) != 0xe);
    if (cVar5 == '\0') {
    LAB_00462742:
        bVar3 = false;
    } else {
        uVar9 = EncodeChecksumDeltaDiv(this->m_pad908 + 0x5e3c, auStack_454, 3);
        bVar2 = true;
        cVar5 = CompareChecksumPair(this->m_pad908 + 0x6060, uVar9);
        if (cVar5 == '\0') goto LAB_00462742;
        bVar3 = true;
    }
    if (bVar2) {
        ScrubChecksumGuard(auStack_454);
    }
    if (bVar3) {
        uVar14 = 0x28;
        PeekChecksumStateUnderLock(this->m_pad908 + 0x228);
        uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 4);
        FUN_00436cd0(uVar9, uVar14);
    }
    uVar9 = EncodeChecksumPairDiff(this->m_pad908 + 0x6284, auStack_454, reinterpret_cast<unsigned int>(this->m_pad908 + 0x6060));
    iVar11 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar9));
    ScrubChecksumGuard(auStack_454);
    iVar11 = (iVar11 < 0) ? iVar11 - 7 : iVar11 + 7;
    SubFromPacketChecksum((int)(iVar11 + (iVar11 >> 0x1f & 7U)) >> 3);
    uVar9 = EncodeChecksumPairDiff(this->m_pad908 + 0x68f0, auStack_230, reinterpret_cast<unsigned int>(this->m_pad908 + 0x66cc));
    iVar11 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar9));
    ScrubChecksumGuard(auStack_230);
    iVar11 = (iVar11 < 0) ? iVar11 - 7 : iVar11 + 7;
    SubFromPacketChecksum((int)(iVar11 + (iVar11 >> 0x1f & 7U)) >> 3);
    iVar11 = *reinterpret_cast<int *>(this->m_padae22 + 0x11c2) - *reinterpret_cast<int *>(this->m_padae22 + 0x11be);
    iVar11 = (iVar11 < 0) ? iVar11 - 9 : iVar11 + 9;
    uVar9 = *reinterpret_cast<unsigned int *>(this->m_padbff4 + 0x2b0);
    *reinterpret_cast<int *>(this->m_padae22 + 0x11c2) = *reinterpret_cast<int *>(this->m_padae22 + 0x11c2) - iVar11 / 10;
    cVar5 = PacketChecksumNotEquals(this->m_pad908 + 4, uVar9);
    if (cVar5 != '\0' ||
        (cVar5 = PacketChecksumNotEquals(this->m_pad908 + 0x228, *reinterpret_cast<unsigned int *>(this->m_padbff4 + 0x2b4)),
         cVar5 != '\0')) {
        SetGuardedBool(1);
    }
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 4);
    *reinterpret_cast<unsigned int *>(this->m_padbff4 + 0x2b0) = uVar9;
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x228);
    *reinterpret_cast<unsigned int *>(this->m_padbff4 + 0x2b4) = uVar9;
LAB_004628db:
    return;
}

/* 0x45f910 HandleFireInput, vtable slot 6 (shared). The local input-side
 * fire handler: decides the outcome of a fire attempt and emits the
 * corresponding battle-action broadcast (0x8403 Fire / 0xc400 no-op /
 * 0xc409 confirm), plus the aim-adjust (0x8402), power-charge (0x4006),
 * cancel (0x8006) and overcharge (0x8005) events. It selects between
 * pre-existing outcome codes from the fire angle/power guard cells (this
 * +0x243/+0x2cc int-index = byte 0x90c/0xb30) and the terrain scan; it does
 * NOT integrate a trajectory. Also scans the shared overlay EDIT control's
 * text for a chat-vs-fire gesture. See ARCHITECTURE.md.
 *
 * This is by far the largest CMobile method (0x2104 bytes). To minimise
 * transcription risk at this scale it is translated VERBATIM from a fresh
 * Ghidra decompile keeping `param_1 = (int*)this` and its exact `param_1[N]`
 * / `param_1 + N` offsets (no field-name remapping), with only the standard
 * transforms applied: SEH frame stripped, vtable slots dispatched via the
 * __fastcall+dummy-EDX trick, guard-cell buffers typed as CValueGuard-sized
 * arrays, and the exact control flow (all goto labels) preserved. Same known
 * gaps as the other CMobile methods.
 *
 * score.sh: 653120/207500 - ~3.1x over max, the least byte-faithful method
 * in this file (compiled 1752 instrs vs the original's 0x2104 bytes). At
 * this scale the score carries NO correctness signal: the divergence is the
 * unavoidable compounding of a 22-state stripped SEH machine, ~15 dummy-EDX
 * vtable dispatches, and ~40 dropped-register-arg external calls across a
 * function 2.6x the size of SimulateMobileFrame. HONEST CAVEAT: this is a
 * faithful line-by-line transcription of the fresh decompile (param_1 kept
 * verbatim so the object offsets cannot drift, the main error class at this
 * size), but it is too large to byte-verify - treat it as a readable
 * reconstruction of the fire-input logic, not a proven-correct port. The
 * raw src/battle port (via State11_InBattle_HandleFireInput.c) remains the
 * live version until this is validated. */
void CMobile::HandleFireInput()
{
    typedef void (__fastcall *VtStr)(void *, int, const void *);
    typedef unsigned int (__fastcall *VtRet)(void *);

    int *param_1 = reinterpret_cast<int *>(this);
    unsigned short *puVar1;
    unsigned char *puVar2;
    bool bVar4 = false, bVar5 = false, bVar6 = false, bVar7 = false, bVar8 = false;
    bool bVar3;
    char cVar9;
    unsigned char bVar10;
    unsigned short uVar11;
    short sVar12, sVar13;
    unsigned short uVar14;
    unsigned int uVar15, uVar16, uVar17;
    int iVar18, iVar21, iVar22, iVar25;
    int *piVar19, *piVar20;
    char *pcVar23;
    unsigned long DVar24;
    unsigned char local_b40[0x224];
    char CStack_91c;
    char acStack_91b[127];
    unsigned char local_89c[0x224];
    unsigned char local_678[0x224];
    unsigned char local_454[0x224];
    unsigned char auStack_230[0x224];

    cVar9 = PeekPacketChecksumBool();
    if (cVar9 != '\0' || (cVar9 = PeekPacketChecksumBool(), cVar9 == '\0') || DAT_007933b8 == '\0')
        goto LAB_004619ff;
    bVar8 = false;
    if (DAT_00e52838 == -1000) {
        if (DAT_007934c4 == '\0') {
            cVar9 = PeekPacketChecksumBool();
            if (cVar9 == '\0') goto LAB_0045fdd7;
            cVar9 = PacketChecksumNotEquals(param_1 + 0x715, 0);
            if (cVar9 == '\0') {
                cVar9 = PeekPacketChecksumBool();
                if (cVar9 == '\x01' && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01') &&
                    (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01') &&
                    (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01') &&
                    (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01') &&
                    (&DAT_006a6481)[g_clientContext] == '\0' && param_1[9] != 0xd) {
                    cVar9 = CompareChecksumPair(param_1 + 0x12db, reinterpret_cast<unsigned int>(param_1 + 0x203d));
                    if (cVar9 == '\0' ||
                        (cVar9 = PacketChecksumGreaterThan(param_1 + 0x214f, 0), cVar9 == '\0')) {
                    LAB_0045fb8c:
                        bVar3 = false;
                    } else {
                        uVar17 = EncodeChecksumDeltaSub(param_1 + 0x2cc, local_b40, 0x1e);
                        uVar15 = EncodeChecksumDeltaDiv(param_1 + 0x355, local_89c, 2);
                        uVar15 = EncodeChecksumPairDiff(param_1 + 0x243, local_454, uVar15);
                        uVar16 = EncodeChecksumDeltaSub(param_1 + 0x2cc, local_678, 0x1e);
                        bVar4 = true; bVar7 = true; bVar6 = true; bVar5 = true;
                        PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar17));
                        PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar15));
                        iVar18 = FindGroundHeightAtColumn();
                        iVar25 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar16));
                        if (iVar18 <= iVar25 ||
                            (cVar9 = PacketChecksumGreaterThan(param_1 + 0x243, 0), cVar9 == '\0'))
                            goto LAB_0045fb8c;
                        bVar3 = true;
                    }
                    if (bVar6) ScrubChecksumGuard(local_678);
                    if (bVar7) ScrubChecksumGuard(local_454);
                    if (bVar4) ScrubChecksumGuard(local_89c);
                    if (bVar5) ScrubChecksumGuard(local_b40);
                    if (bVar3) {
                        if (param_1[9] != 1 && param_1[9] != 3) {
                            uVar17 = EncodeChecksumDeltaDiv(param_1 + 0x19d1, local_b40, 3);
                            cVar9 = CompareChecksumPair(param_1 + 0x1a5a, uVar17);
                            ScrubChecksumGuard(local_b40);
                            if (cVar9 == '\0') (*reinterpret_cast<VtStr *>(*param_1 + 4))(param_1, 0, &DAT_00553f90);
                            else (*reinterpret_cast<VtStr *>(*param_1 + 4))(param_1, 0, s_wmove_00555ca0);
                        }
                        EncodeDecrementedChecksum();
                        uVar17 = EncodeChecksumDeltaMul(param_1 + 0x12db, local_b40, 2);
                        iVar18 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar17));
                        AddToPacketChecksum(0x96 - iVar18);
                        ScrubChecksumGuard(local_b40);
                        uVar17 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                        uVar17 = EncodeChecksumDeltaDiv(param_1 + 0x21d8, local_b40, uVar17);
                        EmitChecksumDiff(reinterpret_cast<void *>(uVar17));
                        ScrubChecksumGuard(local_b40);
                        uVar17 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                        EmitChecksumMod(reinterpret_cast<void *>(uVar17));
                        param_1[0x2b84] = param_1[0x2b84] + 1;
                        param_1[0x2c2c] = 3;
                        bVar8 = true;
                        *reinterpret_cast<unsigned char *>(param_1 + 0x2c2b) = *reinterpret_cast<unsigned char *>(param_1 + 2) & 7;
                    } else {
                        if (param_1[9] != 4) {
                            if (param_1[0x2c29] != -1) {
                                FUN_004eeae0();
                                param_1[0x2c29] = -1;
                            }
                            (*reinterpret_cast<VtStr *>(*param_1 + 4))(param_1, 0, s_unmove_00555c98);
                        }
                        QueueOutgoingPacketField(0);
                    }
                }
            } else {
                QueueOutgoingPacketField(0);
                QueueOutgoingPacketField(0);
                QueueBroadcastEvent(0x4001);
                (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 0;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
                BroadcastQueuedEvent();
            }
            if ((&DAT_006a64a4)[g_clientContext] == '\0' &&
                (cVar9 = PeekPacketChecksumBool(), iVar18 = g_clientContext, cVar9 != '\0')) {
                (&DAT_006a64a4)[g_clientContext] = 1;
                *reinterpret_cast<unsigned int *>(&DAT_006a64a8 + iVar18) = 1;
                *reinterpret_cast<unsigned int *>(&DAT_006a64ac + iVar18) = 0;
            }
            goto LAB_0045fdd7;
        }
    } else {
    LAB_0045fdd7:
        bVar7 = false; bVar6 = false; bVar5 = false;
        if (DAT_00e52838 == 1000 && DAT_007934c4 == '\0' &&
            (cVar9 = PeekPacketChecksumBool(), cVar9 != '\0')) {
            cVar9 = PacketChecksumNotEquals(param_1 + 0x715, 1);
            if (cVar9 == '\0') {
                cVar9 = PeekPacketChecksumBool();
                if (cVar9 == '\x01' && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01') &&
                    (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01') &&
                    (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01') &&
                    (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01') &&
                    (&DAT_006a6481)[g_clientContext] == '\0' && param_1[9] != 0xd) {
                    cVar9 = CompareChecksumPair(param_1 + 0x12db, reinterpret_cast<unsigned int>(param_1 + 0x203d));
                    if (cVar9 == '\0' ||
                        (cVar9 = PacketChecksumGreaterThan(param_1 + 0x214f, 0), cVar9 == '\0')) {
                    LAB_0046000e:
                        bVar4 = false;
                    } else {
                        uVar17 = EncodeChecksumDeltaSub(param_1 + 0x2cc, local_678, 0x1e);
                        uVar15 = EncodeChecksumDeltaDiv(param_1 + 0x355, local_454, 2);
                        uVar15 = EncodeChecksumPairSum(param_1 + 0x243, local_89c, reinterpret_cast<void *>(uVar15));
                        uVar16 = EncodeChecksumDeltaSub(param_1 + 0x2cc, local_b40, 0x1e);
                        bVar7 = true; bVar6 = true; bVar5 = true;
                        PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar17));
                        PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar15));
                        iVar18 = FindGroundHeightAtColumn();
                        iVar25 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar16));
                        if (iVar18 <= iVar25 ||
                            (cVar9 = PacketChecksumLessThan(param_1 + 0x243,
                                *reinterpret_cast<int *>(&g_nCameraBoundX + g_clientContext) - 2), cVar9 == '\0'))
                            goto LAB_0046000e;
                        bVar4 = true;
                    }
                    if (bVar5) ScrubChecksumGuard(local_89c);
                    if (bVar6) ScrubChecksumGuard(local_454);
                    if (bVar7) ScrubChecksumGuard(local_678);
                    if (bVar4) {
                        if (param_1[9] != 1 && param_1[9] != 3) {
                            uVar17 = EncodeChecksumDeltaDiv(param_1 + 0x19d1, local_b40, 3);
                            cVar9 = CompareChecksumPair(param_1 + 0x1a5a, uVar17);
                            ScrubChecksumGuard(local_b40);
                            if (cVar9 == '\0') (*reinterpret_cast<VtStr *>(*param_1 + 4))(param_1, 0, &DAT_00553f90);
                            else (*reinterpret_cast<VtStr *>(*param_1 + 4))(param_1, 0, s_wmove_00555ca0);
                        }
                        EncodeDecrementedChecksum();
                        uVar17 = EncodeChecksumDeltaMul(param_1 + 0x12db, local_b40, 2);
                        iVar18 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar17));
                        AddToPacketChecksum(0x96 - iVar18);
                        ScrubChecksumGuard(local_b40);
                        uVar17 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                        uVar17 = EncodeChecksumDeltaDiv(param_1 + 0x21d8, local_b40, uVar17);
                        EmitChecksumSum(reinterpret_cast<void *>(uVar17));
                        ScrubChecksumGuard(local_b40);
                        uVar17 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                        EmitChecksumMod(reinterpret_cast<void *>(uVar17));
                        param_1[0x2b84] = param_1[0x2b84] + 1;
                        param_1[0x2c2c] = 3;
                        bVar8 = true;
                        *reinterpret_cast<unsigned char *>(param_1 + 0x2c2b) = *reinterpret_cast<unsigned char *>(param_1 + 2) & 7;
                    } else {
                        if (param_1[9] != 4) {
                            if (param_1[0x2c29] != -1) {
                                FUN_004eeae0();
                                param_1[0x2c29] = -1;
                            }
                            (*reinterpret_cast<VtStr *>(*param_1 + 4))(param_1, 0, s_unmove_00555c98);
                        }
                        QueueOutgoingPacketField(0);
                    }
                }
            } else {
                QueueOutgoingPacketField(1);
                QueueOutgoingPacketField(0);
                QueueBroadcastEvent(0x4001);
                (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 1;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
                BroadcastQueuedEvent();
            }
            if ((&DAT_006a64a4)[g_clientContext] == '\0' &&
                (cVar9 = PeekPacketChecksumBool(), iVar18 = g_clientContext, cVar9 != '\0')) {
                (&DAT_006a64a4)[g_clientContext] = 1;
                *reinterpret_cast<unsigned int *>(&DAT_006a64a8 + iVar18) = 1;
                *reinterpret_cast<unsigned int *>(&DAT_006a64ac + iVar18) = 0;
            }
        }
    }
    iVar18 = param_1[9];
    if (iVar18 != 0xd &&
        (iVar18 == 1 || iVar18 == 3 || iVar18 == 4 || iVar18 == 0 || iVar18 == 2) && bVar8) {
        uVar17 = (*reinterpret_cast<VtRet *>(*param_1 + 0x14))(param_1);
        uVar17 = EncodeChecksumDeltaSub(param_1 + 0x2cc, local_b40, uVar17);
        iVar18 = PeekChecksumStateUnderLock(&DAT_00794bf0);
        cVar9 = PacketChecksumLessThan(reinterpret_cast<void *>(uVar17), -iVar18);
        ScrubChecksumGuard(local_b40);
        if (cVar9 != '\0') {
            (*reinterpret_cast<VtStr *>(*param_1 + 4))(param_1, 0, &DAT_00553bcc);
            *reinterpret_cast<unsigned char *>(param_1 + 0x240) = 1;
            QueueOutgoingPacketField(0);
            cVar9 = PeekPacketChecksumBool();
            if (cVar9 == '\x01' && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01')) {
                QueueBroadcastEvent(0x8402);
                uVar11 = (unsigned short)PeekChecksumStateUnderLock(param_1 + 0x243);
                *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                uVar11 = (unsigned short)PeekChecksumStateUnderLock(param_1 + 0x2cc);
                *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                bVar10 = (unsigned char)PacketChecksumEquals(param_1 + 0x715, 1);
                (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = bVar10;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
                BroadcastQueuedEvent();
            }
        }
    }
    if (DAT_00e52838 == 0 && DAT_007934c4 == '\0') {
        iVar18 = param_1[9];
        if (iVar18 == 1 || iVar18 == 3 || iVar18 == 4) {
            uVar17 = EncodeChecksumDeltaDiv(param_1 + 0x19d1, local_b40, 3);
            cVar9 = CompareChecksumPair(param_1 + 0x1a5a, uVar17);
            ScrubChecksumGuard(local_b40);
            if (cVar9 == '\0') (*reinterpret_cast<VtStr *>(*param_1 + 4))(param_1, 0, s_normal_00552230);
            else (*reinterpret_cast<VtStr *>(*param_1 + 4))(param_1, 0, s_wnormal_00553618);
        }
        QueueOutgoingPacketField(0);
        if ((&DAT_006a64a4)[g_clientContext] == '\x01' &&
            (cVar9 = PeekPacketChecksumBool(), iVar18 = g_clientContext, cVar9 != '\0')) {
            (&DAT_006a64a4)[g_clientContext] = 0;
            *reinterpret_cast<unsigned int *>(&DAT_006a64a8 + iVar18) = 0xffffffff;
            *reinterpret_cast<unsigned int *>(&DAT_006a64ac + iVar18) = 1;
        }
    }
    bVar5 = false;
    cVar9 = PeekPacketChecksumBool();
    if (cVar9 == '\x01' && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01') &&
        (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01') &&
        (&DAT_006a6481)[g_clientContext] == '\0') {
        if (DAT_00e5283c == -1000) {
            if (DAT_007934c4 != '\0') goto LAB_00460553;
            cVar9 = PacketChecksumGreaterThan(param_1 + 0x939, 0x5a);
            if (cVar9 == '\0') FUN_0040b030();
            else EncodeDecrementedChecksum();
            bVar5 = true;
        }
        if (DAT_00e5283c == 1000 && DAT_007934c4 == '\0') {
            cVar9 = PacketChecksumGreaterThan(param_1 + 0x939, 0x5a);
            if (cVar9 == '\0') EncodeDecrementedChecksum();
            else FUN_0040b030();
            bVar5 = true;
        }
    }
LAB_00460553:
    cVar9 = PeekPacketChecksumBool();
    if (cVar9 == '\x01') {
        piVar19 = param_1 + 0xf1c;
    } else {
        cVar9 = PeekPacketChecksumBool();
        piVar19 = param_1 + 0xbe6;
        if (cVar9 != '\x01') piVar19 = param_1 + 0x8b0;
    }
    uVar17 = PeekChecksumStateUnderLock(piVar19);
    piVar19 = param_1 + 0x1252;
    cVar9 = PacketChecksumGreaterThan(piVar19, uVar17);
    if (cVar9 != '\0') QueueOutgoingPacketField(uVar17);
    cVar9 = PeekPacketChecksumBool();
    if (cVar9 == '\x01') {
        piVar20 = param_1 + 0xfa5;
    } else {
        cVar9 = PeekPacketChecksumBool();
        piVar20 = param_1 + 0xc6f;
        if (cVar9 != '\x01') piVar20 = param_1 + 0x939;
    }
    uVar17 = PeekChecksumStateUnderLock(piVar20);
    cVar9 = PacketChecksumLessThan(piVar19, uVar17);
    if (cVar9 != '\0') QueueOutgoingPacketField(uVar17);
    if (bVar5) {
        QueueBroadcastEvent(0x4006);
        uVar11 = (unsigned short)PeekChecksumStateUnderLock(piVar19);
        *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        BroadcastQueuedEvent();
    }
    piVar19 = param_1 + 0x1d90;
    uVar17 = EncodeChecksumDeltaMul(piVar19, local_b40, 10);
    cVar9 = FUN_0040b450(param_1 + 0x1e19, uVar17);
    if (cVar9 == '\0' || (cVar9 = PacketChecksumNotEquals(param_1 + 0x1e19, 0), cVar9 == '\0') ||
        (cVar9 = PeekPacketChecksumBool(), cVar9 != '\x01') ||
        (cVar9 = PeekPacketChecksumBool(), cVar9 != '\x01') ||
        (cVar9 = PeekPacketChecksumBool(), cVar9 != '\x01') ||
        (&DAT_006a6481)[g_clientContext] != '\0' ||
        (cVar9 = PacketChecksumGreaterThan(param_1 + 0x22f1, 0), cVar9 == '\0')) {
    LAB_004606d5:
        bVar5 = false;
    } else {
        cVar9 = PeekPacketChecksumBool();
        bVar5 = true;
        if (cVar9 != '\x01') goto LAB_004606d5;
    }
    ScrubChecksumGuard(local_b40);
    if (bVar5) {
        uVar17 = EncodeChecksumDeltaMul(piVar19, local_89c, 10);
        EncodeChecksumState(reinterpret_cast<void *>(uVar17));
        ScrubChecksumGuard(local_89c);
        FUN_0043c860(&DAT_006a7f70 + g_clientContext, param_1);
        cVar9 = PeekPacketChecksumBool();
        if (cVar9 == '\x01') {
            uVar17 = 0xc409;
        } else {
            cVar9 = FUN_0041eaa0(g_clientContext, (short)param_1[0x2fef]);
            uVar17 = (cVar9 == '\0') ? 0xc400u : 0x8403u;
        }
        QueueBroadcastEvent(uVar17);
        uVar11 = (unsigned short)PeekChecksumStateUnderLock(param_1 + 0x243);
        *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        uVar11 = (unsigned short)PeekChecksumStateUnderLock(param_1 + 0x2cc);
        *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        piVar20 = param_1 + 0x715;
        bVar10 = (unsigned char)PacketChecksumEquals(piVar20, 1);
        (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = bVar10;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
        bVar10 = (unsigned char)PeekPacketChecksumBool();
        (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = bVar10;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
        uVar11 = (unsigned short)PeekChecksumStateUnderLock(param_1 + 0x1364);
        *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        sVar12 = (short)PeekChecksumStateUnderLock(&DAT_00e9ba40);
        sVar13 = (short)PeekChecksumStateUnderLock(piVar19);
        *reinterpret_cast<short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = sVar12 * sVar13;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        cVar9 = FUN_0045ec30();
        (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = cVar9 != '\0';
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
        cVar9 = PacketChecksumEquals(piVar20, 0);
        if (cVar9 == '\0') {
            PeekChecksumStateUnderLock(param_1 + 0x273c);
            PeekChecksumStateUnderLock(param_1 + 0x1476);
        } else {
            PeekChecksumStateUnderLock(param_1 + 0x1476);
            PeekChecksumStateUnderLock(param_1 + 0x273c);
        }
        PeekChecksumStateUnderLock(param_1 + 0x27c5);
        uVar11 = (unsigned short)FloatToInt64();
        PeekChecksumStateUnderLock(param_1 + 0x27c5);
        uVar14 = (unsigned short)FloatToInt64();
        *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
        puVar1 = reinterpret_cast<unsigned short *>(&DAT_00e9aace + g_dwBroadcastEventCursor);
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        *puVar1 = uVar14;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        cVar9 = PacketChecksumEquals(piVar20, 0);
        if (cVar9 == '\0') {
            PeekChecksumStateUnderLock(param_1 + 0x284e);
            PeekChecksumStateUnderLock(param_1 + 0x1476);
        } else {
            PeekChecksumStateUnderLock(param_1 + 0x284e);
            PeekChecksumStateUnderLock(param_1 + 0x1476);
        }
        PeekChecksumStateUnderLock(param_1 + 0x28d7);
        uVar11 = (unsigned short)FloatToInt64();
        PeekChecksumStateUnderLock(param_1 + 0x28d7);
        uVar14 = (unsigned short)FloatToInt64();
        *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
        puVar1 = reinterpret_cast<unsigned short *>(&DAT_00e9aace + g_dwBroadcastEventCursor);
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        *puVar1 = uVar14;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        cVar9 = PacketChecksumEquals(piVar20, 0);
        if (cVar9 == '\0') {
            PeekChecksumStateUnderLock(param_1 + 0x2a72);
            PeekChecksumStateUnderLock(param_1 + 0x1476);
        } else {
            PeekChecksumStateUnderLock(param_1 + 0x1476);
            PeekChecksumStateUnderLock(param_1 + 0x2a72);
        }
        PeekChecksumStateUnderLock(param_1 + 0x2afb);
        uVar11 = (unsigned short)FloatToInt64();
        PeekChecksumStateUnderLock(param_1 + 0x2afb);
        uVar14 = (unsigned short)FloatToInt64();
        *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
        puVar1 = reinterpret_cast<unsigned short *>(&DAT_00e9aace + g_dwBroadcastEventCursor);
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        *puVar1 = uVar14;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        uVar11 = (unsigned short)PeekChecksumStateUnderLock(reinterpret_cast<void *>(g_clientContext + 0x5af88));
        iVar18 = g_clientContext;
        *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        uVar11 = (unsigned short)PeekChecksumStateUnderLock(reinterpret_cast<void *>(iVar18 + 0x5b1ac));
        *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
        puVar2 = &DAT_00e9aace + g_dwBroadcastEventCursor;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        *puVar2 = 0;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
        FUN_0043d6d0();
        BroadcastQueuedEvent();
        SetGuardedBool(0);
        SetGuardedBool(0);
        iVar18 = g_clientContext;
        *reinterpret_cast<unsigned char *>(param_1 + 0x2ffa) = 0;
        if ((&DAT_005f2f40)[iVar18] == '\x02') {
            ResolveNamedState(reinterpret_cast<int *>(&DAT_007a7644));
            PeekChecksumStateUnderLock(param_1 + 0x1e19);
            ClampCursorToRect();
        }
        *reinterpret_cast<unsigned char *>(DAT_007934e4 + 8) = 1;
    }
    if (-1 < (char)(&DAT_00e52868)[DAT_00e52e68] ||
        (cVar9 = PacketChecksumNotEquals(reinterpret_cast<void *>(g_clientContext + 0x593b4), 0xffffffff), cVar9 != '\0')) {
        piVar19 = param_1 + 0x1e19;
        cVar9 = PacketChecksumNotEquals(piVar19, 0);
        if (cVar9 != '\0' &&
            (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01') &&
            (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01') &&
            (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01') &&
            (&DAT_006a6481)[g_clientContext] == '\0' && (&DAT_005f2f40)[g_clientContext] != '\x02' &&
            (cVar9 = PacketChecksumGreaterThan(param_1 + 0x22f1, 0), cVar9 != '\0') &&
            (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01')) {
            cVar9 = PacketChecksumEquals(reinterpret_cast<void *>(g_clientContext + 0x59190), 0xffffffff);
            if (cVar9 == '\0') {
                cVar9 = PacketChecksumEquals(reinterpret_cast<void *>(g_clientContext + 0x593b4), 0xffffffff);
                if (cVar9 == '\0') {
                    DVar24 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(g_clientContext + 0x593b4));
                } else {
                    DVar24 = timeGetTime2();
                }
                iVar18 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(g_clientContext + 0x59190));
                iVar18 = DVar24 - iVar18;
                if (iVar18 < 0) iVar18 = 1;
                if ((&DAT_005f2f40)[g_clientContext] == '\x01') {
                    iVar25 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
                    iVar21 = PeekChecksumStateUnderLock(param_1 + 0x1d90);
                    iVar22 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
                    QueueOutgoingPacketField((unsigned int)(iVar25 * iVar21 * iVar18) / 3000 + iVar22);
                }
                uVar17 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
                uVar17 = EncodeChecksumDeltaMul(param_1 + 0x1d90, local_b40, uVar17);
                cVar9 = CompareChecksumExceeds(piVar19, uVar17);
                ScrubChecksumGuard(local_b40);
                if (cVar9 != '\0') {
                    uVar17 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
                    uVar17 = EncodeChecksumDeltaMul(param_1 + 0x1d90, local_89c, uVar17);
                    EncodeChecksumState(reinterpret_cast<void *>(uVar17));
                    ScrubChecksumGuard(local_89c);
                }
                FUN_0043c860(&DAT_006a7f70 + g_clientContext, param_1);
                cVar9 = PeekPacketChecksumBool();
                if (cVar9 == '\x01') {
                    uVar17 = 0xc409;
                } else {
                    cVar9 = FUN_0041eaa0(g_clientContext, (short)param_1[0x2fef]);
                    uVar17 = (cVar9 == '\0') ? 0xc400u : 0x8403u;
                }
                QueueBroadcastEvent(uVar17);
                uVar11 = (unsigned short)PeekChecksumStateUnderLock(param_1 + 0x243);
                *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                uVar11 = (unsigned short)PeekChecksumStateUnderLock(param_1 + 0x2cc);
                *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                piVar20 = param_1 + 0x715;
                bVar10 = (unsigned char)PacketChecksumEquals(piVar20, 1);
                (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = bVar10;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
                bVar10 = (unsigned char)PeekPacketChecksumBool();
                (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = bVar10;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
                uVar11 = (unsigned short)PeekChecksumStateUnderLock(param_1 + 0x1364);
                *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                uVar11 = (unsigned short)PeekChecksumStateUnderLock(piVar19);
                *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                cVar9 = FUN_0045ec30();
                (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = cVar9 != '\0';
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
                cVar9 = PacketChecksumEquals(piVar20, 0);
                if (cVar9 == '\0') {
                    PeekChecksumStateUnderLock(param_1 + 0x273c);
                    PeekChecksumStateUnderLock(param_1 + 0x1476);
                } else {
                    PeekChecksumStateUnderLock(param_1 + 0x1476);
                    PeekChecksumStateUnderLock(param_1 + 0x273c);
                }
                PeekChecksumStateUnderLock(param_1 + 0x27c5);
                FUN_004ead90();
                uVar11 = (unsigned short)FloatToInt64();
                PeekChecksumStateUnderLock(param_1 + 0x27c5);
                FUN_004ead70();
                uVar14 = (unsigned short)FloatToInt64();
                *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
                puVar1 = reinterpret_cast<unsigned short *>(&DAT_00e9aace + g_dwBroadcastEventCursor);
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                *puVar1 = uVar14;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                cVar9 = PacketChecksumEquals(piVar20, 0);
                if (cVar9 == '\0') {
                    PeekChecksumStateUnderLock(param_1 + 0x284e);
                    PeekChecksumStateUnderLock(param_1 + 0x1476);
                } else {
                    PeekChecksumStateUnderLock(param_1 + 0x284e);
                    PeekChecksumStateUnderLock(param_1 + 0x1476);
                }
                PeekChecksumStateUnderLock(param_1 + 0x28d7);
                FUN_004ead90();
                uVar11 = (unsigned short)FloatToInt64();
                PeekChecksumStateUnderLock(param_1 + 0x28d7);
                FUN_004ead70();
                uVar14 = (unsigned short)FloatToInt64();
                *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
                puVar1 = reinterpret_cast<unsigned short *>(&DAT_00e9aace + g_dwBroadcastEventCursor);
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                *puVar1 = uVar14;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                cVar9 = PacketChecksumEquals(piVar20, 0);
                if (cVar9 == '\0') {
                    PeekChecksumStateUnderLock(param_1 + 0x2a72);
                    PeekChecksumStateUnderLock(param_1 + 0x1476);
                } else {
                    PeekChecksumStateUnderLock(param_1 + 0x1476);
                    PeekChecksumStateUnderLock(param_1 + 0x2a72);
                }
                PeekChecksumStateUnderLock(param_1 + 0x2afb);
                FUN_004ead90();
                uVar11 = (unsigned short)FloatToInt64();
                PeekChecksumStateUnderLock(param_1 + 0x2afb);
                FUN_004ead70();
                uVar14 = (unsigned short)FloatToInt64();
                iVar18 = g_clientContext;
                *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
                puVar1 = reinterpret_cast<unsigned short *>(&DAT_00e9aace + g_dwBroadcastEventCursor);
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                *puVar1 = uVar14;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                uVar11 = (unsigned short)PeekChecksumStateUnderLock(reinterpret_cast<void *>(iVar18 + 0x5af88));
                iVar18 = g_clientContext;
                *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                uVar11 = (unsigned short)PeekChecksumStateUnderLock(reinterpret_cast<void *>(iVar18 + 0x5b1ac));
                *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
                puVar2 = &DAT_00e9aace + g_dwBroadcastEventCursor;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                *puVar2 = 0;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
                FUN_0043d6d0();
                BroadcastQueuedEvent();
                SetGuardedBool(0);
                SetGuardedBool(0);
                *reinterpret_cast<unsigned char *>(param_1 + 0x2ffa) = 0;
                QueueOutgoingPacketField(0xffffffff);
                QueueOutgoingPacketField(0xffffffff);
                *reinterpret_cast<unsigned char *>(DAT_007934e4 + 8) = 1;
            } else {
                QueueOutgoingPacketField(0xffffffff);
            }
        }
    }
    bVar5 = true;
    if (*reinterpret_cast<char *>(DAT_007934e4 + 8) == '\0' ||
        (iVar18 = GetWindowTextA(*reinterpret_cast<HWND *>(DAT_007934e4 + 4), &CStack_91c, 0x80), iVar18 == 0)) {
        CStack_91c = '\0';
    }
    pcVar23 = &CStack_91c;
    do {
        cVar9 = *pcVar23;
        pcVar23 = pcVar23 + 1;
    } while (cVar9 != '\0');
    iVar18 = 0;
    if (0 < (int)pcVar23 - (int)acStack_91b) {
        do {
            if ((&CStack_91c)[iVar18] != ' ') {
                if (DAT_005b3438 != 2) {
                    bVar5 = false;
                    goto LAB_004613ad;
                }
                if ((&CStack_91c)[iVar18] != -0x7f || acStack_91b[iVar18] != '@') {
                    bVar5 = false;
                    goto LAB_004613b2;
                }
                iVar18 = iVar18 + 1;
            }
            iVar18 = iVar18 + 1;
        } while (iVar18 < (int)pcVar23 - (int)acStack_91b);
    }
    SetWindowTextA(*reinterpret_cast<HWND *>(DAT_007934e4 + 4), reinterpret_cast<LPCSTR>(&DAT_00551cb1));
LAB_004613ad:
    if (DAT_005b3438 == 2) {
    LAB_004613b2:
        if (DAT_007934c4 != '\0') {
            (&DAT_00e52868)[DAT_00e52e68] = 0;
            EnterCriticalSection(&DAT_005a9068);
            EncodeOutgoingPacketField(0xffffffff);
            LeaveCriticalSection(&DAT_005a9068);
            EnterCriticalSection(&DAT_005a9068);
            EncodeOutgoingPacketField(0xffffffff);
            LeaveCriticalSection(&DAT_005a9068);
            EnterCriticalSection(&DAT_005a9068);
            EncodeOutgoingPacketField(0);
            LeaveCriticalSection(&DAT_005a9068);
        }
    }
    cVar9 = PeekPacketChecksumBool();
    if (cVar9 == '\x01' && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01') &&
        (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01') &&
        (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01') && param_1[9] != 0xd &&
        (&DAT_005f2f40)[g_clientContext] != '\x02' &&
        *reinterpret_cast<int *>(&DAT_005f3768 + g_clientContext) != 1 &&
        *reinterpret_cast<int *>(&DAT_005f3768 + g_clientContext) != 2 &&
        bVar5 && DAT_007934c4 == '\0' &&
        ((char)(&DAT_00e52868)[DAT_00e52e68] < '\0' ||
         ((cVar9 = PacketChecksumNotEquals(reinterpret_cast<void *>(g_clientContext + 0x59190), 0xffffffff), cVar9 != '\0') &&
          DAT_007934c4 == '\0'))) {
        QueueOutgoingPacketField(0xffffffff);
        cVar9 = PacketChecksumEquals(param_1 + 0x1e19, 0);
        if (cVar9 == '\0') {
            if ((&DAT_005f2f40)[g_clientContext] == '\0') {
                uVar17 = EncodeChecksumDeltaDiv(param_1 + 0x1d90, auStack_230, 6);
                EmitChecksumSum(reinterpret_cast<void *>(uVar17));
                ScrubChecksumGuard(auStack_230);
            } else {
                iVar18 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(g_clientContext + 0x59190));
                DVar24 = timeGetTime2();
                iVar25 = PeekChecksumStateUnderLock(param_1 + 0x1d90);
                if ((int)((DVar24 - iVar18) * iVar25 * 10) / 3000 < 1) {
                    iVar18 = 1;
                } else {
                    iVar18 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(g_clientContext + 0x59190));
                    DVar24 = timeGetTime2();
                    iVar25 = PeekChecksumStateUnderLock(param_1 + 0x1d90);
                    iVar18 = (int)((DVar24 - iVar18) * iVar25 * 10) / 3000;
                }
                QueueOutgoingPacketField(iVar18);
            }
        } else {
            DVar24 = timeGetTime2();
            cVar9 = PacketChecksumEquals(reinterpret_cast<void *>(g_clientContext + 0x59190), 0xffffffff);
            if (cVar9 != '\0') QueueOutgoingPacketField(DVar24 + 0x32);
            iVar18 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(g_clientContext + 0x59190));
            if ((&DAT_005f2f40)[g_clientContext] == '\x01') {
                iVar18 = (int)(DVar24 - iVar18) / 5;
                if (iVar18 < 1) iVar18 = 1;
                QueueOutgoingPacketField(iVar18);
            } else {
                uVar17 = EncodeChecksumDeltaDiv(param_1 + 0x1d90, local_b40, 6);
                EncodeChecksumState(reinterpret_cast<void *>(uVar17));
                ScrubChecksumGuard(local_b40);
            }
            InvokeWidget(0);
            iVar18 = DAT_007934e4;
            *reinterpret_cast<unsigned char *>(DAT_007934e4 + 8) = 0;
            SetWindowTextA(*reinterpret_cast<HWND *>(iVar18 + 4), reinterpret_cast<LPCSTR>(&DAT_00551cb1));
            QueueBroadcastEvent(0x8006);
            uVar11 = (unsigned short)PeekChecksumStateUnderLock(param_1 + 0x243);
            *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
            uVar11 = (unsigned short)PeekChecksumStateUnderLock(param_1 + 0x2cc);
            *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
            cVar9 = PeekPacketChecksumBool();
            if (cVar9 == '\0') {
                cVar9 = PeekPacketChecksumBool();
                bVar10 = cVar9 != '\0';
            } else {
                bVar10 = 2;
            }
            (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = bVar10;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
            bVar10 = (unsigned char)PacketChecksumEquals(param_1 + 0x715, 1);
            (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = bVar10;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
            BroadcastQueuedEvent();
        }
    }
    if ((param_1[9] == 1 || param_1[9] == 3) && (cVar9 = PeekPacketChecksumBool(), cVar9 != '\0') &&
        0x14 < param_1[0x2b84]) {
        QueueBroadcastEvent(0x8005);
        uVar11 = (unsigned short)PeekChecksumStateUnderLock(param_1 + 0x243);
        *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        uVar11 = (unsigned short)PeekChecksumStateUnderLock(param_1 + 0x2cc);
        *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        BroadcastQueuedEvent();
        param_1[0x2b84] = 0;
    }
    iVar18 = *reinterpret_cast<int *>(&g_nCameraBoundY + g_clientContext);
    EnterCriticalSection(&DAT_005a9068);
    iVar25 = PeekPacketChecksumState();
    LeaveCriticalSection(&DAT_005a9068);
    if (iVar18 <= iVar25 && param_1[0x2b8b] != 0xff && (char)param_1[0x2b85] == '\0') {
        EnterCriticalSection(&DAT_005a9068);
        iVar18 = _rand();
        *reinterpret_cast<char *>(reinterpret_cast<int>(param_1) + 0xbff7) = (char)iVar18;
        iVar18 = _rand();
        *reinterpret_cast<unsigned char *>(param_1 + 0x2ffe) = (unsigned char)iVar18;
        bVar10 = (unsigned char)(1 << (*reinterpret_cast<unsigned char *>(reinterpret_cast<int>(param_1) + 0xbff7) & 7));
        bVar10 = (~bVar10 & (unsigned char)iVar18) | bVar10;
        *reinterpret_cast<unsigned char *>(param_1 + 0x2ffe) = bVar10;
        *reinterpret_cast<unsigned char *>(reinterpret_cast<int>(param_1) + 0xbff9) =
            *reinterpret_cast<unsigned char *>(reinterpret_cast<int>(param_1) + 0xbff7) + bVar10 - 0x34;
        LeaveCriticalSection(&DAT_005a9068);
        cVar9 = PeekPacketChecksumBool();
        cVar9 = CheckGuardedBoolAnd('\x01' - (cVar9 != '\0'));
        if (cVar9 != '\0' && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\0')) {
            FUN_00464060();
        }
        uVar17 = DecodeGuardedBool();
        cVar9 = CheckGuardedBoolAnd(uVar17);
        if (cVar9 != '\0' && (cVar9 = PeekPacketChecksumBool(), cVar9 == '\x01')) {
            SetGuardedBool(0);
            SetGuardedBool(0);
            SetGuardedBool(1);
            QueueBroadcastEvent(0xc301);
            (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 1;
            puVar1 = reinterpret_cast<unsigned short *>(&DAT_00e9aacd + g_dwBroadcastEventCursor);
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
            *puVar1 = 0xffff;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
            FUN_0041f200(0);
            BroadcastQueuedEvent();
        }
        *reinterpret_cast<unsigned char *>(param_1 + 0x2b85) = 1;
    }
LAB_004619ff:
    return;
}
