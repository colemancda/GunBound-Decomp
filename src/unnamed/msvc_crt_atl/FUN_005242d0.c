/* FUN_005242d0 - 0x005242d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __fastcall FUN_005242d0(undefined4 *param_1)

{
  BOOL BVar1;
  HANDLE pvVar2;
  undefined4 *local_4;
  
  if (DAT_0056adf0 == -1) {
    return 0;
  }
  local_4 = param_1;
  BVar1 = SetStdHandle(0xfffffff6,(HANDLE)*param_1);
  if (BVar1 == 0) {
    return 0;
  }
  BVar1 = SetStdHandle(0xfffffff5,(HANDLE)param_1[1]);
  if (BVar1 == 0) {
    return 0;
  }
  CloseHandle((HANDLE)param_1[5]);
  CloseHandle((HANDLE)param_1[2]);
  DAT_005b1630 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,1,0,(LPCSTR)0x0);
  if (DAT_005b1630 == (HANDLE)0x0) {
    return 0;
  }
  pvVar2 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,FUN_00524400,param_1,0,(LPDWORD)&local_4);
  param_1[6] = pvVar2;
  return -(uint)(pvVar2 != (HANDLE)0x0) & (uint)local_4;
}

