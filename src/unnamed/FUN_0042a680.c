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
  int iVar9;
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
  if ((DAT_0079352c != 0) && (iVar4 = FindSpriteFrame(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7,iVar6 + 0x3a);
    }
    else {
      BlitSpriteClipped(uVar8);
    }
  }
  if (((*(char *)(g_clientContext + 0x449b4 + *(int *)(param_1 + 0x124)) != '\0') &&
      (DAT_0079352c != 0)) && (iVar4 = FindSpriteFrame(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0xb1,iVar6 + 0x42);
    }
    else {
      BlitSpriteClipped(0xe);
    }
  }
  bVar1 = *(byte *)(g_clientContext + 0x4499c + *(int *)(param_1 + 0x124));
  if ((DAT_0079352c != 0) && (iVar4 = FindSpriteFrame(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0xc3,iVar6 + 0x46);
    }
    else {
      BlitSpriteClipped(bVar1 + 10);
    }
  }
  bVar1 = *(byte *)(g_clientContext + 0x449a2 + *(int *)(param_1 + 0x124));
  if ((DAT_0079352c != 0) && (iVar4 = FindSpriteFrame(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0xd2,iVar6 + 0x46);
    }
    else {
      BlitSpriteClipped(bVar1 + 10);
    }
  }
  uVar2 = *(undefined1 *)(g_clientContext + 0x4497c + *(int *)(param_1 + 0x124));
  if ((DAT_0079352c != 0) && (iVar4 = FindSpriteFrame(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0x6a,iVar6 + 0x5b);
    }
    else {
      BlitSpriteClipped(uVar2);
    }
  }
  uVar8 = 9;
  if (*(char *)(g_clientContext + 0x449a8 + *(int *)(param_1 + 0x124)) == '\0') {
    if (*(char *)(g_clientContext + 0x4499c + *(int *)(param_1 + 0x124)) ==
        *(char *)(g_clientContext + *(int *)(param_1 + 0x124) + 0x449a2)) {
      uVar8 = 8;
    }
  }
  else {
    uVar8 = 7;
  }
  if ((DAT_0079352c != 0) && (iVar4 = FindSpriteFrame(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0x13,iVar6 + 0x55);
    }
    else {
      BlitSpriteClipped(uVar8);
    }
  }
  iVar4 = *(int *)(param_1 + 0x124);
  if (*(char *)(iVar4 + 0x449ae + g_clientContext) != '\0') {
    if ((DAT_0079352c != 0) && (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
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
           *(int *)(g_clientContext + 0x44664 + *(int *)(param_1 + 0x124) * 4) + 1);
  BlitSpriteText(0x14,local_80,3,0xb);
  SetClipRect();
  /* BlitRLESprite's dropped args (objdump @0x42aa45): ECX (this) carries
   * over unchanged from the SetClipRect call just above, whose own ECX
   * arg was `lea ecx,[ebp+0x37]` with ebp==iVar7 - so this = iVar7+0x37.
   * EAX (rleData) is `lea eax,[eax+edx+0x4467c]` with eax =
   * *(param_1+0x124)<<7 and edx = g_clientContext, computed fresh right
   * before this call with nothing in between to clobber it. */
  BlitRLESprite(iVar7 + 0x37,iVar6 + 0x44,0xffff,
                (byte *)(g_clientContext + *(int *)(param_1 + 0x124) * 0x80 + 0x4467c));
  SetClipRect();
  uVar3 = *(uint *)(g_clientContext + 0x44984 + *(int *)(param_1 + 0x124) * 4);
  if ((DAT_0079352c != 0) && (iVar4 = FindSpriteFrame(), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar7 + 0xb1,iVar6 + 0x5b);
    }
    else {
      BlitSpriteClipped((uVar3 >> 0x12 & 3) + 10);
    }
  }
  /* Ghidra reused the `iVar7` name for two unrelated SSA values: the
   * "row group" constant set at the top of this function (0x18/0x144,
   * still live in real ECX/ebp up to this point) is about to be
   * clobbered by the loop counter below, but objdump shows the register
   * it lived in (ebp) still feeding the loop body's `this` computation
   * (see iVar9 below) - preserved here under a new name before the
   * overwrite so that value isn't lost. */
  iVar9 = iVar7;
  iVar7 = 0;
  if (*(char *)(param_1 + 0x1b4) != '\0') {
    do {
      iVar4 = (iVar7 / 2) * 0x1f + 0x3d + iVar6 + 0x3a;
      DrawFontString(iVar4 + -1,0x1f);
      /* BlitRLESprite's dropped args (objdump @0x42ab47): ECX (this) =
       * edi = (iVar7/2)*0x6a + iVar9 + 0x21 - the SAME loop-counter
       * halving as iVar4's own `(iVar7/2)*0x1f` term, just scaled by
       * 0x6a instead of 0x1f and offset by the preserved outer iVar9
       * (see above) instead of iVar6. EAX (rleData) = ebx, which starts
       * at param_1+0x1b8+0x220 before the loop and advances by 9 each
       * iteration -> param_1+0x3d8+9*iVar7 on this iteration. */
      BlitRLESprite((iVar7 / 2) * 0x6a + iVar9 + 0x21,iVar4 + -1,0xffff,
                    (byte *)(param_1 + 0x3d8 + iVar7 * 9));
      /* BlitRLESprite's dropped args (objdump @0x42ab5d): ECX (this) is
       * the SAME `edi` as the call just above (unchanged in between).
       * EAX (rleData) here is NOT expressible from this function's
       * existing decompiled locals - it's a separate loop-carried
       * cursor kept only in a spilled stack slot (init'd to
       * param_1+0x1b8 before the loop, then advanced by the PREVIOUS
       * iteration's `iVar4+0x1c` each time around), with no surviving
       * named variable in Ghidra's output. Left as a placeholder
       * (genuine ambiguity - see report). */
      BlitRLESprite((iVar7 / 2) * 0x6a + iVar9 + 0x21,iVar4 + 0xf,0xffff,(byte *)0);
      iVar7 = iVar7 + 1;
    } while (iVar7 < (int)(uint)*(byte *)(param_1 + 0x1b4));
  }
  return;
}

