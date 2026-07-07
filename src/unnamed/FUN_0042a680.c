/* FUN_0042a680 - 0x0042a680 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0042a680(int param_1)

{
  byte bVar1;
  undefined1 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  char local_80 [128];
  
  if (*(int *)(param_1 + 0x124) / 3 == 0) {
    iVar7 = 0x18;
    uVar8 = 0x10;
  }
  else {
    iVar7 = 0x144;
    uVar8 = 0x11;
  }
  iVar6 = (*(int *)(param_1 + 0x124) % 3) * 0x3c;
  if ((DAT_0079352c != 0) && (iVar4 = FUN_004f30c0(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7,iVar6 + 0x3a);
    }
    else {
      BlitSpriteClipped(uVar8);
    }
  }
  if (((*(char *)(DAT_005b3484 + 0x449b4 + *(int *)(param_1 + 0x124)) != '\0') &&
      (DAT_0079352c != 0)) && (iVar4 = FUN_004f30c0(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0xb1,iVar6 + 0x42);
    }
    else {
      BlitSpriteClipped(0xe);
    }
  }
  bVar1 = *(byte *)(DAT_005b3484 + 0x4499c + *(int *)(param_1 + 0x124));
  if ((DAT_0079352c != 0) && (iVar4 = FUN_004f30c0(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0xc3,iVar6 + 0x46);
    }
    else {
      BlitSpriteClipped(bVar1 + 10);
    }
  }
  bVar1 = *(byte *)(DAT_005b3484 + 0x449a2 + *(int *)(param_1 + 0x124));
  if ((DAT_0079352c != 0) && (iVar4 = FUN_004f30c0(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0xd2,iVar6 + 0x46);
    }
    else {
      BlitSpriteClipped(bVar1 + 10);
    }
  }
  uVar2 = *(undefined1 *)(DAT_005b3484 + 0x4497c + *(int *)(param_1 + 0x124));
  if ((DAT_0079352c != 0) && (iVar4 = FUN_004f30c0(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0x6a,iVar6 + 0x5b);
    }
    else {
      BlitSpriteClipped(uVar2);
    }
  }
  uVar8 = 9;
  if (*(char *)(DAT_005b3484 + 0x449a8 + *(int *)(param_1 + 0x124)) == '\0') {
    if (*(char *)(DAT_005b3484 + 0x4499c + *(int *)(param_1 + 0x124)) ==
        *(char *)(DAT_005b3484 + *(int *)(param_1 + 0x124) + 0x449a2)) {
      uVar8 = 8;
    }
  }
  else {
    uVar8 = 7;
  }
  if ((DAT_0079352c != 0) && (iVar4 = FUN_004f30c0(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0x13,iVar6 + 0x55);
    }
    else {
      BlitSpriteClipped(uVar8);
    }
  }
  iVar4 = *(int *)(param_1 + 0x124);
  if (*(char *)(iVar4 + 0x449ae + DAT_005b3484) != '\0') {
    if ((DAT_0079352c != 0) && (iVar5 = FUN_004f30c0(), iVar5 != 0)) {
      if (*(char *)(iVar5 + 0x18) == '\x01') {
        BlitSprite16bpp((-(uint)(iVar4 / 3 + (iVar4 >> 0x1f) != iVar4 >> 0x1f) & 0xffffff06) + 0xea
                        + iVar7,iVar6 + 0x52);
      }
      else {
        BlitSpriteClipped(0xf);
      }
    }
  }
  _sprintf(local_80,(char *)&PTR_DAT_00551ecc,
           *(int *)(DAT_005b3484 + 0x44664 + *(int *)(param_1 + 0x124) * 4) + 1);
  FUN_004ed9f0(0x14,local_80,3,0xb);
  FUN_004eadb0();
  BlitRLESprite(iVar6 + 0x44,0xffff);
  FUN_004eadb0();
  uVar3 = *(uint *)(DAT_005b3484 + 0x44984 + *(int *)(param_1 + 0x124) * 4);
  if ((DAT_0079352c != 0) && (iVar4 = FUN_004f30c0(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0xb1,iVar6 + 0x5b);
    }
    else {
      BlitSpriteClipped((uVar3 >> 0x12 & 3) + 10);
    }
  }
  iVar7 = 0;
  if (*(char *)(param_1 + 0x1b4) != '\0') {
    do {
      iVar4 = (iVar7 / 2) * 0x1f + 0x3d + iVar6 + 0x3a;
      FUN_004eb510(iVar4 + -1,0x1f);
      BlitRLESprite(iVar4 + -1,0xffff);
      BlitRLESprite(iVar4 + 0xf,0xffff);
      iVar7 = iVar7 + 1;
    } while (iVar7 < (int)(uint)*(byte *)(param_1 + 0x1b4));
  }
  return;
}

