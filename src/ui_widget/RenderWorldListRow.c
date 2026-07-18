/* RenderWorldListRow - 0x0050dc80 in the original binary.
 *
 * Draws one server ("world") row of the WORLD LIST, given the row index in a
 * register. Called once per server by the panel's render slot (0x50dc40),
 * which loops the server count at g_clientContext+0x3f808. Layout is a
 * 2-column grid: x = (i%2)*0xf7 + 0x16 + panelX, y = (i/2)*0x49 + 0x2d +
 * panelY. Draws: a row-background sprite whose state reflects selection
 * (state 3 when i == g_gameStateVTableArray[2]+8, the highlighted slot; state
 * 2 when i == +0xc); the server number (sprintf serverId+1, via BlitRLESprite
 * white); the name + two description lines (BlitRLESprite, colour 0xb77f); and
 * a population gauge (currentPlayers*100/maxCapacity bucketed via thresholds at
 * g_fullnessGaugeThresholds -> gauge sprite, the F/E dial). Reads the SoA
 * (serverId +0x3f81a, onlineFlag +0x3f809, players +0x410ca, capacity +0x410ea).
 *
 * Dropped-argument fix (confirmed via objdump -Mintel on the .gme at the
 * call site 0x50dc61-0x50dc65): the caller (WorldListPanel_Draw,
 * 0x50dc40) does `mov eax,esi` / `mov ecx,edi` / `call 0x50dc80` per
 * loop iteration - i.e. this function is __fastcall(this=ECX,
 * index=EAX), with the row index passed as a non-standard extra
 * argument in EAX rather than a real parameter. Ghidra's decompile
 * missed this and emitted it as an uninitialized read of `in_EAX`;
 * promoted to a real second parameter here.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-14): four dropped-argument bugs recovered via objdump
 * (orig 0x50dc80-0x50df31):
 *   - The first FindSpriteFrame() (row-background lookup) was zero-arg;
 *     real args are (container=&DAT_00ea0e18, outerKey=0x2711, cVar8)
 *     (`mov edx,0x2711` / `mov eax,0xea0e18` immediately before
 *     `call 0x4f30c0`, ESI=cVar8 already live).
 *   - Its two blit calls (row background) were stale pre-migration
 *     shapes missing the leading `frame`=cVar8 arg.
 *   - The gauge-sprite blit calls at the end were missing their leading
 *     `frame`=uVar5 arg (EAX stays live as uVar5 across the manually-
 *     inlined list-walk that immediately precedes each).
 * The second "FindSpriteFrame"-shaped list-walk (the gauge-sprite lookup
 * over the 0x2711 sprite set) is already a correct manual inline in both
 * the original and this port - not a dropped call, no fix needed there.
 */
#include "ghidra_types.h"


void __fastcall RenderWorldListRow(int param_1, uint in_EAX)

{
  int iVar1;
  int iVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  char cVar8;
  int iVar9;
  int iVar10;
  int local_84;
  char local_80 [128];
  
  uVar5 = in_EAX & 0x80000001;
  if ((int)uVar5 < 0) {
    uVar5 = (uVar5 - 1 | 0xfffffffe) + 1;
  }
  iVar1 = uVar5 * 0xf7 + 0x16 + *(int *)(param_1 + 0x28);
  iVar2 = ((int)in_EAX / 2) * 0x49 + 0x2d + *(int *)(param_1 + 0x2c);
  cVar8 = (-(*(char *)(g_clientContext + 0x3f809 + in_EAX) != '\x01') & 3U) + 1;
  if (*(uint *)(g_gameStateVTableArray[2] + 0xc) == in_EAX) {
    cVar8 = '\x02';
  }
  if (*(uint *)(g_gameStateVTableArray[2] + 8) == in_EAX) {
    cVar8 = '\x03';
  }
  if ((DAT_0079352c != 0) &&
      (iVar6 = FindSpriteFrame((int)&DAT_00ea0e18,0x2711,cVar8), iVar6 != 0)) {
    if (*(char *)(iVar6 + 0x18) == '\x01') {
      BlitSprite16bpp(cVar8,iVar1,iVar2,0x2711);
    }
    else {
      BlitSpriteClipped(cVar8,iVar1,iVar2,0x2711);
    }
  }
  _sprintf(local_80,&g_rowIndexFormat,*(ushort *)(g_clientContext + 0x3f81a + in_EAX * 2) + 1);
  pcVar7 = local_80;
  do {
    cVar3 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar3 != '\0');
  /* BlitSpriteText's real args (recovered from orig 0x50dd68-0x50dd89):
   * x=iVar1+0xe (ecx), glyphBase=0xf8, string=local_80, count=strlen,
   * advance=8, y=iVar2+8 (ebx+8), charsetKey=0x32 (esi). The prior call
   * passed strlen where the string pointer belongs, faulting inside
   * BlitSpriteText - see that file's header. */
  BlitSpriteText(iVar1 + 0xe,0xf8,(int)local_80,(int)pcVar7 - (int)(local_80 + 1),8,iVar2 + 8,0x32);
  pcVar7 = local_80;
  do {
    cVar3 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar3 != '\0');
  DrawFontString(iVar2 + 9,0);
  pcVar7 = local_80;
  do {
    cVar3 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar3 != '\0');
  /* BlitRLESprite's dropped args (confirmed via objdump -Mintel at this
   * call site, 0x50dde7): ECX (this) = ebp+eax*8+0x11, i.e.
   * iVar1 + strlen(local_80)*8 + 0x11 (the just-computed server-number
   * string length feeds the x-cursor offset); EAX (rleData) = esi =
   * g_clientContext + 0x3f84a + in_EAX*0x80, the per-row world NAME
   * field (ClientContext.h's `name[16][128]`) - NOT local_80, which is
   * only reused here to size the cursor advance. */
  BlitRLESprite(iVar1 + ((int)pcVar7 - (int)(local_80 + 1)) * 8 + 0x11,iVar2 + 9,0xffff,
                (byte *)(g_clientContext + 0x3f84a + in_EAX * 0x80));
  iVar6 = iVar2 + 0x1e;
  local_84 = 2;
  do {
    /* BlitRLESprite's dropped args (confirmed via objdump -Mintel at this
     * call site, 0x50de1b, looped): ECX (this) = ebp+0x10, i.e.
     * iVar1 + 0x10, constant across both loop iterations (unlike the
     * advancing x-cursor iVar6, which is only the stack x arg here);
     * EAX (rleData) = esi = g_clientContext + 0x4004a + in_EAX*0x100 +
     * (loop iteration)*0x40, the per-row description-line field
     * (ClientContext.h's `desc[16][256]`, one 0x40-byte line per
     * iteration - the "two description lines" from this file's header
     * comment). */
    BlitRLESprite(iVar1 + 0x10,iVar6,0xb77f,
                  (byte *)(g_clientContext + 0x4004a + in_EAX * 0x100 + (2 - local_84) * 0x40));
    iVar6 = iVar6 + 0xe;
    local_84 = local_84 + -1;
  } while (local_84 != 0);
  iVar6 = 5;
  if (cVar8 == '\x04') {
    iVar6 = 6;
  }
  iVar10 = iVar6;
  if (*(char *)(g_clientContext + 0x3f809 + in_EAX) == '\x01') {
    iVar9 = 0;
    do {
      iVar10 = iVar9;
      if ((int)((ulonglong)((uint)*(ushort *)(g_clientContext + 0x410ca + in_EAX * 2) * 100) /
               (ulonglong)(longlong)(int)(uint)*(ushort *)(g_clientContext + 0x410ea + in_EAX * 2)) <
          (int)g_fullnessGaugeThresholds[iVar9]) break;
      iVar9 = iVar9 + 1;
      iVar10 = iVar6;
    } while (iVar9 < 5);
  }
  uVar5 = iVar10 + 5;
  if ((DAT_0079352c != 0) && (-1 < (int)uVar5)) {
    iVar6 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar4 = *(uint *)(iVar6 + 4);
    if (uVar4 < 0x2712) {
      while (uVar4 != 0x2711) {
        iVar6 = *(int *)(iVar6 + 0x1c);
        uVar4 = *(uint *)(iVar6 + 4);
        if (0x2711 < uVar4) {
          return;
        }
      }
      iVar6 = *(int *)(iVar6 + 0x10);
      uVar4 = *(uint *)(iVar6 + 8);
      if (uVar4 <= uVar5) {
        while (uVar4 != uVar5) {
          iVar6 = *(int *)(iVar6 + 0x10);
          uVar4 = *(uint *)(iVar6 + 8);
          if (uVar5 < uVar4) {
            return;
          }
        }
        if (*(char *)(iVar6 + 0x18) == '\x01') {
          BlitSprite16bpp(uVar5,iVar1 + 0xb5,iVar2,0x2711);
          return;
        }
        BlitSpriteClipped(uVar5,iVar1 + 0xb5,iVar2,0x2711);
      }
    }
  }
  return;
}

