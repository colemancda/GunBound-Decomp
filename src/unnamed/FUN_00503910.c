/* FUN_00503910 - 0x00503910 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_00503910(undefined4 *param_1)

{
  undefined4 *puVar1;
  int in_EAX;
  
  puVar1 = *(undefined4 **)(in_EAX + 4);
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return 0xffffffff;
    }
    if (param_1 == puVar1) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  return param_1[2];
}

