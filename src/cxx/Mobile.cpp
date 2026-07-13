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
void TreeLowerBound(void *scratch);
int  PeekPacketChecksumState(void);
int  PeekChecksumStateUnderLock(void *cell);
unsigned int EncodeChecksumDeltaDiv(void *cell, void *out, int div);
unsigned int EncodeChecksumPairDiff(void *cell, void *out, unsigned int a);
int  EncodeChecksumDeltaAdd(void *cell, void *out, int delta);
int  FindGroundHeightAtColumn(void);   /* 0x4e4340 - column arg arrives in a register (dropped) */
extern CRITICAL_SECTION DAT_005a9068;  /* the guard family's shared lock, defined in ValueGuard.cpp */
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
