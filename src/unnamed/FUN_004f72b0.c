/* FUN_004f72b0 - 0x004f72b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_004f72b0(undefined4 *param_1,int param_2,undefined4 param_3,int param_4)

{
  short sVar1;
  uint in_EAX;
  uint uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  uVar2 = in_EAX & 0x8000000f;
  bVar5 = uVar2 == 0;
  if ((int)uVar2 < 0) {
    bVar5 = (uVar2 - 1 | 0xfffffff0) == 0xffffffff;
  }
  if (!bVar5) {
    return 0;
  }
  iVar3 = (int)(in_EAX + ((int)in_EAX >> 0x1f & 0xfU)) >> 4;
  if (param_4 < iVar3 * 0xc) {
    return 0;
  }
  if (0 < iVar3) {
    iVar4 = 0;
    do {
      sVar1 = DecodeCipherBlock(&local_10,param_2);
      if ((sVar1 != 1) || (local_10 != *(int *)(param_2 + 0x20c))) {
        return 0;
      }
      *param_1 = local_c;
      iVar4 = iVar4 + 1;
      param_1[1] = local_8;
      param_1[2] = local_4;
      param_1 = param_1 + 3;
    } while (iVar4 < iVar3);
  }
  return 1;
}

