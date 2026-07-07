/* FUN_0053192c - 0x0053192c in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    long __stdcall __CxxUnhandledExceptionFilter(struct _EXCEPTION_POINTERS *)
   
   Library: Visual Studio 2003 Release */

long __CxxUnhandledExceptionFilter(_EXCEPTION_POINTERS *param_1)

{
  PEXCEPTION_RECORD pEVar1;
  int iVar2;
  
  pEVar1 = param_1->ExceptionRecord;
  if (((pEVar1->ExceptionCode == 0xe06d7363) && (pEVar1->NumberParameters == 3)) &&
     ((pEVar1->ExceptionInformation[0] == 0x19930520 ||
      (pEVar1->ExceptionInformation[0] == 0x19930521)))) {
                    /* WARNING: Subroutine does not return */
    terminate();
  }
  if ((DAT_005b1b7c != (_func_int *)0x0) && (iVar2 = _ValidateExecute(DAT_005b1b7c), iVar2 != 0)) {
    iVar2 = (*DAT_005b1b7c)(param_1);
    return iVar2;
  }
  return 0;
}

