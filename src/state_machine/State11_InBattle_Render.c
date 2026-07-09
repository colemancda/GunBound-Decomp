/* State11_InBattle_Render - 0x004c3020 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void State11_InBattle_Render(void)

{
  byte bVar1;
  byte bVar2;
  float fVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  int iVar11;
  int iVar12;
  undefined4 *puVar13;
  int *piVar14;
  byte *pbVar15;
  uint uVar16;
  undefined4 *unaff_FS_OFFSET;
  bool bVar17;
  bool bVar18;
  uint uStack_a38;
  char *pcStack_a34;
  int *piStack_a30;
  int *piStack_a2c;
  char *pcStack_a28;
  int *piStack_a24;
  undefined4 uStack_a20;
  char *pcStack_a1c;
  int *piStack_a18;
  uint uStack_a14;
  char *pcStack_a10;
  int *piStack_a0c;
  uint uStack_a08;
  char *pcStack_a04;
  uint uStack_9f0;
  uint uStack_9e4;
  int iStack_9e0;
  int iStack_9dc;
  int *piStack_9d0;
  int iStack_9cc;
  int *piStack_9c4;
  int iStack_9c0;
  int iStack_9bc;
  int iStack_9b8;
  int iStack_9b4;
  int iStack_9ac;
  int iStack_9a8;
  int iStack_99c;
  int iStack_990;
  uint uStack_98c;
  int iStack_988;
  int iStack_984;
  int iStack_980;
  int iStack_97c;
  int iStack_974;
  int iStack_970;
  int iStack_968;
  int iStack_964;
  int iStack_95c;
  int iVar19;
  int iStack_944;
  uint uStack_93c;
  int iStack_938;
  char acStack_794 [32];
  undefined1 auStack_774 [20];
  int iStack_760;
  undefined1 auStack_550 [20];
  int iStack_53c;
  undefined1 auStack_32c [20];
  int iStack_318;
  undefined4 uStack_114;
  undefined4 uStack_100;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005391af;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  if (DAT_00793611 != '\x01') {
    (**(code **)(*g_pD3DDevice7 + 0x50))();
  }
  DAT_00793611 = 1;
  if (*(int *)(&DAT_005f3768 + g_clientContext) != 0) {
    if (DAT_00793614 != 1) {
      DAT_00793614 = 1;
      _DAT_00792194 = 1;
      (**(code **)(*g_pD3DDevice7 + 0x50))();
      (**(code **)(*g_pD3DDevice7 + 0x50))();
    }
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
    FUN_004edb50();
  }
  iVar6 = g_clientContext;
  iVar5 = FindTextureCacheEntryByName();
  if (DAT_00793614 != 1) {
    DAT_00793614 = 1;
    _DAT_00792194 = 1;
    (**(code **)(*g_pD3DDevice7 + 0x50))();
    (**(code **)(*g_pD3DDevice7 + 0x50))();
    iVar6 = g_clientContext;
  }
  if (iVar5 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    uStack_93c = 0;
    piVar8 = (int *)(iVar6 + 0x20b18);
    do {
      if (*(char *)(iVar6 + 0x20b0c + uStack_93c) == '\x01') {
        if ((((DAT_00793530 <= (piVar8[-1] - *(int *)(&DAT_006a7710 + iVar6)) + 0x1ba) &&
             ((piVar8[-1] - *(int *)(&DAT_006a7710 + iVar6)) + 0x166 <= DAT_0056df30)) &&
            (DAT_00793534 <= (*piVar8 - *(int *)(&DAT_006a7714 + iVar6)) + 0x154)) &&
           ((*piVar8 - *(int *)(&DAT_006a7714 + iVar6)) + 0x100 <= DAT_0056df34)) {
          *(undefined4 *)(iVar5 + 0x88) = 0x3ea80000;
          *(float *)(iVar5 + 0x80) = (float)(uStack_93c % 3) * _DAT_00558064;
          *(float *)(iVar5 + 0x84) = (float)(uStack_93c / 3) * _DAT_00558064;
          FUN_004ecc70();
          iVar6 = g_clientContext;
        }
      }
      uStack_93c = uStack_93c + 1;
      piVar8 = piVar8 + 4;
    } while ((int)uStack_93c < 8);
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))();
    g_spriteVertexCount = 0;
  }
  iVar6 = FindTextureCacheEntryByName();
  if (DAT_00793614 != 1) {
    DAT_00793614 = 1;
    _DAT_00792194 = 1;
    (**(code **)(*g_pD3DDevice7 + 0x50))();
    (**(code **)(*g_pD3DDevice7 + 0x50))();
  }
  if (iVar6 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    iVar19 = 0xc;
    iVar5 = g_clientContext;
    do {
      if (((iVar19 == 0) || (iVar19 == 4)) || ((iVar19 == 6 || (iVar19 == 7)))) {
        uVar16 = 0;
        iStack_938 = 0;
        do {
          if (*(char *)(iVar5 + 0x20b0c + uVar16) == '\0') {
            iVar7 = *(int *)(iVar5 + 0x1ff0c + (uVar16 + iVar19 * 8) * 0x18);
            iVar12 = *(int *)(iVar5 + 0x1ff10 + (uVar16 + iVar19 * 8) * 0x18);
          }
          else {
            iVar7 = *(int *)(iStack_938 + 0x20b14 + iVar5);
            iVar12 = *(int *)(iStack_938 + 0x20b18 + iVar5);
          }
          iVar7 = iVar7 + (400 - *(int *)(&DAT_006a7710 + iVar5));
          iVar12 = iVar12 + (0x12a - *(int *)(&DAT_006a7714 + iVar5));
          if (((DAT_00793530 <= iVar7 + 0x40) && (iVar7 + -0x3e <= DAT_0056df30)) &&
             ((DAT_00793534 <= iVar12 + 0x10 && (iVar12 + -0x70 <= DAT_0056df34)))) {
            fVar3 = (float)(uVar16 & 1) * _DAT_00557fb8;
            *(undefined4 *)(iVar6 + 0x88) = 0x3f000000;
            *(float *)(iVar6 + 0x80) = fVar3;
            *(float *)(iVar6 + 0x84) = (float)(uVar16 >> 1) * _DAT_00557fb8;
            if (*(char *)(iVar5 + 0x20b0c + uVar16) == '\0') {
              iVar7 = GetPlayerRecordBySlot();
              iVar5 = g_clientContext;
              if (((iVar7 != 0) && (*(int *)(iVar7 + 0x24) != 0xe)) &&
                 (*(char *)(g_clientContext + iVar19 * 8 + 0x1fe8c + uVar16) != '\0')) {
                BuildScaledSpriteQuad();
              }
            }
            else {
              FUN_004ecc70();
            }
          }
          iStack_938 = iStack_938 + 0x10;
          uVar16 = uVar16 + 1;
        } while (iStack_938 < 0x40);
      }
      iVar19 = iVar19 + -1;
    } while (-1 < iVar19);
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))();
    g_spriteVertexCount = 0;
  }
  iVar6 = FindTextureCacheEntryByName();
  if (iVar6 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    iStack_944 = 0xc;
    iVar5 = g_clientContext;
    do {
      if (((iStack_944 == 0) || (iStack_944 == 4)) || ((iStack_944 == 6 || (iStack_944 == 7)))) {
        uVar16 = 0;
        iStack_95c = 0;
        do {
          if (*(char *)(iVar5 + 0x20b10 + uVar16) == '\0') {
            iVar19 = *(int *)(iVar5 + 0x1ff6c + (uVar16 + iStack_944 * 8) * 0x18);
            iVar7 = *(int *)(iVar5 + 0x1ff70 + (uVar16 + iStack_944 * 8) * 0x18);
          }
          else {
            iVar19 = *(int *)(iStack_95c + 0x20b54 + iVar5);
            iVar7 = *(int *)(iStack_95c + 0x20b58 + iVar5);
          }
          iVar19 = iVar19 + (400 - *(int *)(&DAT_006a7710 + iVar5));
          iVar7 = iVar7 + (0x12a - *(int *)(&DAT_006a7714 + iVar5));
          if (((DAT_00793530 <= iVar19 + 0x40) && (iVar19 + -0x40 <= DAT_0056df30)) &&
             ((DAT_00793534 <= iVar7 + 0x10 && (iVar7 + -0x70 <= DAT_0056df34)))) {
            fVar3 = (float)(uVar16 & 1) * _DAT_00557fb8;
            *(undefined4 *)(iVar6 + 0x88) = 0x3f000000;
            *(float *)(iVar6 + 0x80) = fVar3;
            *(float *)(iVar6 + 0x84) = (float)(uVar16 >> 1) * _DAT_00557fb8;
            if (*(char *)(iVar5 + 0x20b10 + uVar16) == '\0') {
              iVar19 = GetPlayerRecordBySlot();
              iVar5 = g_clientContext;
              if (((iVar19 != 0) && (*(int *)(iVar19 + 0x24) != 0xe)) &&
                 (*(char *)(g_clientContext + iStack_944 * 8 + 0x1fe90 + uVar16) != '\0')) {
                BuildScaledSpriteQuad();
              }
            }
            else {
              FUN_004ecc70();
            }
          }
          iStack_95c = iStack_95c + 0x10;
          uVar16 = uVar16 + 1;
        } while (iStack_95c < 0x40);
      }
      iStack_944 = iStack_944 + -1;
    } while (-1 < iStack_944);
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))();
    g_spriteVertexCount = 0;
  }
  iVar6 = FindTextureCacheEntryByName();
  if (DAT_00793614 != 1) {
    DAT_00793614 = 1;
    _DAT_00792194 = 1;
    (**(code **)(*g_pD3DDevice7 + 0x50))();
    (**(code **)(*g_pD3DDevice7 + 0x50))();
  }
  if (iVar6 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    iStack_964 = g_clientContext + 0x1feec;
    iStack_968 = 0xc;
    bVar17 = false;
    do {
      if (((bVar17) || (iStack_968 == 4)) || ((iStack_968 == 6 || (iStack_968 == 7)))) {
        iVar5 = 0;
        do {
          piVar8 = (int *)(g_clientContext + 0x1fe6c);
          uVar16 = 0;
          do {
            if ((*piVar8 == iVar5) && (*(char *)(iStack_964 + uVar16) != '\0')) {
              iVar19 = uVar16 + iStack_968 * 8;
              iVar7 = *(int *)(g_clientContext + 0x1ff0c + iVar19 * 0x18) -
                      *(int *)(&DAT_006a7710 + g_clientContext);
              iVar19 = *(int *)(g_clientContext + 0x1ff10 + iVar19 * 0x18) -
                       *(int *)(&DAT_006a7714 + g_clientContext);
              if ((DAT_00793530 <= iVar7 + 0x1d0) &&
                 (((iVar7 + 0x152 <= DAT_0056df30 && (DAT_00793534 <= iVar19 + 0x13a)) &&
                  (iVar19 + 0xba <= DAT_0056df34)))) {
                *(float *)(iVar6 + 0x80) = (float)(uVar16 & 1) * _DAT_00557fb8;
                *(float *)(iVar6 + 0x84) = (float)(uVar16 >> 1) * _DAT_00557fb8;
                *(undefined4 *)(iVar6 + 0x88) = 0x3f000000;
                BuildScaledSpriteQuad();
              }
            }
            uVar16 = uVar16 + 1;
            piVar8 = piVar8 + 1;
          } while ((int)uVar16 < 4);
          iVar5 = iVar5 + 1;
        } while (iVar5 < 3);
      }
      iStack_968 = iStack_968 + -1;
      iStack_964 = iStack_964 + -8;
      bVar17 = iStack_968 == 0;
    } while (-1 < iStack_968);
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))();
    g_spriteVertexCount = 0;
  }
  iVar6 = FindTextureCacheEntryByName();
  if (iVar6 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    iStack_95c = g_clientContext + 0x1fef0;
    iStack_970 = 0xc;
    bVar17 = false;
    do {
      if (((bVar17) || (iStack_970 == 4)) || ((iStack_970 == 6 || (iStack_970 == 7)))) {
        iStack_974 = 0;
        do {
          uVar16 = 0;
          piVar8 = (int *)(g_clientContext + 0x1fe7c);
          do {
            if ((*piVar8 == iStack_974) && (*(char *)(iStack_95c + uVar16) != '\0')) {
              iVar5 = uVar16 + iStack_970 * 8;
              iVar19 = *(int *)(g_clientContext + 0x1ff6c + iVar5 * 0x18) -
                       *(int *)(&DAT_006a7710 + g_clientContext);
              iVar5 = *(int *)(g_clientContext + 0x1ff70 + iVar5 * 0x18) -
                      *(int *)(&DAT_006a7714 + g_clientContext);
              if ((DAT_00793530 <= iVar19 + 0x1d0) &&
                 (((iVar19 + 0x150 <= DAT_0056df30 && (DAT_00793534 <= iVar5 + 0x13a)) &&
                  (iVar5 + 0xba <= DAT_0056df34)))) {
                *(float *)(iVar6 + 0x80) = (float)(uVar16 & 1) * _DAT_00557fb8;
                *(float *)(iVar6 + 0x84) = (float)(uVar16 >> 1) * _DAT_00557fb8;
                *(undefined4 *)(iVar6 + 0x88) = 0x3f000000;
                BuildScaledSpriteQuad();
              }
            }
            uVar16 = uVar16 + 1;
            piVar8 = piVar8 + 1;
          } while ((int)uVar16 < 4);
          iStack_974 = iStack_974 + 1;
        } while (iStack_974 < 3);
      }
      iStack_970 = iStack_970 + -1;
      iStack_95c = iStack_95c + -8;
      bVar17 = iStack_970 == 0;
    } while (-1 < iStack_970);
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))();
    g_spriteVertexCount = 0;
  }
  iVar6 = FindTextureCacheEntryByName();
  if (DAT_00793614 != 2) {
    DAT_00793614 = 2;
    _DAT_00792194 = 2;
    (**(code **)(*g_pD3DDevice7 + 0x50))();
    (**(code **)(*g_pD3DDevice7 + 0x50))();
  }
  if (iVar6 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    iStack_970 = 0;
    iVar5 = g_clientContext;
    do {
      uVar16 = 0;
      iStack_980 = 0;
      iStack_968 = 0;
      iStack_97c = 0x1fe6c;
      do {
        if ((*(int *)(iStack_97c + iVar5) == iStack_970) &&
           (*(int *)(iStack_980 + 0x1ff20 + iVar5) == 1)) {
          if (*(char *)(iVar5 + 0x20b0c + uVar16) == '\0') {
            iVar19 = *(int *)(iStack_980 + 0x1ff0c + iVar5);
            iVar7 = *(int *)(iStack_980 + 0x1ff10 + iVar5);
          }
          else {
            iVar19 = *(int *)(iStack_968 + 0x20b14 + iVar5);
            iVar7 = *(int *)(iStack_968 + 0x20b18 + iVar5);
          }
          iVar19 = iVar19 + (400 - *(int *)(&DAT_006a7710 + iVar5));
          iVar7 = iVar7 + (0x12a - *(int *)(&DAT_006a7714 + iVar5));
          if (((DAT_00793530 <= iVar19 + 0x40) && (iVar19 + -0x3e <= DAT_0056df30)) &&
             ((DAT_00793534 <= iVar7 + 0x10 && (iVar7 + -0x70 <= DAT_0056df34)))) {
            fVar3 = (float)(uVar16 & 1) * _DAT_00557fb8;
            *(undefined4 *)(iVar6 + 0x88) = 0x3f000000;
            *(float *)(iVar6 + 0x80) = fVar3;
            *(float *)(iVar6 + 0x84) = (float)(uVar16 >> 1) * _DAT_00557fb8;
            if (*(char *)(iVar5 + 0x20b0c + uVar16) == '\0') {
              iVar19 = GetPlayerRecordBySlot();
              iVar5 = g_clientContext;
              if ((*(int *)(iVar19 + 0x24) != 0xe) &&
                 (*(char *)(g_clientContext + 0x1fe8c + uVar16) != '\0')) {
                BuildScaledSpriteQuad();
              }
            }
            else {
              FUN_004ecc70();
            }
          }
        }
        iStack_97c = iStack_97c + 4;
        iStack_968 = iStack_968 + 0x10;
        iStack_980 = iStack_980 + 0x18;
        uVar16 = uVar16 + 1;
      } while (iStack_97c < 0x1fe7c);
      iStack_970 = iStack_970 + 1;
    } while (iStack_970 < 3);
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))();
    g_spriteVertexCount = 0;
  }
  iVar6 = FindTextureCacheEntryByName();
  if (iVar6 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    iStack_984 = 0;
    iVar5 = g_clientContext;
    do {
      uStack_98c = 0;
      iStack_974 = 0;
      iStack_988 = 0;
      iStack_970 = 0x1fe7c;
      do {
        if ((*(int *)(iStack_970 + iVar5) == iStack_984) &&
           (*(int *)(iStack_974 + 0x1ff80 + iVar5) == 1)) {
          if (*(char *)(uStack_98c + 0x20b10 + iVar5) == '\0') {
            iVar19 = *(int *)(iStack_974 + 0x1ff6c + iVar5);
            iVar7 = *(int *)(iStack_974 + 0x1ff70 + iVar5);
          }
          else {
            iVar19 = *(int *)(iStack_988 + 0x20b54 + iVar5);
            iVar7 = *(int *)(iStack_988 + 0x20b58 + iVar5);
          }
          iVar19 = iVar19 + (400 - *(int *)(&DAT_006a7710 + iVar5));
          iVar7 = iVar7 + (0x12a - *(int *)(&DAT_006a7714 + iVar5));
          if ((((DAT_00793530 <= iVar19 + 0x40) && (iVar19 + -0x40 <= DAT_0056df30)) &&
              (DAT_00793534 <= iVar7 + 0x10)) && (iVar7 + -0x70 <= DAT_0056df34)) {
            fVar3 = (float)(uStack_98c & 1) * _DAT_00557fb8;
            *(undefined4 *)(iVar6 + 0x88) = 0x3f000000;
            *(float *)(iVar6 + 0x80) = fVar3;
            *(float *)(iVar6 + 0x84) = (float)(uStack_98c >> 1) * _DAT_00557fb8;
            if (*(char *)(uStack_98c + 0x20b0c + iVar5) == '\0') {
              iVar19 = GetPlayerRecordBySlot();
              iVar5 = g_clientContext;
              if (((iVar19 != 0) && (*(int *)(iVar19 + 0x24) != 0xe)) &&
                 (*(char *)(uStack_98c + 0x1fe90 + g_clientContext) != '\0')) {
                BuildScaledSpriteQuad();
              }
            }
            else {
              FUN_004ecc70();
            }
          }
        }
        iStack_970 = iStack_970 + 4;
        uStack_98c = uStack_98c + 1;
        iStack_988 = iStack_988 + 0x10;
        iStack_974 = iStack_974 + 0x18;
      } while (iStack_970 < 0x1fe8c);
      iStack_984 = iStack_984 + 1;
    } while (iStack_984 < 3);
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))();
    g_spriteVertexCount = 0;
  }
  iVar6 = FindTextureCacheEntryByName();
  if (DAT_00793614 != 2) {
    DAT_00793614 = 2;
    _DAT_00792194 = 2;
    (**(code **)(*g_pD3DDevice7 + 0x50))();
    (**(code **)(*g_pD3DDevice7 + 0x50))();
  }
  if (iVar6 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    iStack_990 = 0;
    do {
      piVar8 = (int *)(g_clientContext + 0x1fe6c);
      uVar16 = 0;
      piVar14 = (int *)(g_clientContext + 0x1ff0c);
      do {
        if (((*piVar8 == iStack_990) && (*(char *)(uVar16 + 0x1fe8c + g_clientContext) != '\0')) &&
           (piVar14[4] == 1)) {
          if ((((DAT_00793530 <= (*piVar14 - *(int *)(&DAT_006a7710 + g_clientContext)) + 0x1d0) &&
               ((*piVar14 - *(int *)(&DAT_006a7710 + g_clientContext)) + 0x152 <= DAT_0056df30)) &&
              (DAT_00793534 <= (piVar14[1] - *(int *)(&DAT_006a7714 + g_clientContext)) + 0x13a)) &&
             ((piVar14[1] - *(int *)(&DAT_006a7714 + g_clientContext)) + 0xba <= DAT_0056df34)) {
            fVar3 = (float)(uVar16 & 1) * _DAT_00557fb8;
            *(undefined4 *)(iVar6 + 0x88) = 0x3f000000;
            *(float *)(iVar6 + 0x80) = fVar3;
            *(float *)(iVar6 + 0x84) = (float)(uVar16 >> 1) * _DAT_00557fb8;
            BuildScaledSpriteQuad();
          }
        }
        uVar16 = uVar16 + 1;
        piVar8 = piVar8 + 1;
        piVar14 = piVar14 + 6;
      } while ((int)uVar16 < 4);
      iStack_990 = iStack_990 + 1;
    } while (iStack_990 < 3);
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))();
    g_spriteVertexCount = 0;
  }
  iVar6 = FindTextureCacheEntryByName();
  if (iVar6 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    iStack_99c = 0;
    do {
      piVar8 = (int *)(g_clientContext + 0x1fe7c);
      uVar16 = 0;
      piVar14 = (int *)(g_clientContext + 0x1ff6c);
      do {
        if (((*piVar8 == iStack_99c) && (*(char *)(uVar16 + 0x1fe90 + g_clientContext) != '\0')) &&
           (piVar14[4] == 1)) {
          if (((DAT_00793530 <= (*piVar14 - *(int *)(&DAT_006a7710 + g_clientContext)) + 0x1d0) &&
              ((*piVar14 - *(int *)(&DAT_006a7710 + g_clientContext)) + 0x150 <= DAT_0056df30)) &&
             ((DAT_00793534 <= (piVar14[1] - *(int *)(&DAT_006a7714 + g_clientContext)) + 0x13a &&
              ((piVar14[1] - *(int *)(&DAT_006a7714 + g_clientContext)) + 0xba <= DAT_0056df34)))) {
            fVar3 = (float)(uVar16 & 1) * _DAT_00557fb8;
            *(undefined4 *)(iVar6 + 0x88) = 0x3f000000;
            *(float *)(iVar6 + 0x80) = fVar3;
            *(float *)(iVar6 + 0x84) = (float)(uVar16 >> 1) * _DAT_00557fb8;
            BuildScaledSpriteQuad();
          }
        }
        uVar16 = uVar16 + 1;
        piVar8 = piVar8 + 1;
        piVar14 = piVar14 + 6;
      } while ((int)uVar16 < 4);
      iStack_99c = iStack_99c + 1;
    } while (iStack_99c < 3);
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))();
    g_spriteVertexCount = 0;
  }
  iVar6 = FindTextureCacheEntryByName();
  if (DAT_00793614 != 2) {
    DAT_00793614 = 2;
    _DAT_00792194 = 2;
    (**(code **)(*g_pD3DDevice7 + 0x50))();
    (**(code **)(*g_pD3DDevice7 + 0x50))();
  }
  iVar5 = g_clientContext;
  iStack_9a8 = 0;
  do {
    if (*(char *)(iVar5 + 0x22d33 + iStack_9a8) != '\0') {
      iVar19 = 2;
      do {
        FUN_004ed5a0();
        iVar19 = iVar19 + -1;
      } while (iVar19 != 0);
    }
    iStack_9a8 = iStack_9a8 + 1;
  } while (iStack_9a8 < 0x10);
  if (iVar6 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))();
    g_spriteVertexCount = 0;
  }
  iVar6 = g_clientContext;
  pbVar15 = (byte *)(g_clientContext + 0x22d30);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar1 = *pbVar15;
  bVar2 = *(byte *)(iVar6 + 0x22d31);
  bVar17 = (byte)(bVar1 + bVar2 + -0x34) != *(char *)(iVar6 + 0x22d32);
  if (bVar17) {
    DAT_00793514 = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((bVar17 || (bVar2 >> (bVar1 & 7) & 1) != 1) &&
     (iStack_9a8 = FindTextureCacheEntryByName(), DAT_00793614 != 1)) {
    DAT_00793614 = 1;
    _DAT_00792194 = 1;
    (**(code **)(*g_pD3DDevice7 + 0x50))();
    (**(code **)(*g_pD3DDevice7 + 0x50))();
  }
  iStack_9bc = 0;
  iStack_9b4 = 0x21758;
  iVar6 = g_clientContext;
  do {
    if (*(char *)(iStack_9bc + 0x21748 + iVar6) != '\0') {
      iStack_9b8 = 0;
      iVar5 = iStack_9bc << 8;
      do {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if ((char)(*(char *)(iVar6 + 0x22d30) + *(char *)(iVar6 + 0x22d31) + -0x34) !=
            *(char *)(iVar6 + 0x22d32)) {
          DAT_00793514 = 1;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = g_clientContext;
        pcStack_a04 = (char *)((*(int *)(iVar5 + 0x217b4 + g_clientContext) -
                               *(int *)(&DAT_006a7714 + g_clientContext)) + 0x12a);
        uStack_a08 = (*(int *)(iVar5 + 0x217b0 + g_clientContext) -
                     *(int *)(&DAT_006a7710 + g_clientContext)) + 400;
        piStack_a0c = (int *)0x4c4a04;
        FUN_004ed5a0();
        iStack_9b8 = iStack_9b8 + 1;
        iVar5 = iVar5 + 0x10;
      } while (iStack_9b8 < (int)(uint)*(byte *)(iStack_9bc + 0x21748 + iVar6));
    }
    iStack_9b4 = iStack_9b4 + 4;
    iStack_9bc = iStack_9bc + 1;
  } while (iStack_9b4 < 0x21798);
  if (iStack_9a8 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))();
    g_spriteVertexCount = 0;
  }
  if (*(char *)(g_clientContext + 0x23244) == '\x01') {
    iVar5 = *(int *)(g_clientContext + 0x23248) - *(int *)(&DAT_006a7710 + g_clientContext);
    iVar6 = *(int *)(g_clientContext + 0x2324c) - *(int *)(&DAT_006a7714 + g_clientContext);
    if ((((DAT_00793530 <= iVar5 + 0x210) && (iVar5 + 0x110 <= DAT_0056df30)) &&
        (DAT_00793534 <= iVar6 + 0x1aa)) && (iVar6 + 0xaa <= DAT_0056df34)) {
      if (DAT_00793614 != 1) {
        DAT_00793614 = 1;
        _DAT_00792194 = 1;
        (**(code **)(*g_pD3DDevice7 + 0x50))();
        (**(code **)(*g_pD3DDevice7 + 0x50))();
      }
      iVar6 = FindTextureCacheEntryByName();
      if (iVar6 != 0) {
        *(undefined4 *)(iVar6 + 0x80) = 0;
        *(undefined4 *)(iVar6 + 0x84) = 0;
        *(undefined4 *)(iVar6 + 0x88) = 0x3f800000;
        FUN_004ecc70();
        (**(code **)(*g_pD3DDevice7 + 0x8c))();
        if (g_spriteVertexCount != 0) {
          DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
          (**(code **)(*g_pD3DDevice7 + 100))();
          g_spriteVertexCount = 0;
        }
      }
      if (DAT_00793614 != 2) {
        DAT_00793614 = 2;
        _DAT_00792194 = 2;
        (**(code **)(*g_pD3DDevice7 + 0x50))();
        (**(code **)(*g_pD3DDevice7 + 0x50))();
      }
      iVar6 = FindTextureCacheEntryByName();
      if (iVar6 != 0) {
        *(undefined4 *)(iVar6 + 0x80) = 0;
        *(undefined4 *)(iVar6 + 0x84) = 0;
        *(undefined4 *)(iVar6 + 0x88) = 0x3f800000;
        FUN_004ecc70();
        (**(code **)(*g_pD3DDevice7 + 0x8c))();
        if (g_spriteVertexCount != 0) {
          DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
          (**(code **)(*g_pD3DDevice7 + 100))();
          g_spriteVertexCount = 0;
        }
      }
    }
  }
  if (DAT_00793614 != 1) {
    DAT_00793614 = 1;
    _DAT_00792194 = 1;
    (**(code **)(*g_pD3DDevice7 + 0x50))();
    (**(code **)(*g_pD3DDevice7 + 0x50))();
  }
  iVar6 = FindTextureCacheEntryByName();
  if (iVar6 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    iStack_9ac = g_clientContext + 0x20c14;
    iStack_9b8 = g_clientContext + 0x214f4;
    iStack_9c0 = 7;
    do {
      uVar16 = 0;
      piStack_9c4 = (int *)iStack_9b8;
      do {
        if ((*(char *)(iStack_9ac + uVar16) != '\0') &&
           (*(char *)(uVar16 + 0x21748 + g_clientContext) == '\0')) {
          iVar5 = *(int *)(g_clientContext + (iStack_9c0 * 0x10 + 0x1a35 + uVar16) * 0x14) -
                  *(int *)(&DAT_006a7710 + g_clientContext);
          iVar19 = *(int *)((int)piStack_9c4 + -0xc) - *(int *)(&DAT_006a7714 + g_clientContext);
          if (((DAT_00793530 <= iVar5 + 0x1c0) &&
              ((iVar5 + 0x160 <= DAT_0056df30 && (DAT_00793534 <= iVar19 + 0x15a)))) &&
             (iVar19 + 0xfa <= DAT_0056df34)) {
            fVar3 = (float)(uVar16 & 3) * _DAT_00558054;
            *(undefined4 *)(iVar6 + 0x88) = 0x3e800000;
            *(float *)(iVar6 + 0x80) = fVar3;
            *(float *)(iVar6 + 0x84) = (float)(uVar16 >> 2) * _DAT_00558054;
            FUN_004ebdd0();
          }
        }
        uVar16 = uVar16 + 1;
        piStack_9c4 = (int *)((int)piStack_9c4 + 0x14);
      } while ((int)uVar16 < 0x10);
      iStack_9c0 = iStack_9c0 + -1;
      iStack_9b8 = iStack_9b8 + -0x140;
      iStack_9ac = iStack_9ac + -0x10;
    } while (-1 < iStack_9c0);
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    pcStack_a04 = (char *)0x4c4f4b;
    (**(code **)(*g_pD3DDevice7 + 100))();
    g_spriteVertexCount = 0;
  }
  iVar6 = FindTextureCacheEntryByName();
  if (DAT_00793614 != 2) {
    DAT_00793614 = 2;
    _DAT_00792194 = 2;
    (**(code **)(*g_pD3DDevice7 + 0x50))();
    pcStack_a04 = (char *)0x4c4fa1;
    (**(code **)(*g_pD3DDevice7 + 0x50))();
  }
  if (iVar6 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    iStack_9b8 = g_clientContext + 0x20c14;
    piStack_9c4 = (int *)(g_clientContext + 0x214e8);
    iStack_9cc = 7;
    do {
      uVar16 = 0;
      piStack_9d0 = piStack_9c4;
      do {
        if (((*(char *)(uVar16 + iStack_9b8) != '\0') &&
            (*(char *)(uVar16 + 0x21748 + g_clientContext) == '\0')) && (piStack_9d0[2] == 1)) {
          iVar5 = *(int *)(g_clientContext + (iStack_9cc * 0x10 + 0x1a35 + uVar16) * 0x14) -
                  *(int *)(&DAT_006a7710 + g_clientContext);
          if (((DAT_00793530 <= iVar5 + 0x1c0) && (iVar5 + 0x160 <= DAT_0056df30)) &&
             ((DAT_00793534 <= (*piStack_9d0 - *(int *)(&DAT_006a7714 + g_clientContext)) + 0x15a &&
              ((*piStack_9d0 - *(int *)(&DAT_006a7714 + g_clientContext)) + 0xfa <= DAT_0056df34)))) {
            fVar3 = (float)(uVar16 & 3) * _DAT_00558054;
            *(undefined4 *)(iVar6 + 0x88) = 0x3e800000;
            *(float *)(iVar6 + 0x80) = fVar3;
            *(float *)(iVar6 + 0x84) = (float)(uVar16 >> 2) * _DAT_00558054;
            FUN_004ebdd0();
          }
        }
        uVar16 = uVar16 + 1;
        piStack_9d0 = piStack_9d0 + 5;
      } while ((int)uVar16 < 0x10);
      iStack_9cc = iStack_9cc + -1;
      piStack_9c4 = piStack_9c4 + -0x50;
      iStack_9b8 = iStack_9b8 + -0x10;
    } while (-1 < iStack_9cc);
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    pcStack_a04 = (char *)0x244;
    uStack_a08 = 4;
    piStack_a0c = g_pD3DDevice7;
    pcStack_a10 = (char *)0x4c51a1;
    (**(code **)(*g_pD3DDevice7 + 100))();
    g_spriteVertexCount = 0;
  }
  FUN_00450c20();
  if (DAT_00793614 != 0) {
    DAT_00793614 = 0;
    _DAT_00792194 = 0;
    pcStack_a04 = (char *)0x4c51dc;
    (**(code **)(*g_pD3DDevice7 + 0x50))();
    pcStack_a04 = (char *)0x6;
    uStack_a08 = 0x14;
    piStack_a0c = g_pD3DDevice7;
    pcStack_a10 = (char *)0x4c51eb;
    (**(code **)(*g_pD3DDevice7 + 0x50))();
  }
  iStack_9dc = 0;
  iStack_9e0 = 0;
  iVar6 = g_clientContext;
  do {
    if (*(char *)(iStack_9dc + 0x21714 + iVar6) != '\0') {
      pcStack_a04 = (char *)0x4c5229;
      _sprintf(acStack_794,s_FlameTexture_d_00556778);
      iVar5 = FindTextureCacheEntryByName();
      iVar6 = g_clientContext;
      if (iVar5 != 0) {
        iVar19 = *(int *)(iStack_9e0 + 0x21718 + g_clientContext) -
                 *(int *)(&DAT_006a7710 + g_clientContext);
        iVar7 = *(int *)(iStack_9e0 + 0x2171c + g_clientContext) -
                *(int *)(&DAT_006a7714 + g_clientContext);
        if (((DAT_00793530 <= iVar19 + 0x210) && (iVar19 + 0x110 <= DAT_0056df30)) &&
           ((DAT_00793534 <= iVar7 + 0x1aa && (iVar7 + 0xaa <= DAT_0056df34)))) {
          pcStack_a04 = (char *)0x0;
          *(undefined4 *)(iVar5 + 0x80) = 0;
          *(undefined4 *)(iVar5 + 0x84) = 0;
          *(undefined4 *)(iVar5 + 0x88) = 0x3f800000;
          pcStack_a10 = (char *)0x4c52f4;
          piStack_a0c = (int *)(iVar19 + 400);
          uStack_a08 = iVar7 + 0x12a;
          FUN_004ecc70();
          pcStack_a04 = (char *)0x4c5314;
          (**(code **)(*g_pD3DDevice7 + 0x8c))();
          iVar6 = g_clientContext;
          if (g_spriteVertexCount != 0) {
            DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
            pcStack_a04 = (char *)0x244;
            uStack_a08 = 4;
            piStack_a0c = g_pD3DDevice7;
            pcStack_a10 = (char *)0x4c5349;
            (**(code **)(*g_pD3DDevice7 + 100))();
            g_spriteVertexCount = 0;
            iVar6 = g_clientContext;
          }
        }
      }
    }
    iStack_9e0 = iStack_9e0 + 0xc;
    iStack_9dc = iStack_9dc + 1;
  } while (iStack_9e0 < 0x30);
  iVar6 = FindTextureCacheEntryByName();
  if (iVar6 == 0) {
    pcStack_a04 = (char *)0x4c5548;
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    piVar8 = (int *)(g_clientContext + 0x21658);
    uVar16 = 0;
    iVar5 = g_clientContext;
    do {
      if (*(char *)(uVar16 + 0x21644 + iVar5) != '\0') {
        iVar19 = piVar8[-1] - *(int *)(&DAT_006a7710 + iVar5);
        piVar14 = (int *)(&DAT_006a7714 + iVar5);
        pcStack_a04 = (char *)(iVar19 + 400);
        iVar5 = g_clientContext;
        if ((((DAT_00793530 <= iVar19 + 0x1d0) && (iVar19 + 0x150 <= DAT_0056df30)) &&
            (DAT_00793534 <= (*piVar8 - *piVar14) + 0x16a)) &&
           ((*piVar8 - *piVar14) + 0xea <= DAT_0056df34)) {
          *(float *)(iVar6 + 0x80) = (float)(uVar16 & 1) * _DAT_00557fb8;
          *(undefined4 *)(iVar6 + 0x88) = 0x3f000000;
          *(float *)(iVar6 + 0x84) = (float)(uVar16 >> 1) * _DAT_00557fb8;
          uStack_a08 = 0x4c545d;
          FUN_004ec430();
          iVar5 = g_clientContext;
        }
      }
      uVar16 = uVar16 + 1;
      piVar8 = piVar8 + 3;
    } while ((int)uVar16 < 4);
    pcStack_a04 = (char *)0x4c5498;
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    pcStack_a04 = (char *)0x1;
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    uStack_a08 = g_spriteVertexCount * 3;
    piStack_a0c = &g_spriteVertexBuffer;
    pcStack_a10 = (char *)0x244;
    uStack_a14 = 4;
    piStack_a18 = g_pD3DDevice7;
    pcStack_a1c = (char *)0x4c54cd;
    (**(code **)(*g_pD3DDevice7 + 100))();
    g_spriteVertexCount = 0;
  }
  pcStack_a04 = s_FlameTexture2_00556850;
  uStack_a08 = 0x4c54e6;
  iVar6 = FindTextureCacheEntryByName();
  if (iVar6 == 0) {
    pcStack_a04 = (char *)0x0;
    uStack_a08 = 0;
    piStack_a0c = g_pD3DDevice7;
    pcStack_a10 = (char *)0x4c56e8;
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    piVar8 = (int *)(g_clientContext + 0x21688);
    uStack_9e4 = 0;
    do {
      if (*(char *)(uStack_9e4 + 0x21648 + g_clientContext) != '\0') {
        iVar5 = piVar8[-1] - *(int *)(&DAT_006a7710 + g_clientContext);
        pcStack_a10 = (char *)(iVar5 + 400);
        iVar19 = *piVar8 - *(int *)(&DAT_006a7714 + g_clientContext);
        piStack_a0c = (int *)(iVar19 + 0x12a);
        if (((DAT_00793530 <= iVar5 + 0x1d0) && (iVar5 + 0x150 <= DAT_0056df30)) &&
           ((DAT_00793534 <= iVar19 + 0x16a && (iVar19 + 0xea <= DAT_0056df34)))) {
          pcStack_a04 = (char *)0xffffff;
          uStack_a08 = 0xff;
          *(float *)(iVar6 + 0x80) = (float)(uStack_9e4 & 1) * _DAT_00557fb8;
          *(undefined4 *)(iVar6 + 0x88) = 0x3f000000;
          *(float *)(iVar6 + 0x84) = (float)(uStack_9e4 >> 1) * _DAT_00557fb8;
          uStack_a14 = 0x4c5629;
          FUN_004ec430();
        }
      }
      uStack_9e4 = uStack_9e4 + 1;
      piVar8 = piVar8 + 3;
    } while ((int)uStack_9e4 < 4);
    pcStack_a04 = *(char **)(*(int *)(iVar6 + 0x94) + 0x110);
    uStack_a08 = 0;
    piStack_a0c = g_pD3DDevice7;
    pcStack_a10 = (char *)0x4c5666;
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    pcStack_a10 = (char *)0x1;
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    uStack_a14 = g_spriteVertexCount * 3;
    piStack_a18 = &g_spriteVertexBuffer;
    pcStack_a1c = (char *)0x244;
    uStack_a20 = (int *)0x4;
    piStack_a24 = g_pD3DDevice7;
    pcStack_a28 = (char *)0x4c569b;
    (**(code **)(*g_pD3DDevice7 + 100))();
    g_spriteVertexCount = 0;
  }
  pcStack_a10 = s_FlameTexture3_00556840;
  uStack_a14 = 0x4c56b4;
  iVar6 = FindTextureCacheEntryByName();
  if (iVar6 == 0) {
    pcStack_a10 = (char *)0x0;
    uStack_a14 = 0;
    piStack_a18 = g_pD3DDevice7;
    pcStack_a1c = (char *)0x4c5888;
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    piVar8 = (int *)(g_clientContext + 0x216b8);
    uStack_9f0 = 0;
    do {
      if (*(char *)(uStack_9f0 + 0x2164c + g_clientContext) != '\0') {
        iVar5 = piVar8[-1] - *(int *)(&DAT_006a7710 + g_clientContext);
        pcStack_a1c = (char *)(iVar5 + 400);
        iVar19 = *piVar8 - *(int *)(&DAT_006a7714 + g_clientContext);
        piStack_a18 = (int *)(iVar19 + 0x12a);
        if (((DAT_00793530 <= iVar5 + 0x1d0) && (iVar5 + 0x150 <= DAT_0056df30)) &&
           ((DAT_00793534 <= iVar19 + 0x16a && (iVar19 + 0xea <= DAT_0056df34)))) {
          pcStack_a10 = (char *)0xffffff;
          uStack_a14 = 0xff;
          *(float *)(iVar6 + 0x80) = (float)(uStack_9f0 & 1) * _DAT_00557fb8;
          *(undefined4 *)(iVar6 + 0x88) = 0x3f000000;
          *(float *)(iVar6 + 0x84) = (float)(uStack_9f0 >> 1) * _DAT_00557fb8;
          uStack_a20 = (int *)0x4c57c9;
          FUN_004ec430();
        }
      }
      uStack_9f0 = uStack_9f0 + 1;
      piVar8 = piVar8 + 3;
    } while ((int)uStack_9f0 < 4);
    pcStack_a10 = *(char **)(*(int *)(iVar6 + 0x94) + 0x110);
    uStack_a14 = 0;
    piStack_a18 = g_pD3DDevice7;
    pcStack_a1c = (char *)0x4c5806;
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    pcStack_a1c = (char *)0x1;
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    uStack_a20 = (int *)(g_spriteVertexCount * 3);
    piStack_a24 = &g_spriteVertexBuffer;
    pcStack_a28 = (char *)0x244;
    piStack_a2c = (int *)0x4;
    piStack_a30 = g_pD3DDevice7;
    pcStack_a34 = (char *)0x4c583b;
    (**(code **)(*g_pD3DDevice7 + 100))();
    g_spriteVertexCount = 0;
  }
  pcStack_a1c = s_FlameTexture4_00556830;
  uStack_a20 = (int *)0x4c5854;
  iVar6 = FindTextureCacheEntryByName();
  if (iVar6 == 0) {
    pcStack_a1c = (char *)0x0;
    uStack_a20 = (int *)0x0;
    piStack_a24 = g_pD3DDevice7;
    pcStack_a28 = (char *)0x4c5a5e;
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    piVar8 = (int *)(g_clientContext + 0x216e8);
    uVar16 = 0;
    do {
      if (*(char *)(uVar16 + 0x21650 + g_clientContext) != '\0') {
        iVar5 = piVar8[-1] - *(int *)(&DAT_006a7710 + g_clientContext);
        pcStack_a28 = (char *)(iVar5 + 400);
        iVar19 = *piVar8 - *(int *)(&DAT_006a7714 + g_clientContext);
        piStack_a24 = (int *)(iVar19 + 0x12a);
        if ((((DAT_00793530 <= iVar5 + 0x1d0) && (iVar5 + 0x150 <= DAT_0056df30)) &&
            (DAT_00793534 <= iVar19 + 0x16a)) && (iVar19 + 0xea <= DAT_0056df34)) {
          uStack_a08 = uVar16 >> 1;
          pcStack_a1c = (char *)0xffffff;
          uStack_a20 = (int *)0xff;
          *(float *)(iVar6 + 0x80) = (float)(uVar16 & 1) * _DAT_00557fb8;
          *(undefined4 *)(iVar6 + 0x88) = 0x3f000000;
          *(float *)(iVar6 + 0x84) = (float)uStack_a08 * _DAT_00557fb8;
          piStack_a2c = (int *)0x4c5969;
          FUN_004ec430();
        }
      }
      uVar16 = uVar16 + 1;
      piVar8 = piVar8 + 3;
    } while ((int)uVar16 < 4);
    pcStack_a1c = *(char **)(*(int *)(iVar6 + 0x94) + 0x110);
    uStack_a20 = (int *)0x0;
    piStack_a24 = g_pD3DDevice7;
    pcStack_a28 = (char *)0x4c59a6;
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    pcStack_a28 = (char *)0x1;
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    piStack_a2c = (int *)(g_spriteVertexCount * 3);
    piStack_a30 = &g_spriteVertexBuffer;
    pcStack_a34 = (char *)0x244;
    uStack_a38 = 4;
    (**(code **)(*g_pD3DDevice7 + 100))(g_pD3DDevice7);
    g_spriteVertexCount = 0;
  }
  if (DAT_00793614 != 1) {
    pcStack_a28 = (char *)0x5;
    piStack_a2c = (int *)0x13;
    piStack_a30 = g_pD3DDevice7;
    DAT_00793614 = 1;
    _DAT_00792194 = 1;
    pcStack_a34 = (char *)0x4c5a0c;
    (**(code **)(*g_pD3DDevice7 + 0x50))();
    pcStack_a34 = (char *)0x6;
    uStack_a38 = 0x14;
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7);
  }
  pcStack_a28 = s_RayonTexture1_00556820;
  piStack_a2c = (int *)0x4c5a2a;
  iVar6 = FindTextureCacheEntryByName();
  if (iVar6 == 0) {
    pcStack_a28 = (char *)0x0;
    piStack_a2c = (int *)0x0;
    piStack_a30 = g_pD3DDevice7;
    pcStack_a34 = (char *)0x4c5c7c;
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  else {
    piStack_a0c = (int *)0x0;
    piVar8 = (int *)(g_clientContext + 0x227d8);
    do {
      iVar5 = DAT_00793530;
      if (*(char *)((int)piStack_a0c + g_clientContext + 0x22cd4) != '\0') {
        iVar19 = piVar8[-1] - *(int *)(&DAT_006a7710 + g_clientContext);
        iVar7 = *piVar8 - *(int *)(&DAT_006a7714 + g_clientContext);
        uStack_a14 = (uint)piStack_a0c >> 3;
        fVar3 = (float)((uint)piStack_a0c & 7) * _DAT_00558040;
        *(undefined4 *)(iVar6 + 0x88) = 0x3e000000;
        *(float *)(iVar6 + 0x80) = fVar3;
        *(float *)(iVar6 + 0x84) = (float)uStack_a14 * _DAT_00558040;
        if (piVar8[3] == 0) {
          if (((iVar5 <= iVar19 + 0x1a0) && (iVar19 + 0x180 <= DAT_0056df30)) &&
             ((DAT_00793534 <= iVar7 + 0x132 && (iVar7 + 0x112 <= DAT_0056df34)))) {
            pcStack_a28 = (char *)piVar8[2];
            pcStack_a34 = (char *)0x4c5b3a;
            piStack_a30 = (int *)(iVar19 + 400);
            piStack_a2c = (int *)(iVar7 + 0x12aU);
            BuildRotatedSpriteQuad();
          }
        }
        else if (((iVar5 <= iVar19 + 0x1a0) && (iVar19 + 0x180 <= DAT_0056df30)) &&
                ((DAT_00793534 <= iVar7 + 0x13a && (iVar7 + 0x11a <= DAT_0056df34)))) {
          pcStack_a28 = (char *)0xffffffff;
          pcStack_a34 = (char *)CONCAT31((int3)((uint)piVar8[2] >> 8),piVar8[2] != 0);
          piStack_a2c = (int *)0x20;
          piStack_a30 = (int *)0x20;
          uStack_a38 = iVar7 + 0x12aU;
          FUN_004ecc70(iVar19 + 400);
        }
      }
      piStack_a0c = (int *)((int)piStack_a0c + 1);
      piVar8 = piVar8 + 5;
    } while ((int)piStack_a0c < 0x40);
    pcStack_a28 = *(char **)(*(int *)(iVar6 + 0x94) + 0x110);
    piStack_a2c = (int *)0x0;
    piStack_a30 = g_pD3DDevice7;
    pcStack_a34 = (char *)0x4c5bc3;
    (**(code **)(*g_pD3DDevice7 + 0x8c))();
  }
  if (g_spriteVertexCount != 0) {
    pcStack_a34 = (char *)0x1;
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    uStack_a38 = g_spriteVertexCount * 3;
    (**(code **)(*g_pD3DDevice7 + 100))(g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer);
    g_spriteVertexCount = 0;
  }
  if (DAT_00793614 != 2) {
    pcStack_a34 = (char *)0x5;
    uStack_a38 = 0x13;
    DAT_00793614 = 2;
    _DAT_00792194 = 2;
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7);
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,2);
  }
  pcStack_a34 = s_RayonTexture2_00556810;
  uStack_a38 = 0x4c5c48;
  uStack_a08 = FindTextureCacheEntryByName();
  if (uStack_a08 == 0) {
    pcStack_a34 = (char *)0x0;
    uStack_a38 = 0;
    (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7);
  }
  else {
    piStack_a18 = (int *)0x0;
    piVar8 = (int *)(g_clientContext + 0x227d8);
    do {
      iVar6 = DAT_00793530;
      if (*(char *)((int)piStack_a18 + g_clientContext + 0x22cd4) != '\0') {
        iVar5 = piVar8[-1] - *(int *)(&DAT_006a7710 + g_clientContext);
        iVar19 = *piVar8 - *(int *)(&DAT_006a7714 + g_clientContext);
        uStack_a20 = (int *)((uint)piStack_a18 >> 3);
        fVar3 = (float)((uint)piStack_a18 & 7) * _DAT_00558040;
        *(undefined4 *)(uStack_a08 + 0x88) = 0x3e000000;
        *(float *)(uStack_a08 + 0x80) = fVar3;
        *(float *)(uStack_a08 + 0x84) = (float)(int)uStack_a20 * _DAT_00558040;
        if (piVar8[3] == 0) {
          if (((iVar6 <= iVar5 + 0x1a0) && (iVar5 + 0x180 <= DAT_0056df30)) &&
             ((DAT_00793534 <= iVar19 + 0x132 && (iVar19 + 0x112 <= DAT_0056df34)))) {
            pcStack_a34 = (char *)piVar8[2];
            uStack_a38 = iVar19 + 0x12aU;
            BuildRotatedSpriteQuad(iVar5 + 400);
          }
        }
        else if ((((iVar6 <= iVar5 + 0x1a0) && (iVar5 + 0x180 <= DAT_0056df30)) &&
                 (DAT_00793534 <= iVar19 + 0x13a)) && (iVar19 + 0x11a <= DAT_0056df34)) {
          pcStack_a34 = (char *)0xffffffff;
          uStack_a38 = 0x20;
          FUN_004ecc70(iVar5 + 400,iVar19 + 0x12aU,
                       CONCAT31((int3)((uint)piVar8[2] >> 8),piVar8[2] != 0),0x20);
        }
      }
      piStack_a18 = (int *)((int)piStack_a18 + 1);
      piVar8 = piVar8 + 5;
    } while ((int)piStack_a18 < 0x40);
    pcStack_a34 = *(char **)(*(int *)(uStack_a08 + 0x94) + 0x110);
    uStack_a38 = 0;
    (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7);
  }
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar6 == 3) {
    if (DAT_00793614 != 1) {
      DAT_00793614 = 1;
      _DAT_00792194 = 1;
      (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
      (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,6);
    }
    iVar6 = FindTextureCacheEntryByName(s_JewelTexture_005567c0);
    if (iVar6 == 0) {
      (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
    }
    else {
      uStack_a20 = (int *)(g_clientContext + 0x23284);
      piStack_a18 = (int *)0x0;
      do {
        iVar5 = DAT_00793530;
        if (*(char *)((int)piStack_a18 + g_clientContext + 0x23278) != '\0') {
          iVar12 = uStack_a20[-1] - *(int *)(&DAT_006a7710 + g_clientContext);
          iVar19 = *uStack_a20;
          iVar7 = *(int *)(&DAT_006a7714 + g_clientContext);
          piStack_a2c = (int *)((uint)piStack_a18 >> 2);
          *(float *)(iVar6 + 0x80) = (float)((uint)piStack_a18 & 3) * _DAT_00558054;
          iVar11 = (iVar19 - iVar7) + 0x12a;
          *(undefined4 *)(iVar6 + 0x88) = 0x3e800000;
          *(float *)(iVar6 + 0x84) = (float)(int)piStack_a2c * _DAT_00558054;
          if (((iVar5 <= iVar12 + 0x1a0) && (iVar12 + 0x180 <= DAT_0056df30)) &&
             ((DAT_00793534 <= iVar11 && ((iVar19 - iVar7) + 0x10a <= DAT_0056df34)))) {
            FUN_004ecee0(iVar12 + 400,iVar11);
          }
        }
        piStack_a18 = (int *)((int)piStack_a18 + 1);
        uStack_a20 = uStack_a20 + 4;
      } while ((int)piStack_a18 < 8);
      (**(code **)(*g_pD3DDevice7 + 0x8c))
                (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar6 + 0x94) + 0x110));
    }
    if (g_spriteVertexCount != 0) {
      DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
      (**(code **)(*g_pD3DDevice7 + 100))
                (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
      g_spriteVertexCount = 0;
    }
    if (DAT_00793614 != 2) {
      DAT_00793614 = 2;
      _DAT_00792194 = 2;
      (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
      (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,2);
    }
    if (iVar6 == 0) {
      (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
    }
    else {
      piStack_a2c = (int *)(g_clientContext + 0x23284);
      piStack_a24 = (int *)0x0;
      do {
        iVar5 = DAT_00793530;
        if (*(char *)((int)piStack_a24 + g_clientContext + 0x23278) != '\0') {
          iVar12 = piStack_a2c[-1] - *(int *)(&DAT_006a7710 + g_clientContext);
          iVar19 = *piStack_a2c;
          iVar7 = *(int *)(&DAT_006a7714 + g_clientContext);
          uStack_a38 = (uint)piStack_a24 >> 2;
          *(float *)(iVar6 + 0x80) = (float)((uint)piStack_a24 & 3) * _DAT_00558054;
          iVar11 = (iVar19 - iVar7) + 0x12a;
          *(undefined4 *)(iVar6 + 0x88) = 0x3e800000;
          *(float *)(iVar6 + 0x84) = (float)uStack_a38 * _DAT_00558054 + _DAT_00557fb8;
          if ((((iVar5 <= iVar12 + 0x1a0) && (iVar12 + 0x180 <= DAT_0056df30)) &&
              (DAT_00793534 <= iVar11)) && ((iVar19 - iVar7) + 0x10a <= DAT_0056df34)) {
            FUN_004ecee0(iVar12 + 400,iVar11);
          }
        }
        piStack_a24 = (int *)((int)piStack_a24 + 1);
        piStack_a2c = piStack_a2c + 4;
      } while ((int)piStack_a24 < 8);
      (**(code **)(*g_pD3DDevice7 + 0x8c))
                (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar6 + 0x94) + 0x110));
    }
    if (g_spriteVertexCount != 0) {
      DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
      (**(code **)(*g_pD3DDevice7 + 100))
                (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
      g_spriteVertexCount = 0;
    }
  }
  if (DAT_00793614 != 1) {
    DAT_00793614 = 1;
    _DAT_00792194 = 1;
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,6);
  }
  iVar6 = FindTextureCacheEntryByName(s_SpecialTexture1_00556800);
  if (iVar6 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
  }
  else {
    if (*(char *)(g_clientContext + 0x22d24) != '\0') {
      iVar5 = *(int *)(g_clientContext + 0x22d28) - *(int *)(&DAT_006a7710 + g_clientContext);
      iVar19 = *(int *)(g_clientContext + 0x22d2c) - *(int *)(&DAT_006a7714 + g_clientContext);
      if (((DAT_00793530 < iVar5 + 0x210) && (iVar5 + 0x110 < DAT_0056df30)) &&
         ((DAT_00793534 < iVar19 + 0x16a && (iVar19 + 0x6a < DAT_0056df34)))) {
        *(undefined4 *)(iVar6 + 0x80) = 0;
        *(undefined4 *)(iVar6 + 0x84) = 0;
        *(undefined4 *)(iVar6 + 0x88) = 0x3f800000;
        BuildSpriteQuad(iVar5 + 400,iVar19 + 0x12a);
      }
    }
    (**(code **)(*g_pD3DDevice7 + 0x8c))
              (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar6 + 0x94) + 0x110));
  }
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  if (DAT_00793614 != 2) {
    DAT_00793614 = 2;
    _DAT_00792194 = 2;
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,2);
  }
  iVar6 = FindTextureCacheEntryByName(s_SpecialTexture2_005567f0);
  if (iVar6 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
  }
  else {
    if (*(char *)(g_clientContext + 0x22d24) != '\0') {
      iVar5 = *(int *)(g_clientContext + 0x22d28) - *(int *)(&DAT_006a7710 + g_clientContext);
      iVar19 = *(int *)(g_clientContext + 0x22d2c) - *(int *)(&DAT_006a7714 + g_clientContext);
      if (((DAT_00793530 < iVar5 + 0x210) && (iVar5 + 0x110 < DAT_0056df30)) &&
         ((DAT_00793534 < iVar19 + 0x16a && (iVar19 + 0x6a < DAT_0056df34)))) {
        *(undefined4 *)(iVar6 + 0x80) = 0;
        *(undefined4 *)(iVar6 + 0x84) = 0;
        *(undefined4 *)(iVar6 + 0x88) = 0x3f800000;
        BuildSpriteQuad(iVar5 + 400,iVar19 + 0x12a);
      }
    }
    (**(code **)(*g_pD3DDevice7 + 0x8c))
              (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar6 + 0x94) + 0x110));
  }
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  iVar6 = FindTextureCacheEntryByName(&DAT_00554060);
  piStack_a2c = (int *)iVar6;
  if (DAT_00793614 != 1) {
    DAT_00793614 = 1;
    _DAT_00792194 = 1;
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,6);
  }
  if (iVar6 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
    goto LAB_004c865b;
  }
  iVar6 = *(int *)(g_clientContext + 0x621e0);
  iVar5 = g_clientContext;
  if (iVar6 != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    bVar1 = *(byte *)(iVar6 + 0x8bbd);
    bVar2 = *(byte *)(iVar6 + 0x8bbe);
    bVar17 = (byte)(bVar1 + bVar2 + -0x34) == *(char *)(iVar6 + 0x8bbf);
    if (!bVar17) {
      DAT_00793514 = 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = g_clientContext;
    if (bVar17 && (bVar2 >> (bVar1 & 7) & 1) == 1) {
      iVar6 = *(int *)(g_clientContext + 0x621e0);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      bVar1 = *(byte *)(iVar6 + 0xbff7);
      bVar2 = *(byte *)(iVar6 + 0xbff8);
      bVar17 = (byte)(bVar1 + bVar2 + -0x34) == *(char *)(iVar6 + 0xbff9);
      if (!bVar17) {
        DAT_00793514 = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      bVar18 = (bVar2 >> (bVar1 & 7) & 1) == 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = g_clientContext;
      if (!bVar17 || !bVar18) {
        uVar9 = FUN_0040a6e0(*(int *)(g_clientContext + 0x621e0) + 0x90c,&piStack_a18,
                             *(undefined4 *)(&DAT_006a7710 + g_clientContext));
        uStack_100 = 0;
        FUN_0040a5f0(uVar9,auStack_550,400);
        uStack_100 = 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        piStack_a30 = (int *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uStack_100 = bVar17 && bVar18;
        if (iStack_53c != 0) {
          iVar6 = iStack_53c << 4;
          uStack_a38 = 0x10;
          do {
            iVar5 = _rand();
            *(char *)(DAT_0079376c + iVar6) = (char)iVar5;
            iVar6 = iVar6 + 1;
            uStack_a38 = uStack_a38 - 1;
          } while (uStack_a38 != 0);
          FUN_0040b540(&uStack_a38);
        }
        uStack_100 = 0xffffffff;
        if (pcStack_a04 != (char *)0x0) {
          iVar6 = (int)pcStack_a04 << 4;
          iVar5 = 0x10;
          do {
            iVar19 = _rand();
            *(char *)(DAT_0079376c + iVar6) = (char)iVar19;
            iVar6 = iVar6 + 1;
            iVar5 = iVar5 + -1;
          } while (iVar5 != 0);
          FUN_0040b540(&uStack_a38);
        }
        uVar9 = FUN_0040a6e0(*(int *)(g_clientContext + 0x621e0) + 0xb30,auStack_774,
                             *(undefined4 *)(&DAT_006a7714 + g_clientContext));
        uStack_100 = 2;
        uVar9 = FUN_0040a5f0(uVar9,auStack_550,0x104);
        uStack_100 = 3;
        FUN_0040a5f0(uVar9,&piStack_a18,0x26);
        uStack_100 = 4;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        piStack_a24 = (int *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uStack_100 = 3;
        if (pcStack_a04 != (char *)0x0) {
          iVar6 = (int)pcStack_a04 << 4;
          uStack_a38 = 0x10;
          do {
            iVar5 = _rand();
            *(char *)(DAT_0079376c + iVar6) = (char)iVar5;
            iVar6 = iVar6 + 1;
            uStack_a38 = uStack_a38 - 1;
          } while (uStack_a38 != 0);
          FUN_0040b540(&uStack_a38);
        }
        uStack_100 = 2;
        if (iStack_53c != 0) {
          iVar6 = iStack_53c << 4;
          iVar5 = 0x10;
          do {
            iVar19 = _rand();
            *(char *)(iVar6 + DAT_0079376c) = (char)iVar19;
            iVar6 = iVar6 + 1;
            iVar5 = iVar5 + -1;
          } while (iVar5 != 0);
          FUN_0040b540(&uStack_a38);
        }
        uStack_100 = 0xffffffff;
        if (iStack_760 != 0) {
          iVar6 = iStack_760 << 4;
          iVar5 = 0x10;
          do {
            iVar19 = _rand();
            *(char *)(iVar6 + DAT_0079376c) = (char)iVar19;
            iVar6 = iVar6 + 1;
            iVar5 = iVar5 + -1;
          } while (iVar5 != 0);
          FUN_0040b540(&uStack_a38);
        }
        iVar6 = *(int *)(g_clientContext + 0x621e0);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        bVar1 = *(byte *)(iVar6 + 0x8bba);
        bVar2 = *(byte *)(iVar6 + 0x8bbb);
        bVar17 = (byte)(bVar1 + bVar2 + -0x34) != *(char *)(iVar6 + 0x8bbc);
        if (bVar17) {
          DAT_00793514 = 1;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = *(int *)(g_clientContext + 0x621e0);
        if (bVar17 || (bVar2 >> (bVar1 & 7) & 1) != 1) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          bVar1 = *(byte *)(iVar6 + 0x8bb7);
          bVar2 = *(byte *)(iVar6 + 0x8bb8);
          bVar17 = (byte)(bVar1 + bVar2 + -0x34) != *(char *)(iVar6 + 0x8bb9);
          if (bVar17) {
            DAT_00793514 = 1;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (bVar17 || (bVar2 >> (bVar1 & 7) & 1) != 1) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar6 == 0) {
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
            else {
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = FUN_0053753c();
          }
          else {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar6 == 0) {
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
            else {
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = FUN_0053753c();
          }
        }
        else {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar6 == 0) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          else {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = FUN_0053753c();
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = FUN_0053753c();
        pcStack_a28 = (char *)((int)piStack_a24 - iVar5);
        *(undefined4 *)((int)piStack_a2c + 0x80) = 0x3ba3d70a;
        *(undefined4 *)((int)piStack_a2c + 0x84) = 0x3ba3d70a;
        *(undefined4 *)((int)piStack_a2c + 0x88) = 0x3f3d70a4;
        iVar6 = (int)piStack_a30 + iVar6;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = PeekPacketChecksumState();
        uStack_a20 = (int *)CONCAT13(iVar5 == 0,(undefined3)uStack_a20);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uStack_a38 = iVar5 == 0;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar5 == 2) {
LAB_004c6daa:
          uStack_a38 = uStack_a20._3_1_ == '\0';
        }
        else {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar5 == 0xf) goto LAB_004c6daa;
        }
        iVar5 = *(int *)(g_clientContext + 0x621e0);
        if (*(int *)(g_clientContext + 0x621e4) == iVar5) {
          FUN_0040a500(iVar5 + 0x62f8,auStack_774);
          uStack_100 = 5;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = g_clientContext;
          FUN_004ecc70(iVar6,pcStack_a28,uStack_a38,*(undefined4 *)(g_clientContext + 0x227bc),
                       *(undefined4 *)(g_clientContext + 0x227bc),
                       *(int *)(*(int *)(g_clientContext + 0x621e0) + 0xbfe4) << 0x18 | 0xffffff);
          uStack_100 = 0xffffffff;
          if (iStack_760 != 0) {
            iVar5 = iStack_760 << 4;
            uStack_a38 = 0x10;
            do {
              iVar19 = _rand();
              *(char *)(iVar5 + DAT_0079376c) = (char)iVar19;
              iVar5 = iVar5 + 1;
              uStack_a38 = uStack_a38 - 1;
            } while (uStack_a38 != 0);
LAB_004c6f6d:
            uStack_a38 = 0;
            FUN_0040b540(&uStack_a38);
            iVar5 = g_clientContext;
          }
        }
        else {
          FUN_0040a500(iVar5 + 0x62f8,&piStack_a18);
          uStack_100 = 6;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = g_clientContext;
          FUN_004ecc70(iVar6,pcStack_a28,uStack_a38,0xc0,0xc0,
                       *(int *)(*(int *)(g_clientContext + 0x621e0) + 0xbfe4) << 0x18 | 0xffffff);
          uStack_100 = 0xffffffff;
          if (pcStack_a04 != (char *)0x0) {
            iVar5 = (int)pcStack_a04 << 4;
            uStack_a38 = 0x10;
            do {
              iVar19 = _rand();
              *(char *)(iVar5 + DAT_0079376c) = (char)iVar19;
              iVar5 = iVar5 + 1;
              uStack_a38 = uStack_a38 - 1;
            } while (uStack_a38 != 0);
            goto LAB_004c6f6d;
          }
        }
        if ((*(int *)(iVar5 + 0x227bc) == 0xc0) ||
           (*(int *)(iVar5 + 0x621e4) != *(int *)(iVar5 + 0x621e0))) {
          *(int *)(&DAT_006a64bc + iVar5) = iVar6;
          *(char **)(&DAT_006a64c0 + iVar5) = pcStack_a28;
          *(undefined4 *)((int)piStack_a2c + 0x88) = 0x3e800000;
          *(undefined4 *)((int)piStack_a2c + 0x80) = 0;
          *(undefined4 *)((int)piStack_a2c + 0x84) = 0x3f400000;
          iVar5 = *(int *)(iVar5 + 0x621e0);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          bVar1 = *(byte *)(iVar5 + 0x8bba);
          bVar2 = *(byte *)(iVar5 + 0x8bbb);
          bVar17 = (byte)(bVar1 + bVar2 + -0x34) != *(char *)(iVar5 + 0x8bbc);
          if (bVar17) {
            DAT_00793514 = 1;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (bVar17 || (bVar2 >> (bVar1 & 7) & 1) != 1) {
            iVar5 = *(int *)(g_clientContext + 0x621e0);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            bVar1 = *(byte *)(iVar5 + 0x8bb7);
            bVar2 = *(byte *)(iVar5 + 0x8bb8);
            bVar17 = (byte)(bVar1 + bVar2 + -0x34) != *(char *)(iVar5 + 0x8bb9);
            if (bVar17) {
              DAT_00793514 = 1;
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (bVar17 || (bVar2 >> (bVar1 & 7) & 1) != 1) {
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar5 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              if (iVar5 != 0) {
                EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                iVar5 = PeekPacketChecksumState();
                LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                goto LAB_004c72b1;
              }
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar5 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar5 = 0xb4 - iVar5;
              goto LAB_004c71a8;
            }
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar5 == 0) {
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar5 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar5 = 0xb4 - iVar5;
              goto LAB_004c71a8;
            }
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_004c72b1:
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar19 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          else {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar5 != 0) {
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar5 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              goto LAB_004c72b1;
            }
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = 0xb4 - iVar5;
LAB_004c71a8:
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar19 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar19 = 0xb4 - iVar19;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar7 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = iVar5 - iVar7;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar7 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar19 = iVar19 - iVar7;
          if (iVar5 < 0) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar7 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = iVar5 + iVar7;
          }
          if (0x10e < iVar5) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          if (iVar19 < 0) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar19 = iVar19 + iVar5;
          }
          if (0x10e < iVar19) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          FUN_004ed300(iVar6,pcStack_a28,piStack_a2c,0x40,
                       *(int *)(*(int *)(g_clientContext + 0x621e0) + 0xbfe4) << 0x18 | 0xea16);
          cVar4 = FUN_004065a0();
          if (cVar4 == '\0') {
            cVar4 = FUN_004065a0();
            if (cVar4 == '\0') {
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar5 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              if (iVar5 != 0) {
                EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                iVar5 = PeekPacketChecksumState();
                LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                goto LAB_004c7670;
              }
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar5 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar5 = 0xb4 - iVar5;
              goto LAB_004c7566;
            }
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar5 == 0) {
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar5 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar5 = 0xb4 - iVar5;
              goto LAB_004c7566;
            }
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_004c7670:
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar19 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          else {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar5 != 0) {
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar5 = PeekPacketChecksumState();
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              goto LAB_004c7670;
            }
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = 0xb4 - iVar5;
LAB_004c7566:
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar19 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar19 = 0xb4 - iVar19;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar7 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = iVar5 - iVar7;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar7 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar19 = iVar19 - iVar7;
          if (iVar5 < 0) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar7 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = iVar5 + iVar7;
          }
          if (0x10e < iVar5) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          if (iVar19 < 0) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar19 = iVar19 + iVar5;
          }
          if (0x10e < iVar19) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          piVar8 = piStack_a2c;
          FUN_004ed300(iVar6,pcStack_a28,piStack_a2c,0x40,
                       *(int *)(*(int *)(g_clientContext + 0x621e0) + 0xbfe4) << 0x18 | 0xea16);
          *(undefined4 *)((int)piVar8 + 0x80) = 0x3f0147ae;
          *(undefined4 *)((int)piVar8 + 0x84) = 0x3f4147ae;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = g_clientContext;
          FUN_004ed0c0(iVar6,pcStack_a28,0,0x40,0x40);
        }
      }
    }
  }
  iVar6 = *(int *)(iVar5 + 0x621e4);
  if ((((iVar6 != 0) && (iVar19 = *(int *)(iVar5 + 0x621e0), iVar19 != 0)) && (iVar6 != iVar19)) &&
     (*(char *)(iVar6 + 0xbfe8) == '\x01')) {
    piStack_a30 = (int *)((-(uint)(*(int *)(iVar6 + 0xae2c) != *(int *)(iVar19 + 0xae2c)) & 0xfe45ea
                          ) + 0xc000ea16);
    uVar9 = FUN_0040a6e0(iVar6 + 0x90c,&piStack_a18,*(undefined4 *)(&DAT_006a7710 + iVar5));
    uStack_100 = 7;
    FUN_0040a5f0(uVar9,auStack_774,400);
    uStack_100 = 8;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    piStack_a24 = (int *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_100 = 7;
    if (iStack_760 != 0) {
      iVar5 = 0;
      iVar6 = iStack_760 * 0x10;
      do {
        iVar19 = _rand();
        *(char *)(iVar6 + DAT_0079376c + iVar5) = (char)iVar19;
        iVar5 = iVar5 + 1;
      } while (iVar5 < 0x10);
      FUN_0040b540(&uStack_a38);
    }
    uStack_100 = 0xffffffff;
    if (pcStack_a04 != (char *)0x0) {
      iVar6 = (int)pcStack_a04 << 4;
      iVar5 = 0x10;
      do {
        iVar19 = _rand();
        *(char *)(iVar6 + DAT_0079376c) = (char)iVar19;
        iVar6 = iVar6 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      FUN_0040b540(&uStack_a38);
    }
    uVar9 = FUN_0040a6e0(*(int *)(g_clientContext + 0x621e4) + 0xb30,auStack_550,
                         *(undefined4 *)(&DAT_006a7714 + g_clientContext));
    uStack_100 = 9;
    uVar9 = FUN_0040a5f0(uVar9,&piStack_a18,0x104);
    uStack_100 = 10;
    FUN_0040a5f0(uVar9,auStack_774,0x26);
    uStack_100 = 0xb;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_100 = 10;
    if (iStack_760 != 0) {
      iVar5 = iStack_760 << 4;
      uStack_a38 = 0x10;
      do {
        iVar19 = _rand();
        *(char *)(iVar5 + DAT_0079376c) = (char)iVar19;
        iVar5 = iVar5 + 1;
        uStack_a38 = uStack_a38 - 1;
      } while (uStack_a38 != 0);
      FUN_0040b540(&uStack_a38);
    }
    uStack_100 = 9;
    if (pcStack_a04 != (char *)0x0) {
      iVar5 = (int)pcStack_a04 << 4;
      iVar19 = 0x10;
      do {
        iVar7 = _rand();
        *(char *)(iVar5 + DAT_0079376c) = (char)iVar7;
        iVar5 = iVar5 + 1;
        iVar19 = iVar19 + -1;
      } while (iVar19 != 0);
      FUN_0040b540(&uStack_a38);
    }
    uStack_100 = 0xffffffff;
    if (iStack_53c != 0) {
      iVar5 = iStack_53c << 4;
      iVar19 = 0x10;
      do {
        iVar7 = _rand();
        *(char *)(iVar5 + DAT_0079376c) = (char)iVar7;
        iVar5 = iVar5 + 1;
        iVar19 = iVar19 + -1;
      } while (iVar19 != 0);
      FUN_0040b540(&uStack_a38);
    }
    cVar4 = FUN_004065a0();
    if (cVar4 == '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar5 == 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      else {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uStack_a38 = FUN_0053753c();
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar5 == 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      else {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uStack_a38 = FUN_0053753c();
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = FUN_0053753c();
    iVar19 = (int)piStack_a24 + uStack_a38;
    pcStack_a28 = (char *)(iVar6 - iVar5);
    *(undefined4 *)((int)piStack_a2c + 0x80) = 0x3ba3d70a;
    *(undefined4 *)((int)piStack_a2c + 0x84) = 0x3ba3d70a;
    *(undefined4 *)((int)piStack_a2c + 0x88) = 0x3f3d70a4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    uStack_a20 = (int *)CONCAT13(iVar6 == 0,(undefined3)uStack_a20);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_a38 = iVar6 == 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar6 == 2) {
LAB_004c7ef8:
      uStack_a38 = uStack_a20._3_1_ == '\0';
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar6 == 0xf) goto LAB_004c7ef8;
    }
    FUN_0040a500(*(int *)(g_clientContext + 0x621e4) + 0x62f8,auStack_32c);
    uStack_100 = 0xc;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = g_clientContext;
    FUN_004ecc70(iVar19,pcStack_a28,uStack_a38,*(undefined4 *)(g_clientContext + 0x227bc),
                 *(undefined4 *)(g_clientContext + 0x227bc),0xffffffff);
    uStack_100 = 0xffffffff;
    if (iStack_318 != 0) {
      iVar6 = iStack_318 << 4;
      uStack_a38 = 0x10;
      do {
        iVar5 = _rand();
        *(char *)(iVar6 + DAT_0079376c) = (char)iVar5;
        iVar6 = iVar6 + 1;
        uStack_a38 = uStack_a38 - 1;
      } while (uStack_a38 != 0);
      FUN_0040b540(&uStack_a38);
      iVar6 = g_clientContext;
    }
    if (*(int *)(iVar6 + 0x227bc) == 0xc0) {
      *(undefined4 *)((int)piStack_a2c + 0x88) = 0x3e800000;
      *(undefined4 *)((int)piStack_a2c + 0x80) = 0;
      *(undefined4 *)((int)piStack_a2c + 0x84) = 0x3f400000;
      cVar4 = FUN_004065a0();
      if (cVar4 == '\0') {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar6 != 0) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          goto LAB_004c81b3;
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_004c80a7:
        iVar6 = 0xb4 - iVar6;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = 0xb4 - iVar5;
      }
      else {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar6 == 0) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          goto LAB_004c80a7;
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_004c81b3:
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = iVar6 - iVar7;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = iVar5 - iVar7;
      if (iVar6 < 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = iVar6 + iVar7;
      }
      if (0x10e < iVar6) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      if (iVar5 < 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = iVar5 + iVar6;
      }
      if (0x10e < iVar5) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      FUN_004ed300(iVar19,pcStack_a28,piStack_a2c,0x40,piStack_a30);
      cVar4 = FUN_004065a0();
      if (cVar4 == '\0') {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar6 != 0) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          goto LAB_004c8498;
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_004c838b:
        iVar6 = 0xb4 - iVar6;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = 0xb4 - iVar5;
      }
      else {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar6 == 0) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          goto LAB_004c838b;
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_004c8498:
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = iVar6 - iVar7;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = iVar5 - iVar7;
      if (iVar6 < 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = iVar6 + iVar7;
      }
      if (0x10e < iVar6) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      if (iVar5 < 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = iVar5 + iVar6;
      }
      if (0x10e < iVar5) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      piVar8 = piStack_a2c;
      FUN_004ed300(iVar19,pcStack_a28,piStack_a2c,0x40,piStack_a30);
      *(undefined4 *)((int)piVar8 + 0x80) = 0x3f0147ae;
      *(undefined4 *)((int)piVar8 + 0x84) = 0x3f4147ae;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_004ed0c0(iVar19,pcStack_a28,0,0x40,0x40);
    }
  }
  (**(code **)(*g_pD3DDevice7 + 0x8c))
            (g_pD3DDevice7,0,*(undefined4 *)(*(int *)((int)piStack_a2c + 0x94) + 0x110));
LAB_004c865b:
  if (g_spriteVertexCount != 0) {
    DAT_0079365c = DAT_0079365c + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  iVar5 = g_clientContext;
  *(undefined4 *)(g_clientContext + 0x1fe6c) = 0xffffffff;
  *(undefined4 *)(iVar5 + 0x1fe70) = 0xffffffff;
  *(undefined4 *)(iVar5 + 0x1fe74) = 0xffffffff;
  *(undefined4 *)(iVar5 + 0x1fe78) = 0xffffffff;
  *(undefined4 *)(iVar5 + 0x1fe7c) = 0xffffffff;
  *(undefined4 *)(iVar5 + 0x1fe80) = 0xffffffff;
  *(undefined4 *)(iVar5 + 0x1fe84) = 0xffffffff;
  *(undefined4 *)(iVar5 + 0x1fe88) = 0xffffffff;
  iVar6 = iVar5 + 0x1ff04;
  puVar13 = (undefined4 *)(iVar5 + 0x20a4c);
  iVar19 = 0xf;
  do {
    iVar7 = 0;
    puVar10 = puVar13;
    do {
      *(undefined1 *)(iVar6 + iVar7) = *(undefined1 *)(iVar6 + -8 + iVar7);
      *puVar10 = puVar10[-0x30];
      puVar10[1] = puVar10[-0x2f];
      puVar10[2] = puVar10[-0x2e];
      puVar10[3] = puVar10[-0x2d];
      puVar10[4] = puVar10[-0x2c];
      puVar10[5] = puVar10[-0x2b];
      iVar7 = iVar7 + 1;
      puVar10 = puVar10 + 6;
    } while (iVar7 < 8);
    puVar13 = puVar13 + -0x30;
    iVar6 = iVar6 + -8;
    iVar19 = iVar19 + -1;
  } while (iVar19 != 0);
  *(undefined4 *)(iVar5 + 0x1fe8c) = 0;
  *(undefined4 *)(iVar5 + 0x1fe90) = 0;
  iVar6 = iVar5 + 0x20c14;
  puVar13 = (undefined4 *)(iVar5 + 0x214e8);
  iVar19 = 7;
  do {
    iVar7 = 0;
    puVar10 = puVar13;
    do {
      *(undefined1 *)(iVar7 + iVar6) = *(undefined1 *)(iVar7 + -0x10 + iVar6);
      puVar10[-1] = puVar10[-0x51];
      *puVar10 = puVar10[-0x50];
      puVar10[1] = puVar10[-0x4f];
      puVar10[2] = puVar10[-0x4e];
      puVar10[3] = puVar10[-0x4d];
      iVar7 = iVar7 + 1;
      puVar10 = puVar10 + 5;
    } while (iVar7 < 0x10);
    puVar13 = puVar13 + -0x50;
    iVar6 = iVar6 + -0x10;
    iVar19 = iVar19 + -1;
  } while (iVar19 != 0);
  *(undefined4 *)(iVar5 + 0x20ba4) = 0;
  *(undefined4 *)(iVar5 + 0x20ba8) = 0;
  *(undefined4 *)(iVar5 + 0x20bac) = 0;
  *(undefined4 *)(iVar5 + 0x20bb0) = 0;
  *(undefined4 *)(iVar5 + 0x21644) = 0;
  *(undefined4 *)(iVar5 + 0x21648) = 0;
  *(undefined4 *)(iVar5 + 0x2164c) = 0;
  *(undefined4 *)(iVar5 + 0x21650) = 0;
  *(undefined4 *)(iVar5 + 0x21714) = 0;
  *(undefined4 *)(iVar5 + 0x21748) = 0;
  *(undefined4 *)(iVar5 + 0x2174c) = 0;
  *(undefined4 *)(iVar5 + 0x21750) = 0;
  *(undefined4 *)(iVar5 + 0x21754) = 0;
  *(undefined4 *)(iVar5 + 0x227a8) = 0;
  *(undefined1 *)(iVar5 + 0x22d24) = 0;
  *(undefined4 *)(iVar5 + 0x20b0c) = 0;
  *(undefined4 *)(iVar5 + 0x20b10) = 0;
  *(undefined1 *)(iVar5 + 0x23244) = 0;
  *(undefined4 *)(iVar5 + 0x22d33) = 0;
  *(undefined4 *)(iVar5 + 0x22d37) = 0;
  *(undefined4 *)(iVar5 + 0x22d3b) = 0;
  *(undefined4 *)(iVar5 + 0x22d3f) = 0;
  if (*(char *)((int)pcStack_a28 + 0x11d0) != '\0') {
    _DAT_00792194 = 1;
    FUN_004ed5a0(0,0,799,0,799,599,0,599,0,0,0,0,0x80000000,0x80000000);
  }
  *unaff_FS_OFFSET = uStack_114;
  return;
}

