/* FUN_00503930 - 0x00503930 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_00503930(undefined4 *param_1,char *param_2,char *param_3)

{
  undefined4 *puVar1;
  int in_EAX;
  int iVar2;
  int local_14;
  sockaddr local_10;
  
  puVar1 = *(undefined4 **)(in_EAX + 4);
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    if (param_1 == puVar1) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  if (param_1[2] == 0xffffffff) {
    return 0;
  }
  local_14 = 0x10;
  iVar2 = getsockname(param_1[2],&local_10,&local_14);
  if (iVar2 == -1) {
    return 0;
  }
  *(undefined4 *)param_2 = SUBFIELD(local_10.sa_data,2,undefined4);
  *(undefined2 *)param_3 = SUBFIELD(local_10.sa_data,0,undefined2);
  return 1;
}

