/* DarkenTerrainScorchRow - 0x004e4bc0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
*
 * DROPPED REGISTER RECOVERED AND ARGUMENTS RE-SLOTTED (2026-08-27).  This is
 * `DarkenTerrainScorchRow(terrainCtx, xStart, width, row)`: it darkens one
 * horizontal span of a scorch sprite row.  `ret 4` gives ONE stack argument
 * against three declared parameters, so param_1 is ECX (the terrain context,
 * `cmp edi,[ecx+0x1c]`), param_2 is EDX (`mov ebx,edx`) and only param_3 is
 * pushed -- while in_EAX (`mov edi,eax`, the very first read) is the row.
 *
 * All five call sites, all in CarveTerrainCrater, were MIS-SLOTTED rather
 * than merely short: each passed a single argument that landed in param_1
 * when it is really the pushed param_3.  The value they passed -- the `* 2`
 * the source already writes -- is `lea ecx,[eax+eax]` immediately before the
 * push, so it was the width all along, being read as a terrain pointer.
 */
#include "ghidra_types.h"


void __fastcall DarkenTerrainScorchRow(int param_1,uint param_2,uint param_3,int regEax)

{
  ushort uVar1;
  int in_EAX = regEax;
  int iVar2;
  ushort *puVar3;
  ushort *puVar4;
  uint uVar5;
  uint uVar6;
  int local_8;
  
  if ((-1 < in_EAX) && (in_EAX < *(int *)(param_1 + 0x1c))) {
    if ((int)param_2 < 0) {
      param_3 = param_3 + param_2;
      param_2 = 0;
    }
    if (*(int *)(param_1 + 0x18) < (int)(param_3 + param_2)) {
      param_3 = *(int *)(param_1 + 0x18) - param_2;
    }
    if ((0 < (int)param_3) && (*(char *)(in_EAX + 0x51 + param_1) != '\x01')) {
      *(undefined1 *)(in_EAX + 0x51 + param_1) = 1;
      iVar2 = FindSpriteFrame((int)&g_spriteRegistry,0xea60,0);
      if (iVar2 != 0) {
        puVar3 = *(ushort **)(iVar2 + 0x34);
        if (0 < in_EAX) {
          do {
            in_EAX = in_EAX + -1;
            puVar3 = puVar3 + *puVar3;
          } while (in_EAX != 0);
        }
        uVar1 = puVar3[1];
        puVar3 = puVar3 + 2;
        local_8 = 0;
        if (uVar1 != 0) {
          do {
            uVar6 = (uint)puVar3[1];
            uVar5 = (uint)*puVar3;
            iVar2 = uVar5 + uVar6;
            if ((int)param_2 <= iVar2) {
              if ((int)(param_2 + param_3) < (int)uVar5) {
                return;
              }
              if (uVar5 == param_2) {
                puVar4 = puVar3 + 2;
                if ((int)param_3 <= (int)uVar6) {
                  uVar6 = param_3;
                }
              }
              else if ((int)param_2 < (int)uVar5) {
                uVar5 = param_3 + (param_2 - uVar5);
                puVar4 = puVar3 + 2;
                if ((int)uVar5 <= (int)uVar6) {
                  uVar6 = uVar5;
                }
              }
              else {
                puVar4 = puVar3 + (param_2 - uVar5) + 2;
                uVar6 = param_3;
                if (iVar2 <= (int)(param_2 + param_3)) {
                  uVar6 = iVar2 - param_2;
                }
              }
              if (0 < (int)uVar6) {
                do {
                  uVar6 = uVar6 - 1;
                  *puVar4 = (ushort)((*puVar4 & 0xe79c) >> 2);
                  puVar4 = puVar4 + 1;
                } while (uVar6 != 0);
              }
              uVar6 = (uint)puVar3[1];
            }
            local_8 = local_8 + 1;
            puVar3 = puVar3 + uVar6 + 2;
          } while (local_8 < (int)(uint)uVar1);
        }
      }
    }
  }
  return;
}

