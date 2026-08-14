/* FUN_0046ca60 - 0x0046ca60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 5 argless PeekPacketChecksumState() calls (5 C : 5 orig,
 * goto-free zip).  All five hang off the live-in ECX object (param_1):
 * +0x33c8 read twice around the SpawnShot_Type13 call this function
 * exists to make, plus the +0x35ec/+0x1178/+0xf54 argument cells.
 */
#include "ghidra_types.h"


void __fastcall FUN_0046ca60(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState((void *)(param_1 + 0x33c8));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = (0x2d - iVar1) * 2;
  iVar6 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)(param_1 + 0x35ec));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    SpawnShot_Type13(iVar6,uVar4,uVar3,iVar1,uVar2,5,param_1);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x33c8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = iVar1 + iVar5;
    iVar6 = iVar6 + 1;
  } while (iVar6 < 5);
  return;
}

