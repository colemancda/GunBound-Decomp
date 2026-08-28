/* FUN_004f2f90 - 0x004f2f90 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): EAX is the active-object layer REGISTRY
 * (the sentinel-list container at &DAT_006a7f88 + g_clientContext whose
 * class-id ring this walks: [regEax+4] is the ring head, next at +0x1c,
 * key at +4) and param_2 - declared all along but passed by nobody -
 * is the CLASS ID sought: 0x186a1 (100001, the mobile id base) at all
 * ported sites but one, which asks for 0x186a6. param_1 is a PHANTOM:
 * ECX's first touch is the write at 0x4f2f90. Bare ret, no stack args.
 * Returns the layer node, whose +0x10 chain the callers then sweep with
 * the +0x15 ring-terminator convention FindActiveObjectByIndex
 * documents.
 */
#include "ghidra_types.h"


int __fastcall FUN_004f2f90(undefined4 param_1,uint param_2,int regEax)

{
  int iVar1;
  uint uVar2;
  int in_EAX = regEax;
  
  iVar1 = *(int *)(*(int *)(in_EAX + 4) + 0x1c);
  uVar2 = *(uint *)(iVar1 + 4);
  while( true ) {
    if (param_2 < uVar2) {
      return 0;
    }
    if (uVar2 == param_2) break;
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar2 = *(uint *)(iVar1 + 4);
  }
  return iVar1;
}

