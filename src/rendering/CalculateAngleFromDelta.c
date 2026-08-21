/* CalculateAngleFromDelta - 0x004f1f10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * CONVENTION RECOVERED (2026-08-20), SIGNATURE ONLY - call sites NOT swept.
 * It is an atan2 lookup: EAX and ECX are a delta pair, halved together until
 * both fit in [-0x7f, 0x80], then used to index a 256x256 table of shorts at
 * DAT_00598e7e as (dy * 0x100 + dx) * 2.  Entry at 0x4f1f10 pins the roles:
 *     mov esi,eax / cmp esi,-0x7f / cmp esi,0x80    EAX is the X delta
 *     cmp ecx,-0x7f / cmp ecx,0x80                  ECX is the Y delta
 * so the parameters are now (dx, dy).  Declared plain __cdecl rather than
 * __fastcall for the reason FindSpriteFrame's header sets out - __fastcall
 * decorates the symbol with its stack-byte count - and functions.h keeps the
 * K&R-empty declaration so the 28 still-argless call sites keep compiling.
 *
 * ALL 28 CALL SITES SCANNED, and 24 share one shape exactly:
 *     mov eax,[obj+0x3c] / mov ecx,<localA> / mov edx,[obj+0x38]
 *     sub ecx,eax            <- dy = localA - obj.y   (the OLD eax)
 *     mov eax,<localB> / sub eax,edx
 *                            <- dx = localB - obj.x
 * Note the order: `sub ecx,eax` consumes the value of EAX BEFORE it is
 * reloaded, so a naive backward scan reports ecx as depending on the delta
 * rather than on obj.y.  obj+0x38 and obj+0x3c are the projectile X and Y.
 *
 * NOT SWEPT DELIBERATELY.  localA and localB are caller stack slots, so each
 * site needs its own frame calibration - at DetonateProjectile the anchor is
 * `apuStack_ad0[0] = piVar9[0xf]` against `mov [esp+0x38],eax`, which fixes
 * the constant and makes [esp+0x1c]/[esp+0x20] resolve to local_aec and
 * uStack_ae8.  That is 28 separate hand calibrations where a wrong one is
 * silent - every argument is a plain integer, so a wrong delta still compiles
 * and still produces a plausible angle.  Left for a pass that can verify each
 * one rather than a tired sweep.
 */
#include "ghidra_types.h"


int CalculateAngleFromDelta(int dx,int dy)

{
  
  for (; (((dx < -0x7f || (0x80 < dx)) || (dy < -0x7f)) || (0x80 < dy));
      dy = dy / 2) {
    dx = dx / 2;
  }
  return (int)*(short *)(&DAT_00598e7e + (dy * 0x100 + dx) * 2);
}

