/* FUN_005261af - 0x005261af in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __fread_lk
   
   Library: Visual Studio 2003 Release */

uint __fread_lk(undefined1 *param_1,uint param_2,uint param_3,FILE *param_4)

{
  uint uVar1;
  int iVar2;
  undefined1 *puVar3;
  uint uVar4;
  uint _Size;
  uint local_8;
  
  uVar4 = param_2 * param_3;
  if (uVar4 == 0) {
    param_3 = 0;
  }
  else {
    puVar3 = param_1;
    param_1 = (undefined1 *)uVar4;
    if ((param_4->_flag & 0x10c) == 0) {
      local_8 = 0x1000;
    }
    else {
      local_8 = param_4->_bufsiz;
    }
    do {
      if (((param_4->_flag & 0x10c) == 0) || (uVar1 = param_4->_cnt, uVar1 == 0)) {
        if (param_1 < local_8) {
          iVar2 = __filbuf(param_4);
          if (iVar2 == -1) goto LAB_00526286;
          *puVar3 = (char)iVar2;
          local_8 = param_4->_bufsiz;
          puVar3 = puVar3 + 1;
          param_1 = (undefined1 *)((int)param_1 - 1);
        }
        else {
          uVar1 = (uint)param_1;
          if (local_8 != 0) {
            uVar1 = (int)param_1 - (uint)param_1 % local_8;
          }
          iVar2 = __read(param_4->_file,puVar3,uVar1);
          if (iVar2 == 0) {
            param_4->_flag = param_4->_flag | 0x10;
LAB_00526286:
            return (uVar4 - (int)param_1) / param_2;
          }
          if (iVar2 == -1) {
            param_4->_flag = param_4->_flag | 0x20;
            goto LAB_00526286;
          }
          param_1 = (undefined1 *)((int)param_1 - iVar2);
          puVar3 = puVar3 + iVar2;
        }
      }
      else {
        _Size = (uint)param_1;
        if (uVar1 <= param_1) {
          _Size = uVar1;
        }
        _memcpy(puVar3,param_4->_ptr,_Size);
        param_1 = (undefined1 *)((int)param_1 - _Size);
        param_4->_cnt = param_4->_cnt - _Size;
        param_4->_ptr = param_4->_ptr + _Size;
        puVar3 = puVar3 + _Size;
      }
    } while (param_1 != (undefined1 *)0x0);
  }
  return param_3;
}

