/* ItemCase_ScalarDtor - 0x00476f50 in the original binary.
 *
 * The ItemCase scalar-deleting destructor: runs ItemCase_DtorBody
 * on param_1 and frees it when the delete flag's low bit is set.
 * Class identity: see ItemCase_DtorBody's header.
 */
#include "ghidra_types.h"


void * __thiscall ItemCase_ScalarDtor(void *param_1,int param_2)

{
  ItemCase_DtorBody((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

