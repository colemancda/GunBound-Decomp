/* FUN_004fcee0 - 0x004fcee0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25).  At 0x4fd802 the caller does `mov eax,ebx`
 * where EBX was loaded once at 0x4fd7d4, `mov ebx,[esp+0xc]` with two pushes
 * standing = E+4 = its param_2; the linear trace only reported `pop ebx`
 * because the call sits past a hoisted epilogue.  The second site passes the
 * same kind of value, its caller's param_4.
 */
#include "ghidra_types.h"


void FUN_004fcee0(char *regEax)

{
  char local_24 [16];
  undefined1 local_14;
  
  _strncpy(local_24,regEax,0x10);
  local_14 = 0;
  FUN_00502500(0x3000);
  return;
}

