/* FUN_0052b814 - 0x0052b814 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    ___isctype_mt
   
   Library: Visual Studio 2003 Release */

uint __thiscall ___isctype_mt(undefined4 param_1,int param_2,int param_3,uint param_4)

{
  undefined4 uVar1;
  LPCSTR _LpSrcStr;
  BOOL BVar2;
  undefined4 local_8;
  
  if (param_3 + 1U < 0x101) {
    param_3._2_2_ = *(ushort *)(*(int *)(param_2 + 0x48) + param_3 * 2);
  }
  else {
    local_8._2_2_ = (undefined2)((uint)param_1 >> 0x10);
    if ((*(byte *)(*(int *)(param_2 + 0x48) + 1 + (param_3 >> 8 & 0xffU) * 2) & 0x80) == 0) {
      local_8._0_2_ = (ushort)(byte)param_3;
      _LpSrcStr = (LPCSTR)0x1;
    }
    else {
      local_8 = CONCAT31(CONCAT21(local_8._2_2_,(byte)param_3),(char)((uint)param_3 >> 8));
      uVar1 = local_8;
      local_8._3_1_ = (undefined1)((uint)param_1 >> 0x18);
      local_8._0_2_ = (ushort)uVar1;
      local_8._0_3_ = (uint3)(ushort)local_8;
      _LpSrcStr = (LPCSTR)0x2;
    }
    BVar2 = ___crtGetStringTypeA
                      ((_locale_t)0x1,(DWORD)&local_8,_LpSrcStr,(int)&param_3 + 2,
                       *(LPWORD *)(param_2 + 4),*(int *)(param_2 + 0x14),1);
    if (BVar2 == 0) {
      return 0;
    }
  }
  return param_3._2_2_ & param_4;
}

