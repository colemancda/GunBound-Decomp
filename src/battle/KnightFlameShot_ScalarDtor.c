/* KnightFlameShot_ScalarDtor - 0x0047aad0 in the original binary.
 *
 * The KnightFlameShot scalar-deleting destructor: runs KnightFlameShot_DtorBody
 * on param_1 and frees it when the delete flag's low bit is set.
 * Class identity: see KnightFlameShot_DtorBody's header.
 */
#include "ghidra_types.h"


void * __thiscall KnightFlameShot_ScalarDtor(void *param_1,int param_2)

{
  KnightFlameShot_DtorBody((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

