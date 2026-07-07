/* FUN_004fe6f0 - 0x004fe6f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


LRESULT FUN_004fe6f0(HWND param_1,UINT param_2,WPARAM param_3,uint param_4)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  LONG LVar3;
  SOCKET SVar4;
  LRESULT LVar5;
  sockaddr local_10;
  
  LVar3 = GetWindowLongA(param_1,-0x15);
  if (param_2 != 0x478) {
    LVar5 = DefWindowProcA(param_1,param_2,param_3,param_4);
    return LVar5;
  }
  puVar2 = *(undefined4 **)(LVar3 + 4);
  do {
    puVar1 = puVar2;
    if (puVar1 == (undefined4 *)0x0) goto LAB_004fe749;
    puVar2 = (undefined4 *)*puVar1;
  } while (puVar1[2] != param_3);
  if (puVar1 == (undefined4 *)0x0) {
LAB_004fe749:
    if ((param_4 & 0xffff) != 8) {
      return -5;
    }
  }
  switch(param_4 & 0xffff) {
  case 1:
    FUN_004ff4a0(param_4 >> 0x10);
    return 0;
  case 2:
    FUN_004ff550(LVar3);
    return 0;
  case 8:
    if (*(SOCKET *)(LVar3 + 0x1c) == param_3) {
      param_4 = 0x10;
      SVar4 = accept(*(SOCKET *)(LVar3 + 0x1c),&local_10,(int *)&param_4);
      if (SVar4 != 0xffffffff) {
        FUN_004ff690(&local_10);
      }
    }
    break;
  case 0x10:
    FUN_004ff640();
    return 0;
  case 0x20:
    FUN_004fe6a0();
    return 0;
  }
  return 0;
}

