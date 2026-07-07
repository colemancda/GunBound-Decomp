/* FUN_0051b030 - 0x0051b030 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_0051b030(undefined4 param_1,undefined4 param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined4 in_EAX;
  
  fVar1 = DAT_00f25944 * param_3[0x11] + DAT_00f25900 * *param_3;
  fVar2 = (DAT_00f25900 * *param_3 - DAT_00f25944 * param_3[0x11]) * DAT_00f25960;
  fVar4 = DAT_00f25924 * param_3[9] + DAT_00f25920 * param_3[8];
  fVar3 = (DAT_00f25920 * param_3[8] - DAT_00f25924 * param_3[9]) * DAT_00f25980;
  DAT_00568738 = fVar1 + fVar4;
  DAT_0056874c = fVar1 - fVar4;
  DAT_00568798 = fVar3 + fVar2;
  DAT_005687ac = fVar2 - fVar3;
  fVar1 = DAT_00f25940 * param_3[0x10] + DAT_00f25904 * param_3[1];
  fVar2 = (DAT_00f25904 * param_3[1] - DAT_00f25940 * param_3[0x10]) * DAT_00f25964;
  fVar4 = DAT_00f25928 * param_3[10] + DAT_00f2591c * param_3[7];
  fVar3 = (DAT_00f2591c * param_3[7] - DAT_00f25928 * param_3[10]) * DAT_00f2597c;
  DAT_0056873c = fVar1 + fVar4;
  DAT_00568750 = fVar1 - fVar4;
  DAT_0056879c = fVar3 + fVar2;
  DAT_005687b0 = fVar2 - fVar3;
  fVar1 = DAT_00f2593c * param_3[0xf] + DAT_00f25908 * param_3[2];
  fVar2 = (DAT_00f25908 * param_3[2] - DAT_00f2593c * param_3[0xf]) * DAT_00f25968;
  fVar4 = DAT_00f2592c * param_3[0xb] + DAT_00f25918 * param_3[6];
  fVar3 = (DAT_00f25918 * param_3[6] - DAT_00f2592c * param_3[0xb]) * DAT_00f25978;
  DAT_00568740 = fVar1 + fVar4;
  DAT_00568754 = fVar1 - fVar4;
  DAT_005687a0 = fVar3 + fVar2;
  DAT_005687b4 = fVar2 - fVar3;
  fVar1 = DAT_00f25938 * param_3[0xe] + DAT_00f2590c * param_3[3];
  fVar2 = (DAT_00f2590c * param_3[3] - DAT_00f25938 * param_3[0xe]) * DAT_00f2596c;
  fVar4 = DAT_00f25930 * param_3[0xc] + DAT_00f25914 * param_3[5];
  fVar3 = (DAT_00f25914 * param_3[5] - DAT_00f25930 * param_3[0xc]) * DAT_00f25974;
  DAT_00568744 = fVar1 + fVar4;
  DAT_00568758 = fVar1 - fVar4;
  DAT_005687a4 = fVar3 + fVar2;
  DAT_005687b8 = fVar2 - fVar3;
  DAT_00568748 = DAT_00f25934 * param_3[0xd] + DAT_00f25910 * param_3[4];
  DAT_005687a8 = (DAT_00f25910 * param_3[4] - DAT_00f25934 * param_3[0xd]) * DAT_00f25970;
  fVar1 = (DAT_00568738 + DAT_0056873c + DAT_00568740 + DAT_00568744 + DAT_00568748) * _DAT_005687f8
  ;
  *param_3 = fVar1;
  fVar2 = (DAT_00568798 + DAT_0056879c + DAT_005687a0 + DAT_005687a4 + DAT_005687a8) * _DAT_005687f8
  ;
  fVar4 = DAT_00f259b0 * DAT_0056874c;
  fVar6 = DAT_00f259b4 * DAT_00568750;
  fVar5 = DAT_00f259b8 * DAT_00568754;
  fVar7 = DAT_00f259bc * DAT_00568758;
  fVar3 = (DAT_00f259bc * DAT_005687b8 +
          DAT_00f259b8 * DAT_005687b4 + DAT_00f259b4 * DAT_005687b0 + DAT_00f259b0 * DAT_005687ac) -
          fVar2;
  fVar2 = fVar2 - fVar1;
  param_3[1] = fVar2;
  fVar2 = (fVar7 + fVar5 + fVar6 + fVar4) - fVar2;
  param_3[2] = fVar2;
  fVar1 = (DAT_00f259cc * DAT_00568744 +
          DAT_00f259c8 * DAT_00568740 + DAT_00f259c4 * DAT_0056873c + DAT_00f259c0 * DAT_00568738) -
          DAT_00568748;
  fVar4 = ((DAT_00f259cc * DAT_005687a4 +
           DAT_00f259c8 * DAT_005687a0 + DAT_00f259c4 * DAT_0056879c + DAT_00f259c0 * DAT_00568798)
          - DAT_005687a8) - fVar3;
  fVar3 = fVar3 - fVar2;
  param_3[3] = fVar3;
  fVar1 = fVar1 - fVar3;
  param_3[4] = fVar1;
  fVar2 = ((DAT_0056874c - DAT_00568754) - DAT_00568758) * DAT_00f259d0;
  fVar3 = ((DAT_005687ac - DAT_005687b4) - DAT_005687b8) * DAT_00f259d0 - fVar4;
  fVar4 = fVar4 - fVar1;
  param_3[5] = fVar4;
  fVar2 = fVar2 - fVar4;
  param_3[6] = fVar2;
  fVar1 = DAT_00f259ec * DAT_00568744 +
          DAT_00f259e8 * DAT_00568740 + DAT_00f259e4 * DAT_0056873c + DAT_00f259e0 * DAT_00568738 +
          DAT_00568748;
  fVar4 = (DAT_00f259ec * DAT_005687a4 +
           DAT_00f259e8 * DAT_005687a0 + DAT_00f259e4 * DAT_0056879c + DAT_00f259e0 * DAT_00568798 +
          DAT_005687a8) - fVar3;
  fVar3 = fVar3 - fVar2;
  param_3[7] = fVar3;
  fVar1 = fVar1 - fVar3;
  param_3[8] = fVar1;
  fVar3 = DAT_00f259f0 * DAT_0056874c;
  fVar6 = DAT_00f259f4 * DAT_00568750;
  fVar5 = DAT_00f259f8 * DAT_00568754;
  fVar7 = DAT_00f259fc * DAT_00568758;
  fVar2 = (DAT_00f259fc * DAT_005687b8 +
          DAT_00f259f8 * DAT_005687b4 + DAT_00f259f4 * DAT_005687b0 + DAT_00f259f0 * DAT_005687ac) -
          fVar4;
  fVar4 = fVar4 - fVar1;
  param_3[9] = fVar4;
  fVar4 = (fVar7 + fVar5 + fVar6 + fVar3) - fVar4;
  param_3[10] = fVar4;
  fVar1 = ((DAT_00568738 + DAT_00568740 + DAT_00568744) * _DAT_005687f8 - DAT_0056873c) -
          DAT_00568748;
  fVar3 = (((DAT_00568798 + DAT_005687a0 + DAT_005687a4) * _DAT_005687f8 - DAT_0056879c) -
          DAT_005687a8) - fVar2;
  fVar2 = fVar2 - fVar4;
  param_3[0xb] = fVar2;
  fVar1 = fVar1 - fVar2;
  param_3[0xc] = fVar1;
  fVar2 = DAT_00f25a10 * DAT_0056874c;
  fVar6 = DAT_00f25a14 * DAT_00568750;
  fVar5 = DAT_00f25a18 * DAT_00568754;
  fVar7 = DAT_00f25a1c * DAT_00568758;
  fVar4 = (DAT_00f25a1c * DAT_005687b8 +
          DAT_00f25a18 * DAT_005687b4 + DAT_00f25a14 * DAT_005687b0 + DAT_00f25a10 * DAT_005687ac) -
          fVar3;
  fVar3 = fVar3 - fVar1;
  param_3[0xd] = fVar3;
  fVar3 = (fVar7 + fVar5 + fVar6 + fVar2) - fVar3;
  param_3[0xe] = fVar3;
  fVar1 = DAT_00f25a2c * DAT_00568744 +
          DAT_00f25a28 * DAT_00568740 + DAT_00f25a24 * DAT_0056873c + DAT_00f25a20 * DAT_00568738 +
          DAT_00568748;
  fVar2 = DAT_00f25a2c * DAT_005687a4 +
          DAT_00f25a28 * DAT_005687a0 + DAT_00f25a24 * DAT_0056879c + DAT_00f25a20 * DAT_00568798 +
          DAT_005687a8;
  fVar3 = fVar4 - fVar3;
  param_3[0xf] = fVar3;
  fVar1 = fVar1 - fVar3;
  param_3[0x10] = fVar1;
  param_3[0x11] = (fVar2 - fVar4) - fVar1;
  return CONCAT44(param_2,in_EAX);
}

