/* BlitSpriteText - 0x004ed9f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER ARGUMENTS (pattern #1) - investigated, NOT fixed here:
 * this function reads `unaff_ESI` with no corresponding parameter, and
 * additionally uses EBX (never written anywhere in this function's own
 * body) as the fixed y-coordinate passed to its BlitSprite16bpp()/
 * BlitSpriteClipped() calls - a second, silent register argument. Its
 * already-declared `param_1` (the __thiscall ECX arg - the string's
 * starting x position, walked forward by `param_1 += param_5` each
 * character) is ALSO dropped at every call site below: none of them
 * pass a 5th/"this" argument at all, so whatever garbage is left in ECX
 * at each call gets used as the initial x instead.
 *
 * Confirmed via objdump at the function's own entry (0x4ed9f0):
 *   mov edi,ecx    ; edi = param_1 (this/ECX - the running x position)
 *   ...
 *   cmp edx,esi    ; the inlined tree-walk's outer key (image/charset
 *                    group, node+4) compared against unaff_ESI - never
 *                    written by this function itself
 *   ...
 *   mov edx,esi ; push ebx; push edi; call BlitSprite16bpp   (16bpp path:
 *                 args (x=ebx, y=edi=param_1)      <- ebx never written
 *                                                       here either)
 *   push eax; mov eax,ebx; mov ecx,edi; call BlitSpriteClipped (clipped
 *                 path: args (frame=uVar1, x=ebx, y=edi=param_1))
 *
 * Cross-checked against every call site in the binary (35 call sites in
 * 9 files: RenderRoomCard.c @0x42a5a3, FUN_0042a680.c @0x42aa05,
 * FUN_0044a000.c @0x44a459.., FUN_0050ae40.c/FUN_0050be20.c
 * @0x50aa7a.., FUN_00505f10.c @0x505e3c/0x505e6d, RenderWorldListRow.c
 * @0x50dd89, State09_ReadyRoom_RenderRosterAndItems.c @0x4d7e6f/
 * 0x4d8660). Every single one sets up ECX/EBX/ESI immediately before
 * `call 0x4ed9f0`, e.g. (RenderRoomCard.c @0x42a598-0x42a5a3):
 *   lea ebx,[edi+0xb]     ; ebx = iVar7+0xb   (y - dropped)
 *   lea ecx,[ebp+0x11]    ; ecx = iVar6+0x11  (this/x - dropped)
 *   mov esi,0x1f4         ; esi = 500         (outer key - dropped)
 * ESI is 0x1f4 (500) at 34 of the 35 call sites, but 0x32 (50) at
 * RenderWorldListRow.c's @0x50dd89 - confirming it is a genuine,
 * varying caller-supplied argument, not a function-local constant.
 *
 * Left unfixed: recovering all three dropped arguments would require
 * disassembly-based recovery at all 35 call sites across 9 files (one
 * of which, FUN_0044a000.c, has its own unrelated, deeper corruption -
 * BlitSprite16bpp()/BlitSpriteClipped()/BlitSpriteText() called with
 * zero args and stray unaff_EBP reads) to keep behavior correct - a
 * separate, much larger undertaking outside this pass's scope, the same
 * call as FindSpriteFrame.c's own header comment makes for its 179-call-
 * site fan-out. The unaff_ESI/EBX reads and the dropped param_1 below
 * are confirmed correct against the disassembly, so behavior is
 * preserved as-is; only promote the signature once the caller fan-out
 * can be fixed in the same pass.
 */
#include "ghidra_types.h"


void __thiscall BlitSpriteText(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint unaff_ESI;
  
  iVar4 = 0;
  if (param_4 < 1) {
    return;
  }
LAB_004eda02:
  if (((*(char *)(param_3 + iVar4) != ' ') &&
      (uVar1 = *(char *)(param_3 + iVar4) + -0x30 + param_2, DAT_0079352c != 0)) &&
     (-1 < (int)uVar1)) {
    iVar3 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar2 = *(uint *)(iVar3 + 4);
    while (uVar2 <= unaff_ESI) {
      if (uVar2 == unaff_ESI) {
        iVar3 = *(int *)(iVar3 + 0x10);
        uVar2 = *(uint *)(iVar3 + 8);
        if (uVar2 <= uVar1) goto LAB_004eda4e;
        break;
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar2 = *(uint *)(iVar3 + 4);
    }
  }
  goto LAB_004eda7d;
  while( true ) {
    iVar3 = *(int *)(iVar3 + 0x10);
    uVar2 = *(uint *)(iVar3 + 8);
    if (uVar1 < uVar2) break;
LAB_004eda4e:
    if (uVar2 == uVar1) {
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        BlitSprite16bpp(param_1);
      }
      else {
        BlitSpriteClipped(uVar1);
      }
      break;
    }
  }
LAB_004eda7d:
  iVar4 = iVar4 + 1;
  param_1 = param_1 + param_5;
  if (param_4 <= iVar4) {
    return;
  }
  goto LAB_004eda02;
}

