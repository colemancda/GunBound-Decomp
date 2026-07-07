/* FUN_004fd230 - 0x004fd230 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004fd230(undefined4 *param_1)

{
  SOCKET s;
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_00537a24;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_LAB_005575c8;
  param_1[1] = &PTR_LAB_005575b8;
  param_1[0xb] = &PTR_LAB_005575ac;
  param_1[0xbd] = &PTR_FUN_005575a8;
  local_4 = 6;
  if (param_1[0x69d] == 0) goto LAB_004fd2b5;
  s = *(SOCKET *)(param_1[0x69d] + 8);
  if (s == 0xffffffff) {
LAB_004fd2a0:
    FUN_004fe6a0();
  }
  else {
    iVar1 = shutdown(s,2);
    if (iVar1 == -1) goto LAB_004fd2a0;
  }
  FUN_004fddd0(3000);
LAB_004fd2b5:
  if ((void *)param_1[0x69e] != (void *)0x0) {
    _free((void *)param_1[0x69e]);
  }
  if (param_1[0x6ae] != 0) {
    KillTimer((HWND)param_1[0x6ad],param_1[0x6ae]);
  }
  if ((HWND)param_1[0x6ad] != (HWND)0x0) {
    DestroyWindow((HWND)param_1[0x6ad]);
  }
  if ((void *)param_1[0x808] != (void *)0x0) {
    _free((void *)param_1[0x808]);
    param_1[0x808] = 0;
  }
  if ((void *)param_1[0x767] != (void *)0x0) {
    _free((void *)param_1[0x767]);
    param_1[0x767] = 0;
  }
  FUN_004fefe0();
  FUN_004fee20();
  if ((void *)param_1[0x6a9] != (void *)0x0) {
    _free((void *)param_1[0x6a9]);
  }
  param_1[0x6a9] = 0;
  param_1[0x6aa] = 0;
  param_1[0x6ab] = 0;
  FUN_004fdfd0();
  param_1[1] = &PTR_LAB_00557598;
  if ((HWND)param_1[9] != (HWND)0x0) {
    DestroyWindow((HWND)param_1[9]);
  }
  if (param_1[8] != 0xffffffff) {
    closesocket(param_1[8]);
    param_1[8] = 0xffffffff;
  }
  FUN_004ff6d0();
  *unaff_FS_OFFSET = local_c;
  return;
}

