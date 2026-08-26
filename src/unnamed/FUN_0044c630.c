/* FUN_0044c630 - 0x0044c630 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25), and the ECX slot filled with it: all three sites
 * pass two client-context sub-objects, `mov ecx,[0x5b3484]` then a lea and an
 * add off the same base, so nothing here needs a caller local.  The three
 * pairs are (+0x44e30, +0x44e50) in State07_AvatarStore_ProcessPacket and
 * (+0x44e50, +0x44e30) then (+0x44e50, +0x44e40) in FUN_0044bf00.
 *
 * The two FUN_0044bf00 sites are adjacent source lines inside one
 * straight-line run with no branch between them, which is the one case where
 * VA order and source order are the same thing.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_0044c630(int param_1,int regEax)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = *(undefined4 *)(param_1 + 4);
  FUN_0044c7b0();
  iVar2 = *(int *)(regEax + 4);
  if (iVar2 == 0) {
    return uVar1;
  }
  do {
    FUN_0044c740();
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return uVar1;
}

