/* FUN_00520210 - 0x00520210 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


LONG ImmGetCompositionStringA(HIMC param_1,DWORD param_2,LPVOID lpBuf,DWORD dwBufLen)

{
  LONG LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00520210. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = ImmGetCompositionStringA(param_1,param_2,lpBuf,dwBufLen);
  return LVar1;
}

