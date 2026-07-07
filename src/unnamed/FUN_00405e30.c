/* FUN_00405e30 - 0x00405e30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00405e30(int *param_1)

{
  int in_EAX;
  char *local_18 [4];
  char *local_8;
  char *local_4;
  
  local_18[0] = s_ready_00551e80;
  local_18[1] = &DAT_00551e78;
  local_18[2] = s_mouse_00551e70;
  local_18[3] = s_disable_00551e68;
  local_8 = s_select_00551e60;
  local_4 = s_active_00551e58;
  if ((in_EAX == 0) && ((char)param_1[0x13] == '\x01')) {
    (**(code **)(*param_1 + 4))(s_active_00551e58);
    return;
  }
  (**(code **)(*param_1 + 4))(local_18[in_EAX]);
  return;
}

