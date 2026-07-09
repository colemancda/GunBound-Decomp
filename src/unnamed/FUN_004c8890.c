/* FUN_004c8890 - 0x004c8890 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x004c9c36) */
/* WARNING: Removing unreachable block (ram,0x004c9c40) */

void __fastcall FUN_004c8890(int param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int *piVar12;
  bool bVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  uint uStack_a4;
  int iStack_a0;
  char *pcStack_9c;
  char *pcStack_94;
  byte *pbStack_90;
  ushort *puStack_8c;
  char acStack_80 [128];
  
  if (*(int *)(g_clientContext + 0x621e0) != 0) {
    FUN_00463630(*(int *)(g_clientContext + 0x621e0));
  }
  FUN_00450dd0();
  pbStack_90 = (byte *)(g_clientContext + 0x58c4a);
  pcStack_9c = (char *)(g_clientContext + 0x58bbe);
  puStack_8c = (ushort *)(g_clientContext + 0x5917c);
  iVar6 = -0x58b8b - g_clientContext;
  pcStack_94 = (char *)(g_clientContext + 0x58b64);
  iVar7 = -0x58b8c - g_clientContext;
  uStack_a4 = 10;
  uVar14 = uStack_ac;
LAB_004c8921:
  if (*puStack_8c != 0) {
    uVar10 = *puStack_8c - 1;
    if ((DAT_0079352c != 0) && (-1 < (int)uVar10)) {
      iVar5 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar11 = *(uint *)(iVar5 + 4);
      while (uVar11 < 0x35) {
        if (uVar11 == 0x34) {
          iVar5 = *(int *)(iVar5 + 0x10);
          uVar11 = *(uint *)(iVar5 + 8);
          if (uVar11 <= uVar10) goto LAB_004c897e;
          break;
        }
        iVar5 = *(int *)(iVar5 + 0x1c);
        uVar11 = *(uint *)(iVar5 + 4);
      }
    }
  }
  goto LAB_004c89b9;
  while( true ) {
    iVar5 = *(int *)(iVar5 + 0x10);
    uVar11 = *(uint *)(iVar5 + 8);
    if (uVar10 < uVar11) break;
LAB_004c897e:
    if (uVar11 == uVar10) {
      if (*(char *)(iVar5 + 0x18) == '\x01') {
        BlitSprite16bpp(0x14,pcStack_9c + iVar7);
      }
      else {
        BlitSpriteClipped(uVar10);
      }
      break;
    }
  }
LAB_004c89b9:
  uVar8 = 0x1f;
  switch(*pbStack_90) {
  case 0:
    uStack_b0 = 0xffff;
    goto LAB_004c8a87;
  case 1:
    uStack_b0 = 0xc618;
    goto LAB_004c8a87;
  case 2:
    uStack_b0 = 0;
    uVar14 = 0xffe0;
    uStack_ac = uVar14;
    break;
  case 3:
    uStack_b0 = 0xf800;
    goto LAB_004c8a87;
  case 4:
    uVar14 = 0xafff;
    uStack_b0 = 0xf0;
    uStack_ac = uVar14;
    break;
  case 5:
    uStack_b0 = 0;
    uVar14 = 0xc7f8;
    uStack_ac = uVar14;
    break;
  case 6:
  case 8:
    uStack_b0 = 0x8000;
    uVar14 = 0xf800;
    uStack_ac = uVar14;
    break;
  case 7:
    uVar14 = 0x78e0;
    uStack_b0 = 0xfdb4;
    uVar8 = 0;
    uStack_ac = uVar14;
    break;
  case 9:
    uStack_b0 = 0x400;
    uVar14 = 0xfff2;
    uStack_ac = uVar14;
    break;
  case 10:
    uVar14 = 0xf800;
    uStack_b0 = 0xfebf;
    uStack_ac = uVar14;
    break;
  case 0xb:
    uVar14 = 0xfc20;
    uStack_b0 = 0x4880;
    uStack_ac = uVar14;
    break;
  case 0xc:
    uVar14 = 0x7e0;
    uStack_b0 = 0x210a;
    uStack_ac = uVar14;
    break;
  case 0xd:
    uVar14 = 0x1f;
    uStack_b0 = 0xf6bf;
    uStack_ac = uVar14;
    break;
  case 0xe:
    uVar14 = 0xc018;
    uStack_b0 = 0xfecf;
    uStack_ac = uVar14;
    break;
  case 0xf:
    uVar14 = 0;
    uStack_b0 = 0xffff;
    uStack_ac = uVar14;
    break;
  case 0x10:
    uStack_b0 = 0;
LAB_004c8a87:
    uVar8 = 0x1f;
    uVar14 = 0xffff;
    uStack_ac = uVar14;
  }
  pcVar4 = pcStack_9c + iVar7;
  FUN_004eb510(pcVar4,uVar8);
  BlitRLESprite(pcVar4,uStack_b0);
  pcVar3 = pcStack_94;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  if ((*pbStack_90 < 2) || (*pbStack_90 == 7)) {
    BlitRLESprite(pcStack_9c + iVar6,0);
    BlitRLESprite(pcVar4,uStack_b0);
    pcVar3 = pcStack_9c;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    BlitRLESprite(pcStack_9c + iVar6,0);
    BlitRLESprite(pcVar4,uStack_b0);
    uVar14 = uStack_ac;
  }
  else {
    FUN_004eb510(pcVar4,uStack_b0);
    BlitRLESprite(pcVar4,uVar14);
    pcVar4 = pcStack_9c;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    FUN_004eb510(pcStack_9c + iVar6,uStack_b0);
    BlitRLESprite(pcStack_9c + iVar6,uVar14);
  }
  puStack_8c = puStack_8c + 1;
  pcStack_94 = pcStack_94 + 9;
  pbStack_90 = pbStack_90 + 1;
  pcStack_9c = pcStack_9c + 0xe;
  uStack_a4 = uStack_a4 + -1;
  if (uStack_a4 == 0) goto code_r0x004c8c08;
  goto LAB_004c8921;
code_r0x004c8c08:
  iStack_a0 = 0;
  if (0 < *(int *)(param_1 + 0x98)) {
    piVar12 = (int *)(param_1 + 0x69c);
LAB_004c8c40:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = ((-(uint)(*(char *)(*piVar12 + 0x50126 + g_clientContext) !=
                      *(char *)(g_clientContext + 0x3b6c0)) & 6) + 5 + piVar12[-0x180]) - iVar6;
    if ((DAT_0079352c != 0) && (-1 < (int)uVar10)) {
      iVar6 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar11 = *(uint *)(iVar6 + 4);
      while (uVar11 < 0x2329) {
        if (uVar11 == 9000) {
          iVar6 = *(int *)(iVar6 + 0x10);
          uVar11 = *(uint *)(iVar6 + 8);
          if (uVar11 <= uVar10) goto LAB_004c8ce0;
          break;
        }
        iVar6 = *(int *)(iVar6 + 0x1c);
        uVar11 = *(uint *)(iVar6 + 4);
      }
    }
    goto LAB_004c8d14;
  }
LAB_004c8d32:
  iStack_a0 = 0;
  if (0 < *(int *)(param_1 + 0x89c)) {
    piVar12 = (int *)(param_1 + 0xca0);
LAB_004c8d54:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = ((-(uint)(*(char *)(*piVar12 + 0x50126 + g_clientContext) !=
                      *(char *)(g_clientContext + 0x3b6c0)) & 6) + 5 + piVar12[-0x100]) - iVar6;
    if ((DAT_0079352c != 0) && (-1 < (int)uVar10)) {
      iVar6 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar11 = *(uint *)(iVar6 + 4);
      while (uVar11 < 0x2329) {
        if (uVar11 == 9000) {
          iVar6 = *(int *)(iVar6 + 0x10);
          uVar11 = *(uint *)(iVar6 + 8);
          if (uVar11 <= uVar10) goto LAB_004c8df4;
          break;
        }
        iVar6 = *(int *)(iVar6 + 0x1c);
        uVar11 = *(uint *)(iVar6 + 4);
      }
    }
    goto LAB_004c8e28;
  }
LAB_004c8edb:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (-1 < iVar6 + -1) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
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
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar6 - iVar7 < 1) {
      uStack_a4 = 1;
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uStack_a4 = iVar6 - iVar7;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = *(int *)(param_1 + 8) % 7 + 0x12;
    if ((DAT_0079352c != 0) && (-1 < (int)uVar11)) {
      iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar2 = *(uint *)(iVar7 + 4);
      while (uVar2 < 0x1b59) {
        if (uVar2 == 7000) {
          iVar7 = *(int *)(iVar7 + 0x10);
          uVar2 = *(uint *)(iVar7 + 8);
          if (uVar2 <= uVar11) goto LAB_004c9ad7;
          break;
        }
        iVar7 = *(int *)(iVar7 + 0x1c);
        uVar2 = *(uint *)(iVar7 + 4);
      }
    }
    goto LAB_004c9b12;
  }
  if (iVar6 == 1) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar6 - iVar7 < 1) {
      uStack_a4 = 1;
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uStack_a4 = iVar6 - iVar7;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = *(int *)(param_1 + 8) % 7 + 0x12;
    if ((DAT_0079352c != 0) && (-1 < (int)uVar11)) {
      iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar2 = *(uint *)(iVar7 + 4);
      while (uVar2 < 0x1b59) {
        if (uVar2 == 7000) {
          iVar7 = *(int *)(iVar7 + 0x10);
          uVar2 = *(uint *)(iVar7 + 8);
          if (uVar2 <= uVar11) goto LAB_004c96d9;
          break;
        }
        iVar7 = *(int *)(iVar7 + 0x1c);
        uVar2 = *(uint *)(iVar7 + 4);
      }
    }
    goto LAB_004c9714;
  }
  if (iVar6 == 2) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar6 - iVar7 < 1) {
      uStack_a4 = 1;
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uStack_a4 = iVar6 - iVar7;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = *(int *)(param_1 + 8) % 7 + 0x12;
    if ((DAT_0079352c != 0) && (-1 < (int)uVar11)) {
      iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar2 = *(uint *)(iVar7 + 4);
      while (uVar2 < 0x1b59) {
        if (uVar2 == 7000) {
          iVar7 = *(int *)(iVar7 + 0x10);
          uVar2 = *(uint *)(iVar7 + 8);
          if (uVar2 <= uVar11) goto LAB_004c92db;
          break;
        }
        iVar7 = *(int *)(iVar7 + 0x1c);
        uVar2 = *(uint *)(iVar7 + 4);
      }
    }
    goto LAB_004c9316;
  }
  goto LAB_004c9ba8;
  while( true ) {
    iVar6 = *(int *)(iVar6 + 0x10);
    uVar11 = *(uint *)(iVar6 + 8);
    if (uVar10 < uVar11) break;
LAB_004c8ce0:
    if (uVar11 == uVar10) {
      if (*(char *)(iVar6 + 0x18) == '\x01') {
        BlitSprite16bpp((piVar12[-0x100] - *(int *)(&DAT_006a7710 + g_clientContext)) + 400,0x24);
      }
      else {
        BlitSpriteClipped(uVar10);
      }
      break;
    }
  }
LAB_004c8d14:
  iStack_a0 = iStack_a0 + 1;
  piVar12 = piVar12 + 1;
  if (*(int *)(param_1 + 0x98) <= iStack_a0) goto LAB_004c8d32;
  goto LAB_004c8c40;
  while( true ) {
    iVar6 = *(int *)(iVar6 + 0x10);
    uVar11 = *(uint *)(iVar6 + 8);
    if (uVar10 < uVar11) break;
LAB_004c8df4:
    if (uVar11 == uVar10) {
      if (*(char *)(iVar6 + 0x18) == '\x01') {
        BlitSprite16bpp((piVar12[-0x80] - *(int *)(&DAT_006a7710 + g_clientContext)) + 400,0x24);
      }
      else {
        BlitSpriteClipped(uVar10);
      }
      break;
    }
  }
LAB_004c8e28:
  pcVar4 = (char *)(*piVar12 * 0xd + 0x50196 + g_clientContext);
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  BlitRLESprite(0x2d,(-(uint)(*(char *)(*piVar12 + 0x50126 + g_clientContext) !=
                             *(char *)(g_clientContext + 0x3b6c0)) & 0xfffffae9) + 0xffff);
  FUN_004eb510(0x2d,0);
  iStack_a0 = iStack_a0 + 1;
  piVar12 = piVar12 + 1;
  if (*(int *)(param_1 + 0x89c) <= iStack_a0) goto LAB_004c8edb;
  goto LAB_004c8d54;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar2 = *(uint *)(iVar7 + 8);
    if (uVar11 < uVar2) break;
LAB_004c9ad7:
    if (uVar2 == uVar11) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(((uVar10 % uStack_a4 + iVar6) - *(int *)(&DAT_006a7710 + g_clientContext)) +
                        400,0x24);
      }
      else {
        BlitSpriteClipped(uVar11);
      }
      break;
    }
  }
LAB_004c9b12:
  pcVar4 = (char *)FUN_0043dc70(&DAT_00796eec,0x33e);
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  uVar14 = 0;
  FUN_0043dc70(&DAT_00796eec,0x33e);
  FUN_004eb510(0x28,uVar14);
  uVar14 = 0xffff;
  FUN_0043dc70(&DAT_00796eec,0x33e);
  BlitRLESprite(0x28,uVar14);
  goto LAB_004c9ba8;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar2 = *(uint *)(iVar7 + 8);
    if (uVar11 < uVar2) break;
LAB_004c96d9:
    if (uVar2 == uVar11) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(((uVar10 % uStack_a4 + iVar6) - *(int *)(&DAT_006a7710 + g_clientContext)) +
                        400,0x24);
      }
      else {
        BlitSpriteClipped(uVar11);
      }
      break;
    }
  }
LAB_004c9714:
  pcVar4 = (char *)FUN_0043dc70(&DAT_00796eec,0x33f);
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  uVar14 = 0;
  FUN_0043dc70(&DAT_00796eec,0x33f);
  FUN_004eb510(0x28,uVar14);
  uVar14 = 0xffff;
  FUN_0043dc70(&DAT_00796eec,0x33f);
  BlitRLESprite(0x28,uVar14);
  goto LAB_004c9ba8;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar2 = *(uint *)(iVar7 + 8);
    if (uVar11 < uVar2) break;
LAB_004c92db:
    if (uVar2 == uVar11) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(((uVar10 % uStack_a4 + iVar6) - *(int *)(&DAT_006a7710 + g_clientContext)) +
                        400,0x24);
      }
      else {
        BlitSpriteClipped(uVar11);
      }
      break;
    }
  }
LAB_004c9316:
  pcVar4 = (char *)FUN_0043dc70(&DAT_00796eec,0x340);
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  uVar14 = 0;
  FUN_0043dc70(&DAT_00796eec,0x340);
  FUN_004eb510(0x28,uVar14);
  uVar14 = 0xffff;
  FUN_0043dc70(&DAT_00796eec,0x340);
  BlitRLESprite(0x28,uVar14);
LAB_004c9ba8:
  if ((*(int *)(param_1 + 0x10cc) != -1) && (*(int *)(param_1 + 0x10d0) != -1)) {
    FUN_004cfd20();
  }
  if ((*(int *)(param_1 + 0x10c4) != -1) && (*(int *)(param_1 + 0x10c8) != -1)) {
    FUN_004cfb20();
  }
  FUN_004eadb0();
  FUN_004e93e0(3);
  FUN_00408180(&DAT_006a647c + g_clientContext);
  iVar6 = g_clientContext;
  if ((*(char *)(param_1 + 0x11ac) != '\0') && (*(char *)(param_1 + 0x11d0) == '\0')) {
    if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
      iVar7 = *(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
      uVar10 = *(uint *)(iVar7 + 8);
      while (uVar10 < 0xf) {
        if (uVar10 == 0xe) {
          if (*(int *)(iVar7 + 0x24) != 3) {
            if (DAT_0079352c == 0) goto LAB_004c9d19;
            iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
            uVar10 = *(uint *)(iVar7 + 4);
            goto joined_r0x004c9d02;
          }
          break;
        }
        iVar7 = *(int *)(iVar7 + 0x10);
        uVar10 = *(uint *)(iVar7 + 8);
      }
    }
    *(undefined1 *)(param_1 + 0x11ac) = 0;
  }
  goto LAB_004c9c72;
joined_r0x004c9d02:
  if (0x3f3 < uVar10) goto LAB_004c9d19;
  if (uVar10 == 0x3f3) {
    iVar7 = *(int *)(iVar7 + 0x10);
    bVar13 = true;
    if (*(int *)(iVar7 + 8) == 0) goto LAB_004c9d76;
    goto LAB_004c9d19;
  }
  iVar7 = *(int *)(iVar7 + 0x1c);
  uVar10 = *(uint *)(iVar7 + 4);
  goto joined_r0x004c9d02;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    bVar13 = *(int *)(iVar7 + 8) == 0;
    if (!bVar13) break;
LAB_004c9d76:
    if (bVar13) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(8,0x2d);
      }
      else {
        BlitSpriteClipped(0);
      }
      break;
    }
  }
LAB_004c9d19:
  cVar1 = (&DAT_005f2f40)[iVar6];
  if (cVar1 == '\0') {
    if (DAT_0079352c != 0) {
      iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar10 = *(uint *)(iVar7 + 4);
      while (uVar10 < 0x3f4) {
        if (uVar10 == 0x3f3) {
          iVar7 = *(int *)(iVar7 + 0x10);
          uVar10 = *(uint *)(iVar7 + 8);
          if (uVar10 < 2) goto LAB_004c9ebe;
          break;
        }
        iVar7 = *(int *)(iVar7 + 0x1c);
        uVar10 = *(uint *)(iVar7 + 4);
      }
    }
  }
  else if (cVar1 == '\x01') {
    if (DAT_0079352c != 0) {
      iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar10 = *(uint *)(iVar7 + 4);
      while (uVar10 < 0x3f4) {
        if (uVar10 == 0x3f3) {
          iVar7 = *(int *)(iVar7 + 0x10);
          uVar10 = *(uint *)(iVar7 + 8);
          if (uVar10 < 2) goto LAB_004c9e56;
          break;
        }
        iVar7 = *(int *)(iVar7 + 0x1c);
        uVar10 = *(uint *)(iVar7 + 4);
      }
    }
  }
  else if ((cVar1 == '\x02') && (DAT_0079352c != 0)) {
    iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar10 = *(uint *)(iVar7 + 4);
    while (uVar10 < 0x3f4) {
      if (uVar10 == 0x3f3) {
        iVar7 = *(int *)(iVar7 + 0x10);
        uVar10 = *(uint *)(iVar7 + 8);
        if (uVar10 < 2) goto LAB_004c9ddb;
        break;
      }
      iVar7 = *(int *)(iVar7 + 0x1c);
      uVar10 = *(uint *)(iVar7 + 4);
    }
  }
  goto LAB_004c9ef9;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar10 = *(uint *)(iVar7 + 8);
    if (1 < uVar10) break;
LAB_004c9ebe:
    if (uVar10 == 1) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004c9eeb;
      BlitSprite16bpp(0x71,0x72);
      break;
    }
  }
  goto LAB_004c9ef9;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar10 = *(uint *)(iVar7 + 8);
    if (1 < uVar10) break;
LAB_004c9e56:
    if (uVar10 == 1) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004c9eeb;
      BlitSprite16bpp(0xc6,0x72);
      break;
    }
  }
  goto LAB_004c9ef9;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar10 = *(uint *)(iVar7 + 8);
    if (1 < uVar10) break;
LAB_004c9ddb:
    if (uVar10 == 1) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(0x1d,0x72);
      }
      else {
LAB_004c9eeb:
        BlitSpriteClipped(1);
      }
      break;
    }
  }
LAB_004c9ef9:
  switch(*(int *)(&DAT_005f2f44 + iVar6) / 10) {
  case 2:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(0x27,0xa8);
      }
      else {
LAB_004ca0d3:
        BlitSpriteClipped(1);
      }
    }
    break;
  case 3:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca0d3;
      BlitSprite16bpp(0x4f,0xa8);
    }
    break;
  case 4:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca0d3;
      BlitSprite16bpp(0x77,0xa8);
    }
    break;
  case 5:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca0d3;
      BlitSprite16bpp(0x9f,0xa8);
    }
    break;
  case 6:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca0d3;
      BlitSprite16bpp(199,0xa8);
    }
    break;
  case 7:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca0d3;
      BlitSprite16bpp(0xef,0xa8);
    }
  }
  if ((&DAT_005f2f48)[iVar6] == '\0') {
    if (DAT_0079352c != 0) {
      iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar10 = *(uint *)(iVar7 + 4);
      while (uVar10 < 0x3f4) {
        if (uVar10 == 0x3f3) {
          iVar7 = *(int *)(iVar7 + 0x10);
          uVar10 = *(uint *)(iVar7 + 8);
          if (uVar10 < 2) goto LAB_004ca19e;
          break;
        }
        iVar7 = *(int *)(iVar7 + 0x1c);
        uVar10 = *(uint *)(iVar7 + 4);
      }
    }
  }
  else if (DAT_0079352c != 0) {
    iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar10 = *(uint *)(iVar7 + 4);
    while (uVar10 < 0x3f4) {
      if (uVar10 == 0x3f3) {
        iVar7 = *(int *)(iVar7 + 0x10);
        uVar10 = *(uint *)(iVar7 + 8);
        if (uVar10 < 2) goto LAB_004ca133;
        break;
      }
      iVar7 = *(int *)(iVar7 + 0x1c);
      uVar10 = *(uint *)(iVar7 + 4);
    }
  }
LAB_004ca1dc:
  switch(*(undefined4 *)(&DAT_005f2f4c + iVar6)) {
  case 0:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(0x59,0xf8);
      }
      else {
LAB_004ca3ad:
        BlitSpriteClipped(1);
      }
    }
    break;
  case 0x50:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca3ad;
      BlitSprite16bpp(0x77,0xf8);
    }
    break;
  case 0x5a:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca3ad;
      BlitSprite16bpp(0x95,0xf8);
    }
    break;
  case 0x5f:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca3ad;
      BlitSprite16bpp(0xb3,0xf8);
    }
    break;
  case 0x62:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca3ad;
      BlitSprite16bpp(0xd1,0xf8);
    }
    break;
  case 100:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca3ad;
      BlitSprite16bpp(0xef,0xf8);
    }
  }
  switch(*(undefined4 *)(&DAT_005f2f50 + iVar6)) {
  case 0:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(0x59,0x112);
      }
      else {
LAB_004ca58c:
        BlitSpriteClipped(1);
      }
    }
    break;
  case 0x50:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca58c;
      BlitSprite16bpp(0x77,0x112);
    }
    break;
  case 0x5a:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca58c;
      BlitSprite16bpp(0x95,0x112);
    }
    break;
  case 0x5f:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca58c;
      BlitSprite16bpp(0xb3,0x112);
    }
    break;
  case 0x62:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca58c;
      BlitSprite16bpp(0xd1,0x112);
    }
    break;
  case 100:
    if ((DAT_0079352c != 0) && (iVar7 = FindSpriteFrame(), iVar7 != 0)) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca58c;
      BlitSprite16bpp(0xef,0x112);
    }
  }
  cVar1 = (&DAT_005f2f54)[iVar6];
  if (cVar1 == '\x01') {
    if (DAT_0079352c != 0) {
      iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar10 = *(uint *)(iVar7 + 4);
      while (uVar10 < 0x3f4) {
        if (uVar10 == 0x3f3) {
          iVar7 = *(int *)(iVar7 + 0x10);
          uVar10 = *(uint *)(iVar7 + 8);
          if (uVar10 < 2) goto LAB_004ca6f1;
          break;
        }
        iVar7 = *(int *)(iVar7 + 0x1c);
        uVar10 = *(uint *)(iVar7 + 4);
      }
    }
  }
  else if (cVar1 == '\x02') {
    if (DAT_0079352c != 0) {
      iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar10 = *(uint *)(iVar7 + 4);
      while (uVar10 < 0x3f4) {
        if (uVar10 == 0x3f3) {
          iVar7 = *(int *)(iVar7 + 0x10);
          uVar10 = *(uint *)(iVar7 + 8);
          if (uVar10 < 2) goto LAB_004ca680;
          break;
        }
        iVar7 = *(int *)(iVar7 + 0x1c);
        uVar10 = *(uint *)(iVar7 + 4);
      }
    }
  }
  else if ((cVar1 == '\x03') && (DAT_0079352c != 0)) {
    iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar10 = *(uint *)(iVar7 + 4);
    while (uVar10 < 0x3f4) {
      if (uVar10 == 0x3f3) {
        iVar7 = *(int *)(iVar7 + 0x10);
        uVar10 = *(uint *)(iVar7 + 8);
        if (uVar10 < 2) goto LAB_004ca5fd;
        break;
      }
      iVar7 = *(int *)(iVar7 + 0x1c);
      uVar10 = *(uint *)(iVar7 + 4);
    }
  }
LAB_004ca732:
  if ((&DAT_005f2f55)[iVar6] == '\0') {
    if (DAT_0079352c != 0) {
      iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar10 = *(uint *)(iVar7 + 4);
      while (uVar10 < 0x3f4) {
        if (uVar10 == 0x3f3) {
          iVar7 = *(int *)(iVar7 + 0x10);
          uVar10 = *(uint *)(iVar7 + 8);
          if (uVar10 < 2) goto LAB_004ca813;
          break;
        }
        iVar7 = *(int *)(iVar7 + 0x1c);
        uVar10 = *(uint *)(iVar7 + 4);
      }
    }
  }
  else if (DAT_0079352c != 0) {
    iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar10 = *(uint *)(iVar7 + 4);
    while (uVar10 < 0x3f4) {
      if (uVar10 == 0x3f3) {
        iVar7 = *(int *)(iVar7 + 0x10);
        uVar10 = *(uint *)(iVar7 + 8);
        if (uVar10 < 2) goto LAB_004ca787;
        break;
      }
      iVar7 = *(int *)(iVar7 + 0x1c);
      uVar10 = *(uint *)(iVar7 + 4);
    }
  }
LAB_004c9c72:
  if (*(char *)(param_1 + 0x11d0) == '\0') {
    FUN_004e2b20();
    iVar6 = g_clientContext;
  }
  if (((*(char *)(param_1 + 0x11c5) != '\0') && (*(char *)(param_1 + 0x11d0) == '\0')) &&
     (DAT_0079352c != 0)) {
    iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar10 = *(uint *)(iVar7 + 4);
    while (uVar10 < 0x1b59) {
      if (uVar10 == 7000) {
        iVar7 = *(int *)(iVar7 + 0x10);
        uVar10 = *(uint *)(iVar7 + 8);
        if (uVar10 < 0xf) goto LAB_004ca86a;
        break;
      }
      iVar7 = *(int *)(iVar7 + 0x1c);
      uVar10 = *(uint *)(iVar7 + 4);
    }
  }
LAB_004ca8b0:
  if (*(char *)(param_1 + 0x93) == '\0') {
LAB_004ca958:
    if (*(char *)(param_1 + 0x11d0) == '\0') {
      return;
    }
  }
  else if (*(char *)(param_1 + 0x11d0) == '\0') {
    if (DAT_0079352c != 0) {
      iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar10 = *(uint *)(iVar7 + 4);
      while (uVar10 < 0x1b59) {
        if (uVar10 == 7000) {
          iVar7 = *(int *)(iVar7 + 0x10);
          uVar10 = *(uint *)(iVar7 + 8);
          if (uVar10 < 0xaf) goto LAB_004ca90c;
          break;
        }
        iVar7 = *(int *)(iVar7 + 0x1c);
        uVar10 = *(uint *)(iVar7 + 4);
      }
    }
    goto LAB_004ca958;
  }
  if (*(char *)(param_1 + 0x11d8) != '\0') {
    pcVar4 = (char *)FUN_0043dc70(&DAT_00796eec,0x280);
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    uVar15 = 1;
    uVar8 = 0;
    uVar14 = FUN_0043dc70(&DAT_00796eec,0x280);
    FUN_0041b8c0(g_clientContext,2,0,0,uVar14,uVar8,uVar15);
    FUN_0041b8c0(g_clientContext,2,0,0,&DAT_0054b460,0,1);
    if (*(char *)(g_clientContext + 0x62155) == '\0') {
      pcVar3 = (char *)FUN_0043dc70(&DAT_00796eec,0x27c);
      pcVar4 = acStack_80;
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
        *pcVar4 = cVar1;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
    }
    else {
      pcVar3 = (char *)FUN_0043dc70(&DAT_00796eec,0x27d);
      pcVar4 = acStack_80;
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
        *pcVar4 = cVar1;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
    }
    pcVar4 = acStack_80;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    FUN_0041b8c0(g_clientContext,2,0,0,acStack_80,0,1);
    iVar6 = g_clientContext;
  }
  uVar10 = (uint)(*(char *)(iVar6 + 0x62155) == '\0');
  if (DAT_0079352c != 0) {
    iVar6 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar6 + 4);
    while (uVar11 < 0x232a) {
      if (uVar11 == 0x2329) {
        iVar6 = *(int *)(iVar6 + 0x10);
        uVar11 = *(uint *)(iVar6 + 8);
        if (uVar11 <= uVar10) goto LAB_004caa9a;
        break;
      }
      iVar6 = *(int *)(iVar6 + 0x1c);
      uVar11 = *(uint *)(iVar6 + 4);
    }
  }
LAB_004caad3:
  iVar7 = 0;
  iVar6 = 0x97;
LAB_004caade:
  iVar9 = 0;
  iVar5 = 0;
  do {
    if ((*(char *)(g_clientContext + 0x50126 + iVar5) == '\0') &&
       (*(char *)(iVar5 + 0x5010d + g_clientContext) != '\0')) {
      if (iVar7 == iVar9) goto LAB_004cab11;
      iVar9 = iVar9 + 1;
    }
    iVar5 = iVar5 + 1;
    if (7 < iVar5) goto LAB_004cab43;
  } while( true );
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar10 = *(uint *)(iVar7 + 8);
    if (1 < uVar10) break;
LAB_004ca19e:
    if (uVar10 == 1) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca1ce;
      BlitSprite16bpp(0x23,0xda);
      break;
    }
  }
  goto LAB_004ca1dc;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar10 = *(uint *)(iVar7 + 8);
    if (1 < uVar10) break;
LAB_004ca133:
    if (uVar10 == 1) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(0xd6,0xda);
      }
      else {
LAB_004ca1ce:
        BlitSpriteClipped(1);
      }
      break;
    }
  }
  goto LAB_004ca1dc;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar10 = *(uint *)(iVar7 + 8);
    if (1 < uVar10) break;
LAB_004ca6f1:
    if (uVar10 == 1) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca724;
      BlitSprite16bpp(0xc6,0x144);
      break;
    }
  }
  goto LAB_004ca732;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar10 = *(uint *)(iVar7 + 8);
    if (1 < uVar10) break;
LAB_004ca680:
    if (uVar10 == 1) {
      if (*(char *)(iVar7 + 0x18) != '\x01') goto LAB_004ca724;
      BlitSprite16bpp(0x71,0x144);
      break;
    }
  }
  goto LAB_004ca732;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar10 = *(uint *)(iVar7 + 8);
    if (1 < uVar10) break;
LAB_004ca5fd:
    if (uVar10 == 1) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(0x1d,0x144);
      }
      else {
LAB_004ca724:
        BlitSpriteClipped(1);
      }
      break;
    }
  }
  goto LAB_004ca732;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar10 = *(uint *)(iVar7 + 8);
    if (1 < uVar10) break;
LAB_004ca813:
    if (uVar10 == 1) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(0xdb,0x176);
      }
      else {
        BlitSpriteClipped(1);
      }
      break;
    }
  }
  goto LAB_004c9c72;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar10 = *(uint *)(iVar7 + 8);
    if (1 < uVar10) break;
LAB_004ca787:
    if (uVar10 == 1) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(0x23,0x176);
      }
      else {
        BlitSpriteClipped(1);
      }
      break;
    }
  }
  goto LAB_004c9c72;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar10 = *(uint *)(iVar7 + 8);
    if (0xe < uVar10) break;
LAB_004ca86a:
    if (uVar10 == 0xe) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(0xde,0x1e0);
      }
      else {
        BlitSpriteClipped(0xe);
      }
      break;
    }
  }
  goto LAB_004ca8b0;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar10 = *(uint *)(iVar7 + 8);
    if (0xae < uVar10) break;
LAB_004ca90c:
    if (uVar10 == 0xae) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(0xde,0x1e0);
      }
      else {
        BlitSpriteClipped(0xae);
      }
      break;
    }
  }
  goto LAB_004ca958;
  while( true ) {
    iVar6 = *(int *)(iVar6 + 0x10);
    uVar11 = *(uint *)(iVar6 + 8);
    if (uVar10 < uVar11) break;
LAB_004caa9a:
    if (uVar11 == uVar10) {
      if (*(char *)(iVar6 + 0x18) == '\x01') {
        BlitSprite16bpp(0x18,0x30);
      }
      else {
        BlitSpriteClipped(uVar10);
      }
      break;
    }
  }
  goto LAB_004caad3;
LAB_004cab11:
  if (iVar5 == -1) goto LAB_004cab43;
  FUN_004d0260(param_1,CONCAT31((int3)((uint)iVar5 >> 8),*(char *)(g_clientContext + 0x62155) == '\0'),
               1,iVar6,iVar5);
  iVar6 = iVar6 + 0x42;
  iVar7 = iVar7 + 1;
  if (0x19e < iVar6) goto LAB_004cab43;
  goto LAB_004caade;
LAB_004cab43:
  if (*(char *)(param_1 + 0x11d8) != '\0') {
    FUN_0041b8c0(g_clientContext,2,0,0,&DAT_0054b460,0,1);
    if (*(char *)(g_clientContext + 0x62155) == '\x01') {
      pcVar3 = (char *)FUN_0043dc70(&DAT_00796eec,0x27e);
      pcVar4 = acStack_80;
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
        *pcVar4 = cVar1;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
    }
    else {
      pcVar3 = (char *)FUN_0043dc70(&DAT_00796eec,0x27f);
      pcVar4 = acStack_80;
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
        *pcVar4 = cVar1;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
    }
    pcVar4 = acStack_80;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    FUN_0041b8c0(g_clientContext,2,0,0,acStack_80,0,1);
  }
  uVar10 = (uint)(*(char *)(g_clientContext + 0x62155) == '\x01');
  if (DAT_0079352c != 0) {
    iVar6 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar6 + 4);
    while (uVar11 < 0x232a) {
      if (uVar11 == 0x2329) {
        iVar6 = *(int *)(iVar6 + 0x10);
        uVar11 = *(uint *)(iVar6 + 8);
        if (uVar11 <= uVar10) goto LAB_004cac35;
        break;
      }
      iVar6 = *(int *)(iVar6 + 0x1c);
      uVar11 = *(uint *)(iVar6 + 4);
    }
  }
  goto LAB_004cac71;
  while( true ) {
    iVar6 = *(int *)(iVar6 + 0x10);
    uVar11 = *(uint *)(iVar6 + 8);
    if (uVar10 < uVar11) break;
LAB_004cac35:
    if (uVar11 == uVar10) {
      if (*(char *)(iVar6 + 0x18) == '\x01') {
        BlitSprite16bpp(0x193,0x30);
      }
      else {
        BlitSpriteClipped(uVar10);
      }
      break;
    }
  }
LAB_004cac71:
  iVar7 = 0;
  iVar6 = 0x97;
LAB_004cac7c:
  iVar9 = 0;
  iVar5 = 0;
  do {
    if ((*(char *)(g_clientContext + 0x50126 + iVar5) == '\x01') &&
       (*(char *)(iVar5 + 0x5010d + g_clientContext) != '\0')) {
      if (iVar7 == iVar9) break;
      iVar9 = iVar9 + 1;
    }
    iVar5 = iVar5 + 1;
    if (7 < iVar5) goto LAB_004cacd1;
  } while( true );
  if (iVar5 == -1) goto LAB_004cacd1;
  FUN_004d0260(param_1,CONCAT31((int3)((uint)iVar5 >> 8),*(char *)(g_clientContext + 0x62155) == '\x01'
                               ),0,iVar6,iVar5);
  iVar6 = iVar6 + 0x42;
  iVar7 = iVar7 + 1;
  if (0x19e < iVar6) {
LAB_004cacd1:
    if ((*(char *)(param_1 + 0x11d8) != '\0') &&
       (*(ushort *)(&DAT_006aa660 + g_clientContext) != 0xffff)) {
      pcVar4 = (char *)FUN_0043dc70(&DAT_00796eec,
                                    *(byte *)(g_clientContext + 0x62155) + 0xc35b +
                                    (uint)*(ushort *)(&DAT_006aa660 + g_clientContext) * 2);
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      uVar15 = 1;
      uVar8 = 0;
      uVar14 = FUN_0043dc70(&DAT_00796eec,
                            *(byte *)(g_clientContext + 0x62155) + 0xc35b +
                            (uint)*(ushort *)(&DAT_006aa660 + g_clientContext) * 2);
      FUN_0041b8c0(g_clientContext,2,0,0,uVar14,uVar8,uVar15);
    }
    *(undefined1 *)(param_1 + 0x11d8) = 0;
    return;
  }
  goto LAB_004cac7c;
}

