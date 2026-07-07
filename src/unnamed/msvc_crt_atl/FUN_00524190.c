/* FUN_00524190 - 0x00524190 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_00524190(undefined4 *param_1)

{
  PHANDLE ppvVar1;
  HANDLE pvVar2;
  BOOL BVar3;
  HANDLE pvVar4;
  HANDLE pvVar5;
  LPHANDLE ppvVar6;
  DWORD DVar7;
  DWORD DVar8;
  _SECURITY_ATTRIBUTES local_c;
  
  if (DAT_0056adf0 != -1) {
    return 0;
  }
  local_c.nLength = 0xc;
  local_c.bInheritHandle = 1;
  local_c.lpSecurityDescriptor = (LPVOID)0x0;
  pvVar2 = GetStdHandle(0xfffffff5);
  param_1[1] = pvVar2;
  ppvVar1 = (PHANDLE)(param_1 + 4);
  BVar3 = CreatePipe(ppvVar1,(PHANDLE)(param_1 + 5),&local_c,0);
  if (BVar3 == 0) {
    return 0;
  }
  BVar3 = SetStdHandle(0xfffffff5,(HANDLE)param_1[5]);
  if (BVar3 == 0) {
    return 0;
  }
  DVar8 = 2;
  BVar3 = 0;
  DVar7 = 0;
  ppvVar6 = (LPHANDLE)&DAT_0056adf4;
  pvVar4 = GetCurrentProcess();
  pvVar2 = *ppvVar1;
  pvVar5 = GetCurrentProcess();
  BVar3 = DuplicateHandle(pvVar5,pvVar2,pvVar4,ppvVar6,DVar7,BVar3,DVar8);
  if (BVar3 == 0) {
    return 0;
  }
  CloseHandle(*ppvVar1);
  pvVar2 = GetStdHandle(0xfffffff6);
  *param_1 = pvVar2;
  ppvVar1 = (PHANDLE)(param_1 + 3);
  BVar3 = CreatePipe((PHANDLE)(param_1 + 2),ppvVar1,&local_c,0);
  if (BVar3 == 0) {
    return 0;
  }
  BVar3 = SetStdHandle(0xfffffff6,(HANDLE)param_1[2]);
  if (BVar3 == 0) {
    return 0;
  }
  DVar8 = 2;
  BVar3 = 0;
  DVar7 = 0;
  ppvVar6 = (LPHANDLE)&DAT_0056adf0;
  pvVar4 = GetCurrentProcess();
  pvVar2 = *ppvVar1;
  pvVar5 = GetCurrentProcess();
  BVar3 = DuplicateHandle(pvVar5,pvVar2,pvVar4,ppvVar6,DVar7,BVar3,DVar8);
  if (BVar3 == 0) {
    return 0;
  }
  CloseHandle(*ppvVar1);
  return 1;
}

