/* RenderRoomCard - 0x0042a220 in the original binary.
 *
 * Draws one room card in the lobby's 2x3 grid: background (3-state by selection), flag/mode/status/lock icons, room number, and population gauge. Full offset/sprite tables in docs/screens/03_game_room_list.md. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall RenderRoomCard(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  char local_80 [128];
  
  if (param_2 / 3 == 0) {
    iVar7 = 0x18;
    iVar8 = 1;
  }
  else {
    iVar7 = 0x144;
    iVar8 = 4;
  }
  iVar6 = (param_2 % 3) * 0x3c;
  if (*(int *)(param_1 + 4) == param_2) {
    iVar8 = iVar8 + 2;
  }
  else if (*(int *)(param_1 + 8) == param_2) {
    iVar8 = iVar8 + 1;
  }
  /* RECOVERED (2026-07-20), orig 0x42a280-0x42a2ac. In the original EBP is the
   * card's x base (iVar7) and EDI its y base (= iVar6 + 0x3a, from
   * `imul edx,edx,0x3c / add edx,0x3a / mov edi,edx` at 0x42a25c). ESI is the
   * background frame index (iVar8).
   *   mov edx,0x2710 / mov eax,0xea0e18 / call FindSpriteFrame
   *   push edi / push ebp / mov eax,esi / call BlitSprite16bpp
   *   push esi / mov eax,edi / mov ecx,ebp / call BlitSpriteClipped
   * -> FindSpriteFrame(container=EAX, outerKey=EDX=0x2710, innerKey=ESI),
   *    BlitSprite16bpp(frame=EAX, x=ebp, y=edi, outerKey),
   *    BlitSpriteClipped(frame=stack, x=ECX, y=EAX, outerKey).
   * Cached scan: tools/findspriteframe_sites.json (call_addr 0x42a28a). */
  if ((DAT_0079352c != 0) &&
      (iVar4 = FindSpriteFrame((int)&DAT_00ea0e18,0x2710,iVar8), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar8,iVar7,iVar6 + 0x3a,0x2710);
    }
    else {
      BlitSpriteClipped(iVar8,iVar7,iVar6 + 0x3a,0x2710);
    }
  }
  /* RECOVERED (2026-07-20), orig 0x42a2d0-0x42a30c: `lea ebx,[edi+8]` (y =
   * iVar6+0x42) / mov esi,0xe / mov edx,0x2710 / mov eax,0xea0e18, then
   * `lea eax,[ebp+0xb1] / push ebx / push eax / mov eax,esi` (16bpp) and
   * `push 0xe / mov eax,ebx / lea ecx,[ebp+0xb1]` (clipped). Frame is 0xe at
   * both. Cached scan call_addr 0x42a2df (esi=0xe). */
  if (((*(char *)(g_clientContext + 0x449b4 + param_2) != '\0') && (DAT_0079352c != 0)) &&
     (iVar8 = FindSpriteFrame((int)&DAT_00ea0e18,0x2710,0xe), iVar8 != 0)) {
    if (*(char *)(iVar8 + 0x18) == '\x01') {
      BlitSprite16bpp(0xe,iVar7 + 0xb1,iVar6 + 0x42,0x2710);
    }
    else {
      BlitSpriteClipped(0xe,iVar7 + 0xb1,iVar6 + 0x42,0x2710);
    }
  }
  bVar1 = *(byte *)(g_clientContext + 0x4499c + param_2);
  iVar8 = g_clientContext + 0x4499c;
  /* RECOVERED (2026-07-20), orig 0x42a347-0x42a37d: `add esi,0xa` (esi =
   * bVar1+10, the mode icon frame) / `lea ebx,[edi+0xc]` (y = iVar6+0x46) /
   * mov edx,0x1f4 / mov eax,0xea0e18; then `lea eax,[ebp+0xc3] / push ebx /
   * push eax / mov eax,esi` (16bpp) and `push esi / mov eax,ebx /
   * lea ecx,[ebp+0xc3]` (clipped). Outer key here is 0x1f4, not 0x2710.
   * Cached scan call_addr 0x42a351. */
  if ((DAT_0079352c != 0) &&
      (iVar4 = FindSpriteFrame((int)&DAT_00ea0e18,0x1f4,bVar1 + 10), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(bVar1 + 10,iVar7 + 0xc3,iVar6 + 0x46,0x1f4);
    }
    else {
      BlitSpriteClipped(bVar1 + 10,iVar7 + 0xc3,iVar6 + 0x46,0x1f4);
    }
  }
  bVar1 = *(byte *)(g_clientContext + 0x449a2 + param_2);
  iVar4 = g_clientContext + 0x449a2;
  /* RECOVERED (2026-07-20), orig 0x42a3b4-0x42a3ea: same shape as the site
   * above - esi = bVar1+10, edx = 0x1f4, EBX is still `edi+0xc` (y =
   * iVar6+0x46, unmodified since 0x42a33e), x = `lea ecx/eax,[ebp+0xd2]`.
   * Cached scan call_addr 0x42a3be. */
  if ((DAT_0079352c != 0) &&
      (iVar5 = FindSpriteFrame((int)&DAT_00ea0e18,0x1f4,bVar1 + 10), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(bVar1 + 10,iVar7 + 0xd2,iVar6 + 0x46,0x1f4);
    }
    else {
      BlitSpriteClipped(bVar1 + 10,iVar7 + 0xd2,iVar6 + 0x46,0x1f4);
    }
  }
  bVar1 = *(byte *)(g_clientContext + 0x44986 + param_2 * 4);
  bVar2 = *(byte *)(g_clientContext + 0x4497c + param_2);
  /* RECOVERED (2026-07-20), orig 0x42a42d-0x42a45d: `and edx,3 / imul
   * edx,edx,0xb / add edx,eax / mov esi,edx` gives the frame the port already
   * computes as `(bVar1 & 3) * 0xb + bVar2`; `lea ebx,[edi+0x21]` is y =
   * iVar6+0x5b (also spilled to esp+0x14 for the final blit below);
   * mov edx,0x2716 / mov eax,0xea0e18; x = `lea ecx/eax,[ebp+0x6a]`.
   * Cached scan call_addr 0x42a437 (esi = edx). */
  if ((DAT_0079352c != 0) &&
      (iVar5 = FindSpriteFrame((int)&DAT_00ea0e18,0x2716,(bVar1 & 3) * 0xb + (uint)bVar2),
      iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp((bVar1 & 3) * 0xb + (uint)bVar2,iVar7 + 0x6a,iVar6 + 0x5b,0x2716);
    }
    else {
      BlitSpriteClipped((bVar1 & 3) * 0xb + (uint)bVar2,iVar7 + 0x6a,iVar6 + 0x5b,0x2716);
    }
  }
  uVar9 = 9;
  if (*(char *)(g_clientContext + 0x449a8 + param_2) == '\0') {
    if (*(char *)(iVar8 + param_2) == *(char *)(iVar4 + param_2)) {
      uVar9 = 8;
    }
  }
  else {
    uVar9 = 7;
  }
  /* RECOVERED (2026-07-20), orig 0x42a49c-0x42a4dc: ESI is the 7/8/9 status
   * frame the port already computes as uVar9 (`mov esi,9 / mov esi,7 /
   * mov esi,8` at 0x42a47b-0x42a497); `lea ebx,[edi+0x1b]` -> y = iVar6+0x55;
   * mov edx,0x2710; x = `lea ecx/eax,[ebp+0x13]`. Cached scan call_addr
   * 0x42a4b6 (esi=8 on the branch it sampled). */
  if ((DAT_0079352c != 0) &&
      (iVar8 = FindSpriteFrame((int)&DAT_00ea0e18,0x2710,uVar9), iVar8 != 0)) {
    if (*(char *)(iVar8 + 0x18) == '\x01') {
      BlitSprite16bpp(uVar9,iVar7 + 0x13,iVar6 + 0x55,0x2710);
    }
    else {
      BlitSpriteClipped(uVar9,iVar7 + 0x13,iVar6 + 0x55,0x2710);
    }
  }
  if (*(char *)(g_clientContext + 0x449ae + param_2) != '\0') {
    /* RECOVERED (2026-07-20), orig 0x42a51f-0x42a561: mov esi,0xf (the lock
     * icon frame) / `lea ebx,[edi+0x18]` -> y = iVar6+0x52 / mov edx,0x2710.
     * The x already in the port (spilled to esp+0x10 at 0x42a50f) is reused
     * as the blits' x. Both blit paths re-set `mov edx,0x2710` immediately
     * before the call, confirming the outer key. Cached scan call_addr
     * 0x42a52e (esi=0xf). */
    if ((DAT_0079352c != 0) && (iVar8 = FindSpriteFrame((int)&DAT_00ea0e18,0x2710,0xf), iVar8 != 0))
    {
      if (*(char *)(iVar8 + 0x18) == '\x01') {
        BlitSprite16bpp(0xf,(-(uint)(param_2 / 3 != 0) & 0xffffff06) + 0xea + iVar7,iVar6 + 0x52,
                        0x2710);
      }
      else {
        BlitSpriteClipped(0xf,(-(uint)(param_2 / 3 != 0) & 0xffffff06) + 0xea + iVar7,iVar6 + 0x52,
                          0x2710);
      }
    }
  }
  _sprintf(local_80,(char *)&PTR_DAT_00551ecc,*(int *)(g_clientContext + 0x44664 + param_2 * 4) + 1);
  /* RECOVERED (2026-07-20), orig 0x42a58d-0x42a5a3:
   *   push 0xb / push 3 / lea ecx,[esp+0x34] / push ecx / push 0x14
   *   lea ebx,[edi+0xb] / lea ecx,[ebp+0x11] / mov esi,0x1f4
   * BlitSpriteText's promoted signature is (x=ECX, glyphBase, string, count,
   * advance, y=EBX, charsetKey=ESI) - see src/rendering/BlitSpriteText.c's
   * header, which names this very call site. The raw port dropped the ECX x,
   * the EBX y and the ESI charset key; EBP is the card's x base (iVar7) and
   * EDI its y base (iVar6+0x3a), so x=iVar7+0x11 and y=iVar6+0x45. */
  BlitSpriteText(iVar7 + 0x11,0x14,(int)local_80,3,0xb,iVar6 + 0x45,0x1f4);
  /* FIXED (2026-07-15): SetClipRect's 4 corner args were dropped. x1/x2
   * confirmed by this file's own already-existing comment below
   * (ecx=iVar7+0x37, eax=iVar7+0xc1 - NOT the BlitRLESprite args quoted
   * there, which are for the DIFFERENT following call). y1/y2 traced via
   * angr: `imul edx,edx,0x3c; add edx,0x3a; mov edi,edx` at 0x42a25c-
   * 0x42a264 confirms old-edi = iVar6+0x3a (matching iVar6's own
   * computation just above), so y2=old_edi+0xa=iVar6+0x44 and
   * y1=old_edi+0x16=iVar6+0x50 - identical formula to FUN_0042a680.c's
   * sibling call, cross-validated. */
  SetClipRect(iVar7 + 0x37, iVar7 + 0xc1, iVar6 + 0x50, iVar6 + 0x44);
  /* BlitRLESprite's 1st arg (this/x-cursor, dropped to a bare `0` when the
   * raw port's call-site text wasn't updated for the promoted signature)
   * and 4th arg (rleData, dropped as `in_EAX`) recovered via objdump at
   * this call site (0x42a5da): ECX = iVar7+0x37 (last explicit `lea
   * ecx,[ebp+0x37]` before this call; the intervening SetClipRect call
   * only reads ecx, never writes it, so it survives unmodified - matches
   * this function's other BlitSprite16bpp/BlitSpriteClipped sites, which
   * all use iVar7+<offset> as their x-position), and EAX =
   * g_clientContext + 0x4467c + param_2*0x80 (Ctx_roomPlayerName(param_2),
   * the room-card's player/host name buffer - see src/cxx/ClientContext.h
   * and ARCHITECTURE.md's 0x2105 packet handler). */
  BlitRLESprite(iVar7 + 0x37,iVar6 + 0x44,0xffff,(byte *)(g_clientContext + 0x4467c + param_2 * 0x80));
  SetClipRect(0, 0x31f, 0x257, 0);
  uVar3 = *(uint *)(g_clientContext + 0x44984 + param_2 * 4);
  /* RECOVERED (2026-07-20), orig 0x42a609-0x42a65e: `shr esi,0x12 / and esi,3
   * / add esi,0xa` is the frame the port already computes as
   * `(uVar3 >> 0x12 & 3) + 10`; `add ebp,0xb1` at 0x42a614 makes EBP the x
   * (iVar7+0xb1); `mov eax,[esp+0x14]` at 0x42a63c reloads the y spilled from
   * `lea ebx,[edi+0x21]` back at 0x42a40f (= iVar6+0x5b) and both blit paths
   * use it (16bpp: `push eax / push ebp`; clipped: `push esi / mov ecx,ebp`
   * with that same EAX as y). edx=0x2710. Cached scan call_addr 0x42a62f. */
  if ((DAT_0079352c != 0) &&
      (iVar8 = FindSpriteFrame((int)&DAT_00ea0e18,0x2710,(uVar3 >> 0x12 & 3) + 10), iVar8 != 0)) {
    if (*(char *)(iVar8 + 0x18) == '\x01') {
      BlitSprite16bpp((uVar3 >> 0x12 & 3) + 10,iVar7 + 0xb1,iVar6 + 0x5b,0x2710);
      return;
    }
    BlitSpriteClipped((uVar3 >> 0x12 & 3) + 10,iVar7 + 0xb1,iVar6 + 0x5b,0x2710);
  }
  return;
}

