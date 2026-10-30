/* FUN_00502750 - 0x00502750 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00502750(int param_1,undefined4 regEax)

{
  int iVar1;
  int local_4;
  
  iVar1 = *(int *)(param_1 + 4);
  local_4 = param_1;
  if ((iVar1 != 0) &&
     ((uint)((*(int *)(param_1 + 8) - iVar1) / 0x12) <
      (uint)((*(int *)(param_1 + 0xc) - iVar1) / 0x12))) {
    iVar1 = *(int *)(param_1 + 8);
    /* Count 1 in ECX (`mov ecx,1` at 0x50279f), destination = the old
     * _Mylast in EAX (`mov eax,esi` at 0x5027a4), element in EBX, which
     * holds the incoming EAX (`mov ebx,eax` at 0x50275b); the pushed
     * word is local_4 and is never read.  The port passed only param_1. */
    Vector_UninitFillN_12(1,0,param_1,(undefined4 *)iVar1,(undefined4 *)regEax);
    *(int *)(param_1 + 8) = iVar1 + 0x12;
    return;
  }
  FUN_005029b0(&local_4,*(undefined4 *)(param_1 + 8),regEax);
  return;
}

