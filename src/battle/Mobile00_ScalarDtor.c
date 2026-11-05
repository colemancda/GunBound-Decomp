/* Mobile00_ScalarDtor - 0x0044e8f0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0044e8f0 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: 0x0044e8f0 is
 * slot 0 of the vtable at 0x555af8, the vtable that Mobile00_Destructor
 * (0x0044e910) installs, so it is that class's
 * deleting-destructor slot. Disasm 0x0044e8f0-0x0044e90d: call
 * 0x0044e910 (Mobile00_Destructor) / test flags,1 / free(this)
 * (0x525546), ret 4 - the standard MSVC scalar deleting destructor shape
 * with the real destructor body in the callee. Same convention as
 * Projectile_ScalarDtor and ItemCase_ScalarDtor. The wrapper's own N and
 * its callee's N were checked against each other, not just the vtable.
 */
#include "ghidra_types.h"


void * __thiscall Mobile00_ScalarDtor(void *param_1,int param_2)

{
  Mobile00_Destructor((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

