/* BlitSprite16bpp - 0x004ed6a0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 *
 * DROPPED REGISTER ARGUMENT (pattern #1) - investigated, NOT fixed here:
 * `in_EAX` is read as a sign-checked gate (`-1 < in_EAX`) before the
 * blit proceeds - almost certainly the y-coordinate/frame-valid check
 * companion to param_1/param_2, dropped by Ghidra with no parameter.
 * BlitSprite16bpp has ~30+ call sites across the render pipeline
 * (BlitSpriteText.c, DrawButtonWidget.c, DrawSprite.c, GameTick.c,
 * Widget_DrawSelf.c, and a dozen+ render/State* files - see
 * get_function_callers) - same large caller fan-out as FindSpriteFrame.c/
 * BlitSpriteText.c/DrawFontString.c, deferred for the same reason (fixing
 * it requires per-site disassembly recovery across all callers in one
 * pass, not attempted here).
 *
 * FIXED (2026-07-13): the frame/sprite record arrived via a dropped EAX
 * (read as an uninitialized `in_EAX`) with only (x, y) as real stack args -
 * confirmed via objdump at State06_Logo2_Render's call site (orig 0x443398:
 * `mov eax,esi` immediately before `call 0x4ed6a0`, with two pushed zeros).
 * Promoted to a leading explicit `frame` parameter. functions.h keeps the
 * K&R-empty declaration so the ~240 not-yet-recovered call sites (which pass
 * 0-2 args today) still compile - they under-supply and read stack garbage
 * exactly as they already read register garbage, so this is strictly no worse
 * for them, and it unblocks the render paths being brought up. Recover each
 * remaining caller's real frame value per-site as its screen is brought up.
 *
 * FIXED (2026-07-14): the internal FindSpriteFrame() re-lookup was ALSO
 * a zero-arg dropped-register-argument stub, separate from this function's
 * own now-fixed `frame` parameter. Confirmed via objdump at 0x4ed6a0: entry
 * does `mov esi,eax` (ESI = the caller's frame value, this function's own
 * `frame` param, left untouched through the call), then immediately before
 * `call 0x4f30c0` sets `mov eax,0xea0e18` (container = &DAT_00ea0e18) with
 * no EDX write in between - EDX (outer key) is inherited live from the
 * caller. An EARLIER fix hardcoded EDX=10000 here, verified only against
 * State06_Logo2_Render's specific call site - WRONG in general, since EDX
 * is a genuine per-caller pass-through, not a constant (same bug, same
 * live-reproduction, as BlitSpriteClipped.c's sibling fix - see its header).
 * Promoted to a real trailing `outerKey` parameter; every currently-3-arg
 * (already frame/x/y-migrated) call site updated to pass its real key.
 * functions.h stays K&R-empty so the ~290 still-2-arg call sites keep
 * compiling unchanged.
 */
#include "ghidra_types.h"
#include <windows.h>


undefined4 BlitSprite16bpp(int frame,int param_1,int param_2,int outerKey)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int in_EAX = frame;
  int iVar4;
  ushort *puVar5;
  ushort *puVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  ushort *puVar10;
  undefined4 *puVar11;
  int local_c;
  int local_8;
  
  if (((DAT_0079352c != 0) && (-1 < in_EAX)) &&
     (iVar4 = FindSpriteFrame((int)&DAT_00ea0e18,outerKey,frame), iVar3 = DAT_00793530, iVar4 != 0)) {
    iVar2 = *(int *)(iVar4 + 0x28);
    param_2 = param_2 + *(int *)(iVar4 + 0x2c);
    puVar6 = *(ushort **)(iVar4 + 0x34);
    iVar4 = *(int *)(iVar4 + 0x24);
    iVar8 = 0;
    local_8 = iVar4;
    if (param_2 < DAT_00793534) {
      iVar8 = DAT_00793534 - param_2;
      param_2 = param_2 + iVar8;
      local_8 = iVar4 - iVar8;
    }
    if (DAT_0056df34 < local_8 + param_2) {
      local_8 = (DAT_0056df34 - param_2) + 1;
    }
    if (iVar8 <= iVar4) {
      if (0 < iVar8) {
        do {
          iVar8 = iVar8 + -1;
          puVar6 = puVar6 + *puVar6;
        } while (iVar8 != 0);
      }
      if (0 < local_8) {
        do {
          uVar1 = puVar6[1];
          puVar5 = puVar6 + 2;
          puVar6 = puVar6 + *puVar6;
          local_c = 0;
          if (uVar1 != 0) {
LAB_004ed770:
            uVar9 = (uint)puVar5[1];
            iVar8 = (uint)*puVar5 + param_1 + iVar2;
            iVar4 = uVar9 + iVar8;
            if (iVar8 <= DAT_0056df30) {
              if (iVar4 <= iVar3) goto LAB_004ed80c;
              if (iVar8 < iVar3) {
                if (DAT_0056df30 < iVar4) {
                  iVar4 = DAT_0056df30 + 1;
                }
                uVar9 = (iVar4 - iVar3) * 2;
                puVar10 = puVar5 + (iVar3 - iVar8) + 2;
                uVar9 = uVar9 & ((int)uVar9 < 0) - 1;
                iVar8 = DAT_005b3620 * param_2 + iVar3;
LAB_004ed7f6:
                puVar11 = (undefined4 *)(DAT_0079352c + iVar8 * 2);
                for (uVar7 = uVar9 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                  *puVar11 = *(undefined4 *)puVar10;
                  puVar10 = puVar10 + 2;
                  puVar11 = puVar11 + 1;
                }
                for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
                  *(char *)puVar11 = (char)*puVar10;
                  puVar10 = (ushort *)((int)puVar10 + 1);
                  puVar11 = (undefined4 *)((int)puVar11 + 1);
                }
                uVar9 = (uint)puVar5[1];
                goto LAB_004ed80c;
              }
              if (iVar4 <= DAT_0056df30) {
                uVar9 = uVar9 * 2;
                iVar8 = DAT_005b3620 * param_2 + iVar8;
                puVar10 = puVar5 + 2;
                goto LAB_004ed7f6;
              }
              uVar9 = (DAT_0056df30 - iVar8) * 2 + 2;
              uVar9 = ((int)uVar9 < 0) - 1 & uVar9;
              puVar11 = (undefined4 *)(DAT_0079352c + (DAT_005b3620 * param_2 + iVar8) * 2);
              for (uVar7 = uVar9 >> 2; puVar5 = puVar5 + 2, uVar7 != 0; uVar7 = uVar7 - 1) {
                *puVar11 = *(undefined4 *)puVar5;
                puVar11 = puVar11 + 1;
              }
              for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
                *(char *)puVar11 = (char)*puVar5;
                puVar5 = (ushort *)((int)puVar5 + 1);
                puVar11 = (undefined4 *)((int)puVar11 + 1);
              }
            }
          }
LAB_004ed857:
          param_2 = param_2 + 1;
          local_8 = local_8 + -1;
        } while (local_8 != 0);
      }
    }
  }
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
LAB_004ed80c:
  puVar5 = puVar5 + uVar9 + 2;
  local_c = local_c + 1;
  if ((int)(uint)uVar1 <= local_c) goto LAB_004ed857;
  goto LAB_004ed770;
}

