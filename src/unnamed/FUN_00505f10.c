/* FUN_00505f10 - 0x00505f10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00505f10(int param_1,int param_2)

{
  int iVar1;
  undefined2 uVar2;
  ushort uVar3;
  int iVar4;
  int in_EAX;
  int iVar5;
  undefined4 uVar6;
  char local_80 [128];
  
  iVar4 = *(int *)(in_EAX + 0x28);
  iVar1 = param_1 * 0x1e + 0x2f + *(int *)(in_EAX + 0x2c);
  if (((*(int *)(in_EAX + 0x90) == DAT_00e54da8 + param_1) && (DAT_0079352c != 0)) &&
     (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar4 + 0xe,iVar1 + -2);
    }
    else {
      BlitSpriteClipped(1);
    }
  }
  uVar2 = *(undefined2 *)(param_2 + 0x2e);
  if ((DAT_0079352c != 0) && (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar4 + 0x14,iVar1);
    }
    else {
      BlitSpriteClipped(uVar2);
    }
  }
  BlitRLESprite(iVar1,0xfd0f);
  BlitRLESprite(iVar1 + 0xd,0xffff);
  if (*(char *)(param_2 + 0x30) == '\0') {
    if (DAT_0079352c == 0) {
      return;
    }
    iVar5 = FindSpriteFrame();
    if (iVar5 == 0) {
      return;
    }
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar4 + 0x77,iVar1);
      return;
    }
    uVar6 = 4;
  }
  else {
    if ((*(char *)(param_2 + 0x30) == '\x12') && (*(short *)(param_2 + 0x31) != -1)) {
      if (*(short *)(param_2 + 0x33) != -2) {
        if (*(short *)(param_2 + 0x33) == -1) {
          FUN_004eb890();
          uVar3 = *(ushort *)(param_2 + 0x35);
        }
        else {
          FUN_004eb890();
          uVar3 = *(ushort *)(param_2 + 0x33);
        }
        _sprintf(local_80,(char *)&PTR_DAT_00551ecc,uVar3 + 1);
        BlitSpriteText(0x28,local_80,3,6);
        _sprintf(local_80,(char *)&PTR_DAT_00551ecc,*(ushort *)(param_2 + 0x31) + 1);
        BlitSpriteText(0x28,local_80,3,6);
        return;
      }
      if (*(short *)(param_2 + 0x31) != -1) {
        if (DAT_0079352c == 0) {
          return;
        }
        iVar5 = FindSpriteFrame();
        if (iVar5 == 0) {
          return;
        }
        if (*(char *)(iVar5 + 0x18) == '\x01') {
          BlitSprite16bpp(iVar4 + 0x77,iVar1);
          return;
        }
        uVar6 = 6;
        goto LAB_005061be;
      }
    }
    if (DAT_0079352c == 0) {
      return;
    }
    iVar5 = FindSpriteFrame();
    if (iVar5 == 0) {
      return;
    }
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar4 + 0x77,iVar1);
      return;
    }
    uVar6 = 5;
  }
LAB_005061be:
  BlitSpriteClipped(uVar6);
  return;
}

