/* RenderPlayerNameplate - 0x004dba80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void RenderPlayerNameplate(int param_1)

{
  char *pcVar1;
  int iVar2;
  int in_EAX;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int local_c0 [16];
  char local_80 [128];
  
  iVar4 = g_clientContext;
  iVar5 = (int)*(char *)(in_EAX + 0x4a0 + param_1);
  local_c0[0] = 0x26;
  local_c0[1] = 0xb1;
  local_c0[3] = 0xb1;
  local_c0[2] = 0x26;
  local_c0[5] = 0x27b;
  local_c0[7] = 0x27b;
  local_c0[4] = 0x1f0;
  local_c0[6] = 0x1f0;
  local_c0[8] = 0x8d;
  local_c0[9] = 0x8d;
  local_c0[10] = 0x125;
  local_c0[0xb] = 0x125;
  local_c0[0xc] = 0x8d;
  local_c0[0xd] = 0x8d;
  iVar2 = local_c0[iVar5];
  local_c0[0xe] = 0x125;
  local_c0[0xf] = 0x125;
  iVar5 = local_c0[iVar5 + 8];
  *(int *)(in_EAX + 0x6bc + param_1 * 8) = iVar2 + 0x43;
  *(int *)(in_EAX + 0x6c0 + param_1 * 8) = iVar5 + 0xe;
  iVar3 = 0;
  piVar6 = (int *)(iVar4 + 0x4737c);
  do {
    if (*piVar6 == param_1) goto LAB_004dbb40;
    iVar3 = iVar3 + 1;
    piVar6 = piVar6 + 1;
  } while (iVar3 < 8);
  iVar3 = -1;
LAB_004dbb40:
  if (iVar3 < (int)(uint)*(byte *)(iVar4 + 0x45124)) {
    if (*(char *)(iVar4 + 0x45914 + param_1) == '\0') {
      /* DrawSprite's arg was dropped as `in_EAX` - objdump at this call
       * site (0x4dbb6a) shows EAX = ((int)(signed char)raw byte at
       * [in_EAX + param_1 + 0x4a0] > 3) + 1, i.e. the same raw byte
       * read into `iVar5` above (line 24) before it's overwritten by
       * the local_c0[] lookups - reusing `in_EAX`/`param_1` as they
       * already appear in this file rather than inventing new names. */
      DrawSprite((*(char *)(in_EAX + 0x4a0 + param_1) > 3) + 1);
      return;
    }
    /* DrawSprite's arg was dropped as `in_EAX` - objdump at this call
     * site (0x4dbb87) shows EAX = (byte)*(byte *)(iVar4 + 0x4590c +
     * param_1) + 1. */
    DrawSprite((int)(uint)(byte)*(char *)(iVar4 + 0x4590c + param_1) + 1);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (param_1 == iVar4) {
      if ((DAT_0079352c != 0) && (iVar4 = FindSpriteFrame(), iVar4 != 0)) {
        if (*(char *)(iVar4 + 0x18) == '\x01') {
          BlitSprite16bpp(iVar2 + 99,iVar5 + 0x20);
        }
        else {
          /* BlitSpriteClipped's x/y args were dropped (ECX/EAX) - this
           * site's own disassembly (0x4dbc00) shows the same x/y pair
           * passed to the BlitSprite16bpp() sibling call just above:
           * ECX=iVar2+99, EAX=iVar5+0x20. See BlitSpriteClipped.c's
           * header comment for the full recovery. */
          BlitSpriteClipped(7,iVar2 + 99,iVar5 + 0x20);
        }
      }
    }
    /* DrawSprite's arg was dropped as `in_EAX` - objdump at this call
     * site (0x4dbc28) shows EAX = (ushort)*(ushort *)(g_clientContext +
     * param_1*2 + 0x4591c) (freshly reloads g_clientContext here rather
     * than reusing `iVar4`, which may have been clobbered by the
     * FindSpriteFrame() call just above). */
    DrawSprite((int)(uint)*(ushort *)(g_clientContext + param_1 * 2 + 0x4591c));
    pcVar1 = (char *)(g_clientContext + param_1 * 9 + 0x457a9);
    if (*pcVar1 != '\0') {
      _sprintf(local_80,s__s__3d__3d__005536b8,pcVar1,
               *(undefined4 *)(g_clientContext + 0x4597c + param_1 * 4),
               *(undefined4 *)(g_clientContext + 0x4599c + param_1 * 4));
      /* BlitRLESprite's 1st arg (this/x-cursor) and 4th arg (rleData) were
       * dropped - objdump at this call site (0x4dbc6f) shows ECX =
       * iVar2 + 0x16 (the same running x-cursor `esi` holds at the
       * BlitSprite16bpp/BlitSpriteClipped calls above, offset by 0x16)
       * and EAX = the same `local_80` buffer just sprintf'd above
       * (esp-relative address matches exactly). */
      BlitRLESprite(iVar2 + 0x16,iVar5 + 0x13,0xf800,(byte *)local_80);
    }
    iVar4 = g_clientContext;
    /* BlitRLESprite's 1st arg (this/x-cursor) and 4th arg (rleData) were
     * dropped - objdump at this call site (0x4dbc96) shows ECX =
     * iVar2 + 0x16 (same x-cursor as the call above; unchanged between
     * the two sites) and EAX = g_clientContext + param_1*0xd + 0x457f1,
     * the room-slot name field (see ClientContext.h's Ctx_roomSlotName -
     * a per-slot name string distinct from the `pcVar1` field used above). */
    BlitRLESprite(iVar2 + 0x16,iVar5 + 0x21,0,
                  (byte *)(g_clientContext + param_1 * 0xd + 0x457f1));
    if ((g_bBattleSessionActive == '\0') && (*(char *)(iVar4 + 0x45914 + param_1) == '\x04')) {
      if ((DAT_0079352c != 0) && (iVar4 = FindSpriteFrame(), iVar4 != 0)) {
        if (*(char *)(iVar4 + 0x18) != '\x01') {
          /* BlitSpriteClipped's x/y args were dropped (ECX/EAX) - this
           * site's own disassembly (0x4dbd10) shows ECX=iVar2+0x69,
           * EAX=iVar5-0x1e, the same pair passed to the BlitSprite16bpp()
           * sibling call a few lines below. See BlitSpriteClipped.c's
           * header comment for the full recovery. */
          BlitSpriteClipped(6,iVar2 + 0x69,iVar5 + -0x1e);
          return;
        }
        BlitSprite16bpp(iVar2 + 0x69,iVar5 + -0x1e);
        return;
      }
    }
    else {
      /* DrawSprite's arg is dropped here too (`in_EAX`), but left
       * unfixed: objdump at this call site (0x4dbd39) shows the two
       * paths reaching it use *different* struct fields (+0x449ba vs
       * +0x45914) than the single combined `if` condition above - this
       * `if`/`else` needs its own control-flow fix first. See
       * DrawSprite.c's header comment. */
      DrawSprite(0);
    }
  }
  return;
}

