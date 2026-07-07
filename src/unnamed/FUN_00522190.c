/* FUN_00522190 - 0x00522190 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_00522190(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  DWORD DVar3;
  
  if (*(char *)(param_1 + 0x18) == '\0') {
    return 1;
  }
  iVar1 = param_1 + 0x24;
  uVar2 = FUN_005218c0(&DAT_0056a5e4);
  FUN_00521a90(iVar1,uVar2);
  (**(code **)(param_1 + 0x1148))(*(undefined4 *)(param_1 + 0x10c4),param_1 + 0x10f0);
  *(undefined1 *)(param_1 + 0x18) = 0;
  if (*(HANDLE *)(param_1 + 0x14) != (HANDLE)0x0) {
    SetEvent(*(HANDLE *)(param_1 + 0x14));
  }
  DVar3 = WaitForSingleObject(*(HANDLE *)(param_1 + 0x10ec),2000);
  if (DVar3 == 0x102) {
    uVar2 = FUN_005218c0(&DAT_0056a5cc);
    FUN_00521a90(iVar1,uVar2);
    TerminateThread(*(HANDLE *)(param_1 + 0x10ec),0);
  }
  CloseHandle(*(HANDLE *)(param_1 + 0x10ec));
  if (*(HMODULE *)(param_1 + 0x10e8) != (HMODULE)0x0) {
    FreeLibrary(*(HMODULE *)(param_1 + 0x10e8));
  }
  *(undefined4 *)(param_1 + 0x1144) = 0;
  *(undefined4 *)(param_1 + 0x1148) = 0;
  uVar2 = FUN_005218c0(&DAT_0056a5b8);
  FUN_00521a90(iVar1,uVar2);
  return 1;
}

