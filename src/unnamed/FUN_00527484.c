/* FUN_00527484 - 0x00527484 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    ___toupper_mt
   
   Library: Visual Studio 2003 Release */

uint ___toupper_mt(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  LPCSTR _LpSrcStr;
  int iVar4;
  BOOL unaff_ESI;
  undefined4 local_8;
  
  uVar2 = param_2;
  iVar4 = param_1;
  if ((*(int *)(param_1 + 0x14) == 0) || ((*(int *)(param_1 + 0x24) != 0 && (param_2 < 0x80)))) {
    if ((0x60 < (int)param_2) && ((int)param_2 < 0x7b)) {
      return param_2 - 0x20;
    }
  }
  else {
    if (param_2 < 0x100) {
      if (*(int *)(param_1 + 0x28) < 2) {
        uVar3 = *(byte *)(*(int *)(param_1 + 0x48) + param_2 * 2) & 2;
      }
      else {
        uVar3 = ___isctype_mt(param_1,param_2,2);
      }
      if (uVar3 == 0) {
        return uVar2;
      }
    }
    iVar1 = param_1;
    if ((*(byte *)(*(int *)(iVar4 + 0x48) + 1 + ((int)uVar2 >> 8 & 0xffU) * 2) & 0x80) == 0) {
      param_1._0_2_ = (ushort)(byte)uVar2;
      _LpSrcStr = (LPCSTR)0x1;
    }
    else {
      param_1._0_2_ = CONCAT11((byte)uVar2,(char)(uVar2 >> 8));
      param_1._3_1_ = SUB41(iVar1,3);
      param_1._0_3_ = (uint3)(ushort)param_1;
      _LpSrcStr = (LPCSTR)0x2;
    }
    iVar4 = ___crtLCMapStringA(*(_locale_t *)(iVar4 + 0x14),(LPCWSTR)&DAT_00000200,(DWORD)&param_1,
                               _LpSrcStr,(int)&local_8,(LPSTR)0x3,*(int *)(iVar4 + 4),1,unaff_ESI);
    if (iVar4 != 0) {
      if (iVar4 != 1) {
        return (uint)CONCAT11((undefined1)local_8,local_8._1_1_);
      }
      return local_8 & 0xff;
    }
  }
  return uVar2;
}

