/* Mobile01_ScalarDtor - 0x00488a90 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00488a90 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: 0x00488a90 is
 * slot 0 of the vtable at 0x556230, the vtable that Mobile01_Destructor
 * (0x00488ab0) installs, so it is that class's
 * deleting-destructor slot. Disasm 0x00488a90-0x00488aad: call
 * 0x00488ab0 (Mobile01_Destructor) / test flags,1 / free(this)
 * (0x525546), ret 4 - the standard MSVC scalar deleting destructor shape
 * with the real destructor body in the callee. Same convention as
 * Projectile_ScalarDtor and ItemCase_ScalarDtor. The wrapper's own N and
 * its callee's N were checked against each other, not just the vtable.
 */
#include "ghidra_types.h"


void * __thiscall Mobile01_ScalarDtor(void *param_1,int param_2)

{
  Mobile01_Destructor((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

