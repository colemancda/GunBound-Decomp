/* FUN_0050f000 - 0x0050f000 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ESI RECOVERED (2026-08-25): an immediate at both sites, and they differ --
 * 0x232a from WriteReplayEventRecord, 3 from State09_ReadyRoom_OnCommand --
 * so the two had to be paired rather than filled uniformly.  The pairing is
 * free here: the two binary sites are in two different named functions, one
 * source call each.
 */
#include "ghidra_types.h"


int __fastcall FUN_0050f000(undefined4 param_1,int param_2,int regEax,int regEsi)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = *(undefined4 **)(regEax + 4);
  do {
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    iVar2 = puVar1[2];
    puVar1 = (undefined4 *)*puVar1;
  } while ((*(int *)(iVar2 + 0x20) != param_2) || (*(int *)(iVar2 + 0x24) != regEsi));
  return iVar2;
}

