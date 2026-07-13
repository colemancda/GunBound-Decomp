/* FUN_004b3e60 - 0x004b3e60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004b3e60(undefined2 *param_1)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;

  if (*(char *)(param_1 + 0x191) != '\0') {
    iVar3 = *(int *)(param_1 + 0x194);
    if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar3,0x17d);
      }
      else {
        BlitSpriteClipped(0);
      }
    }
    uVar1 = *param_1;
    if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar3 + 0x13,0x18c);
      }
      else {
        BlitSpriteClipped(uVar1);
      }
    }
    DrawFontString(0x18b,0x1f);
    /* objdump @ 0x4b3f2c-0x4b3f3a: ecx (this) = iVar3+0x24 (esi, loaded at
     * 0x4b3f19 `lea esi,[ebx+0x24]` and unchanged since); eax (rleData) =
     * (byte *)param_1+2 (edi, loaded at 0x4b3f16 `lea edi,[ebp+0x2]` and
     * unchanged since - the same pointer DrawFontString's own dropped
     * in_EAX arg reads a few instructions earlier). */
    BlitRLESprite(iVar3 + 0x24,0x18b,0xffff,(byte *)param_1 + 2);
    /* objdump @ 0x4b3f3f-0x4b3f4e: ecx (this) = iVar3+0x24 (esi, still
     * unchanged since 0x4b3f19); eax (rleData) = (byte *)param_1+0x15
     * (`lea eax,[ebp+0x15]` right before this call). */
    BlitRLESprite(iVar3 + 0x24,0x199,0xffff,(byte *)param_1 + 0x15);
    iVar2 = 0x1b0;
    iVar3 = 6;
    /* objdump @ 0x4b3f53-0x4b3f81 (loop body): ecx (this) = iVar3+0x13
     * (saved to [esp+0x14] at 0x4b3ed1 `lea edi,[ebx+0x13]`, before iVar3
     * is reused as the loop counter - re-derived here as the original
     * iVar3+0x13). eax (rleData) = esi, initialized at 0x4b3f53
     * `lea esi,[ebp+0x22]` ((byte *)param_1+0x22) and advanced by 0x80
     * bytes per iteration (`add esi,0x80` at 0x4b3f77), in lockstep with
     * iVar2's own per-iteration +0xf advance. */
    pbVar4 = (byte *)param_1 + 0x22;
    iVar5 = *(int *)(param_1 + 0x194) + 0x13;
    do {
      BlitRLESprite(iVar5,iVar2,0xffff,pbVar4);
      pbVar4 = pbVar4 + 0x80;
      iVar2 = iVar2 + 0xf;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return;
}

