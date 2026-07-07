/* FUN_00522330 - 0x00522330 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_00522330(int param_1)

{
  BOOL BVar1;
  LPCSTR pCVar2;
  HANDLE hHandle;
  DWORD DVar3;
  undefined4 uVar4;
  _SECURITY_ATTRIBUTES *lpMutexAttributes;
  _SECURITY_ATTRIBUTES local_20;
  undefined1 local_14 [20];
  
  local_20.lpSecurityDescriptor = local_14;
  local_20.nLength = 0xc;
  local_20.bInheritHandle = 0;
  lpMutexAttributes = (LPSECURITY_ATTRIBUTES)0x0;
  BVar1 = InitializeSecurityDescriptor(local_14,1);
  if (BVar1 != 0) {
    BVar1 = SetSecurityDescriptorDacl(local_14,1,(PACL)0x0,0);
    if (BVar1 != 0) {
      lpMutexAttributes = &local_20;
    }
  }
  pCVar2 = (LPCSTR)FUN_005218c0(&DAT_0056a63c);
  hHandle = CreateMutexA(lpMutexAttributes,0,pCVar2);
  if (hHandle == (HANDLE)0x0) {
    pCVar2 = (LPCSTR)FUN_005218c0(&DAT_0056a630);
    hHandle = CreateMutexA(lpMutexAttributes,0,pCVar2);
    if (hHandle == (HANDLE)0x0) {
      GetLastError();
      DVar3 = GetLastError();
      uVar4 = FUN_005218c0(&DAT_0056a60c,DVar3);
      FUN_00521a90(param_1 + 0x24,uVar4);
      return 0;
    }
  }
  DVar3 = GetLastError();
  if (DVar3 == 0xb7) {
    CloseHandle(hHandle);
    return 0;
  }
  DVar3 = WaitForSingleObject(hHandle,0);
  if (DVar3 != 0) {
    CloseHandle(hHandle);
    return 0;
  }
  return 1;
}

