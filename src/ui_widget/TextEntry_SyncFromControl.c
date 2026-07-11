/* TextEntry_SyncFromControl - 0x00507030 in the original binary.
 *
 * Text-entry widget update: syncs the backing Win32 EDIT control's text into the widget buffer at +0x38 via GetWindowTextA, then broadcasts draw to children. See docs/widgets.md. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall TextEntry_SyncFromControl(int param_1)

{
  int iVar1;
  uint uVar2;
  
  if (*(char *)(param_1 + 4) != '\0') {
    if (*(char *)(DAT_007934e4 + 8) != '\0') {
      iVar1 = GetWindowTextA(*(HWND *)(DAT_007934e4 + 4),(LPSTR)(param_1 + 0x38),0x80);
      if (iVar1 != 0) goto LAB_00507061;
    }
    *(LPSTR)(param_1 + 0x38) = '\0';
  }
LAB_00507061:
  uVar2 = 0;
  if (*(int *)(param_1 + 0x10) != 0) {
    if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    do {
      (**(code **)(**(int **)(*(int *)(param_1 + 0xc) + uVar2 * 4) + 0x20))();
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(param_1 + 0x10));
  }
  return;
}

