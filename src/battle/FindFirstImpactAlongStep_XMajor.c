/* FindFirstImpactAlongStep_XMajor - 0x00458920 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00458920 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: it is called
 * from ten projectile Simulate* routines (and CProjectile::SimulateFrame),
 * in one branch of the line stepper (SimulateProjectileFrame has the
 * 0x458920 sites in one branch and the 0x458a00 sites in the mirrored
 * one), immediately after the per-step trace has found the current pixel
 * inside the terrain mask (ctx+0x6a773c, camera bound stride) or
 * HitTestMobilesAndJewels has fired, with the step count (stepDelta) in
 * EAX. The caller then encodes the returned (x, y) into the projectile's
 * guarded position and impact cells and broadcasts the 0xf002 enter-
 * terrain event. The body replays the last stepDelta steps forward (x
 * stepping linearly, y in 16.16 fixed point) and returns the first solid
 * mask pixel, or the first mobile hit when the last argument is set, so
 * the reported impact is the first contact rather than the overshoot
 * pixel. FUN_00458a00 is the Y-major twin (x and y roles swapped, called
 * from the other branch); hence the XMajor suffix.
 *
 * DROPPED REGISTER RECOVERED (2026-08-24): EAX is the caller's STEP COUNT --
 * param_2 of every __thiscall Simulate* caller (stepDelta in the C++ port).
 * The body uses it as the multiplier in `accum - slope * regEax`, and the
 * callers multiply the same slope by the same param_2 themselves
 * (`local_1588 * param_2`), which is what pins the role.
 *
 * Found by frame arithmetic rather than by name.  Every site loads EAX from
 * [esp + 0x15f4..0x1600] -- a slot ABOVE a 0x15b8-byte __chkstk frame, the
 * SEH triple and four callee-saved pushes, at exactly +4 past the return
 * address once the pending argument pushes are subtracted.  +4 is the first
 * stack parameter.  Twenty of 24 sites gave +4 directly; the other four gave
 * +0 (the return address, which cannot be read as an argument) because a
 * `push` on an unrelated branch between the previous call and this one was
 * counted by the linear walk -- e.g. `push 0xf002 / jmp` at 0x004567b9.
 */
#include "ghidra_types.h"


void FindFirstImpactAlongStep_XMajor(int *param_1,int *param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7,char param_8,char param_9,int regEax)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (param_4 != 0) {
    param_7 = param_7 - param_6 * regEax;
    iVar4 = param_4 - regEax;
    if (iVar4 < param_4) {
      param_3 = iVar4 * param_5 + param_3;
      iVar2 = g_clientContext;
      while( true ) {
        param_7 = param_7 + param_6;
        iVar3 = param_7 >> 0x10;
        if (((((param_8 != '\0') && (-1 < param_3)) && (param_3 < *(int *)(&g_nCameraBoundX + iVar2)))
            && ((-1 < iVar3 && (iVar3 < *(int *)(&g_nCameraBoundY + iVar2))))) &&
           (*(char *)(*(int *)(&g_nCameraBoundX + iVar2) * iVar3 + *(int *)(&DAT_006a773c + iVar2) +
                     param_3) != '\0')) {
          *param_1 = param_3;
          *param_2 = iVar3;
          return;
        }
        if ((param_9 != '\0') &&
           (cVar1 = HitTestMobilesAndJewels(iVar3,(int)(&DAT_006a7f88 + g_clientContext),param_3), iVar2 = g_clientContext,
           cVar1 != '\0'))
        break;
        iVar4 = iVar4 + 1;
        param_3 = param_3 + param_5;
        if (param_4 <= iVar4) {
          return;
        }
      }
      *param_1 = param_3;
      *param_2 = iVar3;
    }
  }
  return;
}

