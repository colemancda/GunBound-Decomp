/* RemoveWidget - 0x00405fb0 in the original binary.
 *
 * THE NAME IS A GUESS AND IT IS MISLEADING (analysed 2026-08-20, not renamed).
 * This has nothing to do with widgets. Disassembled at 0x405fb0 it is
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
 * i.e. look up an entry and evict it from the cache. So it is a
 * find-and-evict over the same resource container FindSpriteFrame reads, and
 * a name like FindAndEvictResourceEntry would fit; the current one implies
 * both the wrong subsystem and the wrong operation.
 *
 * Not renamed here only because a rename touches its 13 caller files and all
 * 131 of its call sites currently pass ZERO arguments - the register recovery
 * should land first so the two changes are not tangled together.
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

