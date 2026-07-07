/* FUN_00534ed2 - 0x00534ed2 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    ___add_12
   
   Library: Visual Studio 2003 Release */

void ___add_12(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = ___addl(*param_1,*param_2,param_1);
  if (iVar1 != 0) {
    iVar1 = ___addl(param_1[1],1,param_1 + 1);
    if (iVar1 != 0) {
      param_1[2] = param_1[2] + 1;
    }
  }
  iVar1 = ___addl(param_1[1],param_2[1],param_1 + 1);
  if (iVar1 != 0) {
    param_1[2] = param_1[2] + 1;
  }
  ___addl(param_1[2],param_2[2],param_1 + 2);
  return;
}

