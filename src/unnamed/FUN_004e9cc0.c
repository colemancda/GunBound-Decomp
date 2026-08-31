/* FUN_004e9cc0 - 0x004e9cc0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004e9cc0(int *param_1,undefined4 param_2)

{
  float fVar1;
  float fVar2;
  int *piVar3;
  float fVar4;
  int iVar5;
  int *piVar6;
  undefined4 *puVar7;
  float10 fVar8;
  float10 fVar9;
  
  piVar3 = param_1 + 0x38;
  if (param_1[0x32] == 0) {
    piVar6 = piVar3;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar6 = 0;
      piVar6 = piVar6 + 1;
    }
    param_1[0x47] = 0x3f800000;
    param_1[0x42] = 0x3f800000;
    param_1[0x3d] = 0x3f800000;
    *piVar3 = 0x3f800000;
  }
  else {
    FUN_004e95c0(param_2,piVar3,param_1[0x32]);
  }
  if (param_1[0x34] == 0) {
    /* Binary 0x4e9d4d: `mov edx,0x5a9130` feeds BOTH calls - EDX for
     * FUN_004f3440 (which leaves it untouched) and, via `mov eax,edx`
     * at 0x4e9d5d, the second matrix operand of the multiply. ESI is
     * this object throughout; 0 is FUN_004f3440's dead-ECX slot. */
    FUN_004f3440(0,(float *)DAT_005a9130,(int)param_1);
    puVar7 = MultiplyMatrix4x4ToScratch((float *)(param_1 + 0x68),(float *)DAT_005a9130);
    MultiplyMatrix4x4InPlace((float *)(param_1 + 0x38),(float *)puVar7);
  }
  else {
    /* Binary 0x4e9d06..0x4e9d22: EAX = param_1[0x34] + 0xe0 (the source
     * node's own matrix slot), ECX = param_1 + 0x1a0, then EBX =
     * param_1 + 0xe0 with EAX = the multiply's returned scratch. */
    puVar7 = MultiplyMatrix4x4ToScratch((float *)(param_1 + 0x68),(float *)(param_1[0x34] + 0xe0));
    MultiplyMatrix4x4InPlace((float *)(param_1 + 0x38),(float *)puVar7);
    param_1[0x26] = param_1[0x44];
    param_1[0x27] = param_1[0x45];
    param_1[0x28] = param_1[0x46];
  }
  if ((char)param_1[0x37] != '\0') {
    fVar8 = (float10)fcos((float10)(float)param_1[0xbe]);
    fVar9 = (float10)fsin((float10)(float)param_1[0xbe]);
    fVar1 = (float)(fVar8 / fVar9);
    fVar2 = (float)((fVar8 / fVar9) * (float10)(float)param_1[0xc1]);
    fVar4 = (float)param_1[0xc0] / ((float)param_1[0xc0] - (float)param_1[0xbf]);
    _DAT_0079361c = param_1;
    FUN_004f2530();
    puVar7 = (undefined4 *)DAT_005a9290;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = 0;
      puVar7 = puVar7 + 1;
    }
    _DAT_005a92bc = 1.0f;
    _DAT_005a92c8 = -(fVar4 * (float)param_1[0xbf]);
    _DAT_00588f68 = param_1[0xbf];
    _DAT_00588f6c = param_1[0xc0];
    _DAT_00588f70 = fVar2;
    _DAT_00588f74 = fVar1;
    *(float *)DAT_005a9290 = fVar2;
    _DAT_005a92a4 = fVar1;
    _DAT_005a92b8 = fVar4;
  }
  (**(code **)(*param_1 + 4))(param_2);
  for (piVar3 = (int *)param_1[0x35]; piVar3 != (int *)0x0; piVar3 = (int *)piVar3[0x36]) {
    (**(code **)(*piVar3 + 0xc))(param_2);
  }
  return;
}

