/* FUN_0041bce0 - 0x0041bce0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0041bce0(int param_1)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 local_14;
  int local_10;
  undefined4 local_8;
  int local_4;
  
  local_4 = 0;
  local_10 = 0x13a;
  iVar9 = param_1;
LAB_0041bd02:
  local_8 = 0x1f;
  iVar8 = (((int)*(uint *)(param_1 + 0x3b97c) < 1) - 1 & *(uint *)(param_1 + 0x3b97c)) + local_4;
  uVar3 = *(ushort *)(param_1 + 0x3f73c + iVar8 * 2);
  if (((uVar3 != 0) && (uVar5 = uVar3 - 1, DAT_0079352c != 0)) && (-1 < (int)uVar5)) {
    iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar4 = *(uint *)(iVar7 + 4);
    while (uVar4 < 0x35) {
      if (uVar4 == 0x34) {
        iVar7 = *(int *)(iVar7 + 0x10);
        uVar4 = *(uint *)(iVar7 + 8);
        if (uVar4 <= uVar5) goto LAB_0041bd81;
        break;
      }
      iVar7 = *(int *)(iVar7 + 0x1c);
      uVar4 = *(uint *)(iVar7 + 4);
    }
  }
  goto LAB_0041bdb7;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar4 = *(uint *)(iVar7 + 8);
    if (uVar5 < uVar4) break;
LAB_0041bd81:
    if (uVar4 == uVar5) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(0x24,local_10);
      }
      else {
        BlitSpriteClipped(uVar5);
      }
      break;
    }
  }
LAB_0041bdb7:
  switch(*(undefined1 *)(param_1 + 0x3c4d8 + iVar8)) {
  case 0:
    iVar9 = 0xffff;
    local_14 = 0xffff;
    local_8 = 0x1f;
    break;
  case 1:
    iVar9 = 0xc618;
    goto LAB_0041bebd;
  case 2:
    iVar9 = 0;
    local_14 = 0xffe0;
    break;
  case 3:
    iVar9 = 0xf800;
    goto LAB_0041bebd;
  case 4:
    local_14 = 0xafff;
    iVar9 = 0xf0;
    break;
  case 5:
    iVar9 = 0;
    local_14 = 0xc7f8;
    break;
  case 6:
  case 8:
    iVar9 = 0x8000;
    local_14 = 0xf800;
    break;
  case 7:
    local_14 = 0x78e0;
    iVar9 = 0xfdb4;
    local_8 = 0;
    break;
  case 9:
    iVar9 = 0x400;
    local_14 = 0xfff2;
    break;
  case 10:
    local_14 = 0xf800;
    iVar9 = 0xfebf;
    break;
  case 0xb:
    local_14 = 0xfc20;
    iVar9 = 0x4880;
    break;
  case 0xc:
    local_14 = 0x7e0;
    iVar9 = 0x210a;
    break;
  case 0xd:
    local_14 = 0x1f;
    iVar9 = 0xf6bf;
    break;
  case 0xe:
    local_14 = 0xc018;
    iVar9 = 0xfecf;
    break;
  case 0xf:
    local_14 = 0;
    iVar9 = 0xffff;
    break;
  case 0x10:
    iVar9 = 0;
LAB_0041bebd:
    local_14 = 0xffff;
  }
  pcVar6 = (char *)(iVar8 * 9 + 0x3b984 + param_1);
  DrawFontString(local_10,local_8);
  /* BlitRLESprite's 1st (this/param_1) and 4th (rleData) args were dropped
   * as ECX/in_EAX in the raw port - objdump at this call site (0x41bef0)
   * shows ECX = local_4 (the outer loop counter) and EAX = pcVar6 (the
   * field-name pointer just computed above, walked by the strlen loop
   * immediately below). */
  BlitRLESprite(local_4,local_10,iVar9,(byte *)pcVar6);
  do {
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  bVar2 = *(byte *)(param_1 + 0x3c4d8 + iVar8);
  if ((bVar2 < 2) || (bVar2 == 7)) {
    pcVar6 = (char *)(param_1 + (iVar8 * 5 + 0xef42) * 4);
    /* NOT RECOVERED (left as placeholder): objdump at 0x41bfc6 shows
     * this call's ECX = a dead stack slot ([esp+0x18], holding either the
     * literal 0x24 or 0x32 depending on a control-flow branch ~30 lines
     * above that Ghidra never surfaced as a named C variable) PLUS `ebp`,
     * an accumulated pixel-width (strlen(previous string)*6) that Ghidra
     * also dropped - neither is expressible via any variable already
     * visible in this function's C. EAX at this site IS recoverable
     * (= pcVar6, computed just above), but the two args are fixed
     * together per the task's call-site granularity, so left as-is
     * pending a full ECX reconstruction. */
    BlitRLESprite(0,local_10 + 1,0,(byte *)0);
    /* NOT RECOVERED: objdump at 0x41bfd9 shows ECX = local_4 + the same
     * dropped `ebp` accumulator described above (no C variable holds it);
     * EAX = pcVar6 (same pointer as the call above, recoverable but
     * withheld for the same reason). */
    BlitRLESprite(0,local_10,iVar9,(byte *)0);
    do {
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    /* NOT RECOVERED: objdump at 0x41c016 shows this call reads a SECOND,
     * different field pointer (param_1 + iVar8*0x80 + 0x3c53c) into EAX -
     * not `pcVar6` above and not computed anywhere in this function's C
     * (Ghidra dropped it entirely, same pattern flagged in
     * BlitRLESprite.c's header comment re: RenderReadyRoomChatRow.c).
     * ECX is the same undocumented mystery-constant + ebp seen above. */
    BlitRLESprite(0,local_10 + 1,0,(byte *)0);
    /* NOT RECOVERED: objdump at 0x41c025 shows ECX = the bare mystery
     * constant (no +ebp this time) and EAX = the same new field pointer
     * from the call directly above - same missing-variable problem. */
    BlitRLESprite(0,local_10,iVar9,(byte *)0);
  }
  else {
    pcVar6 = (char *)(param_1 + (iVar8 * 5 + 0xef42) * 4);
    DrawFontString(local_10,iVar9);
    /* NOT RECOVERED: objdump at 0x41bf55 shows ECX = the dropped mystery
     * constant + a dropped strlen-based `ebp` accumulator (see above),
     * and EAX = a field pointer computed as
     * param_1 + (iVar8*5+0xef42)*4 - i.e. the SAME expression as
     * `pcVar6` just above, so EAX here does equal pcVar6; ECX still
     * isn't recoverable from any variable visible in this C, so this
     * site is left as a placeholder rather than fixing only one arg. */
    BlitRLESprite(0,local_10,local_14,(byte *)0);
    do {
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    DrawFontString(local_10,iVar9);
    /* NOT RECOVERED: objdump at 0x41bfa0 shows this call reads a SECOND,
     * different field pointer (param_1 + iVar8*0x80 + 0x3c53c) into EAX,
     * not `pcVar6` - the same dropped-second-pointer pattern as the
     * if-branch above; ECX is again the undocumented mystery+ebp value. */
    BlitRLESprite(0,local_10,local_14,(byte *)0);
  }
  local_10 = local_10 + 0xf;
  local_4 = local_4 + 1;
  if (0x1fc < local_10) {
    return;
  }
  goto LAB_0041bd02;
}

