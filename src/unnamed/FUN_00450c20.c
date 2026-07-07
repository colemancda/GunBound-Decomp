/* FUN_00450c20 - 0x00450c20 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00450c20(void)

{
  char cVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int unaff_EDI;
  undefined4 uVar6;
  
  if (DAT_00793611 != '\x01') {
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x1b,1);
  }
  DAT_00793611 = 1;
  iVar4 = FindTextureCacheEntryByName(s_CrashTexture_00555b80);
  if (iVar4 == 0) {
    iVar4 = *g_pD3DDevice7;
    uVar6 = 0;
  }
  else {
    uVar6 = *(undefined4 *)(*(int *)(iVar4 + 0x94) + 0x110);
    iVar4 = *g_pD3DDevice7;
  }
  (**(code **)(iVar4 + 0x8c))(g_pD3DDevice7,0,uVar6);
  iVar4 = *(int *)(*(int *)(unaff_EDI + 4) + 0x1c);
  iVar5 = g_spriteVertexCount;
  if (iVar4 != *(int *)(unaff_EDI + 4)) {
    do {
      uVar2 = *(uint *)(iVar4 + 4);
      if (uVar2 < 190000) {
        iVar4 = *(int *)(iVar4 + 0x1c);
      }
      else {
        if (200000 < uVar2) {
          return;
        }
        switch(uVar2) {
        case 190000:
        case 0x2e633:
        case 0x2e634:
        case 0x2e644:
          if (DAT_00793614 != 2) {
            DAT_00793614 = 2;
            _DAT_00792194 = 2;
            (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
            uVar6 = 2;
LAB_00450d24:
            (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,uVar6);
            iVar5 = g_spriteVertexCount;
          }
          break;
        case 0x2e631:
        case 0x2e632:
        case 0x2e635:
          if (DAT_00793614 != 1) {
            DAT_00793614 = 1;
            _DAT_00792194 = 1;
            (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
            uVar6 = 6;
            goto LAB_00450d24;
          }
        }
        piVar3 = *(int **)(iVar4 + 0x10);
        cVar1 = *(char *)((int)piVar3 + 0x15);
        while (cVar1 == '\0') {
          (**(code **)(*piVar3 + 0xc))();
          piVar3 = (int *)piVar3[4];
          iVar5 = g_spriteVertexCount;
          cVar1 = *(char *)((int)piVar3 + 0x15);
        }
        iVar4 = *(int *)(iVar4 + 0x1c);
        if (iVar5 != 0) {
          DAT_0079365c = DAT_0079365c + iVar5;
          (**(code **)(*g_pD3DDevice7 + 100))
                    (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,iVar5 * 3,1);
          iVar5 = 0;
          g_spriteVertexCount = 0;
        }
      }
    } while (iVar4 != *(int *)(unaff_EDI + 4));
  }
  return;
}

