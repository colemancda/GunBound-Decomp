/* FUN_004cee30 - 0x004cee30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 8 argless PeekPacketChecksumState() calls.  All are fixed
 * g_clientContext globals and the C sites zip 1:1 with the original in
 * address order (0x4cee55..0x4cf004, no reordering): the turn-counter pair
 * +0xeba98 / +0xebcbc that BeginNewTurn seeds and bumps, plus one read of
 * the turn-limit cell +0x473a0.
 */
#include "ghidra_types.h"


void FUN_004cee30(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  char *pcVar4;
  char acStack_80 [128];
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState((void *)(g_clientContext + 0xebcbc));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0043c620();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar1 + -1 < 0) {
    iVar1 = 0;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = iVar1 + -1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x473a0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar1 % iVar2 != 0) goto LAB_004cefef;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState((void *)(g_clientContext + 0xebcbc));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar1 == 6) {
    *(undefined4 *)(g_clientContext + 0xf0374) = 0xffffffff;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState((void *)(g_clientContext + 0xebcbc));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar1 == 4) {
    piVar3 = (int *)FindSpriteFrame();
    if ((piVar3 != (int *)0x0) &&
       (iVar1 = piVar3[0xf], piVar3[0xf] = iVar1 + 0x28, 1000 < iVar1 + 0x28)) {
      piVar3[0xf] = 1000;
    }
    pcVar4 = s_active_00551e58;
LAB_004cefa6:
    (**(code **)(*piVar3 + 4))(pcVar4);
  }
  else {
    piVar3 = (int *)FindSpriteFrame();
    if (piVar3 != (int *)0x0) {
      pcVar4 = s_normal_00552230;
      goto LAB_004cefa6;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState((void *)(g_clientContext + 0xebcbc));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  _sprintf(acStack_80,s__dmoon_xes_0055674c,iVar1 + 1);
  AcquireSoundChannel(0);
LAB_004cefef:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState((void *)(g_clientContext + 0xebcbc));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar1 == 5) {
    FUN_0043c6a0();
  }
  *(undefined4 *)(param_1 + 0x10b8) = 0;
  AdvanceTurnQueue();
  return;
}

