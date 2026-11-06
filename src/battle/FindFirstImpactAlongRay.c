/* FindFirstImpactAlongRay - 0x004e4fe0 in the original binary.
 *
 * NAMED (batch 35), LIKELY (was FUN_004e4fe0).  A pixel ray cast: from
 * the start point (ECX this = x, EAX = y) along the direction towards the
 * point held in the two in/out cells *param_3 / *param_4, stepping
 * param_5 (always 2) along the major axis and interpolating the minor one
 * in 16.16 fixed point.  Each pixel is tested against the terrain bitmap
 * (byte at bitmap[y * g_nCameraBoundX + x], gated by param_6) and against
 * HitTestMobilesAndJewels (gated by param_7); on the first solid pixel or
 * entity it writes the HIT point back through the two cells and returns
 * 1.  It returns 0 when the walk leaves the bounds block in param_2
 * (+0x18 max x, +0x1c max y, x below 0, y below -500).  The loop never
 * compares against the end point, only the bounds, so it is a RAY along
 * that direction and not a bounded segment - hence "Ray".  External
 * evidence for "first impact": all 26 call sites (tools/count_call_args.py:
 * 8 args at every site) pass (1, 1) for the two gates and the same
 * bounds block &DAT_006a7708 + g_clientContext, and they are the
 * detonation / shot-simulation routines (Detonate*_Bullet*,
 * DetonateProjectile); on a hit they queue the two returned coordinates as
 * outgoing packet fields (Projectile.cpp QueueOutgoingPacketField of
 * uStack_adc / local_ad4), i.e. they treat the result as the impact
 * position.  Siblings in the same job: FindFirstImpactAlongStep_XMajor /
 * _YMajor (0x458920 / 0x458a00), which share HitTestMobilesAndJewels.
 * LIKELY because the direction role of the in/out cells is read from the
 * arithmetic, not stated by a caller.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * EAX RECOVERED AND THE CALL SITES RE-SLOTTED (2026-08-26).  `ret 0x18` is six
 * stack arguments against seven declared parameters, so param_1 is the ECX
 * `this` and the six the 26 source sites were passing had ALL been binding one
 * slot too early.  EAX (`mov esi,eax`, the first instruction after the
 * prologue pushes) is the seventh value and was absent entirely.  Every site
 * is rewritten in full rather than appended to.
 */
#include "ghidra_types.h"


undefined4 __thiscall
FindFirstImpactAlongRay(int param_1,int param_2,int *param_3,int *param_4,int param_5,char param_6,char param_7,
             int in_EAX)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  iVar7 = *param_3;
  uVar3 = param_1 - iVar7 >> 0x1f;
  uVar4 = in_EAX - *param_4 >> 0x1f;
  iVar8 = ((param_1 - iVar7 ^ uVar3) - uVar3) + 1;
  iVar6 = ((in_EAX - *param_4 ^ uVar4) - uVar4) + 1;
  if (iVar6 < iVar8) {
    iVar6 = *param_4 - in_EAX;
    bVar1 = param_1 <= iVar7;
    iVar7 = in_EAX * 0x10000;
    if (param_1 <= *(int *)(param_2 + 0x18)) {
      iVar5 = g_clientContext;
      do {
        iVar7 = iVar7 + ((iVar6 * 0x10000) / iVar8) * param_5;
        in_EAX = iVar7 >> 0x10;
        if (param_1 < 0) {
          return 0;
        }
        if (in_EAX < -500) {
          return 0;
        }
        if (*(int *)(param_2 + 0x1c) < in_EAX) {
          return 0;
        }
        if (((((param_6 != '\0') && (param_1 < *(int *)(&g_nCameraBoundX + iVar5))) && (-1 < in_EAX))
            && ((in_EAX < *(int *)(&g_nCameraBoundY + iVar5) &&
                (*(char *)(*(int *)(&g_nCameraBoundX + iVar5) * in_EAX +
                           *(int *)(&DAT_006a773c + iVar5) + param_1) != '\0')))) ||
           ((param_7 != '\0' &&
            (cVar2 = HitTestMobilesAndJewels(in_EAX,(int)(&DAT_006a7f88 + g_clientContext),param_1),
            iVar5 = g_clientContext, cVar2 != '\0'))
           )) {
LAB_004e51d2:
          *param_3 = param_1;
          *param_4 = in_EAX;
          return 1;
        }
        param_1 = param_1 + ((uint)bVar1 * 2 + -1) * param_5;
      } while (param_1 <= *(int *)(param_2 + 0x18));
    }
  }
  else {
    bVar1 = in_EAX <= *param_4;
    iVar6 = (((iVar7 - param_1) * 0x10000) / iVar6) * param_5;
    iVar7 = param_1 * 0x10000 + iVar6;
    param_1 = iVar7 >> 0x10;
    if (param_1 <= *(int *)(param_2 + 0x18)) {
      iVar8 = g_clientContext;
      while (((-1 < param_1 && (-0x1f5 < in_EAX)) && (in_EAX <= *(int *)(param_2 + 0x1c)))) {
        if ((((param_6 != '\0') && (param_1 < *(int *)(&g_nCameraBoundX + iVar8))) &&
            ((-1 < in_EAX &&
             ((in_EAX < *(int *)(&g_nCameraBoundY + iVar8) &&
              (*(char *)(*(int *)(&g_nCameraBoundX + iVar8) * in_EAX + *(int *)(&DAT_006a773c + iVar8)
                        + param_1) != '\0')))))) ||
           ((param_7 != '\0' &&
            (cVar2 = HitTestMobilesAndJewels(in_EAX,(int)(&DAT_006a7f88 + g_clientContext),param_1),
            iVar8 = g_clientContext, cVar2 != '\0'))
           )) goto LAB_004e51d2;
        iVar7 = iVar7 + iVar6;
        in_EAX = in_EAX + ((uint)bVar1 * 2 + -1) * param_5;
        param_1 = iVar7 >> 0x10;
        if (*(int *)(param_2 + 0x18) < param_1) {
          return 0;
        }
      }
    }
  }
  return 0;
}

