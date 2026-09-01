/* RenderBuddyRow - 0x00505f10 in the original binary.
 *
 * Draws one row of the buddy-list panel - the name src/cxx/Panel.cpp's
 * CBuddyPanel::Update header already uses for this address.  The one
 * binary call site, 0x505ea3, is the 7-row loop of CBuddyPanel::Update
 * (0x505df0, vtable slot 9 of the 0x557be4 buddy panel - the deferred
 * "FindBuddyNode 0x401c10 -> RenderBuddyRow 0x505f10" loop documented
 * there), so: param_1 is the row index (row y = panel m_y + row*0x1e +
 * 0x2f), regEax the panel itself (m_x/m_y read at the CWidget +0x28/
 * +0x2c offsets, and +0x90 - the CBuddyPanel selection slot its ctor
 * inits to -1 - compared against DAT_00e54da8 + row for the
 * selection-highlight blit), and param_2 the buddy node that
 * FindActiveObjectByIndex(&DAT_00e53e88, ...) returned: its +0x18 and
 * +0x21 name strings become the two BlitRLESprite text runs, and its
 * +0x30 status byte picks the state icon - 0x12 with valid +0x31/+0x33
 * shorts renders the "%3d" room numbers, exactly the fields
 * UpdateBuddyStatus (0x401fa0) writes into the node.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void __thiscall RenderBuddyRow(int param_1,int param_2,int regEax)

{
  int iVar1;
  undefined2 uVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  char local_80 [128];
  
  iVar4 = *(int *)(regEax + 0x28);
  iVar1 = param_1 * 0x1e + 0x2f + *(int *)(regEax + 0x2c);
  if (((*(int *)(regEax + 0x90) == DAT_00e54da8 + param_1) && (g_screenSurface != 0)) &&
     (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar4 + 0xe,iVar1 + -2);
    }
    else {
      BlitSpriteClipped(1);
    }
  }
  uVar2 = *(undefined2 *)(param_2 + 0x2e);
  if ((g_screenSurface != 0) && (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar4 + 0x14,iVar1);
    }
    else {
      BlitSpriteClipped(uVar2);
    }
  }
  /* BlitRLESprite's 1st arg (this/x-cursor) and 4th arg (rleData) were
   * dropped - objdump at this call site (0x505fde/0x505fe0) shows
   * ECX = iVar4 + 0x24 (ebp+0x10, where ebp already tracks iVar4 plus a
   * running offset - see the `add ebp,0x14` right after ebp is loaded
   * from *(in_EAX+0x28), matching this file's other iVar4+<offset>
   * call sites like BlitSprite16bpp(iVar4 + 0x77,...)) and EAX =
   * param_2 + 0x18 (ebx+0x18, ebx being this function's own param_2). */
  BlitRLESprite(iVar4 + 0x24,iVar1,0xfd0f,(byte *)(param_2 + 0x18));
  /* Same call shape (objdump 0x505ff1/0x505ff3): ECX = iVar4 + 0x24
   * (same running x-cursor, unchanged since the call above) and EAX =
   * param_2 + 0x21 (ebx+0x21), a second name/label field on the same
   * struct as the +0x18 field used above. */
  BlitRLESprite(iVar4 + 0x24,iVar1 + 0xd,0xffff,(byte *)(param_2 + 0x21));
  if (*(char *)(param_2 + 0x30) == '\0') {
    if (g_screenSurface == 0) {
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
          /* DrawSprite's arg was dropped as `in_EAX` - objdump at this
           * call site (0x50608d) shows a literal `mov eax,3`. */
          DrawSprite(3);
          uVar3 = *(ushort *)(param_2 + 0x35);
        }
        else {
          /* Same dropped-arg case; objdump at 0x5060a4 shows a literal
           * `mov eax,2`. */
          DrawSprite(2);
          uVar3 = *(ushort *)(param_2 + 0x33);
        }
        _sprintf(local_80,(char *)&PTR_DAT_00551ecc,uVar3 + 1);
        BlitSpriteText(0x28,local_80,3,6);
        _sprintf(local_80,(char *)&PTR_DAT_00551ecc,*(ushort *)(param_2 + 0x31) + 1);
        BlitSpriteText(0x28,local_80,3,6);
        return;
      }
      if (*(short *)(param_2 + 0x31) != -1) {
        if (g_screenSurface == 0) {
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
    if (g_screenSurface == 0) {
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

