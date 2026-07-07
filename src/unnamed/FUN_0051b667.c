/* FUN_0051b667 - 0x0051b667 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined8 __fastcall
FUN_0051b667(undefined4 param_1,undefined4 param_2,float *param_3,float *param_4,int param_5,
            int param_6,int param_7,int param_8,int param_9)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  int iVar9;
  
  if (param_6 == 2) {
    param_6 = 0;
  }
  iVar8 = (int)((ulonglong)(longlong)(param_7 + 0x11) / 0x12);
  iVar9 = 0;
  if (0 < iVar8) {
    do {
      fVar1 = DAT_00f25944 * param_3[0x11] + DAT_00f25900 * *param_3;
      fVar4 = (DAT_00f25900 * *param_3 - DAT_00f25944 * param_3[0x11]) * DAT_00f25960;
      fVar2 = DAT_00f25924 * param_3[9] + DAT_00f25920 * param_3[8];
      fVar3 = (DAT_00f25920 * param_3[8] - DAT_00f25924 * param_3[9]) * DAT_00f25980;
      DAT_00568738 = fVar1 + fVar2;
      DAT_0056874c = fVar1 - fVar2;
      DAT_00568798 = fVar3 + fVar4;
      DAT_005687ac = fVar4 - fVar3;
      fVar1 = DAT_00f25940 * param_3[0x10] + DAT_00f25904 * param_3[1];
      fVar4 = (DAT_00f25904 * param_3[1] - DAT_00f25940 * param_3[0x10]) * DAT_00f25964;
      fVar2 = DAT_00f25928 * param_3[10] + DAT_00f2591c * param_3[7];
      fVar3 = (DAT_00f2591c * param_3[7] - DAT_00f25928 * param_3[10]) * DAT_00f2597c;
      DAT_0056873c = fVar1 + fVar2;
      DAT_00568750 = fVar1 - fVar2;
      DAT_0056879c = fVar3 + fVar4;
      DAT_005687b0 = fVar4 - fVar3;
      fVar1 = DAT_00f2593c * param_3[0xf] + DAT_00f25908 * param_3[2];
      fVar4 = (DAT_00f25908 * param_3[2] - DAT_00f2593c * param_3[0xf]) * DAT_00f25968;
      fVar2 = DAT_00f2592c * param_3[0xb] + DAT_00f25918 * param_3[6];
      fVar3 = (DAT_00f25918 * param_3[6] - DAT_00f2592c * param_3[0xb]) * DAT_00f25978;
      DAT_00568740 = fVar1 + fVar2;
      DAT_00568754 = fVar1 - fVar2;
      DAT_005687a0 = fVar3 + fVar4;
      DAT_005687b4 = fVar4 - fVar3;
      fVar1 = DAT_00f25938 * param_3[0xe] + DAT_00f2590c * param_3[3];
      fVar4 = (DAT_00f2590c * param_3[3] - DAT_00f25938 * param_3[0xe]) * DAT_00f2596c;
      fVar2 = DAT_00f25930 * param_3[0xc] + DAT_00f25914 * param_3[5];
      fVar3 = (DAT_00f25914 * param_3[5] - DAT_00f25930 * param_3[0xc]) * DAT_00f25974;
      DAT_00568744 = fVar1 + fVar2;
      DAT_00568758 = fVar1 - fVar2;
      DAT_005687a4 = fVar3 + fVar4;
      DAT_005687b8 = fVar4 - fVar3;
      DAT_00568748 = DAT_00f25934 * param_3[0xd] + DAT_00f25910 * param_3[4];
      DAT_005687a8 = (DAT_00f25910 * param_3[4] - DAT_00f25934 * param_3[0xd]) * DAT_00f25970;
      fVar1 = (DAT_00568738 + DAT_0056873c + DAT_00568740 + DAT_00568744 + DAT_00568748) *
              _DAT_005687f8;
      *param_3 = fVar1;
      fVar2 = (DAT_00568798 + DAT_0056879c + DAT_005687a0 + DAT_005687a4 + DAT_005687a8) *
              _DAT_005687f8;
      fVar4 = DAT_00f259b0 * DAT_0056874c;
      fVar6 = DAT_00f259b4 * DAT_00568750;
      fVar5 = DAT_00f259b8 * DAT_00568754;
      fVar7 = DAT_00f259bc * DAT_00568758;
      fVar3 = (DAT_00f259bc * DAT_005687b8 +
              DAT_00f259b8 * DAT_005687b4 +
              DAT_00f259b4 * DAT_005687b0 + DAT_00f259b0 * DAT_005687ac) - fVar2;
      fVar2 = fVar2 - fVar1;
      param_3[1] = fVar2;
      fVar2 = (fVar7 + fVar5 + fVar6 + fVar4) - fVar2;
      param_3[2] = fVar2;
      fVar1 = (DAT_00f259cc * DAT_00568744 +
              DAT_00f259c8 * DAT_00568740 +
              DAT_00f259c4 * DAT_0056873c + DAT_00f259c0 * DAT_00568738) - DAT_00568748;
      fVar4 = ((DAT_00f259cc * DAT_005687a4 +
               DAT_00f259c8 * DAT_005687a0 +
               DAT_00f259c4 * DAT_0056879c + DAT_00f259c0 * DAT_00568798) - DAT_005687a8) - fVar3;
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
              DAT_00f259e8 * DAT_00568740 +
              DAT_00f259e4 * DAT_0056873c + DAT_00f259e0 * DAT_00568738 + DAT_00568748;
      fVar4 = (DAT_00f259ec * DAT_005687a4 +
               DAT_00f259e8 * DAT_005687a0 +
               DAT_00f259e4 * DAT_0056879c + DAT_00f259e0 * DAT_00568798 + DAT_005687a8) - fVar3;
      fVar3 = fVar3 - fVar2;
      param_3[7] = fVar3;
      fVar1 = fVar1 - fVar3;
      param_3[8] = fVar1;
      fVar3 = DAT_00f259f0 * DAT_0056874c;
      fVar6 = DAT_00f259f4 * DAT_00568750;
      fVar5 = DAT_00f259f8 * DAT_00568754;
      fVar7 = DAT_00f259fc * DAT_00568758;
      fVar2 = (DAT_00f259fc * DAT_005687b8 +
              DAT_00f259f8 * DAT_005687b4 +
              DAT_00f259f4 * DAT_005687b0 + DAT_00f259f0 * DAT_005687ac) - fVar4;
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
              DAT_00f25a18 * DAT_005687b4 +
              DAT_00f25a14 * DAT_005687b0 + DAT_00f25a10 * DAT_005687ac) - fVar3;
      fVar3 = fVar3 - fVar1;
      param_3[0xd] = fVar3;
      fVar3 = (fVar7 + fVar5 + fVar6 + fVar2) - fVar3;
      param_3[0xe] = fVar3;
      fVar1 = DAT_00f25a2c * DAT_00568744 +
              DAT_00f25a28 * DAT_00568740 +
              DAT_00f25a24 * DAT_0056873c + DAT_00f25a20 * DAT_00568738 + DAT_00568748;
      fVar2 = DAT_00f25a2c * DAT_005687a4 +
              DAT_00f25a28 * DAT_005687a0 +
              DAT_00f25a24 * DAT_0056879c + DAT_00f25a20 * DAT_00568798 + DAT_005687a8;
      fVar3 = fVar4 - fVar3;
      param_3[0xf] = fVar3;
      fVar1 = fVar1 - fVar3;
      param_3[0x10] = fVar1;
      param_3[0x11] = (fVar2 - fVar4) - fVar1;
      *(float *)(param_5 + iVar9 * 4) =
           (float)(&DAT_00f25b00)[param_6 * 0x24] * param_3[9] + *param_4;
      *(float *)(param_5 + 0x480 + iVar9 * 4) =
           (float)(&DAT_00f25b24)[param_6 * 0x24] * param_3[0x11] + param_4[9];
      *(float *)(param_5 + 0x80 + iVar9 * 4) =
           (float)(&DAT_00f25b04)[param_6 * 0x24] * param_3[10] + param_4[1];
      *(float *)(param_5 + 0x500 + iVar9 * 4) =
           (float)(&DAT_00f25b28)[param_6 * 0x24] * param_3[0x10] + param_4[10];
      *(float *)(param_5 + 0x100 + iVar9 * 4) =
           (float)(&DAT_00f25b08)[param_6 * 0x24] * param_3[0xb] + param_4[2];
      *(float *)(param_5 + 0x580 + iVar9 * 4) =
           (float)(&DAT_00f25b2c)[param_6 * 0x24] * param_3[0xf] + param_4[0xb];
      *(float *)(param_5 + 0x180 + iVar9 * 4) =
           (float)(&DAT_00f25b0c)[param_6 * 0x24] * param_3[0xc] + param_4[3];
      *(float *)(param_5 + 0x600 + iVar9 * 4) =
           (float)(&DAT_00f25b30)[param_6 * 0x24] * param_3[0xe] + param_4[0xc];
      *(float *)(param_5 + 0x200 + iVar9 * 4) =
           (float)(&DAT_00f25b10)[param_6 * 0x24] * param_3[0xd] + param_4[4];
      *(float *)(param_5 + 0x680 + iVar9 * 4) =
           (float)(&DAT_00f25b34)[param_6 * 0x24] * param_3[0xd] + param_4[0xd];
      *(float *)(param_5 + 0x280 + iVar9 * 4) =
           (float)(&DAT_00f25b14)[param_6 * 0x24] * param_3[0xe] + param_4[5];
      *(float *)(param_5 + 0x700 + iVar9 * 4) =
           (float)(&DAT_00f25b38)[param_6 * 0x24] * param_3[0xc] + param_4[0xe];
      *(float *)(param_5 + 0x300 + iVar9 * 4) =
           (float)(&DAT_00f25b18)[param_6 * 0x24] * param_3[0xf] + param_4[6];
      *(float *)(param_5 + 0x780 + iVar9 * 4) =
           (float)(&DAT_00f25b3c)[param_6 * 0x24] * param_3[0xb] + param_4[0xf];
      *(float *)(param_5 + 0x380 + iVar9 * 4) =
           (float)(&DAT_00f25b1c)[param_6 * 0x24] * param_3[0x10] + param_4[7];
      *(float *)(param_5 + 0x800 + iVar9 * 4) =
           (float)(&DAT_00f25b40)[param_6 * 0x24] * param_3[10] + param_4[0x10];
      *(float *)(param_5 + 0x400 + iVar9 * 4) =
           (float)(&DAT_00f25b20)[param_6 * 0x24] * param_3[0x11] + param_4[8];
      *(float *)(param_5 + 0x880 + iVar9 * 4) =
           (float)(&DAT_00f25b44)[param_6 * 0x24] * param_3[9] + param_4[0x11];
      fVar1 = *param_3;
      fVar2 = param_3[8];
      *param_3 = (float)(&DAT_00f25b48)[param_6 * 0x24] * fVar2;
      param_3[8] = (float)(&DAT_00f25b68)[param_6 * 0x24] * fVar1;
      param_3[9] = fVar1 * (float)(&DAT_00f25b6c)[param_6 * 0x24];
      param_3[0x11] = fVar2 * (float)(&DAT_00f25b8c)[param_6 * 0x24];
      fVar1 = param_3[1];
      fVar2 = param_3[7];
      param_3[1] = (float)(&DAT_00f25b4c)[param_6 * 0x24] * fVar2;
      param_3[7] = (float)(&DAT_00f25b64)[param_6 * 0x24] * fVar1;
      param_3[10] = fVar1 * (float)(&DAT_00f25b70)[param_6 * 0x24];
      param_3[0x10] = fVar2 * (float)(&DAT_00f25b88)[param_6 * 0x24];
      fVar1 = param_3[2];
      fVar2 = param_3[6];
      param_3[2] = (float)(&DAT_00f25b50)[param_6 * 0x24] * fVar2;
      param_3[6] = (float)(&DAT_00f25b60)[param_6 * 0x24] * fVar1;
      param_3[0xb] = fVar1 * (float)(&DAT_00f25b74)[param_6 * 0x24];
      param_3[0xf] = fVar2 * (float)(&DAT_00f25b84)[param_6 * 0x24];
      fVar1 = param_3[3];
      fVar2 = param_3[5];
      param_3[3] = (float)(&DAT_00f25b54)[param_6 * 0x24] * fVar2;
      param_3[5] = (float)(&DAT_00f25b5c)[param_6 * 0x24] * fVar1;
      param_3[0xc] = fVar1 * (float)(&DAT_00f25b78)[param_6 * 0x24];
      param_3[0xe] = fVar2 * (float)(&DAT_00f25b80)[param_6 * 0x24];
      fVar1 = param_3[4];
      fVar2 = (float)(&DAT_00f25b7c)[param_6 * 0x24];
      param_3[4] = fVar1 * (float)(&DAT_00f25b58)[param_6 * 0x24];
      param_3[0xd] = fVar1 * fVar2;
      param_3 = param_3 + 0x12;
      param_4 = param_4 + 0x12;
      iVar9 = iVar9 + 1;
    } while (iVar9 < iVar8);
  }
  for (; iVar9 < (int)((ulonglong)(longlong)(param_8 + 0x11) / 0x12); iVar9 = iVar9 + 1) {
    DAT_00568738 = param_3[0xf] * DAT_00f258d4 + *param_3 * DAT_00f258c0;
    DAT_00568744 = (*param_3 * DAT_00f258c0 - param_3[0xf] * DAT_00f258d4) * DAT_00f258e0;
    DAT_0056873c = param_3[0xc] * DAT_00f258d0 + param_3[3] * DAT_00f258c4;
    DAT_00568748 = (param_3[3] * DAT_00f258c4 - param_3[0xc] * DAT_00f258d0) * DAT_00f258e4;
    DAT_00568740 = param_3[9] * DAT_00f258cc + param_3[6] * DAT_00f258c8;
    DAT_0056874c = (param_3[6] * DAT_00f258c8 - param_3[9] * DAT_00f258cc) * DAT_00f258e8;
    DAT_00568750 = param_3[0x10] * DAT_00f258d4 + param_3[1] * DAT_00f258c0;
    DAT_0056875c = (param_3[1] * DAT_00f258c0 - param_3[0x10] * DAT_00f258d4) * DAT_00f258e0;
    DAT_00568754 = param_3[0xd] * DAT_00f258d0 + param_3[4] * DAT_00f258c4;
    DAT_00568760 = (param_3[4] * DAT_00f258c4 - param_3[0xd] * DAT_00f258d0) * DAT_00f258e4;
    DAT_00568758 = param_3[10] * DAT_00f258cc + param_3[7] * DAT_00f258c8;
    DAT_00568764 = (param_3[7] * DAT_00f258c8 - param_3[10] * DAT_00f258cc) * DAT_00f258e8;
    DAT_00568768 = param_3[0x11] * DAT_00f258d4 + param_3[2] * DAT_00f258c0;
    DAT_00568774 = (param_3[2] * DAT_00f258c0 - param_3[0x11] * DAT_00f258d4) * DAT_00f258e0;
    DAT_0056876c = param_3[0xe] * DAT_00f258d0 + param_3[5] * DAT_00f258c4;
    DAT_00568778 = (param_3[5] * DAT_00f258c4 - param_3[0xe] * DAT_00f258d0) * DAT_00f258e4;
    DAT_00568770 = param_3[0xb] * DAT_00f258cc + param_3[8] * DAT_00f258c8;
    DAT_0056877c = (param_3[8] * DAT_00f258c8 - param_3[0xb] * DAT_00f258cc) * DAT_00f258e8;
    fVar1 = DAT_00568738 + DAT_00568740;
    fVar6 = DAT_00568744 + DAT_0056874c;
    fVar2 = fVar1 + DAT_0056873c;
    *param_3 = fVar2;
    fVar4 = fVar6 + DAT_00568748;
    fVar5 = (DAT_00568738 - DAT_00568740) * _DAT_00f25a30;
    fVar3 = (DAT_00568744 - DAT_0056874c) * _DAT_00f25a30 - fVar4;
    fVar4 = fVar4 - fVar2;
    param_3[1] = fVar4;
    fVar5 = fVar5 - fVar4;
    param_3[2] = fVar5;
    fVar1 = (fVar1 - DAT_0056873c) - DAT_0056873c;
    fVar2 = (fVar6 - DAT_00568748) - DAT_00568748;
    fVar5 = fVar3 - fVar5;
    param_3[3] = fVar5;
    fVar1 = fVar1 - fVar5;
    param_3[4] = fVar1;
    param_3[5] = (fVar2 - fVar3) - fVar1;
    fVar1 = DAT_00568750 + DAT_00568758;
    fVar6 = DAT_0056875c + DAT_00568764;
    fVar2 = fVar1 + DAT_00568754;
    param_3[6] = fVar2;
    fVar4 = fVar6 + DAT_00568760;
    fVar5 = (DAT_00568750 - DAT_00568758) * _DAT_00f25a30;
    fVar3 = (DAT_0056875c - DAT_00568764) * _DAT_00f25a30 - fVar4;
    fVar4 = fVar4 - fVar2;
    param_3[7] = fVar4;
    fVar5 = fVar5 - fVar4;
    param_3[8] = fVar5;
    fVar1 = (fVar1 - DAT_00568754) - DAT_00568754;
    fVar2 = (fVar6 - DAT_00568760) - DAT_00568760;
    fVar5 = fVar3 - fVar5;
    param_3[9] = fVar5;
    fVar1 = fVar1 - fVar5;
    param_3[10] = fVar1;
    param_3[0xb] = (fVar2 - fVar3) - fVar1;
    fVar1 = DAT_00568768 + DAT_00568770;
    fVar6 = DAT_00568774 + DAT_0056877c;
    fVar2 = fVar1 + DAT_0056876c;
    param_3[0xc] = fVar2;
    fVar4 = fVar6 + DAT_00568778;
    fVar5 = (DAT_00568768 - DAT_00568770) * _DAT_00f25a30;
    fVar3 = (DAT_00568774 - DAT_0056877c) * _DAT_00f25a30 - fVar4;
    fVar4 = fVar4 - fVar2;
    param_3[0xd] = fVar4;
    fVar5 = fVar5 - fVar4;
    param_3[0xe] = fVar5;
    fVar1 = (fVar1 - DAT_0056876c) - DAT_0056876c;
    fVar2 = (fVar6 - DAT_00568778) - DAT_00568778;
    fVar5 = fVar3 - fVar5;
    param_3[0xf] = fVar5;
    fVar1 = fVar1 - fVar5;
    param_3[0x10] = fVar1;
    param_3[0x11] = (fVar2 - fVar3) - fVar1;
    *(float *)(param_5 + iVar9 * 4) = *param_4;
    *(float *)(param_5 + 0x180 + iVar9 * 4) = param_4[3];
    fVar1 = DAT_00f25c20;
    *(float *)(param_5 + 0x300 + iVar9 * 4) = param_3[3] * DAT_00f25c20 + param_4[6];
    fVar2 = DAT_00f25c2c;
    *(float *)(param_5 + 0x480 + iVar9 * 4) = param_3[5] * DAT_00f25c2c + param_4[9];
    *(float *)(param_5 + 0x600 + iVar9 * 4) =
         fVar1 * param_3[9] + param_4[0xc] + DAT_00f25c38 * param_3[2];
    *(float *)(param_5 + 0x780 + iVar9 * 4) =
         fVar2 * param_3[0xb] + param_4[0xf] + DAT_00f25c44 * *param_3;
    *(float *)(param_5 + 0x80 + iVar9 * 4) = param_4[1];
    *(float *)(param_5 + 0x200 + iVar9 * 4) = param_4[4];
    fVar1 = DAT_00f25c24;
    *(float *)(param_5 + 0x380 + iVar9 * 4) = param_3[4] * DAT_00f25c24 + param_4[7];
    fVar2 = DAT_00f25c30;
    *(float *)(param_5 + 0x500 + iVar9 * 4) = param_3[4] * DAT_00f25c30 + param_4[10];
    *(float *)(param_5 + 0x680 + iVar9 * 4) =
         fVar1 * param_3[10] + param_4[0xd] + DAT_00f25c3c * param_3[1];
    *(float *)(param_5 + 0x800 + iVar9 * 4) =
         fVar2 * param_3[10] + param_4[0x10] + DAT_00f25c48 * param_3[1];
    *(float *)(param_5 + 0x100 + iVar9 * 4) = param_4[2];
    *(float *)(param_5 + 0x280 + iVar9 * 4) = param_4[5];
    fVar1 = DAT_00f25c28;
    *(float *)(param_5 + 0x400 + iVar9 * 4) = param_3[5] * DAT_00f25c28 + param_4[8];
    fVar2 = DAT_00f25c34;
    *(float *)(param_5 + 0x580 + iVar9 * 4) = param_3[3] * DAT_00f25c34 + param_4[0xb];
    *(float *)(param_5 + 0x700 + iVar9 * 4) =
         fVar1 * param_3[0xb] + param_4[0xe] + DAT_00f25c40 * *param_3;
    *(float *)(param_5 + 0x880 + iVar9 * 4) =
         fVar2 * param_3[9] + param_4[0x11] + DAT_00f25c4c * param_3[2];
    *param_3 = DAT_00f25c20 * param_3[0xf] + DAT_00f25c38 * param_3[8];
    param_3[3] = DAT_00f25c2c * param_3[0x11] + DAT_00f25c44 * param_3[6];
    param_3[1] = DAT_00f25c24 * param_3[0x10] + DAT_00f25c3c * param_3[7];
    param_3[4] = DAT_00f25c30 * param_3[0x10] + DAT_00f25c48 * param_3[7];
    param_3[2] = DAT_00f25c28 * param_3[0x11] + DAT_00f25c40 * param_3[6];
    param_3[5] = DAT_00f25c34 * param_3[0xf] + DAT_00f25c4c * param_3[8];
    param_3[6] = DAT_00f25c38 * param_3[0xe];
    param_3[9] = DAT_00f25c44 * param_3[0xc];
    param_3[7] = DAT_00f25c3c * param_3[0xd];
    param_3[10] = DAT_00f25c48 * param_3[0xd];
    param_3[8] = DAT_00f25c40 * param_3[0xc];
    param_3[0xb] = DAT_00f25c4c * param_3[0xe];
    param_3[0xc] = 0.0;
    param_3[0xf] = 0.0;
    param_3[0xd] = 0.0;
    param_3[0x10] = 0.0;
    param_3[0xe] = 0.0;
    param_3[0x11] = 0.0;
    param_3 = param_3 + 0x12;
    param_4 = param_4 + 0x12;
  }
  iVar8 = DAT_00563d98;
  for (; DAT_00563d98 = iVar8, iVar9 < (int)((ulonglong)(longlong)(param_9 + 0x11) / 0x12);
      iVar9 = iVar9 + 1) {
    *(float *)(param_5 + iVar9 * 4) = *param_4;
    *(float *)(param_5 + 0x80 + iVar9 * 4) = param_4[1];
    *(float *)(param_5 + 0x100 + iVar9 * 4) = param_4[2];
    *(float *)(param_5 + 0x180 + iVar9 * 4) = param_4[3];
    *(float *)(param_5 + 0x200 + iVar9 * 4) = param_4[4];
    *(float *)(param_5 + 0x280 + iVar9 * 4) = param_4[5];
    *(float *)(param_5 + 0x300 + iVar9 * 4) = param_4[6];
    *(float *)(param_5 + 0x380 + iVar9 * 4) = param_4[7];
    *(float *)(param_5 + 0x400 + iVar9 * 4) = param_4[8];
    *(float *)(param_5 + 0x480 + iVar9 * 4) = param_4[9];
    *(float *)(param_5 + 0x500 + iVar9 * 4) = param_4[10];
    *(float *)(param_5 + 0x580 + iVar9 * 4) = param_4[0xb];
    *(float *)(param_5 + 0x600 + iVar9 * 4) = param_4[0xc];
    *(float *)(param_5 + 0x680 + iVar9 * 4) = param_4[0xd];
    *(float *)(param_5 + 0x700 + iVar9 * 4) = param_4[0xe];
    *(float *)(param_5 + 0x780 + iVar9 * 4) = param_4[0xf];
    *(float *)(param_5 + 0x800 + iVar9 * 4) = param_4[0x10];
    *(float *)(param_5 + 0x880 + iVar9 * 4) = param_4[0x11];
    param_4 = param_4 + 0x12;
    iVar8 = DAT_00563d98;
  }
  DAT_005687fc = iVar9 * 0x12;
  for (; iVar9 < iVar8; iVar9 = iVar9 + 1) {
    *(undefined4 *)(param_5 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x80 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x100 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x180 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x200 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x280 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x300 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x380 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x400 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x480 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x500 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x580 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x600 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x680 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x700 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x780 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x800 + iVar9 * 4) = 0;
    *(undefined4 *)(param_5 + 0x880 + iVar9 * 4) = 0;
  }
  return CONCAT44(param_2,DAT_005687fc);
}

