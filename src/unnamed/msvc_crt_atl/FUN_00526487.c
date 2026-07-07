/* FUN_00526487 - 0x00526487 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __fseek_lk
   
   Library: Visual Studio 2003 Release */

int __fseek_lk(FILE *param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  undefined4 *puVar4;
  
  if (((param_1->_flag & 0x83U) == 0) || (((param_3 != 0 && (param_3 != 1)) && (param_3 != 2)))) {
    puVar4 = (undefined4 *)FUN_0052b6d4();
    *puVar4 = 0x16;
    iVar2 = -1;
  }
  else {
    param_1->_flag = param_1->_flag & 0xffffffef;
    if (param_3 == 1) {
      iVar2 = __ftell_lk(param_1);
      param_2 = param_2 + iVar2;
      param_3 = 0;
    }
    __flush(param_1);
    uVar1 = param_1->_flag;
    if ((char)uVar1 < '\0') {
      param_1->_flag = uVar1 & 0xfffffffc;
    }
    else if ((((uVar1 & 1) != 0) && ((uVar1 & 8) != 0)) && ((uVar1 & 0x400) == 0)) {
      param_1->_bufsiz = 0x200;
    }
    lVar3 = __lseek(param_1->_file,param_2,param_3);
    iVar2 = (lVar3 != -1) - 1;
  }
  return iVar2;
}

