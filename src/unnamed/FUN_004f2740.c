/* FUN_004f2740 - 0x004f2740 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f2740(uint *param_1,int param_2,uint param_3)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uStack_20;
  
  if (param_3 != 0) {
    uStack_20 = CONCAT22(param_2,param_2);
    uVar4 = (uStack_20 & 0xe79ce79c) >> 2;
    for (uVar3 = param_3 >> 1; uVar3 != 0; uVar3 = uVar3 - 1) {
      uVar2 = (*param_1 >> 1 & 0x7bef7bef) + uVar4;
      if ((uVar2 & 0x80000000) != 0) {
        uVar2 = uVar2 | 0x78000000;
      }
      if ((uVar2 & 0x4000000) != 0) {
        uVar2 = uVar2 | 0x3e00000;
      }
      if ((uVar2 & 0x100000) != 0) {
        uVar2 = uVar2 | 0xf0000;
      }
      if ((uVar2 & 0x8000) != 0) {
        uVar2 = uVar2 | 0x7800;
      }
      if ((uVar2 & 0x400) != 0) {
        uVar2 = uVar2 | 0x3e0;
      }
      if ((uVar2 & 0x10) != 0) {
        uVar2 = uVar2 | 0xf;
      }
      *param_1 = uVar2 << 1;
      param_1 = param_1 + 1;
    }
    if ((param_3 & 1) != 0) {
      uVar1 = ((ushort)*param_1 >> 1 & 0x7bef) + (short)uVar4;
      if ((uVar1 & 0x8000) != 0) {
        uVar1 = uVar1 | 0x7800;
      }
      if ((uVar1 & 0x400) != 0) {
        uVar1 = uVar1 | 0x3e0;
      }
      if ((uVar1 & 0x10) != 0) {
        uVar1 = uVar1 | 0xf;
      }
      *(ushort *)param_1 = uVar1 << 1;
    }
  }
  return;
}

