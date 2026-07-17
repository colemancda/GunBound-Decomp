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
 * SIGNATURE PROMOTED (2026-07-17): the two dropped register args are now
 * explicit trailing parameters - `y` (was EBX) and `charsetKey` (was
 * unaff_ESI). Recovered from the full disassembly at 0x4ed9f0: the args
 * are (param_1=x/ECX running x, param_2=glyphBase, param_3=string ptr,
 * param_4=char count, param_5=x advance, y=EBX, charsetKey=ESI), and the
 * per-glyph blit is `BlitSprite16bpp/Clipped(frame=glyph, x, y,
 * outerKey=charsetKey)` (the original passes glyph in EAX, x=EDI, y=EBX,
 * key=ESI; the ports take these as cdecl (frame,x,y,outerKey), so the
 * calls below are rewritten to that form - they previously passed a
 * single wrong arg). functions.h keeps this K&R so the ~34 other call
 * sites (still unrecovered - see this header's list) compile unchanged;
 * only the server-list path (RenderWorldListRow) is fixed to pass all
 * seven args. Left it faulting before this: RenderWorldListRow passed
 * the string LENGTH where param_3 (the string pointer) belongs, so the
 * `*(char*)(param_3+i)` read hit a near-null address.
 */
#include "ghidra_types.h"


void __thiscall BlitSpriteText(int param_1,int param_2,int param_3,int param_4,int param_5,
                               int y,int charsetKey)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint unaff_ESI;

  unaff_ESI = (uint)charsetKey;
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
        BlitSprite16bpp(uVar1,param_1,y,charsetKey);
      }
      else {
        BlitSpriteClipped(uVar1,param_1,y,charsetKey);
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

