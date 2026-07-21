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
  /* RECOVERED (2026-07-21), orig 0x42a6c4-0x42a70e. EBP is the card's x base
   * (iVar7, spilled to esp+0x14 at 0x42a6a8/0x42a6b3) and EDI its y base
   * (= iVar6+0x3a, from `imul edx,edx,0x3c / add edx,0x3a / mov edi,edx` at
   * 0x42a6c9-0x42a6d1, also spilled to esp+0x10). ESI is the background frame
   * index (uVar8, 0x10 or 0x11).
   *   mov edx,0x2710 / mov eax,0xea0e18 / call FindSpriteFrame
   *   push edi / push ebp / mov eax,esi / call BlitSprite16bpp
   *   push esi / mov eax,edi / mov ecx,ebp / call BlitSpriteClipped
   * NOTE the raw port's args had slid LEFT: `BlitSprite16bpp(iVar7, iVar6+0x3a)`
   * was passing the x as the frame handle. Frame is uVar8 at both paths.
   * Cached scan: tools/findspriteframe_sites.json (call_addr 0x42a6e7, esi=0x11). */
  if ((DAT_0079352c != 0) &&
      (iVar4 = FindSpriteFrame((int)&DAT_00ea0e18,0x2710,uVar8), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(uVar8,iVar7,iVar6 + 0x3a,0x2710);
    }
    else {
      BlitSpriteClipped(uVar8,iVar7,iVar6 + 0x3a,0x2710);
    }
  }
  /* RECOVERED (2026-07-21), orig 0x42a72e-0x42a774: `lea ebx,[edi+8]` (y =
   * iVar6+0x42) / mov esi,0xe / mov edx,0x2710 / mov eax,0xea0e18, then
   * `lea eax,[ebp+0xb1] / push ebx / push eax / mov eax,esi` (16bpp) and
   * `push 0xe / mov eax,ebx / lea ecx,[ebp+0xb1]` (clipped). Frame is 0xe at
   * both. Cached scan call_addr 0x42a742 (esi=0xe). */
  if (((*(char *)(g_clientContext + 0x449b4 + *(int *)(param_1 + 0x124)) != '\0') &&
      (DAT_0079352c != 0)) &&
      (iVar4 = FindSpriteFrame((int)&DAT_00ea0e18,0x2710,0xe), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(0xe,iVar7 + 0xb1,iVar6 + 0x42,0x2710);
    }
    else {
      BlitSpriteClipped(0xe,iVar7 + 0xb1,iVar6 + 0x42,0x2710);
    }
  }
  bVar1 = *(byte *)(g_clientContext + 0x4499c + *(int *)(param_1 + 0x124));
  /* RECOVERED (2026-07-21), orig 0x42a789-0x42a7db: `movzx esi,[..+0x4499c] /
   * add esi,0xa` (esi = bVar1+10, the mode icon frame) / `add edi,0xc` at
   * 0x42a796 makes EDI the y (iVar6+0x46) / `lea ebx,[ebp+0xc3]` is the x /
   * mov edx,0x1f4 / mov eax,0xea0e18; then `push edi / push ebx / mov eax,esi`
   * (16bpp) and `push esi / mov eax,edi / mov ecx,ebx` (clipped). Outer key
   * here is 0x1f4, not 0x2710. Cached scan call_addr 0x42a7b4. */
  if ((DAT_0079352c != 0) &&
      (iVar4 = FindSpriteFrame((int)&DAT_00ea0e18,0x1f4,bVar1 + 10), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(bVar1 + 10,iVar7 + 0xc3,iVar6 + 0x46,0x1f4);
    }
    else {
      BlitSpriteClipped(bVar1 + 10,iVar7 + 0xc3,iVar6 + 0x46,0x1f4);
    }
  }
  bVar1 = *(byte *)(g_clientContext + 0x449a2 + *(int *)(param_1 + 0x124));
  /* RECOVERED (2026-07-21), orig 0x42a7f0-0x42a83f: same shape as the site
   * above - esi = bVar1+10, edx = 0x1f4, EDI is still the y (iVar6+0x46,
   * unmodified since 0x42a796), x = `lea ebx,[ebp+0xd2]`.
   * Cached scan call_addr 0x42a818. */
  if ((DAT_0079352c != 0) &&
      (iVar4 = FindSpriteFrame((int)&DAT_00ea0e18,0x1f4,bVar1 + 10), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(bVar1 + 10,iVar7 + 0xd2,iVar6 + 0x46,0x1f4);
    }
    else {
      BlitSpriteClipped(bVar1 + 10,iVar7 + 0xd2,iVar6 + 0x46,0x1f4);
    }
  }
  uVar2 = *(undefined1 *)(g_clientContext + 0x4497c + *(int *)(param_1 + 0x124));
  /* RECOVERED (2026-07-21), orig 0x42a854-0x42a8a4: `movzx esi,[..+0x4497c]`
   * is the frame the port already reads into uVar2 (NOTE: unlike the sibling
   * RenderRoomCard @0x42a42d there is no `(bVar1&3)*0xb` term here - esi is
   * the raw byte); EDI is reloaded from the esp+0x10 spill and `add edi,0x21`
   * -> y = iVar6+0x5b; `lea ebx,[ebp+0x6a]` is the x; mov edx,0x2716.
   * Cached scan call_addr 0x42a87d. */
  if ((DAT_0079352c != 0) &&
      (iVar4 = FindSpriteFrame((int)&DAT_00ea0e18,0x2716,uVar2), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(uVar2,iVar7 + 0x6a,iVar6 + 0x5b,0x2716);
    }
    else {
      BlitSpriteClipped(uVar2,iVar7 + 0x6a,iVar6 + 0x5b,0x2716);
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
  /* RECOVERED (2026-07-21), orig 0x42a8ec-0x42a934: ESI is the 7/8/9 status
   * frame the port already computes as uVar8 (`mov esi,9 / mov esi,7 /
   * mov esi,8` at 0x42a8c2-0x42a8e7); EDI is reloaded from the esp+0x10 spill
   * and `add edi,0x1b` -> y = iVar6+0x55; `lea ebx,[ebp+0x13]` is the x;
   * mov edx,0x2710. Cached scan call_addr 0x42a90d (esi=8 on the sampled
   * branch). */
  if ((DAT_0079352c != 0) &&
      (iVar4 = FindSpriteFrame((int)&DAT_00ea0e18,0x2710,uVar8), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(uVar8,iVar7 + 0x13,iVar6 + 0x55,0x2710);
    }
    else {
      BlitSpriteClipped(uVar8,iVar7 + 0x13,iVar6 + 0x55,0x2710);
    }
  }
  iVar4 = *(int *)(param_1 + 0x124);
  if (*(char *)(iVar4 + 0x449ae + g_clientContext) != '\0') {
    /* RECOVERED (2026-07-21), orig 0x42a955-0x42a9be: mov esi,0xf (the lock
     * icon frame) / EBX reloaded from the esp+0x10 spill then `add ebx,0x18`
     * -> y = iVar6+0x52 / EDI is the x the port already computes (the
     * `neg/sbb/and 0xffffff06/add 0xea/add ebp` chain at 0x42a971-0x42a981) /
     * mov edx,0x2710. 16bpp: `push ebx / push edi / mov eax,esi`; clipped:
     * `push 0xf / mov eax,ebx / mov ecx,edi`. Cached scan call_addr 0x42a996
     * (esi=0xf). */
    if ((DAT_0079352c != 0) &&
        (iVar5 = FindSpriteFrame((int)&DAT_00ea0e18,0x2710,0xf), iVar5 != 0)) {
      if (*(char *)(iVar5 + 0x18) == '\x01') {
        BlitSprite16bpp(0xf,(-(uint)(iVar4 / 3 + (iVar4 >> 0x1f) != iVar4 >> 0x1f) & 0xffffff06) +
                        0xea + iVar7,iVar6 + 0x52,0x2710);
      }
      else {
        BlitSpriteClipped(0xf,(-(uint)(iVar4 / 3 + (iVar4 >> 0x1f) != iVar4 >> 0x1f) & 0xffffff06) +
                          0xea + iVar7,iVar6 + 0x52,0x2710);
      }
    }
  }
  _sprintf(local_80,(char *)&PTR_DAT_00551ecc,
           *(int *)(g_clientContext + 0x44664 + *(int *)(param_1 + 0x124) * 4) + 1);
  /* RECOVERED (2026-07-21), orig 0x42a9eb-0x42aa05:
   *   mov ebx,[esp+0x1c] / push 0xb / push 3 / lea eax,[esp+0x30] / push eax
   *   push 0x14 / add ebx,0xb / lea ecx,[ebp+0x11] / mov esi,0x1f4
   * BlitSpriteText's promoted signature is (x=ECX, glyphBase, string, count,
   * advance, y=EBX, charsetKey=ESI) - see src/rendering/BlitSpriteText.c's
   * header, which names this very call site. The raw port dropped the ECX x,
   * the EBX y and the ESI charset key. The `[esp+0x1c]` load is the esp+0x10
   * spill of iVar6+0x3a (3 sprintf args are still pushed, cleaned only at
   * 0x42aa4a's `add esp,0x24`), so y = iVar6+0x3a+0xb = iVar6+0x45 and
   * x = iVar7+0x11 - identical to the sibling RenderRoomCard @0x42a5a3. */
  BlitSpriteText(iVar7 + 0x11,0x14,(int)local_80,3,0xb,iVar6 + 0x45,0x1f4);
  /* FIXED (2026-07-15): SetClipRect's 4 corner args were all dropped.
   * x1/x2 confirmed via the pre-existing comment below (ecx=iVar7+0x37,
   * eax=iVar7+0xc1). y1/y2 needed a manual ESP-offset trace (angr's
   * symbolic engine timed out on this function): the base register at
   * the call (`mov ebx,[esp+0x2c]`) is a spilled copy of `iVar6+0x3a`
   * (`add edx,0x3a; mov edi,edx; mov [esp+0x10],edi` right after iVar6's
   * own `imul edx,edx,0x3c` computation) - so y2=ebx+0xa=iVar6+0x44
   * (cross-validated: matches this file's own BlitRLESprite call 2 lines
   * below exactly) and y1=ebx+0x16=iVar6+0x50. */
  SetClipRect(iVar7 + 0x37, iVar7 + 0xc1, iVar6 + 0x50, iVar6 + 0x44);
  /* BlitRLESprite's dropped args (objdump @0x42aa45): ECX (this) carries
   * over unchanged from the SetClipRect call just above, whose own ECX
   * arg was `lea ecx,[ebp+0x37]` with ebp==iVar7 - so this = iVar7+0x37.
   * EAX (rleData) is `lea eax,[eax+edx+0x4467c]` with eax =
   * *(param_1+0x124)<<7 and edx = g_clientContext, computed fresh right
   * before this call with nothing in between to clobber it. */
  BlitRLESprite(iVar7 + 0x37,iVar6 + 0x44,0xffff,
                (byte *)(g_clientContext + *(int *)(param_1 + 0x124) * 0x80 + 0x4467c));
  SetClipRect(0, 0x31f, 0x257, 0);
  uVar3 = *(uint *)(g_clientContext + 0x44984 + *(int *)(param_1 + 0x124) * 4);
  /* RECOVERED (2026-07-21), orig 0x42aa73-0x42aacc: `shr esi,0x12 / and esi,3
   * / add esi,0xa` is the frame the port already computes as
   * `(uVar3 >> 0x12 & 3) + 10`; `lea edi,[ebp+0xb1]` at 0x42aa8a is the x
   * (iVar7+0xb1); EBX still holds the iVar6+0x3a value loaded at 0x42aa0a and
   * `add ebx,0x21` at 0x42aaac makes it the y (iVar6+0x5b) for both paths
   * (16bpp: `push ebx / push edi`; clipped: `push esi / mov eax,ebx /
   * mov ecx,edi`). edx=0x2710. Cached scan call_addr 0x42aaa0. */
  if ((DAT_0079352c != 0) &&
      (iVar4 = FindSpriteFrame((int)&DAT_00ea0e18,0x2710,(uVar3 >> 0x12 & 3) + 10), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp((uVar3 >> 0x12 & 3) + 10,iVar7 + 0xb1,iVar6 + 0x5b,0x2710);
    }
    else {
      BlitSpriteClipped((uVar3 >> 0x12 & 3) + 10,iVar7 + 0xb1,iVar6 + 0x5b,0x2710);
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
      /* RECOVERED (2026-07-21), orig 0x42ab00-0x42ab5d. The whole loop body's
       * geometry was mis-decompiled; traced register by register:
       *   mov ecx,esi / and ecx,0x80000001 / <sign fixup> -> ecx = iVar7 % 2
       *   imul ecx,ecx,0x6a                                (NOT iVar7/2)
       *   mov eax,esi / cdq / sub eax,edx / sar eax,1 -> eax = iVar7 / 2
       *   imul eax,eax,0x1f
       *   mov edx,[esp+0x10]                          -> edx = iVar6 + 0x3a
       *   lea edi,[ecx+ebp+0x10] / add edi,0x11       -> x  = (iVar7%2)*0x6a
       *                                                       + iVar9 + 0x21
       *   lea ebp,[eax+edx+0x3d]                      -> y-base = iVar4
       * EBP (the outer iVar9) is reloaded from its esp+0x14 spill at 0x42aaf8
       * on every subsequent iteration, so it is intact at the `lea edi`.
       * The two rleData cursors are the state object's two parallel per-player
       * arrays (strides confirmed by State03_GameRoomList_HandleMouseInput.c's
       * zeroing loops: +0x220 is 0x12 dwords = 8*9, +0x1b8 is 0x1a dwords =
       * 8*13):
       *   EBX  - init `lea eax,[ebx+0x1b8] ... add ebx,0x220` at 0x42aae6/
       *          0x42aaf0, `add ebx,9` at 0x42ab77 -> param_1+0x220+9*iVar7
       *          (feeds DrawFontString @0x42ab35 AND BlitRLESprite @0x42ab47)
       *   [esp+0x18] - init param_1+0x1b8 at 0x42aaec, reloaded as
       *          `mov ebp,[esp+0x30]` at 0x42ab55 (6 pushes live, cleaned by
       *          `add esp,0x18` at 0x42ab70) and advanced `add ebp,0xd` /
       *          `mov [esp+0x18],ebp` at 0x42ab74/0x42ab7c
       *          -> param_1+0x1b8+13*iVar7 (feeds BlitRLESprite @0x42ab5d).
       * The previous note calling this second cursor unresolvable was wrong -
       * the stride is a flat 0xd, not the previous iteration's iVar4+0x1c.
       * DrawFontString's own dropped EAX (the same param_1+0x220 string as the
       * BlitRLESprite below it) stays dropped: the port's 3-arg __thiscall
       * signature has no rleData parameter yet - see src/rendering/
       * DrawFontString.c, which is currently a deliberate no-op anyway. Only
       * its ECX `this` (the x) is recovered here. */
      iVar4 = (iVar7 / 2) * 0x1f + 0x3d + iVar6 + 0x3a;
      iVar5 = (iVar7 % 2) * 0x6a + iVar9 + 0x21;
      DrawFontString(iVar5,iVar4 + -1,0x1f);
      BlitRLESprite(iVar5,iVar4 + -1,0xffff,(byte *)(param_1 + 0x220 + iVar7 * 9));
      BlitRLESprite(iVar5,iVar4 + 0xf,0xffff,(byte *)(param_1 + 0x1b8 + iVar7 * 0xd));
      iVar7 = iVar7 + 1;
    } while (iVar7 < (int)(uint)*(byte *)(param_1 + 0x1b4));
  }
  return;
}

