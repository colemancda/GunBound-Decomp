/* FUN_004ff130 - 0x004ff130 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


char * FUN_004ff130(char *param_1,uint *param_2,undefined4 *param_3)

{
  char *pcVar1;
  char *_Str1;
  int *in_EAX;
  uint uVar2;
  int iVar3;
  uint *unaff_EBX;
  
  uVar2 = FUN_004ff310();
  *param_2 = uVar2;
  *unaff_EBX = uVar2 % (uint)in_EAX[2];
  if (*in_EAX != 0) {
    *param_3 = 0;
    pcVar1 = (char *)0x0;
    for (_Str1 = *(char **)(*in_EAX + *unaff_EBX * 4); _Str1 != (char *)0x0;
        _Str1 = *(char **)(_Str1 + 0x14)) {
      if ((*(uint *)(_Str1 + 0x18) == *param_2) && (iVar3 = __stricmp(_Str1,param_1), iVar3 == 0)) {
        *param_3 = pcVar1;
        return _Str1;
      }
      pcVar1 = _Str1;
    }
  }
  return (char *)0x0;
}

