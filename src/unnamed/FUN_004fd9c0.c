/* FUN_004fd9c0 - 0x004fd9c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined4 __thiscall
FUN_004fd9c0(int param_1,char *param_2,char *param_3,undefined2 param_4,undefined2 param_5)

{
  undefined4 uVar1;
  char local_1770 [12];
  char local_1764 [8];
  undefined2 local_175c;
  undefined2 local_175a;
  undefined4 uStack_4;
  
  uStack_4 = 0x4fd9ca;
  if (*(char *)(param_1 + 0x1a70) == '\0') {
    return 0x1700;
  }
  _strncpy(local_1770,param_2,0xc);
  _strncpy(local_1764,param_3,8);
  local_175c = param_4;
  local_175a = param_5;
  uVar1 = FUN_00502500(0x4000);
  return uVar1;
}

