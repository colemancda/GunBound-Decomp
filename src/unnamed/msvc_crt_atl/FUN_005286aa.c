/* FUN_005286aa - 0x005286aa in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    struct FrameInfo * __cdecl _CreateFrameInfo(struct FrameInfo *,void *)
   
   Library: Visual Studio 2003 Release */

FrameInfo * __cdecl _CreateFrameInfo(FrameInfo *param_1,void *param_2)

{
  _ptiddata p_Var1;
  
  *(void **)param_1 = param_2;
  p_Var1 = __getptd();
  *(void **)(param_1 + 4) = p_Var1->_curexception;
  p_Var1 = __getptd();
  p_Var1->_curexception = param_1;
  return param_1;
}

