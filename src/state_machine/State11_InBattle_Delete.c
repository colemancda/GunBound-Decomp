/* State11_InBattle_Delete - 0x004b4060 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * `this` RESTORED (2026-10-30): `mov esi,ecx` at 0x4b4061 then `call` the
 * destructor at 0x4b4063 with ECX untouched, so State11_InBattle_Destroy
 * (__fastcall, reads param_1 from ECX) receives this function's own
 * `this`.  The port called it with no arguments.  Same fix as
 * State07_AvatarStore_Delete.
 */
#include "ghidra_types.h"


void * __thiscall State11_InBattle_Delete(void *param_1,int param_2)

{
  State11_InBattle_Destroy((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

