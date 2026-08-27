/* FUN_004fceb0 - 0x004fceb0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): in_EAX is the string this copies,
 * and at the sole call site (0x504aeb) it is `mov eax,edi` where edi is the
 * argument the vtable call on the line above was given -- `push edi;
 * call [edx+0x30]`, which DispatchP2PMessage.c already spells
 * `(**(code **)(**(int **)(param_3 + 0x1ab0) + 0x30))(param_4)`.  So edi is
 * param_4, the same pointer the neighbouring case arm hands to
 * FUN_004fcee0 as a `char *`.
 */
#include "ghidra_types.h"


void FUN_004fceb0(undefined4 param_1,char *regEax)

{
  char *in_EAX = regEax;
  char local_10 [16];
  
  _strncpy(local_10,in_EAX,0x10);
  FUN_00502500(param_1);
  return;
}

