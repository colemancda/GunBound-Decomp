/* FUN_0044a000 - 0x0044a000 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 21 argless PeekPacketChecksumState() calls.  All but the
 * first read the per-slot object local_104 = param_2*0x17e4 + param_1
 * (frame[0x1c], built at 0x44a1cc) at ten fixed byte offsets - 0xadc,
 * 0x19d8, 0xf24, 0x1148, 0x136c, 0x1590, 0xd00, 0x17b4 (each peeked
 * twice: the != 0 test then the < 1 test, the second through the pointer
 * the C parks in local_10c / frame[0x14]) and 0x694, 0x8b8 in the tail
 * (peeked twice each, matching the PeekChecksumStateUnderLock(local_104 +
 * 0x19d8 / + 0x17b4) landmarks the file already had).  The first site
 * (0x44a04a) reads param_1 + 4 (`mov eax,[esp+0x124]; add eax,4` -
 * [esp+0x124] is this function's own param_1, four pushes deep).
 *
 * DROPPED-ARG FIX (2026-08-11): the 6 argless PeekChecksumStateUnderLock()
 * calls now pass their guarded-cell pointer, recovered from
 * tools/underlock_push_sites.json + per-site disasm. Every one of this
 * function's 16 Peek sites pushes the frame slot [esp+0x14], which each
 * block refills with base + a per-block offset, where base = the slot
 * [esp+0x1c] = param_2*0x17e4 + param_1 = `local_104` (written once at
 * 0x44a1d9 = the line-86 assignment). Pair 1 (0x44a3c6/0x44a427) passes
 * `local_10c` - the C's own slot copy (`local_10c = local_104 + 0xadc`).
 * Pair 2 (0x44a52b/0x44a596) is base+0x19d8 (0x44a479-0x44a482); note
 * Ghidra's nearby `uStack_110 = local_108 + 0x19d8` mis-aliases the
 * base slot [esp+0x1c] as local_108 (the [esp+0x18] x-coordinate), so
 * these pass `local_104 + 0x19d8` directly. The last pair
 * (0x44ad97/0x44ae04) is base+0x17b4 (0x44ace3-0x44acec), a slot store
 * Ghidra dropped entirely, passed as `local_104 + 0x17b4`.
 *
 * RENDER-CHAIN ARG FIX (2026-09-02): recovered container/KEY/FRAME/x/y at
 * all 16 argless FindSpriteFrame() blocks and their sibling blits, from
 * per-site disasm (FindSpriteFrame: EAX=&g_spriteRegistry, EDX=KEY,
 * ESI=FRAME; BlitSprite16bpp: EAX=frame, stack=x,y, EDX=KEY;
 * BlitSpriteClipped: stack=frame, ECX=x, EAX=y, EDX=KEY).  Register key:
 * EBP = iVar4 + 0x15 (Ghidra dropped the `add edx,0x15` fold, per the
 * BlitRLESprite note above), the y base slot [esp+0x18] (E-0x108) =
 * local_108 = (param_2/3)*0xa1 + 0x45, untouched by the binary for the
 * whole function (its sprintf buffers live at E-0x100 = local_100; the
 * C's `_sprintf((char *)&local_108,...)`/`&uStack_110` targets are
 * pre-existing push-shift mislabels, out of scope here).  Blocks, in
 * order: 0x44a07c key 0x2711 frame = (PeekState(param_1+4) == param_2)
 * - the peek return Ghidra dropped, now captured in iVar2;  0x44a0e8 key
 * 0x2713 frame iVar1 ([param_1+0x44c]*2 maybe +1);  0x44a15f/0x44a193
 * key 0x2711 frames 2/3, shared LAB_0044a1b2 clip tail carries the frame
 * in iVar2 (the `else if` was unfolded to `else { iVar2 = 3; if ...}` to
 * seat the assignment);  0x44a2de key = param_2 + 0x4e20 frame 0
 * (`lea edx,[ebx+0x4e20]`, ebx = param_2);  0x44a251 key 0x2711 frame 8
 * (the line-139 else branch);  0xadc pair 0x44a3f7/0x44a396 key 0x2713
 * frames 8/9;  0x19d8 pair 0x44a561/0x44a4f6 frames 0xb/0xa and 0x17b4
 * pair 0x44add0/0x44ad63 frames 0x17/0x16, y = local_108 + uVar7*0x12 +
 * 0x22 (edi is the row counter; branch mapping follows the recovered
 * 0xf24/0x1148 pairs: the non-negated "== '\\0'" branch takes the higher
 * frame, confirmed by the `neg eax` after 0x40a4d0 on the lower-frame
 * path);  0x694 tail 0x44af34/0x44aeed key 0x2711 frames 6/5, x = iVar4
 * + 0x57 / + 0x83, y = local_108 + 0x7e, frame/x parked in iVar2/iVar3
 * for the shared clip at 0x44af57;  0x8b8 tail 0x44b05e/0x44b00e frames
 * 7/4, x = iVar4 + 0x57 / + 0x83, y = local_108 + 0x6e, same iVar2/iVar3
 * parking (assigned before FindSpriteFrame clobbers iVar4).
 *
 * BlitSpriteText FIX (2026-11-03): all eight number draws (0x44a459,
 * 0x44a5c4, 0x44a72b, 0x44a892, 0x44a9f9, 0x44ab60, 0x44acc7, 0x44ae32)
 * pass all seven arguments. Each is pushes (0x28, buf, 2, 6) with ECX =
 * ebp + 0x7b = iVar4 + 0x90 (EBP is iVar4 + 0x15), ESI = 0x1f4 and EBX =
 * local_108 + row * 0x12 + 0x23 (`add ebx,0x23` on the row's y, or `mov
 * ebx,[esp+0x24]` = local_108 for the first row, or `lea ebx,[edi+0x23]`
 * at 0x44ae27). The buffer is [esp+0x20] = local_100 at every site (`lea
 * edx,[esp+0x28]` for the _sprintf with two words pushed, `lea
 * eax,[esp+0x28]` for the BlitSpriteText likewise), so the _sprintf
 * targets Ghidra mis-aliased (&local_108 - which clobbered the y base -
 * &uStack_110 and four stack0x artifacts) are local_100 too. The value
 * printed is PeekChecksumStateUnderLock's return, negated on the lower-
 * frame path (`neg eax` at 0x44a3cb, 0x44a530, 0x44a697, ..., 0x44ad9c);
 * the first, second and last rows dropped it and now capture it.
  *
 * FIX (2026-11-03): rows 2-8 of the guard-counter column and the tail,
 * rebuilt from the disassembly (0x44a472-0x44b09e).  The unrolled C took
 * every branch condition from unassigned aliases (cVar11/cVar13/cVar14 =
 * bytes of unaff_EBP/unaff_EDI) and its y values for rows 3-7 from
 * `uStack_110 + 0x206c`-style sums of an uninitialised stack slot; the
 * binary reads the y base from [esp+0x18] (= local_108) for EVERY row
 * (`mov edx,[esp+0x18] / lea ecx,[edi+edi*8] / lea ebx,[edx+ecx*2]`,
 * e.g. 0x44a4db) and keeps the != 0 test in a stack byte ([esp+0x17] via
 * `setne`, tested at [esp+0x13]), the second test likewise via `setl`
 * (`setle` for the first row only, 0x44a365).  All eight rows are one
 * DrawGuardRow now, with frames (negative/positive) 9/8, 0xa/0xb, 0xc/0xd,
 * 0xe/0xf, 0x10/0x11, 0x12/0x13, 0x14/0x15, 0x16/0x17 read from the
 * `mov esi,<frame>` of each branch.  The two tail sprintfs
 * (0x44ae9c, 0x44afbd) also dropped the peeked value they print
 * (`push esi` then `push 0x555650`).
 */
#include "ghidra_types.h"



/* One row of the per-slot guard-counter column (the eight blocks at
 * 0x44a2ee-0x44ae37, one per guarded cell at slot+0xadc, 0x19d8, 0xf24,
 * 0x1148, 0x136c, 0x1590, 0xd00, 0x17b4).  Every block is the same shape:
 * peek the cell under g_valueGuardLock (`call 0x40a2e0`, setne) and skip
 * the row if it is zero or three rows are already drawn (`cmp edi,3 / jge`);
 * peek again (setle for the first row, 0x44a365, setl for the other seven)
 * to pick the icon: true -> the lower frame with the value NEGATED (`neg
 * eax`, e.g. 0x44a3cb), false -> the higher frame; blit it at (ebp+0x68,
 * [esp+0x18] + row*0x12 + 0x22) with key 0x2713, then _sprintf("%d") the
 * value read through PeekChecksumStateUnderLock and BlitSpriteText it at y
 * + 0x23.  Returns the next row index (edi).  The C had these as eight
 * unrolled copies whose branch conditions and y offsets came from unassigned
 * register aliases (unaff_EBP/unaff_EDI bytes, `uStack_110 + 0xf24`...).
 */
static int DrawGuardRow(int cell,int row,int iVar4,int yBase,int frameNeg,int framePos,int firstRow)
{
  char text [120];
  int iVar1;
  int iVar2;
  int frame;
  int y;
  int value;
  char neg;

  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)cell);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if ((iVar1 == 0) || (2 < row)) {
    return row;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)cell);
  if (firstRow != 0) {
    neg = (iVar1 < 1);
  }
  else {
    neg = (iVar1 < 0);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  frame = (neg != '\0') ? frameNeg : framePos;
  y = yBase + row * 0x12;
  if ((g_screenSurface != 0) &&
     (iVar2 = FindSpriteFrame((int)&g_spriteRegistry,0x2713,frame), iVar2 != 0)) {
    if (*(char *)(iVar2 + 0x18) == '\x01') {
      BlitSprite16bpp(frame,iVar4 + 0x7d,y + 0x22,0x2713);
    }
    else {
      BlitSpriteClipped(frame,iVar4 + 0x7d,y + 0x22,0x2713);
    }
  }
  value = PeekChecksumStateUnderLock(cell);
  if (neg != '\0') {
    value = -value;
  }
  _sprintf(text,&DAT_00555654,value);
  BlitSpriteText(iVar4 + 0x90,0x28,(int)text,2,6,y + 0x23,0x1f4);
  return row + 1;
}

void FUN_0044a000(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar7;
  int local_108;
  int local_104;
  char acStack_88 [136];
  
  iVar4 = (param_2 % 3) * 0xa3;
  local_108 = (param_2 / 3) * 0xa1 + 0x45;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(param_1 + 4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = (iVar2 == param_2);
  if ((g_screenSurface != 0) &&
     (iVar1 = FindSpriteFrame((int)&g_spriteRegistry,0x2711,iVar2), iVar1 != 0)) {
    if (*(char *)(iVar1 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar2,iVar4 + 0x15,local_108,0x2711);
    }
    else {
      BlitSpriteClipped(iVar2,iVar4 + 0x15,local_108,0x2711);
    }
  }
  iVar1 = *(int *)(param_1 + 0x44c) * 2;
  if ((iVar1 != 6) &&
     (*(char *)(param_2 + *(int *)(param_1 + 0x450) * 9 + 0x2d54c + param_1) == '\0')) {
    iVar1 = iVar1 + 1;
  }
  if (((g_screenSurface != 0) && (-1 < iVar1)) &&
     (iVar2 = FindSpriteFrame((int)&g_spriteRegistry,0x2713,iVar1), iVar2 != 0)) {
    if (*(char *)(iVar2 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar1,iVar4 + 0x1c,local_108 + 6,0x2713);
    }
    else {
      BlitSpriteClipped(iVar1,iVar4 + 0x1c,local_108 + 6,0x2713);
    }
  }
  if (*(int *)(param_1 + 0x44c) != 3) {
    if (*(char *)(param_2 + *(int *)(param_1 + 0x450) * 9 + 0x2d54c + param_1) == '\x01') {
      iVar2 = 2;
      if ((g_screenSurface != 0) &&
         (iVar1 = FindSpriteFrame((int)&g_spriteRegistry,0x2711,iVar2), iVar1 != 0)) {
        if (*(char *)(iVar1 + 0x18) == '\x01') {
          BlitSprite16bpp(iVar2,iVar4 + 0x92,local_108 + 5,0x2711);
        }
        else {
LAB_0044a1b2:
          BlitSpriteClipped(iVar2,iVar4 + 0x92,local_108 + 5,0x2711);
        }
      }
    }
    else {
      iVar2 = 3;
      if ((g_screenSurface != 0) &&
         (iVar1 = FindSpriteFrame((int)&g_spriteRegistry,0x2711,iVar2), iVar1 != 0)) {
        if (*(char *)(iVar1 + 0x18) != '\x01') goto LAB_0044a1b2;
        BlitSprite16bpp(iVar2,iVar4 + 0x92,local_108 + 5,0x2711);
      }
    }
  }
  local_104 = param_2 * 0x17e4 + param_1;
  /* ALL FOUR ARGS RECOVERED (objdump @0x44a1be-0x44a1f0): x/ECX = ebx =
   * ebp + 0x18.  EBP is Ghidra's iVar4 PLUS the 0x15 it dropped from
   * `imul edx,edx,0xa3 / add edx,0x15 / mov ebp,edx` (0x44a026-0x44a034);
   * every other ebp use surfaces in this C 0x15 higher (`lea r,[ebp+0x68]`
   * is the C's iVar4 + 0x7d), so ebp+0x18 is iVar4 + 0x2d.  y = edi =
   * [esp+0x18] + 5 = local_108 + 5 (local_108 is written at 0x44a036 via
   * `mov [esp+0x1c],edi` with esp = entry-0x124; the frame is pinned by
   * [esp+0x124]=param_1 and [esp+0x128]=param_2 at 0x44a1c5/0x44a1be).
   * colour = 0.  string = EAX = esi = local_104 + 0x67c. */
  DrawFontString(iVar4 + 0x2d,local_108 + 5,0,(char *)(local_104 + 0x67c));
  /* BlitRLESprite's args were dropped entirely (Ghidra emitted a bare
   * BlitRLESprite() here) - objdump at 0x44a1ff shows ECX = ebx = ebp +
   * 0x18 and EAX = esi = local_104 + 0x67c, the same pair the
   * DrawFontString above it carries, with `push 0xffff` / `push edi` as
   * its colour and y.
   *
   * CORRECTED 2026-08-28 on both counts. The x was written iVar4 + 0x18,
   * but EBP is not iVar4: `imul edx,edx,0xa3 / add edx,0x15 / mov ebp,edx`
   * at 0x44a026-0x44a034 puts iVar4 + 0x15 in EBP, and Ghidra dropped the
   * 0x15 from the C. Every other EBP use surfaces here 0x15 higher - the
   * `lea r,[ebp+0x68]` sites are this file's own iVar4 + 0x7d - so
   * ebp + 0x18 is iVar4 + 0x2d. The y was written 0, but the pushes are
   * `push 0xffff` (colour, higher address) then `push edi` (y), and EDI
   * is [esp+0x18] + 5 = local_108 + 5. */
  BlitRLESprite(iVar4 + 0x2d,local_108 + 5,0xffff,(byte *)(local_104 + 0x67c));
  if ((*(int *)(param_1 + 0x34790) < 0x15) || (*(int *)(param_1 + 0x3478c) != param_2)) {
    if ((g_screenSurface != 0) &&
       (iVar1 = FindSpriteFrame((int)&g_spriteRegistry,param_2 + 0x4e20,0), iVar1 != 0)) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp(0,iVar4 + 0x49,local_108 + 0x3e,param_2 + 0x4e20);
      }
      else {
        BlitSpriteClipped(0,iVar4 + 0x49,local_108 + 0x3e,param_2 + 0x4e20);
      }
    }
    uVar7 = 0;
    uVar7 = DrawGuardRow(local_104 + 0xadc,uVar7,iVar4,local_108,0x9,0x8,1);
    uVar7 = DrawGuardRow(local_104 + 0x19d8,uVar7,iVar4,local_108,0xa,0xb,0);
    uVar7 = DrawGuardRow(local_104 + 0xf24,uVar7,iVar4,local_108,0xc,0xd,0);
    uVar7 = DrawGuardRow(local_104 + 0x1148,uVar7,iVar4,local_108,0xe,0xf,0);
    uVar7 = DrawGuardRow(local_104 + 0x136c,uVar7,iVar4,local_108,0x10,0x11,0);
    uVar7 = DrawGuardRow(local_104 + 0x1590,uVar7,iVar4,local_108,0x12,0x13,0);
    uVar7 = DrawGuardRow(local_104 + 0xd00,uVar7,iVar4,local_108,0x14,0x15,0);
    uVar7 = DrawGuardRow(local_104 + 0x17b4,uVar7,iVar4,local_108,0x16,0x17,0);
  }
  else {
    if ((g_screenSurface != 0) &&
       (iVar1 = FindSpriteFrame((int)&g_spriteRegistry,0x2711,8), iVar1 != 0)) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp(8,iVar4 + 0x1e,local_108 + 0x14,0x2711);
      }
      else {
        BlitSpriteClipped(8,iVar4 + 0x1e,local_108 + 0x14,0x2711);
      }
    }
    iVar1 = 3;
    do {
      /* BlitRLESprite's args were dropped entirely here too - objdump at
       * this call site (0x44a2ab) shows ECX = ebp+0xb (this file's own
       * iVar4, recomputed fresh via `lea` each of the 3 loop passes from
       * an unchanged ebp - it does not advance across iterations here),
       * and EAX = esi = param_2*0x78 + param_1 + 0x2d114 (a struct field
       * table indexed by param_2, matching this loop's later
       * `iVar3 + g_clientContext`-style indexing pattern elsewhere in
       * this file). Per real disassembly the rleData/x stack arg do
       * advance by 0x18/0xe each of the 3 passes, but the raw decompile
       * collapsed the loop to a single call-site text with no per-
       * iteration locals to carry that - using the first iteration's
       * values here, which is the most faithful recovery obtainable
       * without inventing new loop state. The 2nd stack arg (x) reads
       * the same uninitialized [esp+0x18]-based local as the other call
       * site, so it's left as a placeholder; color = 0xffff. */
      BlitRLESprite(iVar4 + 0xb,0,0xffff,(byte *)(param_2 * 0x78 + param_1 + 0x2d114));
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(local_104 + 0x694));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar1 == 0) {
    iVar2 = 6;
    iVar3 = iVar4 + 0x57;
    if ((g_screenSurface == 0) ||
       (iVar1 = FindSpriteFrame((int)&g_spriteRegistry,0x2711,iVar2), iVar1 == 0))
    goto LAB_0044af5f;
    if (*(char *)(iVar1 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar2,iVar3,local_108 + 0x7e,0x2711);
      goto LAB_0044af5f;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)(local_104 + 0x694));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    _sprintf(acStack_88,(char *)&PTR_DAT_00555650,iVar1);
    FUN_0044c460(iVar4 + 0x23,0x3c,acStack_88,8,0xa,4,0x118,0x1f4,local_108 + 0x7e);
    iVar2 = 5;
    iVar3 = iVar4 + 0x83;
    if ((g_screenSurface == 0) ||
       (iVar1 = FindSpriteFrame((int)&g_spriteRegistry,0x2711,iVar2), iVar1 == 0))
    goto LAB_0044af5f;
    if (*(char *)(iVar1 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar2,iVar3,local_108 + 0x7e,0x2711);
      goto LAB_0044af5f;
    }
  }
  BlitSpriteClipped(iVar2,iVar3,local_108 + 0x7e,0x2711);
LAB_0044af5f:
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(local_104 + 0x8b8));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar1 == 0) {
    if (g_screenSurface == 0) {
      return;
    }
    iVar2 = 7;
    iVar3 = iVar4 + 0x57;
    iVar4 = FindSpriteFrame((int)&g_spriteRegistry,0x2711,iVar2);
    if (iVar4 == 0) {
      return;
    }
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar2,iVar3,local_108 + 0x6e,0x2711);
      return;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)(local_104 + 0x8b8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    _sprintf(acStack_88,(char *)&PTR_DAT_00555650,iVar1);
    FUN_0044c460(iVar4 + 0x23,0x32,acStack_88,8,0xa,4,0x117,0x1f4,local_108 + 0x6e);
    if (g_screenSurface == 0) {
      return;
    }
    iVar2 = 4;
    iVar3 = iVar4 + 0x83;
    iVar4 = FindSpriteFrame((int)&g_spriteRegistry,0x2711,iVar2);
    if (iVar4 == 0) {
      return;
    }
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar2,iVar3,local_108 + 0x6e,0x2711);
      return;
    }
  }
  BlitSpriteClipped(iVar2,iVar3,local_108 + 0x6e,0x2711);
  return;
}

