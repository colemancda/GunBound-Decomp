/* PanelManager_GrowNodePool - 0x0050f390 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-14): `unaff_ESI` is the same manager pointer already
 * fixed on PanelManager_Register/PanelManager_PrependNode - confirmed
 * via objdump at PrependNode's real entry (0x50f350-0x50f353): `mov
 * esi,eax` (manager) immediately before `call 0x50f390` (this function),
 * with no other ESI write in between - i.e. it's simply inherited, not a
 * fresh value. This function's only caller is PrependNode.
 */
#include "ghidra_types.h"


void PanelManager_GrowNodePool(void *manager)

{
  undefined4 *puVar1;
  int iVar2;
  int unaff_ESI;

  unaff_ESI = (int)manager;
  if (*(int *)(unaff_ESI + 0x10) == 0) {
    puVar1 = _malloc(*(int *)(unaff_ESI + 0x14) * 0xc + 4);
    if (puVar1 == (undefined4 *)0x0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    *puVar1 = *(undefined4 *)(unaff_ESI + 0xc);
    *(undefined4 **)(unaff_ESI + 0xc) = puVar1;
    iVar2 = *(int *)(unaff_ESI + 0x14);
    puVar1 = puVar1 + iVar2 * 3 + -2;
    if (-1 < iVar2 + -1) {
      do {
        *puVar1 = *(undefined4 *)(unaff_ESI + 0x10);
        *(undefined4 **)(unaff_ESI + 0x10) = puVar1;
        puVar1 = puVar1 + -3;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  return;
}

