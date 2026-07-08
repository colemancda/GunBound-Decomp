/* FUN_00491a40 - 0x00491a40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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
  iVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = (uint3)((uint)extraout_EAX >> 8);
  if (-1 < iVar1) {
    iVar1 = *(int *)(&DAT_006a7720 + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = (uint3)((uint)extraout_EAX_00 >> 8);
    if (iVar2 < iVar1) {
      iVar1 = *(int *)(&DAT_006a7724 + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = extraout_var;
      if (iVar2 < iVar1) {
        FUN_0040b330(param_1 + 0x1178,0xfffffc18);
        uVar3 = extraout_var_00;
        if (extraout_AL == '\0') {
          return CONCAT31(extraout_var_00,1);
        }
      }
    }
  }
  return (uint)uVar3 << 8;
}

