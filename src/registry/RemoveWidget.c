/* RemoveWidget - 0x00405fb0 in the original binary.
 *
 * THE NAME IS BETTER THAN I FIRST CLAIMED - CORRECTION (2026-08-20).  An
 * earlier revision of this header, and commit 2755ae1, asserted that this
 * function "has nothing to do with widgets" and that the name names the wrong
 * subsystem.  THAT WAS WRONG, and scanning the call sites is what showed it:
 * EDI - the container - is the immediate 0xe9be90 at 132 of 133 sites, and
 * DAT_00e9be90 is the ACTIVE-OBJECT (widget) REGISTRY, the same container
 * SweepActiveObjectRegistry, DrawActiveObjectRegistry and
 * TickActiveObjectRegistry walk.  So this really does operate on widgets.
 *
 * What survives from that analysis is the part about the ALGORITHM, which is
 * genuinely shared: the lookup is a generic two-level keyed container walk, and
 * FindSpriteFrame runs the identical code over a different container.  I
 * inferred the subsystem from the algorithm, which does not follow - the same
 * container shape is reused for sprites and for widgets alike.
 *
 * Disassembled at 0x405fb0 it is
 * byte-for-byte the SAME two-level keyed lookup as FindSpriteFrame
 * (0x4f30c0): outer list from container+4 then +0x1c, walked by +0x1c and
 * keyed at +4; inner list from the matched node's +0x10, walked by +0x10 and
 * keyed at +8; `xor eax,eax` on either miss.
 *
 *     mov eax,[edi+4] / mov eax,[eax+0x1c]   container -> outer list
 *     cmp ecx,edx                            outer key is EDX
 *     mov eax,[eax+0x10] / cmp ecx,esi       inner key is ESI
 *
 * so the register arguments are EDI=container, EDX=outerKey, ESI=innerKey -
 * the same three FindSpriteFrame takes, differing only in that the container
 * arrives in EDI rather than EAX. And as there, ECX is a PHANTOM: `mov
 * ecx,[eax+4]` at 0x405fb6 writes it before anything reads it, so Ghidra's
 * `param_1` is not an argument at all. `param_2` (EDX) is real.
 *
 * What it does beyond the lookup is the tail, and it is where the "Remove"
 * came from: having found the record it clears the container's two cached
 * slots if either points at it -
 *     cmp eax,[edi+8]  / jne / mov [edi+8],0
 *     cmp eax,[edi+0xc] / ...
 * i.e. look up an entry and evict it from the registry's two cached slots.
 * "Remove" is therefore a fair description of the tail, over the right
 * subsystem - so the name stands, and no rename is called for.
 *
 * CALL SITES SCANNED (133 direct calls, cached in
 * tools/removewidget_regs.json).  The arguments are almost entirely literal,
 * so this should sweep cleanly once the source-to-site pairing is settled:
 *     EDI  0xe9be90 at 132/133 - &DAT_00e9be90, the widget registry
 *     EDX  `xor edx,edx` at 131/133 - the outer key is 0
 *     ESI  an immediate at ~124/133, spread over 37 distinct values
 *          (0x32..0x3c and friends - widget ids)
 * ECX is a phantom and must NOT be given a value.  The ESI spread means the
 * pairing does matter here, unlike the uniform cases: see
 * tools/count_call_args.py and the block/witness techniques used for the
 * render chain.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified.
 * See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall RemoveWidget(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint unaff_ESI;
  int unaff_EDI;
  
  iVar1 = *(int *)(*(int *)(unaff_EDI + 4) + 0x1c);
  uVar2 = *(uint *)(iVar1 + 4);
  while (uVar2 <= param_2) {
    if (uVar2 == param_2) {
      puVar3 = *(undefined4 **)(iVar1 + 0x10);
      uVar2 = puVar3[2];
      if (uVar2 <= unaff_ESI) goto LAB_00405fd5;
      break;
    }
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar2 = *(uint *)(iVar1 + 4);
  }
  goto LAB_00405fe1;
  while( true ) {
    puVar3 = (undefined4 *)puVar3[4];
    uVar2 = puVar3[2];
    if (unaff_ESI < uVar2) break;
LAB_00405fd5:
    if (uVar2 == unaff_ESI) goto LAB_00405fe3;
  }
LAB_00405fe1:
  puVar3 = (undefined4 *)0x0;
LAB_00405fe3:
  if (puVar3 == *(undefined4 **)(unaff_EDI + 8)) {
    *(undefined4 *)(unaff_EDI + 8) = 0;
  }
  if (puVar3 == *(undefined4 **)(unaff_EDI + 0xc)) {
    *(undefined4 *)(unaff_EDI + 0xc) = 0;
  }
  if (puVar3 != (undefined4 *)0x0) {
    *(undefined4 *)(puVar3[3] + 0x10) = puVar3[4];
    *(undefined4 *)(puVar3[4] + 0xc) = puVar3[3];
    (**(code **)*puVar3)(1);
  }
  return;
}

