/* BlastEffect_ScalarDtor - 0x004aa8c0 in the original binary.
 *
 * The BlastEffect scalar-deleting destructor: runs BlastEffect_DtorBody
 * on param_1 and frees it when the delete flag's low bit is set.
 * Class identity: see BlastEffect_DtorBody's header.
 */
#include "ghidra_types.h"


void * __thiscall BlastEffect_ScalarDtor(void *param_1,int param_2)

{
  BlastEffect_DtorBody((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

