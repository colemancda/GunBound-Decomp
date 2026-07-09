/* FUN_004f3ee0 - 0x004f3ee0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004f3ee0(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  byte local_5;
  int local_4;
  
  pbVar4 = *(byte **)(DAT_00792190 + 0x7c);
  iVar3 = 0;
  local_4 = 0;
  local_5 = 0xff;
  if (DAT_00793611 != '\x01') {
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x1b,1);
  }
  DAT_00793611 = 1;
  if (pbVar4 != (byte *)0x0) {
    do {
      if (((*(int *)(pbVar4 + 0x70) != iVar3) || (*(int *)(pbVar4 + 0x74) != local_4)) ||
         (*pbVar4 != local_5)) {
        if (local_5 != 0xff) {
          if (iVar3 == 0) {
            (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
          }
          else {
            (**(code **)(*g_pD3DDevice7 + 0x8c))
                      (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar3 + 0x94) + 0x110));
          }
          uVar1 = (uint)local_5;
          if (g_currentBlendMode != uVar1) {
            _DAT_00792194 = uVar1;
            g_currentBlendMode = uVar1;
            if ((uVar1 == 0) || (uVar1 == 1)) {
              (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
              uVar7 = 6;
            }
            else {
              if (uVar1 != 2) goto LAB_004f3fcd;
              (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
              uVar7 = 2;
            }
            (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,uVar7);
          }
LAB_004f3fcd:
          if (g_spriteVertexCount != 0) {
            g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
            (**(code **)(*g_pD3DDevice7 + 100))
                      (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
            g_spriteVertexCount = 0;
          }
        }
        iVar3 = *(int *)(pbVar4 + 0x70);
        local_4 = *(int *)(pbVar4 + 0x74);
        local_5 = *pbVar4;
        _DAT_00792198 = iVar3;
      }
      if (g_spriteVertexCount == 0x2000) {
        g_frameTriangleCounter = g_frameTriangleCounter + 0x2000;
        (**(code **)(*g_pD3DDevice7 + 100))(g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,0x6000,1);
        g_spriteVertexCount = 0;
      }
      puVar6 = &g_spriteVertexBuffer + g_spriteVertexCount * 0x1b;
      pbVar5 = pbVar4;
      for (iVar2 = 0x1b; pbVar5 = pbVar5 + 4, iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *(undefined4 *)pbVar5;
        puVar6 = puVar6 + 1;
      }
      pbVar4 = *(byte **)(pbVar4 + 0x7c);
      g_spriteVertexCount = g_spriteVertexCount + 1;
    } while (pbVar4 != (byte *)0x0);
    if (iVar3 != 0) {
      (**(code **)(*g_pD3DDevice7 + 0x8c))
                (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar3 + 0x94) + 0x110));
      goto LAB_004f40b2;
    }
  }
  (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
LAB_004f40b2:
  FUN_004f01d0();
  if (g_spriteVertexCount != 0) {
    g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  return;
}

