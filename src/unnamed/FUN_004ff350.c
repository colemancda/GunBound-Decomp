/* FUN_004ff350 - 0x004ff350 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_004ff350(SOCKET param_1,u_long param_2,undefined4 param_3)

{
  u_long uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  uVar1 = param_2;
  puStack_8 = &LAB_005377f8;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  local_4 = 0;
  param_2 = 1;
  ioctlsocket(param_1,-0x7ffb9982,&param_2);
  iVar2 = WSAAsyncSelect(param_1,*(HWND *)(uVar1 + 0x20),0x478,0x33);
  if (iVar2 == -1) {
    FUN_00501010();
    *unaff_FS_OFFSET = local_c;
    return 0;
  }
  param_3 = 6000;
  setsockopt(param_1,0xffff,0x1002,(char *)&param_3,4);
  setsockopt(param_1,0xffff,0x1001,(char *)&param_3,4);
  uVar3 = FUN_00500fa0(*(undefined4 *)(uVar1 + 8),0);
  if (*(undefined4 **)(uVar1 + 8) == (undefined4 *)0x0) {
    *(undefined4 *)(uVar1 + 4) = uVar3;
  }
  else {
    **(undefined4 **)(uVar1 + 8) = uVar3;
  }
  *(undefined4 *)(uVar1 + 8) = uVar3;
  FUN_00501010();
  *unaff_FS_OFFSET = local_c;
  return uVar3;
}

