/* FUN_00471b40 - 0x00471b40 in the original binary.
 *
 * PROTOTYPE PROMOTED (2026-08-18): this sprite-cache blitter takes its
 * sprite KEY in EAX (Ghidra's in_EAX; the walk key for the DAT_00ea0e1c
 * cache list) and a second sort key in EDX; the old __fastcall(param_1)
 * ECX slot was never used.  ZERO existing C callers - its only callers in
 * the original are the effect-class Draw vtable slots Ghidra never carved
 * (now ported: src/battle/Draw*Effect.c, see src/cxx/Effects.h) - so the
 * promotion needs no caller sweep.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00471b40(uint spriteKey,uint sortKey,int rowBase,int stride)

{
  int iVar1;
    int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined4 *puVar11;
  
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar10 = *(uint *)(iVar2 + 4);
  if (uVar10 <= sortKey) {
    while (uVar10 != sortKey) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar10 = *(uint *)(iVar2 + 4);
      if (sortKey < uVar10) {
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar10 = *(uint *)(iVar2 + 8);
    if (uVar10 <= spriteKey) {
      while (uVar10 != spriteKey) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar10 = *(uint *)(iVar2 + 8);
        if (spriteKey < uVar10) {
          return;
        }
      }
      iVar4 = *(int *)(iVar2 + 0x20);
      iVar5 = *(int *)(iVar2 + 0x28) + 0x40;
      iVar1 = iVar4 + iVar5;
      uVar10 = *(int *)(iVar2 + 0x2c) + 0x40;
      if ((0 < iVar1) && (iVar5 < 0x80)) {
        uVar7 = -uVar10;
        puVar3 = (undefined4 *)(*(int *)(iVar2 + 0x34) + iVar4 * (((int)uVar7 < 0) - 1 & uVar7) * 2)
        ;
        iVar8 = *(int *)(iVar2 + 0x24) - (((int)uVar7 < 0) - 1 & uVar7);
        uVar10 = ((int)uVar10 < 0) - 1 & uVar10;
        if (0x7f < (int)(iVar8 + uVar10)) {
          iVar8 = 0x7f - uVar10;
        }
        if (iVar5 < 0) {
          puVar3 = (undefined4 *)((int)puVar3 + iVar5 * -2);
          iVar5 = 0;
          iVar4 = iVar1;
        }
        if (0x7f < iVar4 + iVar5) {
          iVar4 = 0x7f - iVar5;
        }
        if (0 < iVar8) {
          puVar6 = (undefined4 *)(uVar10 * stride + rowBase + iVar5 * 2);
          rowBase = iVar8;
          do {
            uVar7 = (iVar4 * 2 < 0) - 1 & iVar4 * 2;
            puVar9 = puVar3;
            puVar11 = puVar6;
            for (uVar10 = uVar7 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
              *puVar11 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar11 = puVar11 + 1;
            }
            for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
              *(undefined1 *)puVar11 = *(undefined1 *)puVar9;
              puVar9 = (undefined4 *)((int)puVar9 + 1);
              puVar11 = (undefined4 *)((int)puVar11 + 1);
            }
            puVar3 = (undefined4 *)((int)puVar3 + *(int *)(iVar2 + 0x20) * 2);
            puVar6 = (undefined4 *)((int)puVar6 + stride);
            rowBase = rowBase + -1;
          } while (rowBase != 0);
        }
      }
    }
  }
  return;
}

