/* ExplodeMine - 0x00497ad0 in the original binary.
 *
 * NAMED 2026-08-19 (was a FUN_ name).  slot 8, the post-detonation effect of the Mine class's
 * vtable.  The class was already fixed by a slot UNIQUE to that vtable (see
 * the InitMine / DestroyMine notes); this slot's role comes from the
 * CProjectile slot map in src/cxx/Projectile.h, and the name was only
 * assigned because this function too appears in exactly one vtable - a slot
 * shared between vtables would say nothing about which class it belongs to.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 23 argless PeekPacketChecksumState() calls (peek status
 * "clean", 23 C : 23 orig).  Cells from tools/guard_cell_resolve.py over
 * 0x497ad0-0x497fba; no gotos, straight-line, so the sites order-zip.
 *
 * Structural twin of ExplodeSuperMine (same crater block, same five
 * EncodeChecksumDeltaSub rounds), and the two cross-check each other.
 * Five cells are chained returns the decompile discarded: each DeltaSub
 * (0x40a6e0, at 0x497b38/0x497d2f/0x497dc3/0x497e85/0x497f47) returns
 * its dest cell in EAX and the next Peek re-reads it - captured in a new
 * uVar6.
 *
 * The `[esp+0x14]`-based cells are param_1: the PROLOGUE stores it at
 * 0x497af5 as `mov [esp+8],ebx`, three callee-saved pushes above the
 * settled esp, so the operand text is not the frame slot it names.  That
 * reading is confirmed independently by the two Encode sites the
 * 2026-07-15 sweep already fixed from a direct register trace - it read
 * `lea edi,[ebx+0xf54]` / `[ebx+0x1178]` and wrote param_1+0xf54 /
 * param_1+0x1178, which is exactly what [esp+0x14]+0xf54/+0x1178
 * resolves to here.
 */
#include "ghidra_types.h"


void __fastcall ExplodeMine(int param_1)

{
  int iCraterX;
  int iCraterY;
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar6;
  int iVar5;
  undefined4 local_474 [2];
  undefined4 local_46c;
  undefined4 local_468;
  undefined4 local_464;
  undefined4 local_460;
  undefined4 local_45c;
  undefined4 local_458;
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053ef67) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  if (*(char *)(param_1 + 0x14) != '\x01') {
    *(undefined1 *)(param_1 + 0x14) = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = EncodeChecksumDeltaSub(param_1 + 0x264,local_454,uVar3);
    local_4 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_458 = PeekPacketChecksumState((void *)(param_1 + 0x6ac));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_468 = PeekPacketChecksumState((void *)(param_1 + 0x488));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_460 = PeekPacketChecksumState((void *)(param_1 + 0x2f74));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_464 = PeekPacketChecksumState((void *)(param_1 + 0x2d50));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_46c = PeekPacketChecksumState((void *)(param_1 + 0x2b2c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_45c = PeekPacketChecksumState((void *)(param_1 + 0x2908));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_474[0] = PeekPacketChecksumState((void *)(param_1 + 0x26e4));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x24c0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iCraterY = PeekPacketChecksumState((void *)uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iCraterX = PeekPacketChecksumState((void *)(param_1 + 0x40));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    ApplyCraterExcavation(uVar3,local_474[0],local_45c,local_46c,local_464,local_460,local_468,local_458,
                 (int)(&DAT_006a7708 + g_clientContext),(int)iCraterX,(int)iCraterY);
    local_4 = 0xffffffff;
    if ((*(int *)(local_454 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&DAT_0079376c);
      TreeLowerBound(local_474);
    }
    RebuildTerrainColumnCache(&DAT_006a7708 + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x40));
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x497cfc
     * (`lea edi,[ebx + 0xf54]`, ebx = this file's own param_1): cell is
     * param_1+0xf54. `param_1` is plain `int`, so byte offsets are
     * natural. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(param_1 + 0xf54, uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = EncodeChecksumDeltaSub(param_1 + 0x264,local_454,uVar3);
    local_4 = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)uVar6);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x497d56
     * (`lea edi,[ebx + 0x1178]`, ebx = param_1): cell is param_1+0x1178.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(param_1 + 0x1178, uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if ((*(int *)(local_454 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&DAT_0079376c);
      TreeLowerBound(local_474);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = EncodeChecksumDeltaSub(param_1 + 0x264,local_454,uVar3);
    local_4 = 2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState((void *)(param_1 + 0x40));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00450eb0(uVar4,uVar3,param_1,0,0,0);
    local_4 = 0xffffffff;
    if ((*(int *)(local_454 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&DAT_0079376c);
      TreeLowerBound(local_474);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = EncodeChecksumDeltaSub(param_1 + 0x264,local_454,uVar3);
    local_4 = 3;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState((void *)(param_1 + 0x40));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436ac0(uVar4,uVar3);
    local_4 = 0xffffffff;
    if ((*(int *)(local_454 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&DAT_0079376c);
      TreeLowerBound(local_474);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = EncodeChecksumDeltaSub(param_1 + 0x264,local_230,uVar3);
    local_4 = 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState((void *)(param_1 + 0x40));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    SpawnFlameEffect(*(uint *)(param_1 + 8) & 0xf,uVar4,uVar3,*(undefined4 *)(param_1 + 0x3894),
                 param_1 + 0x3898);
    local_4 = 0xffffffff;
    if ((*(int *)(local_230 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_230 + 0x14),&DAT_0079376c);
      TreeLowerBound(local_474);
    }
    iVar1 = g_clientContext;
    cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
    if (cVar2 != '\x01') {
      iVar5 = *(int *)(&DAT_006a7750 + iVar1);
      if (iVar5 < 0x10) {
        iVar5 = 0xf;
      }
      *(int *)(&DAT_006a7750 + iVar1) = iVar5;
      iVar5 = *(int *)(&DAT_006a7754 + iVar1);
      if (iVar5 < 0xb) {
        iVar5 = 10;
      }
      *(int *)(&DAT_006a7754 + iVar1) = iVar5;
    }
    cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
    if (cVar2 == '\0') {
      AcquireSoundChannel(0);
    }
  }
  return;
}

