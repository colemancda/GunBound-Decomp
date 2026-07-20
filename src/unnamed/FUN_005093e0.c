/* FUN_005093e0 - 0x005093e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
/* DROPPED-REGISTER FIX (2026-07-20): the object walked here arrives in EAX -
 * `piVar2 = *(int **)(in_EAX + 4)` is the first thing it does, and Ghidra
 * emitted EAX as an uninitialised `in_EAX`, so it faulted reading 0x4. The
 * sole call site loads it explicitly: orig 0x42931d `mov eax, 0xe53c40`
 * (= &g_uiPanelManager) immediately before `call 0x5093e0` at 0x42932c.
 * Promoted to an explicit parameter. */
#include "ghidra_types.h"


void FUN_005093e0(int panelManager)

{
  int iVar1;
  int in_EAX = panelManager;
  int *piVar2;
  
  piVar2 = *(int **)(in_EAX + 4);
  if (piVar2 != (int *)0x0) {
    while( true ) {
      iVar1 = piVar2[2];
      piVar2 = (int *)*piVar2;
      if ((*(int *)(iVar1 + 0x20) == 0) && (*(int *)(iVar1 + 0x24) == 20000)) break;
      if (piVar2 == (int *)0x0) {
        return;
      }
    }
    *(undefined1 *)(iVar1 + 0x1d) = 1;
  }
  return;
}

