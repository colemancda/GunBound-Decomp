/* FUN_0040c6f0 - 0x0040c6f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


LRESULT FUN_0040c6f0(HWND param_1,uint param_2,WPARAM param_3,LPARAM param_4)

{
  char cVar1;
  HIMC pHVar2;
  LONG LVar3;
  char *pcVar4;
  BOOL BVar5;
  LRESULT LVar6;
  int iVar7;
  undefined4 *puVar8;
  DWORD DVar9;
  DWORD dwBufLen;
  char local_88;
  undefined4 local_87;
  
  local_88 = '\0';
  puVar8 = &local_87;
  for (iVar7 = 0x1f; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  *(undefined2 *)puVar8 = 0;
  dwBufLen = 0x7f;
  *(undefined1 *)((int)puVar8 + 2) = 0;
  pcVar4 = &local_88;
  DVar9 = 8;
  pHVar2 = ImmGetContext(param_1);
  LVar3 = ImmGetCompositionStringA(pHVar2,DVar9,pcVar4,dwBufLen);
  if (LVar3 == -1) {
    DAT_007934c4 = false;
  }
  else {
    pcVar4 = &local_88;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    DAT_007934c4 = pcVar4 != (char *)&local_87;
  }
  pHVar2 = ImmGetContext(param_1);
  BVar5 = ImmGetOpenStatus(pHVar2);
  DAT_007934c5 = BVar5 != 0;
  if (param_2 < 0x106) {
    if (param_2 < 0x104) {
      if (param_2 == 0x7b) {
        return 0;
      }
      if ((param_2 < 0x100) || (0x101 < param_2)) goto LAB_0040c7ad;
    }
    SendMessageA((HWND)*DAT_005b1c48,param_2,param_3,param_4);
  }
LAB_0040c7ad:
  if (*(char *)(DAT_005b1c48 + 2) == '\0') {
    switch(param_2) {
    case 0x100:
    case 0x102:
    case 0x104:
    case 0x105:
      return 1;
    }
  }
  else {
    switch(param_2 - 0x100) {
    case 0:
      if ((((param_3 == 9) || (param_3 == 0x26)) || (param_3 == 0x28)) || (param_3 == 0xd)) {
        return 1;
      }
      break;
    case 2:
    case 4:
    case 5:
      if (param_3 == 0xd) {
        return 1;
      }
      if (param_3 == 9) {
        return 1;
      }
    default:
      LVar6 = CallWindowProcA((WNDPROC)DAT_005b1c48[3],(HWND)DAT_005b1c48[1],param_2,param_3,param_4
                             );
      return LVar6;
    }
  }
  LVar6 = CallWindowProcA((WNDPROC)DAT_005b1c48[3],(HWND)DAT_005b1c48[1],param_2,param_3,param_4);
  return LVar6;
}

