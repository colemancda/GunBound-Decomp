/* FUN_00501510 - 0x00501510 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ESI RECOVERED (2026-08-25): FUN_00500fa0's entry is `push esi; mov esi,eax`
 * and the call follows immediately, so ESI is that caller's own incoming EAX.
 * NOTE: FUN_00500fa0's EAX is itself an open backlog item; when it becomes a
 * parameter the argument at that call site is renamed with it.
 */
#include "ghidra_types.h"


void FUN_00501510(int regEsi)

{
  undefined4 *puVar1;
  int iVar2;
  
  if (*(int *)(regEsi + 0x10) == 0) {
    puVar1 = _malloc(*(int *)(regEsi + 0x14) * 0x38 + 4);
    if (puVar1 == (undefined4 *)0x0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    *puVar1 = *(undefined4 *)(regEsi + 0xc);
    *(undefined4 **)(regEsi + 0xc) = puVar1;
    iVar2 = *(int *)(regEsi + 0x14);
    puVar1 = puVar1 + iVar2 * 0xe + -0xd;
    if (-1 < iVar2 + -1) {
      do {
        *puVar1 = *(undefined4 *)(regEsi + 0x10);
        *(undefined4 **)(regEsi + 0x10) = puVar1;
        puVar1 = puVar1 + -0xe;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  return;
}

