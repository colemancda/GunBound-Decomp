/* FUN_004d0260 - 0x004d0260 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004d0260(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  char cVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  char *pcVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int local_194;
  char local_180 [128];
  char local_100 [128];
  char local_80 [128];
  
  uVar10 = -(uint)(param_3 != '\0') & 0xfffffe85;
  iVar4 = 3 - (uint)(param_3 != '\0');
  if (((DAT_0079352c != 0) && (-1 < iVar4)) && (iVar5 = FUN_004f30c0(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(uVar10 + 0x1af,param_4);
    }
    else {
      BlitSpriteClipped(iVar4);
    }
  }
  iVar4 = DAT_005b3484;
  uVar2 = *(undefined2 *)(DAT_005b3484 + 0x50116 + param_5 * 2);
  if ((DAT_0079352c != 0) && (iVar5 = FUN_004f30c0(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(uVar10 + 0x1d8,param_4 + 0x11);
    }
    else {
      BlitSpriteClipped(uVar2);
    }
  }
  iVar5 = param_5 * 9;
  if (*(char *)(iVar5 + 0x457a9 + iVar4) != '\0') {
    _sprintf(local_80,s__s__3d__3d__005536b8,iVar5 + 0x457a9 + iVar4,
             *(undefined4 *)(iVar4 + 0x4597c + param_5 * 4),
             *(undefined4 *)(iVar4 + 0x4599c + param_5 * 4));
    BlitRLESprite(param_4 + 0x10,0xf800);
  }
  BlitRLESprite(param_4 + 0x1e,0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  _sprintf(local_180,(char *)&PTR_DAT_00551ecc,iVar4);
  local_194 = 0;
  iVar12 = uVar10 + 0x2ad;
LAB_004d0450:
  cVar1 = local_180[local_194];
  if (cVar1 != ' ') {
    if (cVar1 == '-') {
      if (DAT_0079352c != 0) {
        iVar11 = *(int *)(DAT_00ea0e1c + 0x1c);
        uVar6 = *(uint *)(iVar11 + 4);
        while (uVar6 < 0x1f5) {
          if (uVar6 == 500) {
            iVar11 = *(int *)(iVar11 + 0x10);
            uVar6 = *(uint *)(iVar11 + 8);
            if (uVar6 < 0x67) goto LAB_004d04ad;
            break;
          }
          iVar11 = *(int *)(iVar11 + 0x1c);
          uVar6 = *(uint *)(iVar11 + 4);
        }
      }
    }
    else {
      uVar6 = (int)cVar1 + ((-1 < iVar4) - 1 & 10) + 0x20;
      if ((DAT_0079352c != 0) && (-1 < (int)uVar6)) {
        iVar11 = *(int *)(DAT_00ea0e1c + 0x1c);
        uVar3 = *(uint *)(iVar11 + 4);
        while (uVar3 < 0x1f5) {
          if (uVar3 == 500) {
            iVar11 = *(int *)(iVar11 + 0x10);
            uVar3 = *(uint *)(iVar11 + 8);
            if (uVar3 <= uVar6) goto LAB_004d0525;
            break;
          }
          iVar11 = *(int *)(iVar11 + 0x1c);
          uVar3 = *(uint *)(iVar11 + 4);
        }
      }
    }
  }
  goto LAB_004d0557;
  while( true ) {
    iVar11 = *(int *)(iVar11 + 0x10);
    uVar3 = *(uint *)(iVar11 + 8);
    if (uVar6 < uVar3) break;
LAB_004d0525:
    if (uVar3 == uVar6) {
      if (*(char *)(iVar11 + 0x18) != '\x01') goto LAB_004d054d;
      BlitSprite16bpp(iVar12,param_4 + 8);
      break;
    }
  }
  goto LAB_004d0557;
  while( true ) {
    iVar11 = *(int *)(iVar11 + 0x10);
    uVar6 = *(uint *)(iVar11 + 8);
    if (0x66 < uVar6) break;
LAB_004d04ad:
    if (uVar6 == 0x66) {
      if (*(char *)(iVar11 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar12,param_4 + 8);
      }
      else {
        uVar6 = 0x66;
LAB_004d054d:
        BlitSpriteClipped(uVar6);
      }
      break;
    }
  }
LAB_004d0557:
  local_194 = local_194 + 1;
  iVar12 = iVar12 + 9;
  if (2 < local_194) goto code_r0x004d056c;
  goto LAB_004d0450;
code_r0x004d056c:
  uVar6 = (iVar4 < 0) + 100;
  if (DAT_0079352c != 0) {
    iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar3 = *(uint *)(iVar4 + 4);
    while (uVar3 < 0x1f5) {
      if (uVar3 == 500) {
        iVar4 = *(int *)(iVar4 + 0x10);
        uVar3 = *(uint *)(iVar4 + 8);
        if (uVar3 <= uVar6) goto LAB_004d05c1;
        break;
      }
      iVar4 = *(int *)(iVar4 + 0x1c);
      uVar3 = *(uint *)(iVar4 + 4);
    }
  }
  goto LAB_004d05f1;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    uVar3 = *(uint *)(iVar4 + 8);
    if (uVar6 < uVar3) break;
LAB_004d05c1:
    if (uVar3 == uVar6) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(uVar10 + 0x2c8,param_4 + 8);
      }
      else {
        BlitSpriteClipped(uVar6);
      }
      break;
    }
  }
LAB_004d05f1:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  _sprintf(local_180,(char *)&PTR_DAT_00551ed0,uVar7);
  iVar4 = 0;
  iVar12 = uVar10 + 0x272;
LAB_004d0660:
  cVar1 = local_180[iVar4];
  if (cVar1 != ' ') {
    if (cVar1 == '-') {
      uVar6 = 0xe1 - (param_3 != '\0');
      if ((DAT_0079352c != 0) && (-1 < (int)uVar6)) {
        iVar11 = *(int *)(DAT_00ea0e1c + 0x1c);
        uVar3 = *(uint *)(iVar11 + 4);
        while (uVar3 < 0x1f5) {
          if (uVar3 == 500) {
            iVar11 = *(int *)(iVar11 + 0x10);
            uVar3 = *(uint *)(iVar11 + 8);
            if (uVar3 <= uVar6) goto LAB_004d06dd;
            break;
          }
          iVar11 = *(int *)(iVar11 + 0x1c);
          uVar3 = *(uint *)(iVar11 + 4);
        }
      }
    }
    else {
      uVar6 = (int)cVar1 + (-(uint)(param_3 != '\0') & 0xfffffff5) + 0x42;
      if ((DAT_0079352c != 0) && (-1 < (int)uVar6)) {
        iVar11 = *(int *)(DAT_00ea0e1c + 0x1c);
        uVar3 = *(uint *)(iVar11 + 4);
        while (uVar3 < 0x1f5) {
          if (uVar3 == 500) {
            iVar11 = *(int *)(iVar11 + 0x10);
            uVar3 = *(uint *)(iVar11 + 8);
            if (uVar3 <= uVar6) goto LAB_004d074b;
            break;
          }
          iVar11 = *(int *)(iVar11 + 0x1c);
          uVar3 = *(uint *)(iVar11 + 4);
        }
      }
    }
  }
  goto LAB_004d0766;
  while( true ) {
    iVar11 = *(int *)(iVar11 + 0x10);
    uVar3 = *(uint *)(iVar11 + 8);
    if (uVar6 < uVar3) break;
LAB_004d074b:
    if (uVar3 == uVar6) goto LAB_004d06eb;
  }
  goto LAB_004d0766;
  while( true ) {
    iVar11 = *(int *)(iVar11 + 0x10);
    uVar3 = *(uint *)(iVar11 + 8);
    if (uVar6 < uVar3) break;
LAB_004d06dd:
    if (uVar3 == uVar6) goto LAB_004d06eb;
  }
LAB_004d0766:
  iVar4 = iVar4 + 1;
  iVar12 = iVar12 + 0x10;
  if (4 < iVar4) goto code_r0x004d0773;
  goto LAB_004d0660;
LAB_004d06eb:
  if (*(char *)(iVar11 + 0x18) == '\x01') {
    BlitSprite16bpp(iVar12,param_4 + 0x1a);
  }
  else {
    BlitSpriteClipped(uVar6);
  }
  goto LAB_004d0766;
code_r0x004d0773:
  uVar6 = (-(uint)(param_3 != '\0') & 0xfffffff5) + 0x7c;
  if ((DAT_0079352c != 0) && (-1 < (int)uVar6)) {
    iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar3 = *(uint *)(iVar4 + 4);
    while (uVar3 < 0x1f5) {
      if (uVar3 == 500) {
        iVar4 = *(int *)(iVar4 + 0x10);
        uVar3 = *(uint *)(iVar4 + 8);
        if (uVar3 <= uVar6) goto LAB_004d07d1;
        break;
      }
      iVar4 = *(int *)(iVar4 + 0x1c);
      uVar3 = *(uint *)(iVar4 + 4);
    }
  }
  goto LAB_004d0801;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    uVar3 = *(uint *)(iVar4 + 8);
    if (uVar6 < uVar3) break;
LAB_004d07d1:
    if (uVar3 == uVar6) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(uVar10 + 0x2c1,param_4 + 0x1a);
      }
      else {
        BlitSpriteClipped(uVar6);
      }
      break;
    }
  }
LAB_004d0801:
  if (*(char *)(param_1 + 0x11d8) != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    _sprintf(local_100,s___8s___12s__3dP__6dG_00556720,iVar5 + 0x5012e + DAT_005b3484,
             param_5 * 0xd + 0x50196 + DAT_005b3484,uVar8,uVar7);
    pcVar9 = local_100;
    do {
      cVar1 = *pcVar9;
      pcVar9 = pcVar9 + 1;
    } while (cVar1 != '\0');
    FUN_0041b8c0(DAT_005b3484,2,0,0,local_100,0,1);
  }
  if ((*(ushort *)(&DAT_006aa660 + DAT_005b3484) != 0xffff) && (param_2 != '\0')) {
    uVar6 = *(ushort *)(&DAT_006aa660 + DAT_005b3484) + 4;
    if (DAT_0079352c != 0) {
      iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar3 = *(uint *)(iVar4 + 4);
      if (uVar3 < 0x232a) {
        while (uVar3 != 0x2329) {
          iVar4 = *(int *)(iVar4 + 0x1c);
          uVar3 = *(uint *)(iVar4 + 4);
          if (0x2329 < uVar3) {
            return;
          }
        }
        iVar4 = *(int *)(iVar4 + 0x10);
        uVar3 = *(uint *)(iVar4 + 8);
        if (uVar3 <= uVar6) {
          while (uVar3 != uVar6) {
            iVar4 = *(int *)(iVar4 + 0x10);
            uVar3 = *(uint *)(iVar4 + 8);
            if (uVar6 < uVar3) {
              return;
            }
          }
          if (*(char *)(iVar4 + 0x18) == '\x01') {
            BlitSprite16bpp(uVar10 + 0x2c6,param_4 + 9);
            return;
          }
          BlitSpriteClipped(uVar6);
        }
      }
    }
  }
  return;
}

