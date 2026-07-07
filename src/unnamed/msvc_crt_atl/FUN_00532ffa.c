/* FUN_00532ffa - 0x00532ffa in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __getenv_lk
   
   Library: Visual Studio 2003 Release */

int __getenv_lk(uchar *param_1)

{
  int iVar1;
  size_t _MaxCount;
  size_t sVar2;
  int *piVar3;
  
  if (DAT_00f29680 == 0) {
    return 0;
  }
  if (((DAT_005b18e8 != (int *)0x0) ||
      (((DAT_005b18f0 != 0 && (iVar1 = ___wtomb_environ(), iVar1 == 0)) &&
       (DAT_005b18e8 != (int *)0x0)))) && (piVar3 = DAT_005b18e8, param_1 != (uchar *)0x0)) {
    _MaxCount = _strlen((char *)param_1);
    for (; (char *)*piVar3 != (char *)0x0; piVar3 = piVar3 + 1) {
      sVar2 = _strlen((char *)*piVar3);
      if (((_MaxCount < sVar2) && (((uchar *)*piVar3)[_MaxCount] == '=')) &&
         (iVar1 = __mbsnbicoll((uchar *)*piVar3,param_1,_MaxCount), iVar1 == 0)) {
        return *piVar3 + 1 + _MaxCount;
      }
    }
  }
  return 0;
}

