/* DropCaseProjectile_ScalarDtor - 0x0046aee0 in the original binary.
 *
 * The DropCaseProjectile scalar-deleting destructor: runs DropCaseProjectile_DtorBody
 * on param_1 and frees it when the delete flag's low bit is set.
 * Class identity: see DropCaseProjectile_DtorBody's header.
 */
#include "ghidra_types.h"


void * __thiscall DropCaseProjectile_ScalarDtor(void *param_1,int param_2)

{
  DropCaseProjectile_DtorBody((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

