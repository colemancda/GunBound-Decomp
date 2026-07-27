/* RenderChannelUserRow - 0x005074a0 in the original binary.
 *
 * Row renderer (vtable slot 9) for the channel user-list panel: draws up to 7 user rows - a status icon (flag bit 0x80 at +0x42949), a rank/level icon (+0x43e48), and the user name - indexed via the +0x44248 array off g_clientContext. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * BlitRLESprite's 4th arg (rleData) and 1st arg (this/x-cursor) were
 * dropped as in_EAX/a bare `0` in the raw port - recovered via objdump at
 * this function's two call sites (0x507600 and 0x50761e, both `call
 * 0x4eb450`):
 *   mov  esi,[esp+0x10]        ; esi = iVar1
 *   add  esi,0x39              ; esi = iVar1 + 0x39   <-- param_1/this
 *   push 0xfd0f                ; color
 *   lea  eax,[ebx+edi*8]       ; ebx=g_clientContext, edi=iVar2 (user idx)
 *   lea  eax,[edi+eax*1+0x43548] ; eax = g_clientContext + iVar2*9 + 0x43548
 *   push ebp                   ; ebp = iVar7 (x)
 *   mov  ecx,esi
 *   call BlitRLESprite
 * g_clientContext + iVar2*9 + 0x43548 is the same 9-byte-stride chat-name
 * field used elsewhere as `byteVal * 9 + 0x43548 + g_clientContext` (see
 * State03_GameRoomList_ProcessPacket.c:352, ApplyBattleActionToContext.c:
 * 125) - the per-user name string. `esi` (iVar1 + 0x39) is unchanged
 * between both call sites. The second call:
 *   imul edi,edi,0xd           ; edi = iVar2 * 13
 *   lea  ecx,[ebp+0xe]         ; x = iVar7 + 0xe
 *   push 0xffff                ; color
 *   push ecx
 *   lea  eax,[edi+ebx*1+0x41445] ; eax = g_clientContext + iVar2*13 + 0x41445
 *   mov  ecx,esi               ; same this as call 1
 *   call BlitRLESprite
 * g_clientContext + iVar2*0xd + 0x41445 is the well-established 13-byte-
 * stride nickname array (see FUN_00507310.c, State03_GameRoomList_
 * ProcessPacket.c:350/353, ApplyBattleActionToContext.c:120 - same base +
 * stride pattern) - the user's login/nickname string, matching the same
 * shape as FUN_00442e00.c's analogous BlitRLESprite call.
 *
 * RECOVERED (2026-07-27): the four sprite blits and the two FindSpriteFrame
 * lookups had all of their register-passed arguments dropped (FindSpriteFrame
 * with zero args; BlitSprite16bpp/BlitSpriteClipped with their args slid LEFT
 * so the x was landing in the frame slot). Recovered per-site from objdump
 * --start-address=0x5074a0 --stop-address=0x507660 - see each site's comment.
 * Row layout confirmed by the recovery: status icon at m_x+9, rank icon at
 * m_x+0x27, both name strings at m_x+0x39, first row y = m_y+0x25, row pitch
 * 0x1e, at most 7 rows (`cmp eax,7 / jl` at 0x507643).
 */
#include "ghidra_types.h"


void __fastcall RenderChannelUserRow(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int local_4;
  
  if (*(char *)(param_1 + 0x1e) != '\0') {
    return;
  }
  Widget_DrawSelf(param_1);
  iVar4 = g_clientContext;
  FUN_0041b6b0();
  iVar1 = *(int *)(param_1 + 0x28);
  local_4 = 0;
  iVar7 = *(int *)(param_1 + 0x2c) + 0x25;
LAB_005074e1:
  iVar2 = *(int *)(iVar4 + 0x44248 + (*(int *)(&DAT_005f2f3c + iVar4) + local_4) * 4);
  if (iVar2 == -1) {
    return;
  }
  iVar6 = iVar1 + 9;
  /* RECOVERED (2026-07-27), orig 0x50750f-0x507580 - the status-flag icon.
   * EBX is the icon x (iVar6 = m_x+9, from `mov ebx,[esp+0x10] / add ebx,9` at
   * 0x5074fb/0x507504) and EBP the row y (iVar7). ESI is the frame/inner key:
   * `mov esi,1` at 0x507515 on the flag-SET path, `mov esi,2` at 0x507549 on
   * the flag-CLEAR path (`je 0x507545` at 0x50750f takes the ==0 branch, so
   * the C `if ((byte & 0x80) == 0)` arm is the esi=2 one). Both paths do
   *   mov edx,0x12c / mov eax,0xea0e18 / call FindSpriteFrame
   *   push ebp / push ebx / mov eax,esi / call BlitSprite16bpp
   * and the shared tail at 0x507577 is
   *   push 1|2 / mov ecx,ebx / mov eax,ebp / call BlitSpriteClipped
   * EDX (outer key 0x12c) is never rewritten between the FindSpriteFrame and
   * the blit - it is inherited live, as FindSpriteFrame preserves EDX.
   * The raw port's args had slid LEFT: `BlitSprite16bpp(iVar6, iVar7)` was
   * passing the x as the frame handle and the y as the x.
   * Cached scan: tools/findspriteframe_sites.json call_addr 0x507524 (esi=1)
   * and 0x507558 (esi=2). */
  if ((*(byte *)(iVar4 + 0x42949 + iVar2 * 8) & 0x80) == 0) {
    if ((DAT_0079352c != 0) &&
        (iVar4 = FindSpriteFrame((int)&DAT_00ea0e18,0x12c,2), iVar4 != 0)) {
      if (*(char *)(iVar4 + 0x18) != '\x01') {
        uVar8 = 2;
        goto LAB_00507577;
      }
      BlitSprite16bpp(2,iVar6,iVar7,0x12c);
    }
  }
  else if ((DAT_0079352c != 0) &&
           (iVar4 = FindSpriteFrame((int)&DAT_00ea0e18,0x12c,1), iVar4 != 0)) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(1,iVar6,iVar7,0x12c);
    }
    else {
      uVar8 = 1;
LAB_00507577:
      BlitSpriteClipped(uVar8,iVar6,iVar7,0x12c);
    }
  }
  uVar5 = (uint)*(ushort *)(g_clientContext + 0x43e48 + iVar2 * 2);
  if (DAT_0079352c != 0) {
    iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar3 = *(uint *)(iVar4 + 4);
    while (uVar3 < 0x65) {
      if (uVar3 == 100) {
        iVar4 = *(int *)(iVar4 + 0x10);
        uVar3 = *(uint *)(iVar4 + 8);
        if (uVar3 <= uVar5) goto LAB_005075d0;
        break;
      }
      iVar4 = *(int *)(iVar4 + 0x1c);
      uVar3 = *(uint *)(iVar4 + 4);
    }
  }
  goto LAB_00507600;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    uVar3 = *(uint *)(iVar4 + 8);
    if (uVar5 < uVar3) break;
LAB_005075d0:
    if (uVar3 == uVar5) {
      /* RECOVERED (2026-07-27), orig 0x5075de-0x5075fd - the rank/level icon.
       * The frame/inner key is uVar5 (the rank word, still live in EAX since
       * `movzx eax,[ebx+edi*2+0x43e48]` at 0x507593) and ECX is the icon x
       * (`mov ecx,[esp+0x10] / add ecx,0x27` at 0x507583/0x50759b = m_x+0x27);
       * EBP is the row y (iVar7).
       *   mov edx,0x64                     ; outer key 100, reloaded here
       *   push ebp / push ecx              ; (x, y)      -> BlitSprite16bpp
       *   push eax / mov eax,ebp / (ecx=x) -> BlitSpriteClipped
       * EDX is re-set to 0x64 at 0x5075e2 because the inlined two-level list
       * walk above (0x5075a6-0x5075dc) clobbers it - that walk IS a hand-
       * inlined FindSpriteFrame(&DAT_00ea0e18, 100, uVar5), which is why the
       * outer key here is 100 and not 0x12c.
       * The raw port's args had slid LEFT here too: `BlitSprite16bpp(iVar1 +
       * 0x27, iVar7)` was passing the x as the frame handle. */
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(uVar5,iVar1 + 0x27,iVar7,100);
      }
      else {
        BlitSpriteClipped(uVar5,iVar1 + 0x27,iVar7,100);
      }
      break;
    }
  }
LAB_00507600:
  /* RE-VERIFIED (2026-07-27) against orig 0x507600-0x507637: both calls are
   * already complete. `mov esi,[esp+0x10] / add esi,0x39 / mov ecx,esi` gives
   * this = m_x+0x39 for both; push order is (colour, x) so param_2 is EBP
   * (iVar7) / `lea ecx,[ebp+0xe]` (iVar7+0xe) and param_3 the 0xfd0f/0xffff
   * colour; EAX (rleData) is `lea eax,[ebx+edi*8] / lea eax,[edi+eax+0x43548]`
   * (= g_clientContext + iVar2*9 + 0x43548) and `imul edi,edi,0xd / lea
   * eax,[edi+ebx+0x41445]`. See this file's header comment. */
  BlitRLESprite(iVar1 + 0x39,iVar7,0xfd0f,(byte *)(g_clientContext + iVar2 * 9 + 0x43548));
  BlitRLESprite(iVar1 + 0x39,iVar7 + 0xe,0xffff,(byte *)(g_clientContext + iVar2 * 0xd + 0x41445));
  local_4 = local_4 + 1;
  iVar7 = iVar7 + 0x1e;
  iVar4 = g_clientContext;
  if (6 < local_4) {
    return;
  }
  goto LAB_005074e1;
}

