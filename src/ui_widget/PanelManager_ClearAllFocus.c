/* PanelManager_ClearAllFocus - 0x0050efa0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * VERIFIED (2026-10-30), the slot-6 tail call: 0x50efe5-0x50efeb is
 * `mov ecx,[esp+0x10]` (this) / `mov edx,[ecx]` / `call [edx+0x18]` with
 * nothing pushed. Slot 6 of the manager's vtable 0x557cfc is 0x507ed0, a
 * thunk (`push ecx / mov [esp],ecx / add esp,4 / jmp 0x507e30`) into a
 * body that reads only globals, and the port's table (globals_sized.c)
 * points it at the argless TextEntry_RestoreChatInput. So the argless
 * dispatch is ABI-correct as it stands and is left alone.
 *
 * FIXED (2026-10-30): the child loop at 0x50efce-0x50efd4 is
 * `mov eax,[esi+0xc] / mov ecx,[eax+edi*4] / call 0x50e790`, ESI = the
 * panel. So Widget_ClearPressedRecursive takes child[i] in ECX. The port
 * called it with nothing.
 */
#include "ghidra_types.h"


void PanelManager_ClearAllFocus(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  
  puVar1 = (undefined4 *)param_1[1];
  DAT_00793664 = 0;
  while( true ) {
    do {
      if (puVar1 == (undefined4 *)0x0) {
        (**(code **)(*param_1 + 0x18))();
        return;
      }
      iVar2 = puVar1[2];
      puVar1 = (undefined4 *)*puVar1;
      uVar3 = 0;
      *(undefined1 *)(iVar2 + 4) = 0;
    } while (*(int *)(iVar2 + 0x10) == 0);
    if (*(int *)(iVar2 + 0x10) == 0) break;
    do {
      Widget_ClearPressedRecursive(*(int *)(*(int *)(iVar2 + 0xc) + uVar3 * 4));
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(iVar2 + 0x10));
  }
                    /* WARNING: Subroutine does not return */
  ThrowCxxException(0x80070057);
}

