/* State11_InBattle_Delete - 0x004b4060 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void * __thiscall State11_InBattle_Delete(void *param_1,int param_2)

{
  State11_InBattle_Destroy();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

