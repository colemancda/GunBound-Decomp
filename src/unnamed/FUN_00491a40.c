/* FUN_00491a40 - 0x00491a40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 3 argless PeekPacketChecksumState() calls (3 C : 3 orig,
 * goto-free zip) - all off the live-in ECX object: +0xf54 twice, then +0x1178.
 */
#include "ghidra_types.h"


int __fastcall FUN_00491a40(int param_1)

{
  char extraout_AL;
  int iVar1;
  undefined4 extraout_EAX;
  uint3 uVar3;
  int iVar2;
  undefined4 extraout_EAX_00;
  uint3 extraout_var;
  uint3 extraout_var_00;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = (uint3)((uint)extraout_EAX >> 8);
  if (-1 < iVar1) {
    iVar1 = *(int *)(&g_nCameraBoundX + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = (uint3)((uint)extraout_EAX_00 >> 8);
    if (iVar2 < iVar1) {
      iVar1 = *(int *)(&g_nCameraBoundY + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = extraout_var;
      if (iVar2 < iVar1) {
        PacketChecksumLessThan(param_1 + 0x1178,0xfffffc18);
        uVar3 = extraout_var_00;
        if (extraout_AL == '\0') {
          return CONCAT31(extraout_var_00,1);
        }
      }
    }
  }
  return (uint)uVar3 << 8;
}

