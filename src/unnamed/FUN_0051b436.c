/* FUN_0051b436 - 0x0051b436 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_0051b436(undefined4 param_1,undefined4 param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  undefined4 in_EAX;
  
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
  return CONCAT44(param_2,in_EAX);
}

