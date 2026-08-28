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
 * column coordinate arrives in a register Ghidra never resolved).
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 15 argless PeekPacketChecksumState() /
 * EncodeOutgoingPacketField() sites in this file.
 *
 *   - v5_ComputeGroundY (0x45c6e0): six of the nine peeks read EAX
 *     straight out of the helper called on the line above -- the
 *     delta/pair helpers RETURN THEIR SECOND ARGUMENT -- so they are the
 *     named scratch guards this port already declares: &g454 (0x45c755),
 *     &g678 (0x45c84f, 0x45c908, 0x45c9aa, 0x45ca28) and &g230
 *     (0x45caca).  The other three (0x45c77c, 0x45c921, 0x45ca41) all read
 *     the same spilled pointer [esp + 0x2c], built once at 0x45c770 as
 *     EDI + 0x90c = this->m_pad908 + 4 -- exactly the value the C already
 *     names local_67c (which is why the `(void)local_67c` suppression
 *     further down is now redundant, though harmless).
 *   - v3_Render (0x462900): 0x462981 and 0x4629b4 read
 *     g_clientContext + 0x45354 and + 0x3b49c.
 *   - HandleFireInput (0x45f910): the three encodes at 0x4613de /
 *     0x4613ff / 0x46141a are g_clientContext + 0x59190,
 *     g_clientContext + 0x593b4 and EBP + 0x7864, and the peek at
 *     0x461872 is EBP + 0xb30.  EBP is `param_1` here (confirmed by
 *     0x461849's `mov [ebp+0xae10],0` = the C's `param_1[0x2b84] = 0`),
 *     and param_1 is an int *, so the byte offsets become + 0x1e19 and
 *     + 0x2cc.
 *
 * Being C++, the file-local extern declarations of
 * PeekPacketChecksumState / EncodeOutgoingPacketField had to gain the
 * `void *self` parameter -- an empty parameter list means "no arguments"
 * here, unlike in the .c ports.  Both stay __cdecl, so the extra pushed
 * argument is caller-cleaned and behaviour is unchanged until the
 * guard-family prototype flip lands. */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include "Mobile.h"
#include "ValueGuard.h"

extern "C" {
void ScrambleChecksumGuardBytes(int slot, int *guardTable);
extern int g_valueGuardKeyTable;   /* guard-table base pointer cell (0x79376c) */
void ScrubChecksumGuard(void *cell);
void TreeLowerBound(void *scratch, void *guardMap);
extern unsigned char g_valueGuardMap;  /* guard-cell std::map object (0x793770) */
int  PeekPacketChecksumState(void *self);
int  PeekChecksumStateUnderLock(void *cell);
char PeekPacketChecksumBool(unsigned char *cell);
unsigned int EncodeChecksumDeltaDiv(void *cell, void *out, int div);
unsigned int EncodeChecksumPairDiff(void *cell, void *out, unsigned int a);
unsigned int EncodeChecksumDeltaAdd(void *cell, void *out, int delta);
unsigned int EncodeChecksumDeltaSub(void *cell, void *out, unsigned int v);
unsigned int EncodeChecksumPairSum(void *cell, void *out, void *b);
unsigned int EncodeChecksumDeltaMul(void *cell, void *out, int m);
unsigned int EncodeChecksumNegate(void *cell, void *out);
int  FindGroundHeightAtColumn(void);   /* 0x4e4340 - column arg arrives in a register (dropped) */
extern CRITICAL_SECTION g_valueGuardLock;  /* the guard family's shared lock, defined in ValueGuard.cpp */

/* RenderMobile's additional dependencies. The Blit / Draw / FillRect calls
 * all drop most of their real (register-passed) coordinate/handle args in
 * Ghidra's decompile - kept with the exact argument shape the decompile
 * shows (documented gap, same as elsewhere in this tree). GBFillRect is the
 * game's own 2-int sprite-fill primitive (Ghidra labelled it "FillRect");
 * renamed here only to avoid colliding with <windows.h>'s FillRect - the
 * name is irrelevant to the score (it compiles to an external-call reloc). */
/* __fastcall with a PHANTOM first parameter (ECX) - see
 * src/rendering/BlitSpriteDirect.c.  `spriteSetId` is EDX (the outer
 * DAT_00ea0e1c registry key), `dest`/`pitch` are the two real stack
 * arguments, and `attachOwner` is the original's EAX register argument
 * (the inner key), promoted to a real trailing parameter because MSVC
 * cannot express EAX.  It is the same CMobile +0x30 field the
 * BlitSpriteAttached extern below already calls `attachOwner`. */
void __fastcall BlitSpriteDirect(unsigned int phantom, unsigned int spriteSetId, int dest,
                                 int pitch, unsigned int attachOwner);
/* __fastcall with a PHANTOM first parameter (ECX) - see
 * src/rendering/BlitSpriteAttached.c.  `attachOwner` is EDX and `classId`
 * is the original's EAX register argument, promoted to a real trailing
 * parameter because MSVC cannot express EAX. */
unsigned int __fastcall BlitSpriteAttached(unsigned int phantom, unsigned int attachOwner,
                                           unsigned int spriteId, unsigned int tex, int pos,
                                           int layer, unsigned int classId);
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
extern unsigned char g_replayContext;  /* 0xe55ce0 - battle/replay turn-event buffer sized in globals_sized.c; declared scalar and always used as &g_replayContext, the same offset-macro idiom as globals.h */
extern unsigned char g_nCameraX, g_nCameraY;  /* 1-byte: used only as &sym + g_clientContext ctx bases (see Projectile.cpp) */
extern int g_clipMinX, g_clipMaxX, g_clipMinY, g_clipMaxY;  /* on-screen clip bounds */
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
void AddToPacketChecksum(void *self, int v);
void SubFromPacketChecksum(void *self, int v);
void AdvanceSpriteAnimation(void);
/* FIXED (2026-07-15): same calling-convention mismatch as UpdateMobileEmotionState
 * above (real signature `void __fastcall FUN_0045cb50(int *param_1)`). */
void __fastcall FUN_0045cb50(int *param_1);
char FUN_0043c820(void);
void AlignMobileToTerrain(CMobile *self);
/* FIXED (2026-07-15): was declared void(void) with no explicit calling
 * convention (defaults to __cdecl in a C++ TU) - real signature is
 * `void __fastcall UpdateMobileEmotionState(int *param_1)` (functions.h already has
 * this right; this file's own local declaration didn't, a genuine
 * calling-convention/decorated-symbol mismatch - confirmed via the real
 * bring-up stub list, this function only linked because the mismatch
 * left it unresolved and auto-stubbed). __fastcall is fine to state
 * explicitly on a free-function declaration (unlike __thiscall, no
 * C4234 restriction). */
void __fastcall UpdateMobileEmotionState(int *param_1);
void FUN_00436cd0(unsigned int a, unsigned int b);
unsigned short CommitTurnDelay(int a, int regEax);
void FUN_0041f200(int a, int regEax);
char ChecksumPairDiffers(void *a, void *b);
unsigned int EncodeChecksumDeltaMod(void *cell, void *out, int m);
void EncodeChecksumState(void *cell);
void EmitChecksumSum(void *self, void *other);
void EmitChecksumDiff(void *self, void *other);
void EmitChecksumMod(void *self, int divisor);
void EncodeDecrementedChecksum(void *self);
unsigned int AcquireSoundChannel(int a);   /* returns the acquired channel handle */
void ResolveNamedState(int *arg);
int  DecodeGuardedBool(unsigned char *cell);
int SetGuardedBool(int value, int guardPtr);
void QueueBroadcastEvent(unsigned int event, int replayCtx);
void BroadcastQueuedEvent(void);

extern int DAT_005b3424;               /* second per-connection base (distinct from g_clientContext) */
extern unsigned char g_nCameraBoundX, g_nCameraBoundY;  /* 1-byte ctx bases (&sym + g_clientContext) */
extern unsigned char DAT_005f3768;     /* 1-byte ctx base */
extern unsigned char DAT_006a7758;     /* 1-byte ctx base (byte-indexed) */
extern unsigned int  g_sharedTextInputControl;     /* shared overlay EDIT control singleton (holds an address) */
extern unsigned char DAT_007a7644[0x1c];/* animated cursor object (address taken);
                                        * real extent now backed in globals_sized.c */
extern unsigned char g_abBroadcastEventBuffer;
extern unsigned int  g_dwBroadcastEventCursor;
extern const char s_normal_00552230[], s_wnormal_00553618[], s_wmove_00555ca0[];
extern unsigned char DAT_00553f90, DAT_00555c90;

/* HandleFireInput's additional dependencies. */
void EncodeOutgoingPacketField(void *self, unsigned int v);
char CompareChecksumExceeds(void *cell, unsigned int other);
void StopSoundChannel(int soundChannelIndex);
void FUN_0040b030(void *self);
char FUN_0040b450(void *cell, unsigned int v);
void FUN_0043c860(void *base, int *self);
char FUN_0041eaa0(int a, short b);
char FUN_0045ec30(int mobile);
void FUN_0043d6d0(int regEax);
void FUN_00464060(void);
void ClampCursorToRect(void);
void InvokeWidget(int widgetId, int a);
int  _rand(void);
unsigned long timeGetTime2(void);   /* winmm timeGetTime; renamed to dodge the <mmsystem.h> proto */

extern char g_chatInputActive;
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

/* Mobile00_MainAction's additional dependencies. */
unsigned int FUN_0045f840(int regEbx);   /* regEbx = the mobile (this) */
char InitChecksumSeed(void);
/* the shot spawners (SpawnPrimaryShot/Item/Super) - many args arrive by
 * register in the original; kept with the exact arg shape the decompile shows. */
void SpawnPrimaryShot(char owner, int power, int a, int b, int c, unsigned int d, unsigned int e,
                      unsigned int f, unsigned int g, unsigned int h, unsigned int i,
                      unsigned int wind, int shotIndex);  /* 13 args - ret 0x34; see
                      src/battle/SpawnPrimaryShot.c's SIGNATURE FIX note */
void SpawnItemProjectile(char owner, unsigned int a, unsigned int b, unsigned int c, unsigned int d,
                         unsigned int e, unsigned int f);
void SpawnSuperShot(char owner, int a, int b, int c, unsigned int d, unsigned int e, unsigned int f,
                    unsigned int g, unsigned int h, unsigned int i, unsigned int j, unsigned int k);
/* PeekPacketChecksumBool_2 is GONE (2026-08-18): it was a Ghidra fabrication -
 * the "2-arg peek" was the real 1-arg peek of this+0xbfcd whose neighbouring
 * pushes belonged to SpawnPrimaryShot's args 12-13 (wind, shot index).  See
 * memory spawnprimaryshot-13-args and the caller sweep of the same day. */
extern char g_soundAvailable, DAT_00793568;
extern int  g_soundChannels;
extern unsigned char DAT_00794e48, DAT_007949c8;
extern unsigned char DAT_005f376c;
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
    EnterCriticalSection(&g_valueGuardLock);
    PeekPacketChecksumState((void *)(&g454));
    LeaveCriticalSection(&g_valueGuardLock);
    EnterCriticalSection(&g_valueGuardLock);
    local_67c = this->m_pad908 + 4;        /* column x - passed to FindGroundHeightAtColumn via register */
    (void)local_67c;
    PeekPacketChecksumState((void *)(local_67c));
    LeaveCriticalSection(&g_valueGuardLock);
    local_680 = FindGroundHeightAtColumn();
    if (g454.tableHandle != 0) { ScrambleChecksumGuardBytes(g454.tableHandle,&g_valueGuardKeyTable); TreeLowerBound(scratch,&g_valueGuardMap); }
    if (g678.tableHandle != 0) { ScrambleChecksumGuardBytes(g678.tableHandle,&g_valueGuardKeyTable); TreeLowerBound(scratch,&g_valueGuardMap); }

    uVar3 = EncodeChecksumDeltaDiv(pbVar1, &g454, 2);
    EncodeChecksumPairDiff(pbVar2, &g678, uVar3);
    EnterCriticalSection(&g_valueGuardLock);
    iVar4 = PeekPacketChecksumState((void *)(&g678));
    LeaveCriticalSection(&g_valueGuardLock);
    bool bVar7 = local_680 == iVar4;
    if (g678.tableHandle != 0) { ScrambleChecksumGuardBytes(g678.tableHandle,&g_valueGuardKeyTable); TreeLowerBound(scratch,&g_valueGuardMap); }
    if (g454.tableHandle != 0) { ScrambleChecksumGuardBytes(g454.tableHandle,&g_valueGuardKeyTable); TreeLowerBound(scratch,&g_valueGuardMap); }

    iVar4 = local_680;
    if (bVar7) {
        EncodeChecksumPairDiff(pbVar2, &g678, reinterpret_cast<unsigned int>(pbVar1));
        EnterCriticalSection(&g_valueGuardLock);
        PeekPacketChecksumState((void *)(&g678));
        LeaveCriticalSection(&g_valueGuardLock);
        EnterCriticalSection(&g_valueGuardLock);
        PeekPacketChecksumState((void *)(local_67c));
        LeaveCriticalSection(&g_valueGuardLock);
        iVar5 = FindGroundHeightAtColumn();
        if (g678.tableHandle != 0) { ScrambleChecksumGuardBytes(g678.tableHandle,&g_valueGuardKeyTable); TreeLowerBound(scratch,&g_valueGuardMap); }

        EncodeChecksumPairDiff(pbVar2, &g678, reinterpret_cast<unsigned int>(pbVar1));
        EnterCriticalSection(&g_valueGuardLock);
        iVar6 = PeekPacketChecksumState((void *)(&g678));
        LeaveCriticalSection(&g_valueGuardLock);
        if (g678.tableHandle != 0) { ScrambleChecksumGuardBytes(g678.tableHandle,&g_valueGuardKeyTable); TreeLowerBound(scratch,&g_valueGuardMap); }

        iVar4 = local_680;
        if (iVar5 == iVar6) {
            EncodeChecksumDeltaAdd(pbVar2, &g678, 1);
            EnterCriticalSection(&g_valueGuardLock);
            PeekPacketChecksumState((void *)(&g678));
            LeaveCriticalSection(&g_valueGuardLock);
            EnterCriticalSection(&g_valueGuardLock);
            PeekPacketChecksumState((void *)(local_67c));
            LeaveCriticalSection(&g_valueGuardLock);
            iVar4 = FindGroundHeightAtColumn();
            if (g678.tableHandle != 0) { ScrambleChecksumGuardBytes(g678.tableHandle,&g_valueGuardKeyTable); TreeLowerBound(scratch,&g_valueGuardMap); }

            EncodeChecksumDeltaAdd(pbVar2, &g230, 1);
            EnterCriticalSection(&g_valueGuardLock);
            iVar5 = PeekPacketChecksumState((void *)(&g230));
            LeaveCriticalSection(&g_valueGuardLock);
            if (g230.tableHandle != 0) { ScrambleChecksumGuardBytes(g230.tableHandle,&g_valueGuardKeyTable); TreeLowerBound(scratch,&g_valueGuardMap); }

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
    cVar4 = PeekPacketChecksumBool((unsigned char *)this + 0x908);
    iVar9 = g_clientContext;
    if (cVar4 == '\0') {
        EnterCriticalSection(&g_valueGuardLock);
        iVar6 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
        LeaveCriticalSection(&g_valueGuardLock);
        if (iVar6 == 2) {
            EnterCriticalSection(&g_valueGuardLock);
            uVar7 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b49c));
            LeaveCriticalSection(&g_valueGuardLock);
            if ((this->m_owner & 7) == uVar7) {
                iVar6 = *reinterpret_cast<int *>(g_clientContext + 0x1fe2c);
                iVar11 = *reinterpret_cast<int *>(g_clientContext + 0x1fe30);
                if (iVar6 != 0) {
                    BlitSpriteDirect(0, this->m_spriteId, iVar6, iVar11,
                                     *reinterpret_cast<unsigned int *>(this->m_pad20 + 0x10));
                    BlitSpriteDirect(0, this->m_spriteId2, iVar11 / 2 + iVar6, iVar11,
                                     *reinterpret_cast<unsigned int *>(this->m_pad20 + 0x10));
                }
            }
        }
    } else {
        uVar5 = this->m_owner >> 2 & 1;
        uVar15 = (uVar7 & 3) / 2;
        iVar16 = (uVar7 & 1) * 2;
        uVar7 = (*reinterpret_cast<int *>(this->m_pad20 + 4) == 0xe) ? 0xffffffffu : this->m_spriteId;
        BlitSpriteAttached(0, *reinterpret_cast<unsigned int *>(this->m_pad20 + 0x10),
                           uVar7, *reinterpret_cast<unsigned int *>(this->m_pad58 + 0x10),
                           (*reinterpret_cast<int *>(g_clientContext + 0x1fe4c + uVar5 * 4) * (int)uVar15 + iVar16) * 0x80 +
                           *reinterpret_cast<int *>(g_clientContext + 0x1fe44 + uVar5 * 4), iVar11,
                           (this->m_owner & 7) + 0x30d40);
        uVar7 = this->m_owner >> 2 & 1;
        uVar5 = (*reinterpret_cast<int *>(this->m_pad20 + 4) == 0xe) ? 0xffffffffu : this->m_spriteId;
        uVar7 = BlitSpriteAttached(0, *reinterpret_cast<unsigned int *>(this->m_pad20 + 0x10),
                                   uVar5, *reinterpret_cast<unsigned int *>(this->m_pad58 + 0x10),
                                   (*reinterpret_cast<int *>(iVar9 + 0x1fe5c + uVar7 * 4) * (int)uVar15 + iVar16) * 0x80 +
                                   *reinterpret_cast<int *>(iVar9 + 0x1fe54 + uVar7 * 4), iVar11,
                                   (this->m_owner & 7) + 0x493e0);
        *reinterpret_cast<unsigned int *>(iVar9 + ((this->m_owner & 7) + 0x154c) * 0x18) = uVar7 & 0xff;
        if (iVar6 != 0 && this->m_pad908[0xa50c] == 0 &&
            (cVar4 = PeekPacketChecksumBool((unsigned char *)this + 0xbff7), cVar4 != '\x01')) {
            cVar4 = PeekPacketChecksumBool((unsigned char *)this + 0xb090);
            iVar9 = g_clientContext;
            if (cVar4 != '\0') {
                *reinterpret_cast<unsigned char *>((this->m_owner & 7) + 0x1fe94 + g_clientContext) = 0;
            }
            *reinterpret_cast<unsigned int *>(iVar9 + 0x1fe6c + (this->m_owner & 7) * 4) = 1;
            if (*reinterpret_cast<int *>(this->m_pad20 + 4) == 0xe) {
                *reinterpret_cast<unsigned int *>(iVar9 + 0x1fe6c + (this->m_owner & 7) * 4) = 0;
            }
            cVar4 = PeekPacketChecksumBool((unsigned char *)this + 0x8ba8);
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
            BlitSpriteDirect(0, this->m_spriteId,
                             ((int)uVar15 * iVar11 + iVar16) * 0x80 + iVar6, iVar11,
                             *reinterpret_cast<unsigned int *>(this->m_pad20 + 0x10));
            if (*reinterpret_cast<int *>(iVar9 + 0x1fe34 + (this->m_owner >> 2 & 1) * 4) != 0) {
                uVar7 = this->m_owner >> 2 & 1;
                iVar6 = *reinterpret_cast<int *>(iVar9 + 0x1fe3c + uVar7 * 4);
                BlitSpriteDirect(0, this->m_spriteId2,
                                 (iVar6 * (int)uVar15 + iVar16) * 0x80 + *reinterpret_cast<int *>(iVar9 + 0x1fe34 + uVar7 * 4),
                                 iVar6, *reinterpret_cast<unsigned int *>(this->m_pad20 + 0x10));
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
            if (g_clipMinX <= iVar6 + 0x53 && iVar6 <= g_clipMaxX &&
                g_clipMinY <= iVar11 + 0x1f && iVar11 <= g_clipMaxY) {
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
    cVar5 = PeekPacketChecksumBool((unsigned char *)this + 0xbff7);
    if (cVar5 == '\x01') goto LAB_004628db;
    cVar5 = PeekPacketChecksumBool((unsigned char *)this + 0x908);
    if (cVar5 == '\0') {
        AdvanceSpriteAnimation();
        return;
    }
    cVar5 = PeekPacketChecksumBool((unsigned char *)this + 0xbff4);
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
    FUN_0045cb50(reinterpret_cast<int *>(this));
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
    cVar5 = PeekPacketChecksumBool((unsigned char *)this + 0x1c50);
    if (cVar5 != '\0') {
        (*reinterpret_cast<VtVoid *>(*reinterpret_cast<int *>(this) + 0x18))(this);
    }
    AlignMobileToTerrain(this);
    AdvanceSpriteAnimation();
    if (this->m_pad20[0x14] != 0) {
        UpdateMobileEmotionState(reinterpret_cast<int *>(this));
    }
    (*reinterpret_cast<VtAb *>(*reinterpret_cast<int *>(this) + 0x1c))(
        this, 0, *reinterpret_cast<unsigned int *>(this->m_pad20 + 4), *reinterpret_cast<unsigned int *>(this->m_pad20 + 0xc));
    cVar5 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    if (cVar5 == '\x01') goto LAB_004628db;
    cVar5 = PeekPacketChecksumBool((unsigned char *)this + 0x1c50);
    if (cVar5 == '\0' && *reinterpret_cast<int *>(this->m_pad20 + 4) != 0xd &&
        (cVar5 = PeekPacketChecksumBool((unsigned char *)this + 0x8ba8), cVar5 != '\0')) {
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
                    AddToPacketChecksum(this->m_pad908 + 0x7e58, 0x96 - iVar11);
                    ScrubChecksumGuard(auStack_454);
                    uVar9 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                    uVar9 = EncodeChecksumDeltaDiv(this->m_pad908 + 0x7e58, auStack_454, uVar9);
                    EmitChecksumSum(this->m_pad908 + 4, reinterpret_cast<void *>(uVar9));
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
                    AddToPacketChecksum(this->m_pad908 + 0x7e58, 0x96 - iVar11);
                    ScrubChecksumGuard(auStack_454);
                    uVar9 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                    uVar9 = EncodeChecksumDeltaDiv(this->m_pad908 + 0x7e58, auStack_454, uVar9);
                    EmitChecksumDiff(this->m_pad908 + 4, reinterpret_cast<void *>(uVar9));
                LAB_0046205f:
                    ScrubChecksumGuard(auStack_454);
                    uVar9 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                    EmitChecksumMod(this->m_pad908 + 0x7e58, static_cast<int>(uVar9));
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
    cVar5 = PeekPacketChecksumBool((unsigned char *)this + 0x8ba8);
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
    if (cVar5 != '\0' && (cVar5 = PeekPacketChecksumBool((unsigned char *)this + 0x8bae), cVar5 == '\x01') &&
        (cVar5 = PeekPacketChecksumBool((unsigned char *)this + 0x8bb1), cVar5 == '\x01') &&
        *reinterpret_cast<int *>(&DAT_005f3768 + g_clientContext) != 1 &&
        *reinterpret_cast<int *>(&DAT_005f3768 + g_clientContext) != 2) {
        EncodeDecrementedChecksum(pbVar12);
        uVar9 = EncodeChecksumDeltaMod(pbVar12, auStack_454, 0x14);
        cVar5 = PacketChecksumEquals(reinterpret_cast<void *>(uVar9), 0);
        if (cVar5 == '\0' ||
            (cVar5 = PeekPacketChecksumBool((unsigned char *)this + 0x1c50), cVar5 == '\0') ||
            (cVar5 = PeekPacketChecksumBool((unsigned char *)this + 0x8ba8), cVar5 == '\0') ||
            (cVar5 = PeekPacketChecksumBool((unsigned char *)this + 0x8bb1), cVar5 == '\0') ||
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
    if (cVar5 != '\0' && (cVar5 = PeekPacketChecksumBool((unsigned char *)this + 0x8bae), cVar5 == '\x01')) {
        QueueOutgoingPacketField(0xffffffff);
        cVar5 = PacketChecksumNotEquals(this->m_pad908 + 0x6f5c, 0);
        if (cVar5 != '\0') {
            *reinterpret_cast<unsigned char *>(g_sharedTextInputControl + 8) = 1;
        }
        ResolveNamedState(reinterpret_cast<int *>(DAT_007a7644));
        uVar9 = DecodeGuardedBool((unsigned char *)this + 0x8bab);
        cVar5 = CheckGuardedBoolAnd(uVar9);
        if (cVar5 != '\0' && (cVar5 = PeekPacketChecksumBool((unsigned char *)this + 0x8bae), cVar5 != '\0') &&
            (cVar5 = PeekPacketChecksumBool((unsigned char *)this + 0x1c50), cVar5 != '\0')) {
            QueueBroadcastEvent(0x8402,(int)&g_replayContext);
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
            SetGuardedBool(0,GB_GUARD_UNRECOVERED);
            SetGuardedBool(0,GB_GUARD_UNRECOVERED);
            QueueBroadcastEvent(0xc301,(int)&g_replayContext);
            (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 1;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
            uVar7 = CommitTurnDelay(1,reinterpret_cast<int>(this));
            *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar7;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
            FUN_0041f200(0,(int)g_clientContext);
            BroadcastQueuedEvent();
        }
    }
    cVar5 = PacketChecksumGreaterEqual(this->m_pad908 + 0x228,
                                       *reinterpret_cast<unsigned int *>(&g_nCameraBoundY + g_clientContext));
    if (cVar5 != '\0' && (cVar5 = PeekPacketChecksumBool((unsigned char *)this + 0xbff4), cVar5 == '\x01') &&
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
        SetGuardedBool(0,GB_GUARD_UNRECOVERED);
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
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
    SubFromPacketChecksum(this->m_pad908 + 0x6284, (int)(iVar11 + (iVar11 >> 0x1f & 7U)) >> 3);
    uVar9 = EncodeChecksumPairDiff(this->m_pad908 + 0x68f0, auStack_230, reinterpret_cast<unsigned int>(this->m_pad908 + 0x66cc));
    iVar11 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar9));
    ScrubChecksumGuard(auStack_230);
    iVar11 = (iVar11 < 0) ? iVar11 - 7 : iVar11 + 7;
    SubFromPacketChecksum(this->m_pad908 + 0x6284, (int)(iVar11 + (iVar11 >> 0x1f & 7U)) >> 3);
    iVar11 = *reinterpret_cast<int *>(this->m_padae22 + 0x11c2) - *reinterpret_cast<int *>(this->m_padae22 + 0x11be);
    iVar11 = (iVar11 < 0) ? iVar11 - 9 : iVar11 + 9;
    uVar9 = *reinterpret_cast<unsigned int *>(this->m_padbff4 + 0x2b0);
    *reinterpret_cast<int *>(this->m_padae22 + 0x11c2) = *reinterpret_cast<int *>(this->m_padae22 + 0x11c2) - iVar11 / 10;
    cVar5 = PacketChecksumNotEquals(this->m_pad908 + 4, uVar9);
    if (cVar5 != '\0' ||
        (cVar5 = PacketChecksumNotEquals(this->m_pad908 + 0x228, *reinterpret_cast<unsigned int *>(this->m_padbff4 + 0x2b4)),
         cVar5 != '\0')) {
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
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

    cVar9 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    if (cVar9 != '\0' || (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x908), cVar9 == '\0') || g_chatInputActive == '\0')
        goto LAB_004619ff;
    bVar8 = false;
    if (DAT_00e52838 == -1000) {
        if (DAT_007934c4 == '\0') {
            cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bb1);
            if (cVar9 == '\0') goto LAB_0045fdd7;
            cVar9 = PacketChecksumNotEquals(param_1 + 0x715, 0);
            if (cVar9 == '\0') {
                cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x1c50);
                if (cVar9 == '\x01' && (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8ba8), cVar9 == '\x01') &&
                    (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bae), cVar9 == '\x01') &&
                    (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bb1), cVar9 == '\x01') &&
                    (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bbd), cVar9 == '\x01') &&
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
                        EncodeDecrementedChecksum(param_1 + 0x214f);
                        uVar17 = EncodeChecksumDeltaMul(param_1 + 0x12db, local_b40, 2);
                        iVar18 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar17));
                        AddToPacketChecksum(param_1 + 0x21d8, 0x96 - iVar18);
                        ScrubChecksumGuard(local_b40);
                        uVar17 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                        uVar17 = EncodeChecksumDeltaDiv(param_1 + 0x21d8, local_b40, uVar17);
                        EmitChecksumDiff(param_1 + 0x243, reinterpret_cast<void *>(uVar17));
                        ScrubChecksumGuard(local_b40);
                        uVar17 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                        EmitChecksumMod(param_1 + 0x21d8, static_cast<int>(uVar17));
                        param_1[0x2b84] = param_1[0x2b84] + 1;
                        param_1[0x2c2c] = 3;
                        bVar8 = true;
                        *reinterpret_cast<unsigned char *>(param_1 + 0x2c2b) = *reinterpret_cast<unsigned char *>(param_1 + 2) & 7;
                    } else {
                        if (param_1[9] != 4) {
                            if (param_1[0x2c29] != -1) {
                                StopSoundChannel(param_1[0x2c29]);
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
                QueueBroadcastEvent(0x4001,(int)&g_replayContext);
                (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 0;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
                BroadcastQueuedEvent();
            }
            if ((&DAT_006a64a4)[g_clientContext] == '\0' &&
                (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8ba8), iVar18 = g_clientContext, cVar9 != '\0')) {
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
            (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bb1), cVar9 != '\0')) {
            cVar9 = PacketChecksumNotEquals(param_1 + 0x715, 1);
            if (cVar9 == '\0') {
                cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x1c50);
                if (cVar9 == '\x01' && (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8ba8), cVar9 == '\x01') &&
                    (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bae), cVar9 == '\x01') &&
                    (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bb1), cVar9 == '\x01') &&
                    (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bbd), cVar9 == '\x01') &&
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
                        EncodeDecrementedChecksum(param_1 + 0x214f);
                        uVar17 = EncodeChecksumDeltaMul(param_1 + 0x12db, local_b40, 2);
                        iVar18 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar17));
                        AddToPacketChecksum(param_1 + 0x21d8, 0x96 - iVar18);
                        ScrubChecksumGuard(local_b40);
                        uVar17 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                        uVar17 = EncodeChecksumDeltaDiv(param_1 + 0x21d8, local_b40, uVar17);
                        EmitChecksumSum(param_1 + 0x243, reinterpret_cast<void *>(uVar17));
                        ScrubChecksumGuard(local_b40);
                        uVar17 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                        EmitChecksumMod(param_1 + 0x21d8, static_cast<int>(uVar17));
                        param_1[0x2b84] = param_1[0x2b84] + 1;
                        param_1[0x2c2c] = 3;
                        bVar8 = true;
                        *reinterpret_cast<unsigned char *>(param_1 + 0x2c2b) = *reinterpret_cast<unsigned char *>(param_1 + 2) & 7;
                    } else {
                        if (param_1[9] != 4) {
                            if (param_1[0x2c29] != -1) {
                                StopSoundChannel(param_1[0x2c29]);
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
                QueueBroadcastEvent(0x4001,(int)&g_replayContext);
                (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 1;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
                BroadcastQueuedEvent();
            }
            if ((&DAT_006a64a4)[g_clientContext] == '\0' &&
                (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8ba8), iVar18 = g_clientContext, cVar9 != '\0')) {
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
            cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x1c50);
            if (cVar9 == '\x01' && (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8ba8), cVar9 == '\x01')) {
                QueueBroadcastEvent(0x8402,(int)&g_replayContext);
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
            (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8ba8), iVar18 = g_clientContext, cVar9 != '\0')) {
            (&DAT_006a64a4)[g_clientContext] = 0;
            *reinterpret_cast<unsigned int *>(&DAT_006a64a8 + iVar18) = 0xffffffff;
            *reinterpret_cast<unsigned int *>(&DAT_006a64ac + iVar18) = 1;
        }
    }
    bVar5 = false;
    cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x1c50);
    if (cVar9 == '\x01' && (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bb1), cVar9 == '\x01') &&
        (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bbd), cVar9 == '\x01') &&
        (&DAT_006a6481)[g_clientContext] == '\0') {
        if (DAT_00e5283c == -1000) {
            if (DAT_007934c4 != '\0') goto LAB_00460553;
            cVar9 = PacketChecksumGreaterThan(param_1 + 0x939, 0x5a);
            if (cVar9 == '\0') FUN_0040b030(param_1 + 0x1252);
            else EncodeDecrementedChecksum(param_1 + 0x1252);
            bVar5 = true;
        }
        if (DAT_00e5283c == 1000 && DAT_007934c4 == '\0') {
            cVar9 = PacketChecksumGreaterThan(param_1 + 0x939, 0x5a);
            if (cVar9 == '\0') EncodeDecrementedChecksum(param_1 + 0x1252);
            else FUN_0040b030(param_1 + 0x1252);
            bVar5 = true;
        }
    }
LAB_00460553:
    cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bba);
    if (cVar9 == '\x01') {
        piVar19 = param_1 + 0xf1c;
    } else {
        cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bb7);
        piVar19 = param_1 + 0xbe6;
        if (cVar9 != '\x01') piVar19 = param_1 + 0x8b0;
    }
    uVar17 = PeekChecksumStateUnderLock(piVar19);
    piVar19 = param_1 + 0x1252;
    cVar9 = PacketChecksumGreaterThan(piVar19, uVar17);
    if (cVar9 != '\0') QueueOutgoingPacketField(uVar17);
    cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bba);
    if (cVar9 == '\x01') {
        piVar20 = param_1 + 0xfa5;
    } else {
        cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bb7);
        piVar20 = param_1 + 0xc6f;
        if (cVar9 != '\x01') piVar20 = param_1 + 0x939;
    }
    uVar17 = PeekChecksumStateUnderLock(piVar20);
    cVar9 = PacketChecksumLessThan(piVar19, uVar17);
    if (cVar9 != '\0') QueueOutgoingPacketField(uVar17);
    if (bVar5) {
        QueueBroadcastEvent(0x4006,(int)&g_replayContext);
        uVar11 = (unsigned short)PeekChecksumStateUnderLock(piVar19);
        *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        BroadcastQueuedEvent();
    }
    piVar19 = param_1 + 0x1d90;
    uVar17 = EncodeChecksumDeltaMul(piVar19, local_b40, 10);
    cVar9 = FUN_0040b450(param_1 + 0x1e19, uVar17);
    if (cVar9 == '\0' || (cVar9 = PacketChecksumNotEquals(param_1 + 0x1e19, 0), cVar9 == '\0') ||
        (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x1c50), cVar9 != '\x01') ||
        (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bae), cVar9 != '\x01') ||
        (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bbd), cVar9 != '\x01') ||
        (&DAT_006a6481)[g_clientContext] != '\0' ||
        (cVar9 = PacketChecksumGreaterThan(param_1 + 0x22f1, 0), cVar9 == '\0')) {
    LAB_004606d5:
        bVar5 = false;
    } else {
        cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bb1);
        bVar5 = true;
        if (cVar9 != '\x01') goto LAB_004606d5;
    }
    ScrubChecksumGuard(local_b40);
    if (bVar5) {
        uVar17 = EncodeChecksumDeltaMul(piVar19, local_89c, 10);
        EncodeChecksumState(reinterpret_cast<void *>(uVar17));
        ScrubChecksumGuard(local_89c);
        FUN_0043c860(&DAT_006a7f70 + g_clientContext, param_1);
        cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bba);
        if (cVar9 == '\x01') {
            uVar17 = 0xc409;
        } else {
            cVar9 = FUN_0041eaa0(g_clientContext, (short)param_1[0x2fef]);
            uVar17 = (cVar9 == '\0') ? 0xc400u : 0x8403u;
        }
        QueueBroadcastEvent(uVar17,(int)&g_replayContext);
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
        bVar10 = (unsigned char)PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bb7);
        (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = bVar10;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
        uVar11 = (unsigned short)PeekChecksumStateUnderLock(param_1 + 0x1364);
        *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        sVar12 = (short)PeekChecksumStateUnderLock(&DAT_00e9ba40);
        sVar13 = (short)PeekChecksumStateUnderLock(piVar19);
        *reinterpret_cast<short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = sVar12 * sVar13;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
        cVar9 = FUN_0045ec30(reinterpret_cast<int>(this));
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
        FUN_0043d6d0((int)(&DAT_006a7f70 + g_clientContext));
        BroadcastQueuedEvent();
        SetGuardedBool(0,GB_GUARD_UNRECOVERED);
        SetGuardedBool(0,GB_GUARD_UNRECOVERED);
        iVar18 = g_clientContext;
        *reinterpret_cast<unsigned char *>(param_1 + 0x2ffa) = 0;
        if ((&DAT_005f2f40)[iVar18] == '\x02') {
            ResolveNamedState(reinterpret_cast<int *>(DAT_007a7644));
            PeekChecksumStateUnderLock(param_1 + 0x1e19);
            ClampCursorToRect();
        }
        *reinterpret_cast<unsigned char *>(g_sharedTextInputControl + 8) = 1;
    }
    if (-1 < (char)(&DAT_00e52868)[DAT_00e52e68] ||
        (cVar9 = PacketChecksumNotEquals(reinterpret_cast<void *>(g_clientContext + 0x593b4), 0xffffffff), cVar9 != '\0')) {
        piVar19 = param_1 + 0x1e19;
        cVar9 = PacketChecksumNotEquals(piVar19, 0);
        if (cVar9 != '\0' &&
            (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x1c50), cVar9 == '\x01') &&
            (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bae), cVar9 == '\x01') &&
            (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bbd), cVar9 == '\x01') &&
            (&DAT_006a6481)[g_clientContext] == '\0' && (&DAT_005f2f40)[g_clientContext] != '\x02' &&
            (cVar9 = PacketChecksumGreaterThan(param_1 + 0x22f1, 0), cVar9 != '\0') &&
            (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bb1), cVar9 == '\x01')) {
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
                cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bba);
                if (cVar9 == '\x01') {
                    uVar17 = 0xc409;
                } else {
                    cVar9 = FUN_0041eaa0(g_clientContext, (short)param_1[0x2fef]);
                    uVar17 = (cVar9 == '\0') ? 0xc400u : 0x8403u;
                }
                QueueBroadcastEvent(uVar17,(int)&g_replayContext);
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
                bVar10 = (unsigned char)PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bb7);
                (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = bVar10;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
                uVar11 = (unsigned short)PeekChecksumStateUnderLock(param_1 + 0x1364);
                *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                uVar11 = (unsigned short)PeekChecksumStateUnderLock(piVar19);
                *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
                g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
                cVar9 = FUN_0045ec30(reinterpret_cast<int>(this));
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
                FUN_0043d6d0((int)(&DAT_006a7f70 + g_clientContext));
                BroadcastQueuedEvent();
                SetGuardedBool(0,GB_GUARD_UNRECOVERED);
                SetGuardedBool(0,GB_GUARD_UNRECOVERED);
                *reinterpret_cast<unsigned char *>(param_1 + 0x2ffa) = 0;
                QueueOutgoingPacketField(0xffffffff);
                QueueOutgoingPacketField(0xffffffff);
                *reinterpret_cast<unsigned char *>(g_sharedTextInputControl + 8) = 1;
            } else {
                QueueOutgoingPacketField(0xffffffff);
            }
        }
    }
    bVar5 = true;
    if (*reinterpret_cast<char *>(g_sharedTextInputControl + 8) == '\0' ||
        (iVar18 = GetWindowTextA(*reinterpret_cast<HWND *>(g_sharedTextInputControl + 4), &CStack_91c, 0x80), iVar18 == 0)) {
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
    SetWindowTextA(*reinterpret_cast<HWND *>(g_sharedTextInputControl + 4), reinterpret_cast<LPCSTR>(&DAT_00551cb1));
LAB_004613ad:
    if (DAT_005b3438 == 2) {
    LAB_004613b2:
        if (DAT_007934c4 != '\0') {
            (&DAT_00e52868)[DAT_00e52e68] = 0;
            EnterCriticalSection(&g_valueGuardLock);
            EncodeOutgoingPacketField((void *)(g_clientContext + 0x59190), 0xffffffff);
            LeaveCriticalSection(&g_valueGuardLock);
            EnterCriticalSection(&g_valueGuardLock);
            EncodeOutgoingPacketField((void *)(g_clientContext + 0x593b4), 0xffffffff);
            LeaveCriticalSection(&g_valueGuardLock);
            EnterCriticalSection(&g_valueGuardLock);
            EncodeOutgoingPacketField((void *)(param_1 + 0x1e19), 0);
            LeaveCriticalSection(&g_valueGuardLock);
        }
    }
    cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x1c50);
    if (cVar9 == '\x01' && (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bae), cVar9 == '\x01') &&
        (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bb1), cVar9 == '\x01') &&
        (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bbd), cVar9 == '\x01') && param_1[9] != 0xd &&
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
                EmitChecksumSum(param_1 + 0x1e19, reinterpret_cast<void *>(uVar17));
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
            InvokeWidget(3, 0);
            iVar18 = g_sharedTextInputControl;
            *reinterpret_cast<unsigned char *>(g_sharedTextInputControl + 8) = 0;
            SetWindowTextA(*reinterpret_cast<HWND *>(iVar18 + 4), reinterpret_cast<LPCSTR>(&DAT_00551cb1));
            QueueBroadcastEvent(0x8006,(int)&g_replayContext);
            uVar11 = (unsigned short)PeekChecksumStateUnderLock(param_1 + 0x243);
            *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
            uVar11 = (unsigned short)PeekChecksumStateUnderLock(param_1 + 0x2cc);
            *reinterpret_cast<unsigned short *>(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar11;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
            cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bba);
            if (cVar9 == '\0') {
                cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bb7);
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
    if ((param_1[9] == 1 || param_1[9] == 3) && (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bb1), cVar9 != '\0') &&
        0x14 < param_1[0x2b84]) {
        QueueBroadcastEvent(0x8005,(int)&g_replayContext);
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
    EnterCriticalSection(&g_valueGuardLock);
    iVar25 = PeekPacketChecksumState((void *)(param_1 + 0x2cc));
    LeaveCriticalSection(&g_valueGuardLock);
    if (iVar18 <= iVar25 && param_1[0x2b8b] != 0xff && (char)param_1[0x2b85] == '\0') {
        EnterCriticalSection(&g_valueGuardLock);
        iVar18 = _rand();
        *reinterpret_cast<char *>(reinterpret_cast<int>(param_1) + 0xbff7) = (char)iVar18;
        iVar18 = _rand();
        *reinterpret_cast<unsigned char *>(param_1 + 0x2ffe) = (unsigned char)iVar18;
        bVar10 = (unsigned char)(1 << (*reinterpret_cast<unsigned char *>(reinterpret_cast<int>(param_1) + 0xbff7) & 7));
        bVar10 = (~bVar10 & (unsigned char)iVar18) | bVar10;
        *reinterpret_cast<unsigned char *>(param_1 + 0x2ffe) = bVar10;
        *reinterpret_cast<unsigned char *>(reinterpret_cast<int>(param_1) + 0xbff9) =
            *reinterpret_cast<unsigned char *>(reinterpret_cast<int>(param_1) + 0xbff7) + bVar10 - 0x34;
        LeaveCriticalSection(&g_valueGuardLock);
        cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bc0);
        cVar9 = CheckGuardedBoolAnd('\x01' - (cVar9 != '\0'));
        if (cVar9 != '\0' && (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0xbff4), cVar9 == '\0')) {
            FUN_00464060();
        }
        uVar17 = DecodeGuardedBool((unsigned char *)param_1 + 0x8bab);
        cVar9 = CheckGuardedBoolAnd(uVar17);
        if (cVar9 != '\0' && (cVar9 = PeekPacketChecksumBool((unsigned char *)param_1 + 0x8bae), cVar9 == '\x01')) {
            SetGuardedBool(0,GB_GUARD_UNRECOVERED);
            SetGuardedBool(0,GB_GUARD_UNRECOVERED);
            SetGuardedBool(1,GB_GUARD_UNRECOVERED);
            QueueBroadcastEvent(0xc301,(int)&g_replayContext);
            (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 1;
            puVar1 = reinterpret_cast<unsigned short *>(&DAT_00e9aacd + g_dwBroadcastEventCursor);
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
            *puVar1 = 0xffff;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
            FUN_0041f200(0,(int)g_clientContext);
            BroadcastQueuedEvent();
        }
        *reinterpret_cast<unsigned char *>(param_1 + 0x2b85) = 1;
    }
LAB_004619ff:
    return;
}

/* 0x44e920 Mobile00_MainAction - mobile TYPE 0's vtable-slot-7 weapon-fire
 * dispatcher (the only one of the 16 per-type MainActions reconstructed so
 * far). switch(animEvent):
 *   case 1 / 4: acquire the firing sound channel (stash handle at
 *               m_padae22+0x282) if not already held
 *   default:    release it (run the held channel's slot-3 teardown) and
 *               reset the handle to -1
 *   case 5 (subType 2)  : fire primary shot #0 - SpawnPrimaryShot, aim from
 *                         the fire angle/power guards (m_pad908+4 / +0x228)
 *   case 6 (subType 0xe): fire primary shot #1 (mirror of case 5, dir flag 1)
 *   case 8 (subType 2)  : fire the equipped item projectile - SpawnItemProjectile
 *   case 10 (subType 0xe): fire the super shot - SpawnSuperShot
 * Cases 5/6/8/10 all: queue the fire packet, spawn, release the aim sound,
 * and (via InitChecksumSeed) latch the turn-end / next-player transition.
 * Faithful translation of a fresh Ghidra decompile; SEH stripped, guard
 * cells typed as CValueGuard-sized arrays, control flow (goto joins)
 * preserved. Same dropped-register-arg gaps as the rest of this tree. */
void CMobile::Mobile00_MainAction(int animEvent, int subType)
{
    int iVar1;
    unsigned int uVarPB;
    char cVar2;
    unsigned int uVar3, uVar5, uVar6, uVar7, uVar8, uVar9, uVar10, uVar12;
    unsigned int uVar4;
    unsigned char *puVar11;
    int local_1134, local_1130;
    unsigned char local_112c[0x224];
    unsigned char local_f08[0x224];
    unsigned char local_ce4[0x224];
    unsigned char local_ac0[0x224];
    unsigned char local_89c[0x224];
    unsigned char local_678[0x224];
    unsigned char local_454[0x224];
    unsigned char local_230[0x224];

    uVar3 = FUN_0045f840(reinterpret_cast<int>(this));
    switch (animEvent) {
    case 1:
        if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
            uVar3 = AcquireSoundChannel(1);
            *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
        }
        break;
    default:
        iVar1 = *reinterpret_cast<int *>(this->m_padae22 + 0x282);
        if (g_soundAvailable != '\0') {
            if (iVar1 != -1) {
                int *obj = *reinterpret_cast<int **>(g_soundChannels + iVar1 * 4);
                (*reinterpret_cast<void (**)()>(*obj + 0xc))();
            }
            if (iVar1 == 0) {
                DAT_00793568 = 0;
            }
        }
        this->m_padae22[0x282] = 0xff;
        this->m_padae22[0x283] = 0xff;
        this->m_padae22[0x284] = 0xff;
        this->m_padae22[0x285] = 0xff;
        break;
    case 4:
        if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
            uVar3 = AcquireSoundChannel(1);
            *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
        }
        break;
    case 5:
        if (subType != 2) break;
        QueueOutgoingPacketField(0xffffffff);
        puVar11 = (this->m_pad908[0x5c14] == 1) ? &DAT_00796aa0 : &DAT_00794e48;
        uVar5 = PeekChecksumStateUnderLock(puVar11);
        cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfbe);
        if (cVar2 == '\x01') {
        LAB_0044ea19:
            local_1134 = 0;
        } else {
            cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfc1);
            local_1134 = 8;
            if (cVar2 == '\x01') goto LAB_0044ea19;
        }
        uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ce4, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
        uVar7 = EncodeChecksumPairSum(this->m_pad908 + 4, local_454, this->m_pad908 + 0x4af4);
        uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
        uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
        uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
        uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
        uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
        SpawnPrimaryShot((char)this->m_owner, local_1134, 0, 0,
                         *reinterpret_cast<int *>(this->m_padae22 + 10) != 0, uVar7, uVar6, uVar9, uVar8, uVar3, uVarPB, uVar5, 1);
        ScrubChecksumGuard(local_454);
        ScrubChecksumGuard(local_ce4);
        cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
        goto joined_r0x0044ec61;
    case 6:
        if (subType != 0xe) break;
        QueueOutgoingPacketField(0xffffffff);
        puVar11 = (this->m_pad908[0x5c14] == 1) ? &DAT_00796aa0 : &DAT_00794e48;
        uVar5 = PeekChecksumStateUnderLock(puVar11);
        cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfbe);
        if (cVar2 == '\x01') {
        LAB_0044eb7a:
            local_1130 = 0;
        } else {
            cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfc1);
            local_1130 = 8;
            if (cVar2 == '\x01') goto LAB_0044eb7a;
        }
        uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_89c, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
        uVar7 = EncodeChecksumPairSum(this->m_pad908 + 4, local_112c, this->m_pad908 + 0x4f3c);
        uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
        uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
        uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
        uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
        uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
        SpawnPrimaryShot((char)this->m_owner, local_1130, 0, 1,
                         *reinterpret_cast<int *>(this->m_padae22 + 10) != 0, uVar7, uVar6, uVar9, uVar8, uVar3, uVarPB, uVar5, 2);
        ScrubChecksumGuard(local_112c);
        ScrubChecksumGuard(local_89c);
        cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    joined_r0x0044ec61:
        if (cVar2 == '\0') {
            AcquireSoundChannel(0);
        }
        cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfbe);
        if (cVar2 == '\0' && (cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfc1), cVar2 == '\0')) {
        LAB_0044edbd:
            cVar2 = InitChecksumSeed();
            if (cVar2 == '\0') {
                uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
                QueueOutgoingPacketField(uVar3);
            }
            SetGuardedBool(1,GB_GUARD_UNRECOVERED);
        }
        break;
    case 8:
        if (subType != 2) break;
        QueueOutgoingPacketField(0xffffffff);
        cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfbe);
        if (cVar2 == '\x01' || (cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfc1), cVar2 == '\x01')) {
            uVar3 = 0;
        } else {
            uVar3 = 8;
        }
        uVar5 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ac0, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
        uVar6 = EncodeChecksumPairSum(this->m_pad908 + 4, local_f08, this->m_pad908 + 0x4af4);
        uVar4 = (unsigned int)*reinterpret_cast<unsigned short *>(this->m_padae22 + 0x119a);
        uVar7 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
        uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
        uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
        uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
        SpawnItemProjectile((char)this->m_owner, uVar3, uVar6, uVar5, uVar8, uVar7, uVar4);
        ScrubChecksumGuard(local_f08);
        ScrubChecksumGuard(local_ac0);
        cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
        if (cVar2 == '\0') {
            AcquireSoundChannel(0);
        }
        goto LAB_0044edbd;
    case 10:
        if (subType == 0xe) {
            QueueOutgoingPacketField(0xffffffff);
            puVar11 = (this->m_pad908[0x5c14] == 1) ? &DAT_00796aa0 : &DAT_00794e48;
            uVar5 = PeekChecksumStateUnderLock(puVar11);
            uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_230, reinterpret_cast<unsigned int>(this->m_pad908 + 0x55a8));
            uVar7 = EncodeChecksumPairSum(this->m_pad908 + 4, local_678, this->m_pad908 + 0x5384);
            uVar12 = 1;
            uVar8 = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
            uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
            uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
            uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
            uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
            SpawnSuperShot((char)this->m_owner, 0, 0, *reinterpret_cast<int *>(this->m_padae22 + 10) != 0,
                           uVar7, uVar6, uVar10, uVar9, uVar3, uVar8, uVar5, uVar12);
            ScrubChecksumGuard(local_678);
            ScrubChecksumGuard(local_230);
            cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
            if (cVar2 == '\0') {
                AcquireSoundChannel(0);
            }
            cVar2 = InitChecksumSeed();
            if (cVar2 == '\0') {
                uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
                QueueOutgoingPacketField(uVar3);
                iVar1 = g_clientContext;
                *reinterpret_cast<unsigned int *>(&DAT_005f3768 + g_clientContext) = 5;
                *reinterpret_cast<unsigned int *>(&DAT_005f376c + iVar1) = 0;
                SetGuardedBool(1,GB_GUARD_UNRECOVERED);
            } else {
                SetGuardedBool(1,GB_GUARD_UNRECOVERED);
            }
        }
    }
}

/* 0x488ac0 Mobile01_MainAction - mobile TYPE 1's vtable-slot-7 weapon-fire
 * dispatcher (the second MainAction promoted; Mobile00 above is the
 * template).  Same skeleton - switch(animEvent) with the sound-channel
 * acquire/release cases and the fire cases - with type 1's differences:
 *   - the subType gate is 1 (type 0 gates on 2 / 0xe)
 *   - case 5 fires primary shot #0 with weapon-index arg 1 (type 0: 0)
 *   - case 6 is the DOUBLE-SHOT: two SpawnPrimaryShot volleys back to
 *     back (the Mobile.h table's "type 1's case 6" note), each with its
 *     own aim-guard Encode/Peek/Scrub set; the second volley re-peeks the
 *     wind cell and passes power 1/9 where the first passed 0/8
 *   - per-weapon aim-cell pairs: +0x4d18/+0x4af4 (weapon 0),
 *     +0x5160/+0x4f3c (weapon 1 volleys), +0x55a8/+0x5384 (super)
 * Faithful translation of the raw port (src/battle/Mobile01_MainAction.c,
 * which remains the linking reference); SEH stripped, scrub order = the
 * SEH unwind order (reverse construction).  KNOWN ODDITY kept verbatim:
 * the second volley's 10th SpawnPrimaryShot argument is uVar5 - the FIRST
 * volley's diff-cell peek - where every other spawn passes the
 * FUN_0045f840 value; likely a dropped-register artifact to settle at
 * byte-verify. */
void CMobile::Mobile01_MainAction(int animEvent, int subType)
{
    int iVar1;
    unsigned int uVarPB;
    char cVar2;
    unsigned int uVar3, uVar4, uVar5, uVar6, uVar7, uVar8, uVar9, uVar10, uVar12;
    unsigned char *puVar11;
    int local_1584;
    unsigned char local_1574[0x224];
    unsigned char auStack_1384[0x224];
    unsigned char local_112c[0x224];
    unsigned char local_f08[0x224];
    unsigned char local_ce4[0x224];
    unsigned char local_ac0[0x224];
    unsigned char local_89c[0x224];
    unsigned char local_678[0x224];
    unsigned char auStack_488[0x224];
    unsigned char local_230[0x224];

    uVar3 = FUN_0045f840(reinterpret_cast<int>(this));
    switch (animEvent) {
    case 1:
        if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
            uVar3 = AcquireSoundChannel(1);
            *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
        }
        break;
    default:
        iVar1 = *reinterpret_cast<int *>(this->m_padae22 + 0x282);
        if (g_soundAvailable != '\0') {
            if (iVar1 != -1) {
                int *obj = *reinterpret_cast<int **>(g_soundChannels + iVar1 * 4);
                (*reinterpret_cast<void (**)()>(*obj + 0xc))();
            }
            if (iVar1 == 0) {
                DAT_00793568 = 0;
            }
        }
        *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = 0xffffffff;
        break;
    case 4:
        if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
            uVar3 = AcquireSoundChannel(1);
            *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
        }
        break;
    case 5:
        if (subType != 1) break;
        QueueOutgoingPacketField(0xffffffff);
        puVar11 = (this->m_pad908[0x5c14] == 1) ? &DAT_00796aa0 : &DAT_00794e48;
        uVar4 = PeekChecksumStateUnderLock(puVar11);
        cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfbe);
        if (cVar2 == '\x01' || (cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfc1), cVar2 == '\x01')) {
            uVar5 = 0;
        } else {
            uVar5 = 8;
        }
        uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_112c, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
        uVar7 = EncodeChecksumPairSum(this->m_pad908 + 4, local_89c, this->m_pad908 + 0x4af4);
        uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
        uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
        uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
        uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
        uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
        SpawnPrimaryShot((char)this->m_owner, uVar5, 1, 0,
                         *reinterpret_cast<int *>(this->m_padae22 + 10) != 0, uVar7, uVar6, uVar9, uVar8, uVar3, uVarPB, uVar4, 1);
        ScrubChecksumGuard(local_89c);
        ScrubChecksumGuard(local_112c);
        cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
        goto joined_r0x00488f1e;
    case 6:
        if (subType != 1) break;
        QueueOutgoingPacketField(0xffffffff);
        /* volley 1 */
        puVar11 = (this->m_pad908[0x5c14] == 1) ? &DAT_00796aa0 : &DAT_00794e48;
        uVar4 = PeekChecksumStateUnderLock(puVar11);
        cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfbe);
        if (cVar2 == '\x01') {
        LAB_00488d15:
            local_1584 = 0;
        } else {
            cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfc1);
            local_1584 = 8;
            if (cVar2 == '\x01') goto LAB_00488d15;
        }
        uVar5 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ce4, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
        uVar6 = EncodeChecksumPairSum(this->m_pad908 + 4, local_1574, this->m_pad908 + 0x4f3c);
        uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
        uVar7 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
        uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
        uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
        uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
        SpawnPrimaryShot((char)this->m_owner, local_1584, 1, 1,
                         *reinterpret_cast<int *>(this->m_padae22 + 10) != 0, uVar6, uVar5, uVar8, uVar7, uVar3, uVarPB, uVar4, 2);
        ScrubChecksumGuard(local_1574);
        ScrubChecksumGuard(local_ce4);
        /* volley 2 (the double-shot) */
        puVar11 = (this->m_pad908[0x5c14] == 1) ? &DAT_00796aa0 : &DAT_00794e48;
        uVar3 = PeekChecksumStateUnderLock(puVar11);
        cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfbe);
        if (cVar2 == '\x01') {
        LAB_00488e3f:
            uVar4 = 1;
        } else {
            cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfc1);
            uVar4 = 9;
            if (cVar2 == '\x01') goto LAB_00488e3f;
        }
        uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, auStack_1384, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
        uVar7 = EncodeChecksumPairSum(this->m_pad908 + 4, auStack_488, this->m_pad908 + 0x4f3c);
        uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
        uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
        uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
        uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
        uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
        SpawnPrimaryShot((char)this->m_owner, uVar4, 1, 1,
                         *reinterpret_cast<int *>(this->m_padae22 + 10) != 0, uVar7, uVar6, uVar9, uVar8,
                         uVar5 /* sic - see the header note */, uVarPB, uVar3, 2);
        ScrubChecksumGuard(auStack_488);
        ScrubChecksumGuard(auStack_1384);
        cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    joined_r0x00488f1e:
        if (cVar2 == '\0') {
            AcquireSoundChannel(0);
        }
        cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfbe);
        if (cVar2 == '\0' && (cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfc1), cVar2 == '\0')) {
        LAB_0048907a:
            cVar2 = InitChecksumSeed();
            if (cVar2 == '\0') {
                uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
                QueueOutgoingPacketField(uVar3);
            }
            SetGuardedBool(1,GB_GUARD_UNRECOVERED);
        }
        break;
    case 8:
        if (subType != 1) break;
        QueueOutgoingPacketField(0xffffffff);
        cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfbe);
        if (cVar2 == '\x01' || (cVar2 = PeekPacketChecksumBool((unsigned char *)this + 0xbfc1), cVar2 == '\x01')) {
            uVar3 = 0;
        } else {
            uVar3 = 8;
        }
        uVar4 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ac0, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
        uVar5 = EncodeChecksumPairSum(this->m_pad908 + 4, local_f08, this->m_pad908 + 0x4af4);
        uVar10 = (unsigned int)*reinterpret_cast<unsigned short *>(this->m_padae22 + 0x119a);
        uVar6 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
        uVar7 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
        uVar4 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar4));
        uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
        SpawnItemProjectile((char)this->m_owner, uVar3, uVar5, uVar4, uVar7, uVar6, uVar10);
        ScrubChecksumGuard(local_f08);
        ScrubChecksumGuard(local_ac0);
        cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
        if (cVar2 == '\0') {
            AcquireSoundChannel(0);
        }
        goto LAB_0048907a;
    case 10:
        if (subType == 1) {
            QueueOutgoingPacketField(0xffffffff);
            puVar11 = (this->m_pad908[0x5c14] == 1) ? &DAT_00796aa0 : &DAT_00794e48;
            uVar4 = PeekChecksumStateUnderLock(puVar11);
            uVar5 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_230, reinterpret_cast<unsigned int>(this->m_pad908 + 0x55a8));
            uVar6 = EncodeChecksumPairSum(this->m_pad908 + 4, local_678, this->m_pad908 + 0x5384);
            uVar12 = 1;
            uVar7 = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
            uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
            uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
            uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
            uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
            SpawnSuperShot((char)this->m_owner, 0, 1, *reinterpret_cast<int *>(this->m_padae22 + 10) != 0,
                           uVar6, uVar5, uVar9, uVar8, uVar3, uVar7, uVar4, uVar12);
            ScrubChecksumGuard(local_678);
            ScrubChecksumGuard(local_230);
            cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
            if (cVar2 == '\0') {
                AcquireSoundChannel(0);
            }
            cVar2 = InitChecksumSeed();
            if (cVar2 == '\0') {
                uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
                QueueOutgoingPacketField(uVar3);
                iVar1 = g_clientContext;
                *reinterpret_cast<unsigned int *>(&DAT_005f3768 + g_clientContext) = 5;
                *reinterpret_cast<unsigned int *>(&DAT_005f376c + iVar1) = 0;
                SetGuardedBool(1,GB_GUARD_UNRECOVERED);
            } else {
                SetGuardedBool(1,GB_GUARD_UNRECOVERED);
            }
        }
    }
}

/* 0x48d1f0 Mobile02_MainAction - mobile TYPE 2's vtable-slot-7 weapon-fire
 * dispatcher, promoted with the Mobile00/Mobile01 mechanical recipe
 * (43a7ee7): SEH stripped, guard scratch as 0x224 buffers, scrub order =
 * SEH unwind order, faithful control flow and argument shapes.  The raw
 * port (src/battle/Mobile02_MainAction.c) remains the linking reference. */
void CMobile::Mobile02_MainAction(int animEvent, int subType)
{
  unsigned int uVarPB;
  int iVar1;
  char cVar2;
  unsigned int uVar3;
  unsigned int uVar4;
  unsigned int uVar5;
  unsigned int uVar6;
  unsigned int uVar7;
  unsigned int uVar8;
  unsigned int uVar9;
  unsigned int uVar10;
  unsigned char *puVar11;
  unsigned int uVar12;
  unsigned int local_1134;
  unsigned int local_1130;
  unsigned char local_112c[0x224];
  unsigned char local_f08[0x224];
  unsigned char local_ce4[0x224];
  unsigned char local_ac0[0x224];
  unsigned char local_89c[0x224];
  unsigned char local_678[0x224];
  unsigned char local_454[0x224];
  unsigned char local_230[0x224];
  
  uVar3 = FUN_0045f840(reinterpret_cast<int>(this));
  switch (animEvent) {
  case 1:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  case 4:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  case 5:
    if (subType != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar2 == '\x01') {
LAB_0048d2e9:
      local_1134 = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      local_1134 = 8;
      if (cVar2 == '\x01') goto LAB_0048d2e9;
    }
    uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ce4, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_454,this->m_pad908 + 0x4af4);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    SpawnPrimaryShot((char)this->m_owner,local_1134,2,0,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,
                 uVar6,uVar9,uVar8,uVar3,uVarPB, uVar5, 1);
    ScrubChecksumGuard(local_454);
    ScrubChecksumGuard(local_ce4);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    goto joined_r0x0048d531;
  case 6:
    if (subType != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar2 == '\x01') {
LAB_0048d44a:
      local_1130 = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      local_1130 = 8;
      if (cVar2 == '\x01') goto LAB_0048d44a;
    }
    uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_89c, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
    uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_112c,this->m_pad908 + 0x4f3c);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    SpawnPrimaryShot((char)this->m_owner,local_1130,2,1,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,
                 uVar6,uVar9,uVar8,uVar3,uVarPB, uVar5, 1);
    ScrubChecksumGuard(local_112c);
    ScrubChecksumGuard(local_89c);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
joined_r0x0048d531:
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 == '\0') && (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\0')) {
LAB_0048d68d:
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
      }
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
    break;
  case 8:
    if (subType != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 == '\x01') || (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\x01')) {
      uVar3 = 0;
    }
    else {
      uVar3 = 8;
    }
    uVar5 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ac0, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar6 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_f08,this->m_pad908 + 0x4af4);
    uVar4 = (unsigned int)*reinterpret_cast<unsigned short *>(this->m_padae22 + 0x119a);
    uVar7 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    SpawnItemProjectile((char)this->m_owner,uVar3,uVar6,uVar5,uVar8,uVar7,uVar4);
    ScrubChecksumGuard(local_f08);
    ScrubChecksumGuard(local_ac0);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    goto LAB_0048d68d;
  case 10:
    if (subType == 1) {
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_230, reinterpret_cast<unsigned int>(this->m_pad908 + 0x55a8));
      uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_678,this->m_pad908 + 0x5384);
      uVar12 = 1;
      uVar8 = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      SpawnSuperShot((char)this->m_owner,0,2,
                   *reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,uVar6,uVar10,uVar9,uVar3,uVar8,
                   uVar5,uVar12);
      ScrubChecksumGuard(local_678);
      ScrubChecksumGuard(local_230);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
        iVar1 = g_clientContext;
        *reinterpret_cast<unsigned int *>(&DAT_005f3768 + g_clientContext) = 5;
        *reinterpret_cast<unsigned int *>(&DAT_005f376c + iVar1) = 0;
      }
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
  default:
    iVar1 = *reinterpret_cast<int *>(this->m_padae22 + 0x282);
    if (g_soundAvailable != '\0') {
      if (iVar1 != -1) {
        int *obj = *reinterpret_cast<int **>(g_soundChannels + iVar1 * 4);
                (*reinterpret_cast<void (**)()>(*obj + 0xc))();
      }
      if (iVar1 == 0) {
        DAT_00793568 = 0;
      }
    }
    *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = 0xffffffff;
  }
  return;
}

/* 0x4b31f0 Mobile03_MainAction - mobile TYPE 3's vtable-slot-7 weapon-fire
 * dispatcher, promoted with the Mobile00/Mobile01 mechanical recipe
 * (43a7ee7): SEH stripped, guard scratch as 0x224 buffers, scrub order =
 * SEH unwind order, faithful control flow and argument shapes.  The raw
 * port (src/battle/Mobile03_MainAction.c) remains the linking reference. */
void CMobile::Mobile03_MainAction(int animEvent, int subType)
{
  unsigned int uVarPB;
  int iVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  unsigned int uVar5;
  unsigned int uVar6;
  unsigned int uVar7;
  unsigned int uVar8;
  unsigned int uVar9;
  unsigned int uVar10;
  unsigned int uVar11;
  unsigned int uVar12;
  unsigned char *puVar13;
  unsigned int uVar14;
  unsigned int local_19cc;
  unsigned char local_19bc[0x224];
  unsigned char auStack_1800[0x28c];
  unsigned char local_1574[0x224];
  unsigned char auStack_13b8[0x28c];
  unsigned char local_112c[0x224];
  unsigned char local_f08[0x224];
  unsigned char auStack_d18[0x258];
  unsigned char local_ac0[0x224];
  unsigned char auStack_8d0[0x258];
  unsigned char local_678[0x224];
  unsigned char local_454[0x224];
  unsigned char local_230[0x224];
  
  uVar5 = FUN_0045f840(reinterpret_cast<int>(this));
  switch (animEvent) {
  case 1:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar5 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar5;
    }
    break;
  default:
    iVar3 = *reinterpret_cast<int *>(this->m_padae22 + 0x282);
    if (g_soundAvailable != '\0') {
      if (iVar3 != -1) {
        int *obj = *reinterpret_cast<int **>(g_soundChannels + iVar3 * 4);
                (*reinterpret_cast<void (**)()>(*obj + 0xc))();
      }
      if (iVar3 == 0) {
        DAT_00793568 = 0;
      }
    }
    *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = 0xffffffff;
    break;
  case 4:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar5 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar5;
    }
    break;
  case 5:
    if (subType != 0xc) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar13 = &DAT_00796aa0;
    }
    else {
      puVar13 = &DAT_00794e48;
    }
    uVar6 = PeekChecksumStateUnderLock(puVar13);
    cVar4 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar4 == '\x01') || (cVar4 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar4 == '\x01')) {
      uVar7 = 0;
    }
    else {
      uVar7 = 8;
    }
    uVar8 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_1574, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar9 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_112c,this->m_pad908 + 0x4af4);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar11 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar8 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
    uVar9 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar9));
    SpawnPrimaryShot((char)this->m_owner,uVar7,3,0,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar9,uVar8,
                 uVar11,uVar10,uVar5,uVarPB, uVar6, 1);
    ScrubChecksumGuard(local_112c);
    ScrubChecksumGuard(local_1574);
    cVar4 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    goto joined_r0x004b376c;
  case 6:
    if (subType != 6) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar13 = &DAT_00796aa0;
    }
    else {
      puVar13 = &DAT_00794e48;
    }
    uVar6 = PeekChecksumStateUnderLock(puVar13);
    cVar4 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar4 == '\x01') {
LAB_004b3445:
      local_19cc = 0;
    }
    else {
      cVar4 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      local_19cc = 8;
      if (cVar4 == '\x01') goto LAB_004b3445;
    }
    iVar3 = reinterpret_cast<int>(this->m_pad908 + 0x5160);
    iVar1 = reinterpret_cast<int>(this->m_pad908 + 0x228);
    uVar7 = EncodeChecksumPairDiff(reinterpret_cast<void *>(iVar1),local_19bc,iVar3);
    iVar2 = reinterpret_cast<int>(this->m_pad908 + 0x4f3c);
    uVar8 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_454,reinterpret_cast<void *>(iVar2));
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    uVar8 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
    SpawnPrimaryShot((char)this->m_owner,local_19cc,3,1,
                 *reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar8,uVar7,uVar10,uVar9,uVar5,uVarPB, uVar6, 3);
    ScrubChecksumGuard(local_454);
    ScrubChecksumGuard(local_19bc);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar13 = &DAT_00796aa0;
    }
    else {
      puVar13 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar13);
    cVar4 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar4 == '\x01') {
LAB_004b356f:
      uVar6 = 1;
    }
    else {
      cVar4 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      uVar6 = 9;
      if (cVar4 == '\x01') goto LAB_004b356f;
    }
    uVar8 = EncodeChecksumPairDiff(reinterpret_cast<void *>(iVar1),auStack_d18,iVar3);
    uVar9 = EncodeChecksumPairSum(this->m_pad908 + 0x4,auStack_8d0,reinterpret_cast<void *>(iVar2));
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar11 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar8 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
    uVar9 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar9));
    SpawnPrimaryShot((char)this->m_owner,uVar6,3,1,
                 *reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar9,uVar8,uVar11,uVar10,uVar7,uVarPB, uVar5, 3);
    ScrubChecksumGuard(auStack_8d0);
    ScrubChecksumGuard(auStack_d18);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar13 = &DAT_00796aa0;
    }
    else {
      puVar13 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar13);
    cVar4 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar4 == '\x01') {
LAB_004b368d:
      uVar6 = 2;
    }
    else {
      cVar4 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      uVar6 = 10;
      if (cVar4 == '\x01') goto LAB_004b368d;
    }
    uVar7 = EncodeChecksumPairDiff(reinterpret_cast<void *>(iVar1),auStack_13b8,iVar3);
    uVar9 = EncodeChecksumPairSum(this->m_pad908 + 0x4,auStack_1800,reinterpret_cast<void *>(iVar2));
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar11 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    uVar9 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar9));
    SpawnPrimaryShot((char)this->m_owner,uVar6,3,1,
                 *reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar9,uVar7,uVar11,uVar10,uVar8,uVarPB, uVar5, 3);
    ScrubChecksumGuard(auStack_1800);
    ScrubChecksumGuard(auStack_13b8);
    cVar4 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
joined_r0x004b376c:
    if (cVar4 == '\0') {
      AcquireSoundChannel(0);
    }
    cVar4 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar4 == '\0') && (cVar4 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar4 == '\0')) {
LAB_004b38c8:
      cVar4 = InitChecksumSeed();
      if (cVar4 == '\0') {
        uVar5 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar5);
      }
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
    break;
  case 8:
    if (subType != 0xc) break;
    QueueOutgoingPacketField(0xffffffff);
    cVar4 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar4 == '\x01') || (cVar4 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar4 == '\x01')) {
      uVar5 = 0;
    }
    else {
      uVar5 = 8;
    }
    uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ac0, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_f08,this->m_pad908 + 0x4af4);
    uVar12 = (unsigned int)*reinterpret_cast<unsigned short *>(this->m_padae22 + 0x119a);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    SpawnItemProjectile((char)this->m_owner,uVar5,uVar7,uVar6,uVar9,uVar8,uVar12);
    ScrubChecksumGuard(local_f08);
    ScrubChecksumGuard(local_ac0);
    cVar4 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    if (cVar4 == '\0') {
      AcquireSoundChannel(0);
    }
    goto LAB_004b38c8;
  case 10:
    if (subType == 6) {
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar13 = &DAT_00796aa0;
      }
      else {
        puVar13 = &DAT_00794e48;
      }
      uVar6 = PeekChecksumStateUnderLock(puVar13);
      uVar7 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_230, reinterpret_cast<unsigned int>(this->m_pad908 + 0x55a8));
      uVar8 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_678,this->m_pad908 + 0x5384);
      uVar14 = 1;
      uVar9 = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar11 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      uVar8 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
      SpawnSuperShot((char)this->m_owner,0,3,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar8,uVar7,
                   uVar11,uVar10,uVar5,uVar9,uVar6,uVar14);
      ScrubChecksumGuard(local_678);
      ScrubChecksumGuard(local_230);
      cVar4 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar4 == '\0') {
        AcquireSoundChannel(0);
      }
      cVar4 = InitChecksumSeed();
      if (cVar4 == '\0') {
        uVar5 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar5);
        iVar3 = g_clientContext;
        *reinterpret_cast<unsigned int *>(&DAT_005f3768 + g_clientContext) = 5;
        *reinterpret_cast<unsigned int *>(&DAT_005f376c + iVar3) = 0;
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
      else {
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
    }
  }
  return;
}

/* 0x4542a0 Mobile05_MainAction - mobile TYPE 5's vtable-slot-7 weapon-fire
 * dispatcher, promoted with the Mobile00/Mobile01 mechanical recipe
 * (43a7ee7): SEH stripped, guard scratch as 0x224 buffers, scrub order =
 * SEH unwind order, faithful control flow and argument shapes.  The raw
 * port (src/battle/Mobile05_MainAction.c) remains the linking reference. */
void CMobile::Mobile05_MainAction(int animEvent, int subType)
{
  unsigned int uVarPB;
  int iVar1;
  char cVar2;
  unsigned int uVar3;
  unsigned int uVar4;
  unsigned int uVar5;
  unsigned int uVar6;
  unsigned int uVar7;
  unsigned int uVar8;
  unsigned int uVar9;
  unsigned int uVar10;
  unsigned char *puVar11;
  unsigned int uVar12;
  unsigned int local_1e0c;
  unsigned int local_1e08;
  unsigned char local_1e04[0x224];
  unsigned char local_1be0[0x224];
  unsigned char local_19bc[0x224];
  unsigned char local_1798[0x224];
  unsigned char local_1574[0x224];
  unsigned char local_1350[0x224];
  unsigned char local_112c[0x224];
  unsigned char local_f08[0x224];
  unsigned char local_ce4[0x224];
  unsigned char local_ac0[0x224];
  unsigned char local_89c[0x224];
  unsigned char local_678[0x224];
  unsigned char local_454[0x224];
  unsigned char local_230[0x224];
  
  uVar3 = FUN_0045f840(reinterpret_cast<int>(this));
  switch (animEvent) {
  case 1:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  default:
    iVar1 = *reinterpret_cast<int *>(this->m_padae22 + 0x282);
    if (g_soundAvailable != '\0') {
      if (iVar1 != -1) {
        int *obj = *reinterpret_cast<int **>(g_soundChannels + iVar1 * 4);
                (*reinterpret_cast<void (**)()>(*obj + 0xc))();
      }
      if (iVar1 == 0) {
        DAT_00793568 = 0;
      }
    }
    *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = 0xffffffff;
    break;
  case 4:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  case 5:
    if (subType != 8) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar2 == '\x01') {
LAB_0045439b:
      local_1e0c = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      local_1e0c = 8;
      if (cVar2 == '\x01') goto LAB_0045439b;
    }
    uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_19bc, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_112c,this->m_pad908 + 0x4af4);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    SpawnPrimaryShot((char)this->m_owner,local_1e0c,5,0,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,
                 uVar6,uVar9,uVar8,uVar3,uVarPB, uVar5, 1);
    ScrubChecksumGuard(local_112c);
    ScrubChecksumGuard(local_19bc);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    goto joined_r0x00454a06;
  case 6:
    switch(subType) {
    case 8:
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
      if (cVar2 == '\x01') {
LAB_00454508:
        local_1e08 = 0;
      }
      else {
        cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
        local_1e08 = 8;
        if (cVar2 == '\x01') goto LAB_00454508;
      }
      uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_1574, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
      uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_ce4,this->m_pad908 + 0x4f3c);
      uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      SpawnPrimaryShot((char)this->m_owner,local_1e08,5,1,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7
                   ,uVar6,uVar9,uVar8,uVar3,uVarPB, uVar5, 4);
      ScrubChecksumGuard(local_ce4);
      ScrubChecksumGuard(local_1574);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
    default:
      goto switchD_004544ac_caseD_9;
    case 10:
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
      if (cVar2 == '\x01') {
LAB_00454665:
        local_1e08 = 1;
      }
      else {
        cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
        local_1e08 = 9;
        if (cVar2 == '\x01') goto LAB_00454665;
      }
      uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_1e04, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
      uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_454,this->m_pad908 + 0x4f3c);
      uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      SpawnPrimaryShot((char)this->m_owner,local_1e08,5,1,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7
                   ,uVar6,uVar9,uVar8,uVar3,uVarPB, uVar5, 4);
      ScrubChecksumGuard(local_454);
      ScrubChecksumGuard(local_1e04);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
      goto switchD_004544ac_caseD_9;
    case 0xc:
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
      if (cVar2 == '\x01') {
LAB_004547bc:
        local_1e08 = 2;
      }
      else {
        cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
        local_1e08 = 10;
        if (cVar2 == '\x01') goto LAB_004547bc;
      }
      uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_1be0, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
      uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_89c,this->m_pad908 + 0x4f3c);
      uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      SpawnPrimaryShot((char)this->m_owner,local_1e08,5,1,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7
                   ,uVar6,uVar9,uVar8,uVar3,uVarPB, uVar5, 4);
      ScrubChecksumGuard(local_89c);
      ScrubChecksumGuard(local_1be0);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
      goto switchD_004544ac_caseD_9;
    case 0xe:
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
      if (cVar2 == '\x01') {
LAB_00454919:
        local_1e08 = 3;
      }
      else {
        cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
        local_1e08 = 0xb;
        if (cVar2 == '\x01') goto LAB_00454919;
      }
      uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_1350, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
      uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_1798,this->m_pad908 + 0x4f3c);
      uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      SpawnPrimaryShot((char)this->m_owner,local_1e08,5,1,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7
                   ,uVar6,uVar9,uVar8,uVar3,uVarPB, uVar5, 4);
      ScrubChecksumGuard(local_1798);
      ScrubChecksumGuard(local_1350);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    }
joined_r0x00454a06:
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 == '\0') && (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\0')) {
LAB_00454b61:
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
      }
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
    break;
  case 8:
    uVar3 = 8;
    if (subType != 8) break;
    QueueOutgoingPacketField(0xffffffff);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 == '\x01') || (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\x01')) {
      uVar3 = 0;
    }
    uVar5 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ac0, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar6 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_f08,this->m_pad908 + 0x4af4);
    uVar4 = (unsigned int)*reinterpret_cast<unsigned short *>(this->m_padae22 + 0x119a);
    uVar7 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    SpawnItemProjectile((char)this->m_owner,uVar3,uVar6,uVar5,uVar8,uVar7,uVar4);
    ScrubChecksumGuard(local_f08);
    ScrubChecksumGuard(local_ac0);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    goto LAB_00454b61;
  case 10:
    if (subType == 8) {
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_230, reinterpret_cast<unsigned int>(this->m_pad908 + 0x55a8));
      uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_678,this->m_pad908 + 0x5384);
      uVar12 = 1;
      uVar8 = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      SpawnSuperShot((char)this->m_owner,0,5,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,uVar6,
                   uVar10,uVar9,uVar3,uVar8,uVar5,uVar12);
      ScrubChecksumGuard(local_678);
      ScrubChecksumGuard(local_230);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
        iVar1 = g_clientContext;
        *reinterpret_cast<unsigned int *>(&DAT_005f3768 + g_clientContext) = 5;
        *reinterpret_cast<unsigned int *>(&DAT_005f376c + iVar1) = 0;
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
      else {
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
    }
  }
switchD_004544ac_caseD_9:
  return;
}

/* 0x484ff0 Mobile07_MainAction - mobile TYPE 7's vtable-slot-7 weapon-fire
 * dispatcher, promoted with the Mobile00/Mobile01 mechanical recipe
 * (43a7ee7): SEH stripped, guard scratch as 0x224 buffers, scrub order =
 * SEH unwind order, faithful control flow and argument shapes.  The raw
 * port (src/battle/Mobile07_MainAction.c) remains the linking reference. */
void CMobile::Mobile07_MainAction(int animEvent, int subType)
{
  unsigned int uVarPB;
  int iVar1;
  char cVar2;
  unsigned int uVar3;
  unsigned int uVar4;
  unsigned int uVar5;
  unsigned int uVar6;
  unsigned int uVar7;
  unsigned int uVar8;
  unsigned int uVar9;
  unsigned int uVar10;
  unsigned char *puVar11;
  unsigned int uVar12;
  unsigned int local_1134;
  unsigned int local_1130;
  unsigned char local_112c[0x224];
  unsigned char local_f08[0x224];
  unsigned char local_ce4[0x224];
  unsigned char local_ac0[0x224];
  unsigned char local_89c[0x224];
  unsigned char local_678[0x224];
  unsigned char local_454[0x224];
  unsigned char local_230[0x224];
  
  uVar3 = FUN_0045f840(reinterpret_cast<int>(this));
  switch (animEvent) {
  case 1:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  default:
    iVar1 = *reinterpret_cast<int *>(this->m_padae22 + 0x282);
    if (g_soundAvailable != '\0') {
      if (iVar1 != -1) {
        int *obj = *reinterpret_cast<int **>(g_soundChannels + iVar1 * 4);
                (*reinterpret_cast<void (**)()>(*obj + 0xc))();
      }
      if (iVar1 == 0) {
        DAT_00793568 = 0;
      }
    }
    *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = 0xffffffff;
    break;
  case 4:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  case 5:
    if (subType != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar2 == '\x01') {
LAB_004850e9:
      local_1134 = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      local_1134 = 8;
      if (cVar2 == '\x01') goto LAB_004850e9;
    }
    uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ce4, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_454,this->m_pad908 + 0x4af4);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    SpawnPrimaryShot((char)this->m_owner,local_1134,7,0,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,
                 uVar6,uVar9,uVar8,uVar3,uVarPB, uVar5, 1);
    ScrubChecksumGuard(local_454);
    ScrubChecksumGuard(local_ce4);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    goto joined_r0x00485331;
  case 6:
    if (subType != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar2 == '\x01') {
LAB_0048524a:
      local_1130 = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      local_1130 = 8;
      if (cVar2 == '\x01') goto LAB_0048524a;
    }
    uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_89c, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
    uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_112c,this->m_pad908 + 0x4f3c);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    SpawnPrimaryShot((char)this->m_owner,local_1130,7,1,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,
                 uVar6,uVar9,uVar8,uVar3,uVarPB, uVar5, 1);
    ScrubChecksumGuard(local_112c);
    ScrubChecksumGuard(local_89c);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
joined_r0x00485331:
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 == '\0') && (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\0')) {
LAB_0048548d:
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
      }
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
    break;
  case 8:
    if (subType != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 == '\x01') || (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\x01')) {
      uVar3 = 0;
    }
    else {
      uVar3 = 8;
    }
    uVar5 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ac0, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar6 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_f08,this->m_pad908 + 0x4af4);
    uVar4 = (unsigned int)*reinterpret_cast<unsigned short *>(this->m_padae22 + 0x119a);
    uVar7 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    SpawnItemProjectile((char)this->m_owner,uVar3,uVar6,uVar5,uVar8,uVar7,uVar4);
    ScrubChecksumGuard(local_f08);
    ScrubChecksumGuard(local_ac0);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    goto LAB_0048548d;
  case 10:
    if (subType == 1) {
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_230, reinterpret_cast<unsigned int>(this->m_pad908 + 0x55a8));
      uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_678,this->m_pad908 + 0x5384);
      uVar12 = 1;
      uVar8 = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      SpawnSuperShot((char)this->m_owner,8,7,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,uVar6,
                   uVar10,uVar9,uVar3,uVar8,uVar5,uVar12);
      ScrubChecksumGuard(local_678);
      ScrubChecksumGuard(local_230);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
        iVar1 = g_clientContext;
        *reinterpret_cast<unsigned int *>(&DAT_005f3768 + g_clientContext) = 5;
        *reinterpret_cast<unsigned int *>(&DAT_005f376c + iVar1) = 0;
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
      else {
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
    }
  }
  return;
}

/* 0x466890 Mobile08_MainAction - mobile TYPE 8's vtable-slot-7 weapon-fire
 * dispatcher, promoted with the Mobile00/Mobile01 mechanical recipe
 * (43a7ee7): SEH stripped, guard scratch as 0x224 buffers, scrub order =
 * SEH unwind order, faithful control flow and argument shapes.  The raw
 * port (src/battle/Mobile08_MainAction.c) remains the linking reference. */
void CMobile::Mobile08_MainAction(int animEvent, int subType)
{
  unsigned int uVarPB;
  int iVar1;
  char cVar2;
  unsigned int uVar3;
  unsigned int uVar4;
  unsigned int uVar5;
  unsigned int uVar6;
  unsigned int uVar7;
  unsigned int uVar8;
  unsigned int uVar9;
  unsigned int uVar10;
  unsigned char *puVar11;
  unsigned int uVar12;
  unsigned char local_112c[0x224];
  unsigned char local_f08[0x224];
  unsigned char local_ce4[0x224];
  unsigned char local_ac0[0x224];
  unsigned char local_89c[0x224];
  unsigned char local_678[0x224];
  unsigned char local_454[0x224];
  unsigned char local_230[0x224];
  
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_005400f8) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. local_4's
   * `._0_1_`/`._1_3_` partial-field accesses are rewritten as plain
   * int operations, same reasoning as FUN_004174c0.c's fix. */
  uVar3 = FUN_0045f840(reinterpret_cast<int>(this));
  switch (animEvent) {
  case 1:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  default:
    iVar1 = *reinterpret_cast<int *>(this->m_padae22 + 0x282);
    if (g_soundAvailable != '\0') {
      if (iVar1 != -1) {
        int *obj = *reinterpret_cast<int **>(g_soundChannels + iVar1 * 4);
                (*reinterpret_cast<void (**)()>(*obj + 0xc))();
      }
      if (iVar1 == 0) {
        DAT_00793568 = 0;
      }
    }
    *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = 0xffffffff;
    break;
  case 4:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  case 5:
    if (subType != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 == '\x01') || (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\x01')) {
      uVar6 = 0;
    }
    else {
      uVar6 = 8;
    }
    uVar7 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ce4, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar8 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_454,this->m_pad908 + 0x4af4);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    uVar8 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
    SpawnPrimaryShot((char)this->m_owner,uVar6,8,0,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar8,uVar7,
                 uVar10,uVar9,uVar3,uVarPB, uVar5, 1);
    ScrubChecksumGuard(local_454);
    ScrubChecksumGuard(local_ce4);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 != '\0') || (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 != '\0')) break;
    goto LAB_00466d5c;
  case 6:
    if (subType != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 == '\x01') || (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\x01')) {
      uVar6 = 0;
    }
    else {
      uVar6 = 8;
    }
    uVar7 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_89c, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
    uVar8 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_112c,this->m_pad908 + 0x4f3c);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    uVar8 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
    SpawnPrimaryShot((char)this->m_owner,uVar6,8,1,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar8,uVar7,
                 uVar10,uVar9,uVar3,uVarPB, uVar5, 1);
    ScrubChecksumGuard(local_112c);
    ScrubChecksumGuard(local_89c);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 != '\0') || (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 != '\0')) break;
    cVar2 = InitChecksumSeed();
    if (cVar2 == '\0') {
      uVar3 = 0x1e;
      goto LAB_00466d70;
    }
    goto LAB_00466d7f;
  case 8:
    if (subType != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 == '\x01') || (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\x01')) {
      uVar3 = 0;
    }
    else {
      uVar3 = 8;
    }
    uVar5 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ac0, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar6 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_f08,this->m_pad908 + 0x4af4);
    uVar4 = (unsigned int)*reinterpret_cast<unsigned short *>(this->m_padae22 + 0x119a);
    uVar7 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    SpawnItemProjectile((char)this->m_owner,uVar3,uVar6,uVar5,uVar8,uVar7,uVar4);
    ScrubChecksumGuard(local_f08);
    ScrubChecksumGuard(local_ac0);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
LAB_00466d5c:
    cVar2 = InitChecksumSeed();
    if (cVar2 == '\0') {
      uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
LAB_00466d70:
      QueueOutgoingPacketField(uVar3);
    }
LAB_00466d7f:
    SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    break;
  case 10:
    if (subType == 1) {
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_230, reinterpret_cast<unsigned int>(this->m_pad908 + 0x55a8));
      uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_678,this->m_pad908 + 0x5384);
      uVar12 = 1;
      uVar8 = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      SpawnSuperShot((char)this->m_owner,8,8,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,uVar6,
                   uVar10,uVar9,uVar3,uVar8,uVar5,uVar12);
      ScrubChecksumGuard(local_678);
      ScrubChecksumGuard(local_230);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
        iVar1 = g_clientContext;
        *reinterpret_cast<unsigned int *>(&DAT_005f3768 + g_clientContext) = 5;
        *reinterpret_cast<unsigned int *>(&DAT_005f376c + iVar1) = 0;
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
      else {
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
    }
  }
  return;
}

/* 0x47f2d0 Mobile09_MainAction - mobile TYPE 9's vtable-slot-7 weapon-fire
 * dispatcher, promoted with the Mobile00/Mobile01 mechanical recipe
 * (43a7ee7): SEH stripped, guard scratch as 0x224 buffers, scrub order =
 * SEH unwind order, faithful control flow and argument shapes.  The raw
 * port (src/battle/Mobile09_MainAction.c) remains the linking reference. */
void CMobile::Mobile09_MainAction(int animEvent, int subType)
{
  unsigned int uVarPB;
  int iVar1;
  char cVar2;
  unsigned int uVar3;
  unsigned int uVar4;
  unsigned int uVar5;
  unsigned int uVar6;
  unsigned int uVar7;
  unsigned int uVar8;
  unsigned int uVar9;
  unsigned int uVar10;
  unsigned char *puVar11;
  unsigned int uVar12;
  unsigned int local_1134;
  unsigned int local_1130;
  unsigned char local_112c[0x224];
  unsigned char local_f08[0x224];
  unsigned char local_ce4[0x224];
  unsigned char local_ac0[0x224];
  unsigned char local_89c[0x224];
  unsigned char local_678[0x224];
  unsigned char local_454[0x224];
  unsigned char local_230[0x224];
  
  uVar3 = FUN_0045f840(reinterpret_cast<int>(this));
  switch (animEvent) {
  case 1:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  default:
    iVar1 = *reinterpret_cast<int *>(this->m_padae22 + 0x282);
    if (g_soundAvailable != '\0') {
      if (iVar1 != -1) {
        int *obj = *reinterpret_cast<int **>(g_soundChannels + iVar1 * 4);
                (*reinterpret_cast<void (**)()>(*obj + 0xc))();
      }
      if (iVar1 == 0) {
        DAT_00793568 = 0;
      }
    }
    *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = 0xffffffff;
    break;
  case 4:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  case 5:
    if (subType != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar2 == '\x01') {
LAB_0047f3c9:
      local_1134 = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      local_1134 = 8;
      if (cVar2 == '\x01') goto LAB_0047f3c9;
    }
    uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ce4, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_454,this->m_pad908 + 0x4af4);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    SpawnPrimaryShot((char)this->m_owner,local_1134,9,0,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,
                 uVar6,uVar9,uVar8,uVar3,uVarPB, uVar5, 1);
    ScrubChecksumGuard(local_454);
    ScrubChecksumGuard(local_ce4);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    goto joined_r0x0047f611;
  case 6:
    if (subType != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar2 == '\x01') {
LAB_0047f52a:
      local_1130 = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      local_1130 = 8;
      if (cVar2 == '\x01') goto LAB_0047f52a;
    }
    uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_89c, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
    uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_112c,this->m_pad908 + 0x4f3c);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    SpawnPrimaryShot((char)this->m_owner,local_1130,9,1,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,
                 uVar6,uVar9,uVar8,uVar3,uVarPB, uVar5, 1);
    ScrubChecksumGuard(local_112c);
    ScrubChecksumGuard(local_89c);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
joined_r0x0047f611:
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (((cVar2 == '\0') && (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\0')) &&
       (cVar2 = InitChecksumSeed(), cVar2 == '\0')) {
      uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
      QueueOutgoingPacketField(uVar3);
    }
    break;
  case 8:
    if (subType == 1) {
      QueueOutgoingPacketField(0xffffffff);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
      if ((cVar2 == '\x01') || (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\x01')) {
        uVar3 = 0;
      }
      else {
        uVar3 = 8;
      }
      uVar5 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ac0, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
      uVar6 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_f08,this->m_pad908 + 0x4af4);
      uVar4 = (unsigned int)*reinterpret_cast<unsigned short *>(this->m_padae22 + 0x119a);
      uVar7 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      SpawnItemProjectile((char)this->m_owner,uVar3,uVar6,uVar5,uVar8,uVar7,uVar4);
      ScrubChecksumGuard(local_f08);
      ScrubChecksumGuard(local_ac0);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
      }
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
    break;
  case 10:
    if (subType == 1) {
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_230, reinterpret_cast<unsigned int>(this->m_pad908 + 0x55a8));
      uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_678,this->m_pad908 + 0x5384);
      uVar12 = 1;
      uVar8 = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      SpawnSuperShot((char)this->m_owner,0,9,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,uVar6,
                   uVar10,uVar9,uVar3,uVar8,uVar5,uVar12);
      ScrubChecksumGuard(local_678);
      ScrubChecksumGuard(local_230);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
        iVar1 = g_clientContext;
        *reinterpret_cast<unsigned int *>(&DAT_005f3768 + g_clientContext) = 5;
        *reinterpret_cast<unsigned int *>(&DAT_005f376c + iVar1) = 0;
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
      else {
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
    }
  }
  return;
}

/* 0x475e40 Mobile10_MainAction - mobile TYPE 10's vtable-slot-7 weapon-fire
 * dispatcher, promoted with the Mobile00/Mobile01 mechanical recipe
 * (43a7ee7): SEH stripped, guard scratch as 0x224 buffers, scrub order =
 * SEH unwind order, faithful control flow and argument shapes.  The raw
 * port (src/battle/Mobile10_MainAction.c) remains the linking reference. */
void CMobile::Mobile10_MainAction(int animEvent, int subType)
{
  unsigned int uVarPB;
  int iVar1;
  char cVar2;
  unsigned int uVar3;
  unsigned int uVar4;
  unsigned int uVar5;
  unsigned int uVar6;
  unsigned int uVar7;
  unsigned int uVar8;
  unsigned int uVar9;
  unsigned int uVar10;
  unsigned char *puVar11;
  unsigned int uVar12;
  unsigned int local_1134;
  unsigned int local_1130;
  unsigned char local_112c[0x224];
  unsigned char local_f08[0x224];
  unsigned char local_ce4[0x224];
  unsigned char local_ac0[0x224];
  unsigned char local_89c[0x224];
  unsigned char local_678[0x224];
  unsigned char local_454[0x224];
  unsigned char local_230[0x224];
  
  uVar3 = FUN_0045f840(reinterpret_cast<int>(this));
  switch (animEvent) {
  case 1:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  case 4:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  case 5:
    if (subType != 0xd) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar2 == '\x01') {
LAB_00475f39:
      local_1134 = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      local_1134 = 8;
      if (cVar2 == '\x01') goto LAB_00475f39;
    }
    uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ce4, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_454,this->m_pad908 + 0x4af4);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    SpawnPrimaryShot((char)this->m_owner,local_1134,10,0,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,
                 uVar6,uVar9,uVar8,uVar3,uVarPB, uVar5, 1);
    ScrubChecksumGuard(local_454);
    ScrubChecksumGuard(local_ce4);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    goto joined_r0x00476181;
  case 6:
    if (subType != 4) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar2 == '\x01') {
LAB_0047609a:
      local_1130 = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      local_1130 = 8;
      if (cVar2 == '\x01') goto LAB_0047609a;
    }
    uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_89c, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
    uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_112c,this->m_pad908 + 0x4f3c);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    SpawnPrimaryShot((char)this->m_owner,local_1130,10,1,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,
                 uVar6,uVar9,uVar8,uVar3,uVarPB, uVar5, 1);
    ScrubChecksumGuard(local_112c);
    ScrubChecksumGuard(local_89c);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
joined_r0x00476181:
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 == '\0') && (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\0')) {
LAB_004762dd:
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
      }
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
    break;
  case 8:
    if (subType != 0xd) break;
    QueueOutgoingPacketField(0xffffffff);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 == '\x01') || (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\x01')) {
      uVar3 = 0;
    }
    else {
      uVar3 = 8;
    }
    uVar5 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ac0, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar6 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_f08,this->m_pad908 + 0x4af4);
    uVar4 = (unsigned int)*reinterpret_cast<unsigned short *>(this->m_padae22 + 0x119a);
    uVar7 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    SpawnItemProjectile((char)this->m_owner,uVar3,uVar6,uVar5,uVar8,uVar7,uVar4);
    ScrubChecksumGuard(local_f08);
    ScrubChecksumGuard(local_ac0);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    goto LAB_004762dd;
  case 10:
    if (subType == 8) {
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_230, reinterpret_cast<unsigned int>(this->m_pad908 + 0x55a8));
      uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_678,this->m_pad908 + 0x5384);
      uVar12 = 1;
      uVar8 = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      SpawnSuperShot((char)this->m_owner,8,10,
                   *reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,uVar6,uVar10,uVar9,uVar3,uVar8,
                   uVar5,uVar12);
      ScrubChecksumGuard(local_678);
      ScrubChecksumGuard(local_230);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
        iVar1 = g_clientContext;
        *reinterpret_cast<unsigned int *>(&DAT_005f3768 + g_clientContext) = 5;
        *reinterpret_cast<unsigned int *>(&DAT_005f376c + iVar1) = 0;
      }
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
  default:
    iVar1 = *reinterpret_cast<int *>(this->m_padae22 + 0x282);
    if (g_soundAvailable != '\0') {
      if (iVar1 != -1) {
        int *obj = *reinterpret_cast<int **>(g_soundChannels + iVar1 * 4);
                (*reinterpret_cast<void (**)()>(*obj + 0xc))();
      }
      if (iVar1 == 0) {
        DAT_00793568 = 0;
      }
    }
    *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = 0xffffffff;
  }
  return;
}

/* 0x4aed30 Mobile11_MainAction - mobile TYPE 11's vtable-slot-7 weapon-fire
 * dispatcher, promoted with the Mobile00/Mobile01 mechanical recipe
 * (43a7ee7): SEH stripped, guard scratch as 0x224 buffers, scrub order =
 * SEH unwind order, faithful control flow and argument shapes.  The raw
 * port (src/battle/Mobile11_MainAction.c) remains the linking reference. */
void CMobile::Mobile11_MainAction(int animEvent, int subType)
{
  unsigned int uVarPB;
  int iVar1;
  char cVar2;
  unsigned int uVar3;
  unsigned int uVar4;
  unsigned int uVar5;
  unsigned int uVar6;
  unsigned int uVar7;
  unsigned int uVar8;
  unsigned int uVar9;
  unsigned int uVar10;
  unsigned char *puVar11;
  unsigned int uVar12;
  unsigned int local_1584;
  unsigned char local_1574[0x224];
  unsigned char auStack_1384[0x258];
  unsigned char local_112c[0x224];
  unsigned char local_f08[0x224];
  unsigned char local_ce4[0x224];
  unsigned char local_ac0[0x224];
  unsigned char local_89c[0x224];
  unsigned char local_678[0x224];
  unsigned char auStack_488[0x258];
  unsigned char local_230[0x224];
  
  uVar3 = FUN_0045f840(reinterpret_cast<int>(this));
  switch (animEvent) {
  case 1:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  default:
    iVar1 = *reinterpret_cast<int *>(this->m_padae22 + 0x282);
    if (g_soundAvailable != '\0') {
      if (iVar1 != -1) {
        int *obj = *reinterpret_cast<int **>(g_soundChannels + iVar1 * 4);
                (*reinterpret_cast<void (**)()>(*obj + 0xc))();
      }
      if (iVar1 == 0) {
        DAT_00793568 = 0;
      }
    }
    *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = 0xffffffff;
    break;
  case 4:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  case 5:
    if (subType != 6) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar4 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 == '\x01') || (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\x01')) {
      uVar5 = 0;
    }
    else {
      uVar5 = 8;
    }
    uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_112c, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_89c,this->m_pad908 + 0x4af4);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    SpawnPrimaryShot((char)this->m_owner,uVar5,0xb,0,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,
                 uVar6,uVar9,uVar8,uVar3,uVarPB, uVar4, 1);
    ScrubChecksumGuard(local_89c);
    ScrubChecksumGuard(local_112c);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    goto joined_r0x004af18e;
  case 6:
    if (subType != 6) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar4 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar2 == '\x01') {
LAB_004aef85:
      local_1584 = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      local_1584 = 8;
      if (cVar2 == '\x01') goto LAB_004aef85;
    }
    uVar5 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ce4, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
    uVar6 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_1574,this->m_pad908 + 0x4f3c);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar7 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    SpawnPrimaryShot((char)this->m_owner,local_1584,0xb,1,
                 *reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar6,uVar5,uVar8,uVar7,uVar3,uVarPB, uVar4, 2);
    ScrubChecksumGuard(local_1574);
    ScrubChecksumGuard(local_ce4);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar3 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar2 == '\x01') {
LAB_004af0af:
      uVar4 = 1;
    }
    else {
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      uVar4 = 9;
      if (cVar2 == '\x01') goto LAB_004af0af;
    }
    uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, auStack_1384, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
    uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,auStack_488,this->m_pad908 + 0x4f3c);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    SpawnPrimaryShot((char)this->m_owner,uVar4,0xb,1,
                 *reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,uVar6,uVar9,uVar8,uVar5,uVarPB, uVar3, 2);
    ScrubChecksumGuard(auStack_488);
    ScrubChecksumGuard(auStack_1384);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
joined_r0x004af18e:
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 == '\0') && (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\0')) {
LAB_004af2ec:
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
      }
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
    break;
  case 8:
    if (subType != 6) break;
    QueueOutgoingPacketField(0xffffffff);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 == '\x01') || (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\x01')) {
      uVar3 = 0;
    }
    else {
      uVar3 = 8;
    }
    uVar4 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ac0, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar5 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_f08,this->m_pad908 + 0x4af4);
    uVar10 = (unsigned int)*reinterpret_cast<unsigned short *>(this->m_padae22 + 0x119a);
    uVar6 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar7 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar4 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar4));
    uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
    SpawnItemProjectile((char)this->m_owner,uVar3,uVar5,uVar4,uVar7,uVar6,uVar10);
    ScrubChecksumGuard(local_f08);
    ScrubChecksumGuard(local_ac0);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    goto LAB_004af2ec;
  case 10:
    if (subType == 6) {
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar4 = PeekChecksumStateUnderLock(puVar11);
      uVar5 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_230, reinterpret_cast<unsigned int>(this->m_pad908 + 0x55a8));
      uVar6 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_678,this->m_pad908 + 0x5384);
      uVar12 = 1;
      uVar7 = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      SpawnSuperShot((char)this->m_owner,0,0xb,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar6,uVar5,
                   uVar9,uVar8,uVar3,uVar7,uVar4,uVar12);
      ScrubChecksumGuard(local_678);
      ScrubChecksumGuard(local_230);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
        iVar1 = g_clientContext;
        *reinterpret_cast<unsigned int *>(&DAT_005f3768 + g_clientContext) = 5;
        *reinterpret_cast<unsigned int *>(&DAT_005f376c + iVar1) = 0;
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
      else {
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
    }
  }
  return;
}

/* 0x47ab90 Mobile14_MainAction - mobile TYPE 14's vtable-slot-7 weapon-fire
 * dispatcher, promoted with the Mobile00/Mobile01 mechanical recipe
 * (43a7ee7): SEH stripped, guard scratch as 0x224 buffers, scrub order =
 * SEH unwind order, faithful control flow and argument shapes.  The raw
 * port (src/battle/Mobile14_MainAction.c) remains the linking reference. */
void CMobile::Mobile14_MainAction(int animEvent, int subType)
{
  unsigned int uVarPB;
  int iVar1;
  char cVar2;
  unsigned int uVar3;
  unsigned int uVar4;
  unsigned int uVar5;
  unsigned int uVar6;
  unsigned int uVar7;
  unsigned int uVar8;
  unsigned int uVar9;
  unsigned int uVar10;
  unsigned char *puVar11;
  unsigned int uVar12;
  unsigned int local_1134;
  unsigned int local_1130;
  unsigned char local_112c[0x224];
  unsigned char local_f08[0x224];
  unsigned char local_ce4[0x224];
  unsigned char local_ac0[0x224];
  unsigned char local_89c[0x224];
  unsigned char local_678[0x224];
  unsigned char local_454[0x224];
  unsigned char local_230[0x224];
  
  uVar3 = FUN_0045f840(reinterpret_cast<int>(this));
  switch (animEvent) {
  case 1:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  default:
    iVar1 = *reinterpret_cast<int *>(this->m_padae22 + 0x282);
    if (g_soundAvailable != '\0') {
      if (iVar1 != -1) {
        int *obj = *reinterpret_cast<int **>(g_soundChannels + iVar1 * 4);
                (*reinterpret_cast<void (**)()>(*obj + 0xc))();
      }
      if (iVar1 == 0) {
        DAT_00793568 = 0;
      }
    }
    *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = 0xffffffff;
    break;
  case 4:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  case 5:
    if (subType != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar4 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar2 == '\x01') {
LAB_0047ac89:
      local_1134 = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      local_1134 = 8;
      if (cVar2 == '\x01') goto LAB_0047ac89;
    }
    uVar5 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ce4, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar6 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_454,this->m_pad908 + 0x4af4);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar7 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    SpawnPrimaryShot((char)this->m_owner,local_1134,0xe,0,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar6
                 ,uVar5,uVar8,uVar7,uVar3,uVarPB, uVar4, 1);
    ScrubChecksumGuard(local_454);
    ScrubChecksumGuard(local_ce4);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    goto joined_r0x0047aed1;
  case 6:
    if (subType != 7) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar4 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar2 == '\x01') {
LAB_0047adea:
      local_1130 = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      local_1130 = 8;
      if (cVar2 == '\x01') goto LAB_0047adea;
    }
    uVar5 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_89c, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
    uVar6 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_112c,this->m_pad908 + 0x4f3c);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar7 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    SpawnPrimaryShot((char)this->m_owner,local_1130,0xe,1,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar6
                 ,uVar5,uVar8,uVar7,uVar3,uVarPB, uVar4, 1);
    ScrubChecksumGuard(local_112c);
    ScrubChecksumGuard(local_89c);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
joined_r0x0047aed1:
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (((cVar2 == '\0') && (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\0')) &&
       (cVar2 = InitChecksumSeed(), cVar2 == '\0')) {
      uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
      QueueOutgoingPacketField(uVar3);
    }
    break;
  case 8:
    if (subType == 1) {
      QueueOutgoingPacketField(0xffffffff);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x11ab));
      if ((cVar2 == '\x01') || (cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74)), cVar2 == '\x01')) {
        uVar3 = 0;
      }
      else {
        uVar3 = 8;
      }
      uVar4 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_230, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
      uVar5 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_678,this->m_pad908 + 0x4af4);
      uVar10 = (unsigned int)*reinterpret_cast<unsigned short *>(this->m_padae22 + 0x119a);
      uVar6 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar7 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar4 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar4));
      uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
      SpawnItemProjectile((char)this->m_owner,uVar3,uVar5,uVar4,uVar7,uVar6,uVar10);
      ScrubChecksumGuard(local_678);
      ScrubChecksumGuard(local_230);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
        iVar1 = g_clientContext;
        *reinterpret_cast<unsigned int *>(&DAT_005f3768 + g_clientContext) = 5;
        *reinterpret_cast<unsigned int *>(&DAT_005f376c + iVar1) = 0;
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
      else {
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
    }
    break;
  case 10:
    if (subType == 1) {
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar4 = PeekChecksumStateUnderLock(puVar11);
      uVar5 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ac0, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
      uVar6 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_f08,this->m_pad908 + 0x4af4);
      uVar12 = 1;
      uVar7 = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      SpawnSuperShot((char)this->m_owner,8,0xe,
                   *reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar6,uVar5,uVar9,uVar8,uVar3,uVar7,
                   uVar4,uVar12);
      ScrubChecksumGuard(local_f08);
      ScrubChecksumGuard(local_ac0);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
      }
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
  }
  return;
}

/* 0x466fd0 Mobile15_MainAction - mobile TYPE 15's vtable-slot-7 weapon-fire
 * dispatcher, promoted with the Mobile00/Mobile01 mechanical recipe
 * (43a7ee7): SEH stripped, guard scratch as 0x224 buffers, scrub order =
 * SEH unwind order, faithful control flow and argument shapes.  The raw
 * port (src/battle/Mobile15_MainAction.c) remains the linking reference. */
void CMobile::Mobile15_MainAction(int animEvent, int subType)
{
  unsigned int uVarPB;
  int iVar1;
  char cVar2;
  unsigned int uVar3;
  unsigned int uVar4;
  unsigned int uVar5;
  unsigned int uVar6;
  unsigned int uVar7;
  unsigned int uVar8;
  unsigned int uVar9;
  unsigned int uVar10;
  unsigned char *puVar11;
  unsigned int uVar12;
  unsigned int local_1e0c;
  unsigned int local_1e08;
  unsigned char local_1e04[0x224];
  unsigned char local_1be0[0x224];
  unsigned char local_19bc[0x224];
  unsigned char local_1798[0x224];
  unsigned char local_1574[0x224];
  unsigned char local_1350[0x224];
  unsigned char local_112c[0x224];
  unsigned char local_f08[0x224];
  unsigned char local_ce4[0x224];
  unsigned char local_ac0[0x224];
  unsigned char local_89c[0x224];
  unsigned char local_678[0x224];
  unsigned char local_454[0x224];
  unsigned char local_230[0x224];
  
  uVar3 = FUN_0045f840(reinterpret_cast<int>(this));
  switch (animEvent) {
  case 1:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  case 4:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  case 5:
    if (subType != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar2 == '\x01') {
LAB_004670c9:
      local_1e0c = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      local_1e0c = 8;
      if (cVar2 == '\x01') goto LAB_004670c9;
    }
    uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_19bc, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_112c,this->m_pad908 + 0x4af4);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    SpawnPrimaryShot((char)this->m_owner,local_1e0c,0xf,0,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7
                 ,uVar6,uVar9,uVar8,uVar3,uVarPB, uVar5, 1);
    ScrubChecksumGuard(local_112c);
    ScrubChecksumGuard(local_19bc);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    goto joined_r0x00467322;
  case 6:
    if (subType == 2) {
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
      if (cVar2 == '\x01') {
LAB_004673e8:
        local_1e08 = 0;
      }
      else {
        cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
        local_1e08 = 8;
        if (cVar2 == '\x01') goto LAB_004673e8;
      }
      uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_1e04, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
      uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_454,this->m_pad908 + 0x4f3c);
      uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      SpawnPrimaryShot((char)this->m_owner,local_1e08,0xf,1,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,
                   uVar7,uVar6,uVar9,uVar8,uVar3,uVarPB, uVar5, 1);
      ScrubChecksumGuard(local_454);
      ScrubChecksumGuard(local_1e04);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
      break;
    }
    if (subType != 6) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar5 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar2 == '\x01') {
LAB_00467235:
      local_1e08 = 1;
    }
    else {
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      local_1e08 = 9;
      if (cVar2 == '\x01') goto LAB_00467235;
    }
    uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_1574, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
    uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_ce4,this->m_pad908 + 0x4f3c);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    SpawnPrimaryShot((char)this->m_owner,local_1e08,0xf,1,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7
                 ,uVar6,uVar9,uVar8,uVar3,uVarPB, uVar5, 1);
    ScrubChecksumGuard(local_ce4);
    ScrubChecksumGuard(local_1574);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
joined_r0x00467322:
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x11ab));
    if ((cVar2 == '\0') && (cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74)), cVar2 == '\0')) {
LAB_0046735a:
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
      }
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
    break;
  case 8:
    if (subType != 1) break;
    QueueOutgoingPacketField(0xffffffff);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 == '\x01') || (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\x01')) {
      uVar3 = 0;
    }
    else {
      uVar3 = 8;
    }
    uVar5 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_1be0, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar6 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_89c,this->m_pad908 + 0x4af4);
    uVar4 = (unsigned int)*reinterpret_cast<unsigned short *>(this->m_padae22 + 0x119a);
    uVar7 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    SpawnItemProjectile((char)this->m_owner,uVar3,uVar6,uVar5,uVar8,uVar7,uVar4);
    ScrubChecksumGuard(local_89c);
    ScrubChecksumGuard(local_1be0);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    goto LAB_0046735a;
  case 10:
    if (subType == 2) {
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_230, reinterpret_cast<unsigned int>(this->m_pad908 + 0x55a8));
      uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_678,this->m_pad908 + 0x5384);
      uVar12 = 1;
      uVar8 = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      SpawnSuperShot((char)this->m_owner,0,0xf,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,uVar6,
                   uVar10,uVar9,uVar3,uVar8,uVar5,uVar12);
      ScrubChecksumGuard(local_678);
    }
    else {
      if (subType != 6) {
        if (subType == 10) {
          QueueOutgoingPacketField(0xffffffff);
          if (this->m_pad908[0x5c14] == '\x01') {
            puVar11 = &DAT_00796aa0;
          }
          else {
            puVar11 = &DAT_00794e48;
          }
          uVar5 = PeekChecksumStateUnderLock(puVar11);
          uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_1350, reinterpret_cast<unsigned int>(this->m_pad908 + 0x55a8));
          uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_1798,this->m_pad908 + 0x5384);
          uVar12 = 1;
          uVar8 = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
          uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
          uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
          uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
          uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
          SpawnSuperShot((char)this->m_owner,2,0xf,
                       *reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,uVar6,uVar10,uVar9,uVar3,
                       uVar8,uVar5,uVar12);
          ScrubChecksumGuard(local_1798);
          ScrubChecksumGuard(local_1350);
          cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x11ab));
          if (cVar2 == '\0') {
            AcquireSoundChannel(0);
          }
          cVar2 = InitChecksumSeed();
          if (cVar2 == '\0') {
            uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
            QueueOutgoingPacketField(uVar3);
            iVar1 = g_clientContext;
            *reinterpret_cast<unsigned int *>(&DAT_005f3768 + g_clientContext) = 5;
            *reinterpret_cast<unsigned int *>(&DAT_005f376c + iVar1) = 0;
            SetGuardedBool(1,GB_GUARD_UNRECOVERED);
          }
          else {
            SetGuardedBool(1,GB_GUARD_UNRECOVERED);
          }
        }
        goto switchD_0046700f_caseD_2;
      }
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar5 = PeekChecksumStateUnderLock(puVar11);
      uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_ac0, reinterpret_cast<unsigned int>(this->m_pad908 + 0x55a8));
      uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_f08,this->m_pad908 + 0x5384);
      uVar12 = 1;
      uVar8 = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar10 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      SpawnSuperShot((char)this->m_owner,1,0xf,
                   *reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,uVar6,uVar10,uVar9,uVar3,uVar8,
                   uVar5,uVar12);
      ScrubChecksumGuard(local_f08);
    }
    ScrubChecksumGuard(local_ac0);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
  default:
switchD_0046700f_caseD_2:
    iVar1 = *reinterpret_cast<int *>(this->m_padae22 + 0x282);
    if (g_soundAvailable != '\0') {
      if (iVar1 != -1) {
        int *obj = *reinterpret_cast<int **>(g_soundChannels + iVar1 * 4);
                (*reinterpret_cast<void (**)()>(*obj + 0xc))();
      }
      if (iVar1 == 0) {
        DAT_00793568 = 0;
      }
    }
    *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = 0xffffffff;
  }
  return;
}

/* 0x46d070 Mobile13_MainAction - mobile TYPE 13's vtable-slot-7 weapon-fire
 * dispatcher, promoted with the Mobile00/Mobile01 mechanical recipe
 * (43a7ee7): SEH stripped, guard scratch as 0x224 buffers, scrub order =
 * SEH unwind order, faithful control flow and argument shapes.  The raw
 * port (src/battle/Mobile13_MainAction.c) remains the linking reference. */
void CMobile::Mobile13_MainAction(int animEvent, int subType)
{
  unsigned int uVarPB;
  int iVar1;
  char cVar2;
  unsigned int uVar3;
  unsigned int uVar4;
  unsigned int uVar5;
  unsigned int uVar6;
  unsigned int uVar7;
  unsigned int uVar8;
  unsigned int uVar9;
  unsigned int uVar10;
  unsigned char *puVar11;
  unsigned int uVar12;
  unsigned int local_337c;
  unsigned int local_3378;
  unsigned char local_336c[0x224];
  unsigned char local_3148[0x224];
  unsigned char local_2f24[0x224];
  unsigned char local_2d00[0x224];
  unsigned char local_2adc[0x224];
  unsigned char local_28b8[0x224];
  unsigned char local_2694[0x224];
  unsigned char local_2470[0x224];
  unsigned char local_224c[0x224];
  unsigned char local_2028[0x224];
  unsigned char local_1e04[0x224];
  unsigned char local_1be0[0x224];
  unsigned char local_19bc[0x224];
  unsigned char local_1798[0x224];
  unsigned char local_1574[0x224];
  unsigned char local_1350[0x224];
  unsigned char local_112c[0x224];
  unsigned char local_f08[0x224];
  unsigned char local_ce4[0x224];
  unsigned char local_ac0[0x224];
  unsigned char local_89c[0x224];
  unsigned char local_678[0x224];
  unsigned char local_454[0x224];
  unsigned char local_230[0x224];
  
  uVar3 = FUN_0045f840(reinterpret_cast<int>(this));
  switch (animEvent) {
  case 1:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  default:
    iVar1 = *reinterpret_cast<int *>(this->m_padae22 + 0x282);
    if (g_soundAvailable != '\0') {
      if (iVar1 != -1) {
        int *obj = *reinterpret_cast<int **>(g_soundChannels + iVar1 * 4);
                (*reinterpret_cast<void (**)()>(*obj + 0xc))();
      }
      if (iVar1 == 0) {
        DAT_00793568 = 0;
      }
    }
    *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = 0xffffffff;
    break;
  case 4:
    if (*reinterpret_cast<int *>(this->m_padae22 + 0x282) == -1) {
      uVar3 = AcquireSoundChannel(1);
      *reinterpret_cast<unsigned int *>(this->m_padae22 + 0x282) = uVar3;
    }
    break;
  case 5:
    if (subType != 4) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar4 = PeekChecksumStateUnderLock(puVar11);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if (cVar2 == '\x01') {
LAB_0046d169:
      local_337c = 0;
    }
    else {
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
      local_337c = 8;
      if (cVar2 == '\x01') goto LAB_0046d169;
    }
    uVar5 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
    uVar5 = EncodeChecksumDeltaAdd(this->m_pad908 + 0x6f5c,local_ce4,uVar5);
    uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_2f24, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_1e04,this->m_pad908 + 0x4af4);
    uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
    uVar8 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    SpawnPrimaryShot((char)this->m_owner,local_337c,0xd,0,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7
                 ,uVar6,uVar8,uVar5,uVar3,uVarPB, uVar4, 1);
    ScrubChecksumGuard(local_1e04);
    ScrubChecksumGuard(local_2f24);
    ScrubChecksumGuard(local_ce4);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    goto joined_r0x0046d9da;
  case 6:
    switch(subType) {
    case 1:
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar4 = PeekChecksumStateUnderLock(puVar11);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
      if (cVar2 == '\x01') {
LAB_0046d318:
        local_3378 = 0;
      }
      else {
        cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
        local_3378 = 8;
        if (cVar2 == '\x01') goto LAB_0046d318;
      }
      uVar5 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
      uVar5 = EncodeChecksumDeltaAdd(this->m_pad908 + 0x6f5c,local_454,uVar5);
      uVar6 = EncodeChecksumDeltaAdd(this->m_pad908 + 0x4488,local_2694,1);
      uVar7 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_1574, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
      uVar8 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_2adc,this->m_pad908 + 0x4f3c);
      uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      uVar8 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
      SpawnPrimaryShot((char)this->m_owner,local_3378,0xd,1,
                   *reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar8,uVar7,uVar6,uVar5,uVar3,uVarPB, uVar4, 4);
      ScrubChecksumGuard(local_2adc);
      ScrubChecksumGuard(local_1574);
      ScrubChecksumGuard(local_2694);
      ScrubChecksumGuard(local_454);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
    default:
      goto switchD_0046d2bc_caseD_2;
    case 6:
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar4 = PeekChecksumStateUnderLock(puVar11);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
      if (cVar2 == '\x01') {
LAB_0046d4e6:
        local_3378 = 1;
      }
      else {
        cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
        local_3378 = 9;
        if (cVar2 == '\x01') goto LAB_0046d4e6;
      }
      uVar5 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
      uVar5 = EncodeChecksumDeltaSub(this->m_pad908 + 0x6f5c,local_89c,uVar5);
      uVar6 = EncodeChecksumDeltaAdd(this->m_pad908 + 0x4488,local_336c,1);
      uVar7 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_112c, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
      uVar8 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_224c,this->m_pad908 + 0x4f3c);
      uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      uVar8 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
      SpawnPrimaryShot((char)this->m_owner,local_3378,0xd,1,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,
                   uVar8,uVar7,uVar6,uVar5,uVar3,uVarPB, uVar4, 4);
      ScrubChecksumGuard(local_224c);
      ScrubChecksumGuard(local_112c);
      ScrubChecksumGuard(local_336c);
      ScrubChecksumGuard(local_89c);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
      goto switchD_0046d2bc_caseD_2;
    case 0xb:
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar4 = PeekChecksumStateUnderLock(puVar11);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
      if (cVar2 == '\x01') {
LAB_0046d6ae:
        local_3378 = 2;
      }
      else {
        cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
        local_3378 = 10;
        if (cVar2 == '\x01') goto LAB_0046d6ae;
      }
      uVar5 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
      uVar5 = EncodeChecksumDeltaAdd(this->m_pad908 + 0x6f5c,local_28b8,uVar5);
      uVar6 = EncodeChecksumDeltaSub(this->m_pad908 + 0x4488,local_2d00,1);
      uVar7 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_3148, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
      uVar8 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_19bc,this->m_pad908 + 0x4f3c);
      uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      uVar8 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
      SpawnPrimaryShot((char)this->m_owner,local_3378,0xd,1,*reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,
                   uVar8,uVar7,uVar6,uVar5,uVar3,uVarPB, uVar4, 4);
      ScrubChecksumGuard(local_19bc);
      ScrubChecksumGuard(local_3148);
      ScrubChecksumGuard(local_2d00);
      ScrubChecksumGuard(local_28b8);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
      goto switchD_0046d2bc_caseD_2;
    case 0x10:
      QueueOutgoingPacketField(0xffffffff);
      if (this->m_pad908[0x5c14] == '\x01') {
        puVar11 = &DAT_00796aa0;
      }
      else {
        puVar11 = &DAT_00794e48;
      }
      uVar4 = PeekChecksumStateUnderLock(puVar11);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
      if (cVar2 == '\x01') {
LAB_0046d87c:
        local_3378 = 3;
      }
      else {
        cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f));
        local_3378 = 0xb;
        if (cVar2 == '\x01') goto LAB_0046d87c;
      }
      uVar5 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
      uVar5 = EncodeChecksumDeltaSub(this->m_pad908 + 0x6f5c,local_1798,uVar5);
      uVar6 = EncodeChecksumDeltaSub(this->m_pad908 + 0x4488,local_1be0,1);
      uVar7 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_2028, reinterpret_cast<unsigned int>(this->m_pad908 + 0x5160));
      uVar8 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_2470,this->m_pad908 + 0x4f3c);
      uVarPB = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
      uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
      uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
      uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
      uVar8 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar8));
      SpawnPrimaryShot((char)this->m_owner,local_3378,0xd,1,
                   *reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar8,uVar7,uVar6,uVar5,uVar3,uVarPB, uVar4, 4);
      ScrubChecksumGuard(local_2470);
      ScrubChecksumGuard(local_2028);
      ScrubChecksumGuard(local_1be0);
      ScrubChecksumGuard(local_1798);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    }
joined_r0x0046d9da:
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
    if ((cVar2 == '\0') && (cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119f)), cVar2 == '\0')) {
LAB_0046db83:
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
      }
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
    break;
  case 8:
    if (subType == 4) {
      QueueOutgoingPacketField(0xffffffff);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x11ab));
      if ((cVar2 == '\x01') || (cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74)), cVar2 == '\x01')) {
        uVar3 = 0;
      }
      else {
        uVar3 = 8;
      }
      uVar4 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_230, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
      uVar5 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_678,this->m_pad908 + 0x4af4);
      uVar10 = (unsigned int)*reinterpret_cast<unsigned short *>(this->m_padae22 + 0x119a);
      uVar6 = PeekChecksumStateUnderLock(this->m_pad908 + 0x6f5c);
      uVar7 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
      uVar4 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar4));
      uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
      SpawnItemProjectile((char)this->m_owner,uVar3,uVar5,uVar4,uVar7,uVar6,uVar10);
      ScrubChecksumGuard(local_678);
      ScrubChecksumGuard(local_230);
      cVar2 = PeekPacketChecksumBool((unsigned char *)(this->m_padae22 + 0x119c));
      if (cVar2 == '\0') {
        AcquireSoundChannel(0);
      }
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        uVar3 = PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField(uVar3);
        iVar1 = g_clientContext;
        *reinterpret_cast<unsigned int *>(&DAT_005f3768 + g_clientContext) = 5;
        *reinterpret_cast<unsigned int *>(&DAT_005f376c + iVar1) = 0;
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
      else {
        SetGuardedBool(1,GB_GUARD_UNRECOVERED);
      }
    }
    break;
  case 10:
    if (subType != 4) break;
    QueueOutgoingPacketField(0xffffffff);
    if (this->m_pad908[0x5c14] == '\x01') {
      puVar11 = &DAT_00796aa0;
    }
    else {
      puVar11 = &DAT_00794e48;
    }
    uVar4 = PeekChecksumStateUnderLock(puVar11);
    uVar5 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
    uVar5 = EncodeChecksumDeltaAdd(this->m_pad908 + 0x6f5c,local_ac0,uVar5);
    uVar6 = EncodeChecksumPairDiff(this->m_pad908 + 0x228, local_f08, reinterpret_cast<unsigned int>(this->m_pad908 + 0x4d18));
    uVar7 = EncodeChecksumPairSum(this->m_pad908 + 0x4,local_1350,this->m_pad908 + 0x4af4);
    uVar12 = 1;
    uVar8 = PeekPacketChecksumBool((unsigned char *)this + 0xbfcd);
    uVar5 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar5));
    uVar9 = PeekChecksumStateUnderLock(this->m_pad908 + 0x4488);
    uVar6 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar6));
    uVar7 = PeekChecksumStateUnderLock(reinterpret_cast<void *>(uVar7));
    SpawnSuperShot((char)this->m_owner,8,0xd,
                 *reinterpret_cast<int *>(this->m_padae22 + 0xa) != 0,uVar7,uVar6,uVar9,uVar5,uVar3,uVar8,uVar4
                 ,uVar12);
    ScrubChecksumGuard(local_1350);
    ScrubChecksumGuard(local_f08);
    ScrubChecksumGuard(local_ac0);
    cVar2 = PeekPacketChecksumBool((unsigned char *)(g_clientContext + 0x6a7f74));
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
    goto LAB_0046db83;
  }
switchD_0046d2bc_caseD_2:
  return;
}
