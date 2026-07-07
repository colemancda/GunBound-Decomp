/* FUN_00526a6c - 0x00526a6c in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __expandtime
   
   Library: Visual Studio 2003 Release */

undefined4 __thiscall
__expandtime(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  char in_AL;
  int iVar1;
  int *unaff_EBX;
  undefined4 uVar2;
  
  if (in_AL < '[') {
    if (in_AL == 'Z') {
LAB_00526c5d:
      ___tzset();
LAB_00526cc2:
      __store_str();
      return 1;
    }
    if (in_AL < 'N') {
      if (in_AL != 'M') {
        if (in_AL == '%') {
          *(undefined1 *)*param_1 = 0x25;
          *param_1 = *param_1 + 1;
          *unaff_EBX = *unaff_EBX + -1;
          return 1;
        }
        if ((in_AL == 'A') || (in_AL == 'B')) goto LAB_00526cc2;
        if ((in_AL != 'H') && (in_AL != 'I')) {
          return 1;
        }
      }
LAB_00526b34:
      __store_num(param_5);
      return 1;
    }
    if (((in_AL == 'S') || (in_AL == 'U')) || (in_AL == 'W')) goto LAB_00526b34;
    if (in_AL != 'X') {
      if (in_AL != 'Y') {
        return 1;
      }
      goto LAB_00526b34;
    }
  }
  else {
    if ('m' < in_AL) {
      if (in_AL == 'p') goto LAB_00526cc2;
      if (in_AL == 'w') goto LAB_00526b34;
      if (in_AL == 'x') {
        if (param_5 == 0) {
          uVar2 = 0;
        }
        else {
          uVar2 = 1;
        }
        goto LAB_00526b49;
      }
      if (in_AL == 'y') goto LAB_00526b34;
      if (in_AL != 'z') {
        return 1;
      }
      goto LAB_00526c5d;
    }
    if (in_AL == 'm') goto LAB_00526b34;
    if ((in_AL == 'a') || (in_AL == 'b')) goto LAB_00526cc2;
    if (in_AL != 'c') {
      if ((in_AL != 'd') && (in_AL != 'j')) {
        return 1;
      }
      goto LAB_00526b34;
    }
    iVar1 = __store_winword(param_2,param_5 != 0,param_3,param_1);
    if (iVar1 == 0) {
      return 0;
    }
    if (*unaff_EBX == 0) {
      return 0;
    }
    *(undefined1 *)*param_1 = 0x20;
    *param_1 = *param_1 + 1;
    *unaff_EBX = *unaff_EBX + -1;
  }
  uVar2 = 2;
LAB_00526b49:
  iVar1 = __store_winword(param_2,uVar2,param_3,param_1);
  if (iVar1 != 0) {
    return 1;
  }
  return 0;
}

