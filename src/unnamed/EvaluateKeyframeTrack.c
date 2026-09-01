/* EvaluateKeyframeTrack - 0x004e95c0 in the original binary.
 *
 * The keyframe TRS-track evaluator of the scene-node cluster - both of
 * its named callers, SceneNode_UpdateTransform (0x4f37b0) and
 * SceneNode_UpdateTransformAndCamera (0x4e9cc0), already describe it as
 * exactly that in their own headers: called as (time, dest 4x4 matrix =
 * the node's world matrix at +0xe0, track object = the node's +0xc8
 * field) whenever the node carries a track, with an identity matrix
 * substituted when it does not.
 *
 * The track object holds three keyframe channels, each a count + time
 * array + value array: scale at +0x120/+0x124/+0x128 (scalar values),
 * rotation at +0x114/+0x118/+0x11c (0x10-stride quaternions), and
 * translation at +0x108/+0x10c/+0x110 (0xc-stride vec3).  Each channel
 * does the same unrolled forward scan for the key interval containing
 * `time`, then interpolates: rotation through the already-named
 * SlerpQuaternionsToScratch -> QuaternionToRotationMatrix pair (via the
 * DAT_005a90e0 quaternion scratch), translation by lerp into
 * DAT_00793668..70, scale by lerp.  The result is composed into the
 * dest matrix: rotation in the 3x3, translation into rows 12-14, and a
 * uniform scale multiply of the 3x3 when the scale differs from 1.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* param_2 is a register slot Ghidra typed float * but reuses as a
 * float value carrier; undefined4 keeps every site legal C. */
void EvaluateKeyframeTrack(double param_1,undefined4 param_2,int regEbx)

{
  int iVar1;
  float fVar2;
  float *pfVar3;
  undefined4 *puVar4;
  float *pfVar5;
  int iVar6;
  float *pfVar7;
  
  pfVar3 = param_2;
  if (param_1 < _DAT_00557fb4) {
    param_1 = 0.0;
  }
  iVar1 = *(int *)(regEbx + 0x120);
  if (iVar1 < 2) {
    param_2 = (float *)0x3f800000;
  }
  else {
    pfVar5 = *(float **)(regEbx + 0x124);
    if (*pfVar5 <= param_1) {
      iVar6 = 0;
      if (3 < iVar1) {
        pfVar7 = pfVar5 + 2;
        do {
          if (param_1 < pfVar7[-2]) goto LAB_004e9694;
          if (param_1 < pfVar7[-1]) {
            iVar6 = iVar6 + 1;
            goto LAB_004e9694;
          }
          if (param_1 < *pfVar7) {
            iVar6 = iVar6 + 2;
            goto LAB_004e9694;
          }
          if (param_1 < pfVar7[1]) {
            iVar6 = iVar6 + 3;
            goto LAB_004e9694;
          }
          iVar6 = iVar6 + 4;
          pfVar7 = pfVar7 + 4;
        } while (iVar6 < iVar1 + -3);
      }
      if (iVar6 < iVar1) {
        pfVar5 = pfVar5 + iVar6;
        do {
          if (param_1 < *pfVar5) break;
          iVar6 = iVar6 + 1;
          pfVar5 = pfVar5 + 1;
        } while (iVar6 < iVar1);
      }
LAB_004e9694:
      if (iVar6 == iVar1) {
        param_2 = *(float **)(*(int *)(regEbx + 0x128) + -4 + iVar1 * 4);
      }
      else {
        pfVar5 = (float *)(*(int *)(regEbx + 0x124) + iVar6 * 4);
        pfVar7 = (float *)(*(int *)(regEbx + 0x128) + iVar6 * 4);
        /* float->pointer isn't a legal C cast; go through (int) (raw-port
         * register-reuse artifact, value semantics unverified). */
        param_2 = (float *)(int)((*pfVar7 - pfVar7[-1]) *
                            ((param_1 - *(float *)(*(int *)(regEbx + 0x124) + -4 + iVar6 * 4)) /
                            (*pfVar5 - pfVar5[-1])) + pfVar7[-1]);
      }
    }
    else {
      param_2 = (float *)0x3f800000;
    }
  }
  iVar1 = *(int *)(regEbx + 0x114);
  if ((iVar1 < 2) || (pfVar5 = *(float **)(regEbx + 0x118), param_1 < *pfVar5)) {
    FUN_004f3af0(0,0,0,(float *)&DAT_005a90e0);
  }
  else {
    iVar6 = 0;
    if (3 < iVar1) {
      pfVar7 = pfVar5 + 2;
      do {
        if (param_1 < pfVar7[-2]) goto LAB_004e9784;
        if (param_1 < pfVar7[-1]) {
          iVar6 = iVar6 + 1;
          goto LAB_004e9784;
        }
        if (param_1 < *pfVar7) {
          iVar6 = iVar6 + 2;
          goto LAB_004e9784;
        }
        if (param_1 < pfVar7[1]) {
          iVar6 = iVar6 + 3;
          goto LAB_004e9784;
        }
        iVar6 = iVar6 + 4;
        pfVar7 = pfVar7 + 4;
      } while (iVar6 < iVar1 + -3);
    }
    if (iVar6 < iVar1) {
      pfVar5 = pfVar5 + iVar6;
      do {
        if (param_1 < *pfVar5) break;
        iVar6 = iVar6 + 1;
        pfVar5 = pfVar5 + 1;
      } while (iVar6 < iVar1);
    }
LAB_004e9784:
    if (iVar6 == iVar1) {
      puVar4 = (undefined4 *)(iVar1 * 0x10 + -0x10 + *(int *)(regEbx + 0x11c));
      _DAT_005a90e0 = *puVar4;
      _DAT_005a90e4 = puVar4[1];
      _DAT_005a90e8 = puVar4[2];
      _DAT_005a90ec = puVar4[3];
    }
    else {
      pfVar5 = (float *)(*(int *)(regEbx + 0x118) + iVar6 * 4);
      puVar4 = (undefined4 *)
               SlerpQuaternionsToScratch((float *)(iVar6 * 0x10 + *(int *)(regEbx + 0x11c)),(param_1 - *(float *)(*(int *)(regEbx + 0x118) + -4 + iVar6 * 4)) / (*pfVar5 - pfVar5[-1]),(float *)(iVar6 * 0x10 + -0x10 + *(int *)(regEbx + 0x11c)));
      _DAT_005a90e0 = *puVar4;
      _DAT_005a90e4 = puVar4[1];
      _DAT_005a90e8 = puVar4[2];
      _DAT_005a90ec = puVar4[3];
    }
  }
  iVar1 = *(int *)(regEbx + 0x108);
  if (iVar1 < 2) {
    DAT_00793668 = 0.0;
    DAT_0079366c = 0.0;
    DAT_00793670 = 0.0;
  }
  else {
    pfVar5 = *(float **)(regEbx + 0x10c);
    if (*pfVar5 <= param_1) {
      iVar6 = 0;
      if (3 < iVar1) {
        pfVar7 = pfVar5 + 2;
        do {
          if (param_1 < pfVar7[-2]) goto LAB_004e98f4;
          if (param_1 < pfVar7[-1]) {
            iVar6 = iVar6 + 1;
            goto LAB_004e98f4;
          }
          if (param_1 < *pfVar7) {
            iVar6 = iVar6 + 2;
            goto LAB_004e98f4;
          }
          if (param_1 < pfVar7[1]) {
            iVar6 = iVar6 + 3;
            goto LAB_004e98f4;
          }
          iVar6 = iVar6 + 4;
          pfVar7 = pfVar7 + 4;
        } while (iVar6 < iVar1 + -3);
      }
      if (iVar6 < iVar1) {
        pfVar5 = pfVar5 + iVar6;
        do {
          if (param_1 < *pfVar5) break;
          iVar6 = iVar6 + 1;
          pfVar5 = pfVar5 + 1;
        } while (iVar6 < iVar1);
      }
LAB_004e98f4:
      if (iVar6 == iVar1) {
        pfVar5 = (float *)(*(int *)(regEbx + 0x110) + -0xc + iVar1 * 0xc);
        DAT_00793668 = *pfVar5;
        DAT_0079366c = pfVar5[1];
        DAT_00793670 = pfVar5[2];
      }
      else {
        pfVar5 = (float *)(*(int *)(regEbx + 0x10c) + iVar6 * 4);
        fVar2 = (param_1 - *(float *)(*(int *)(regEbx + 0x10c) + -4 + iVar6 * 4)) /
                (*pfVar5 - pfVar5[-1]);
        pfVar5 = (float *)(*(int *)(regEbx + 0x110) + iVar6 * 0xc);
        DAT_0079371c = *pfVar5 - pfVar5[-3];
        DAT_00793720 = pfVar5[1] - pfVar5[-2];
        DAT_00793724 = pfVar5[2] - pfVar5[-1];
        pfVar5 = (float *)(iVar6 * 0xc + -0xc + *(int *)(regEbx + 0x110));
        DAT_00793668 = DAT_0079371c * fVar2 + *pfVar5;
        DAT_0079366c = DAT_00793720 * fVar2 + pfVar5[1];
        DAT_00793670 = DAT_00793724 * fVar2 + pfVar5[2];
      }
    }
    else {
      DAT_00793668 = 0.0;
      DAT_0079366c = 0.0;
      DAT_00793670 = 0.0;
    }
  }
  QuaternionToRotationMatrix(pfVar3,(float *)&DAT_005a90e0);
  fVar2 = (float)param_2 - _DAT_00557fb0;
  pfVar3[0xc] = DAT_00793668;
  pfVar3[0xd] = DAT_0079366c;
  pfVar3[0xe] = DAT_00793670;
  if (_DAT_0054c870 <= ABS(fVar2)) {
    *pfVar3 = (float)param_2 * *pfVar3;
    pfVar3[1] = (float)param_2 * pfVar3[1];
    pfVar3[2] = (float)param_2 * pfVar3[2];
    pfVar3[4] = (float)param_2 * pfVar3[4];
    pfVar3[5] = (float)param_2 * pfVar3[5];
    pfVar3[6] = (float)param_2 * pfVar3[6];
    pfVar3[8] = (float)param_2 * pfVar3[8];
    pfVar3[9] = (float)param_2 * pfVar3[9];
    pfVar3[10] = (float)param_2 * pfVar3[10];
  }
  return;
}

