/* FUN_005286f3 - 0x005286f3 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    void __cdecl _FindAndUnlinkFrame(struct FrameInfo *)
   
   Library: Visual Studio 2003 Release */

void __cdecl _FindAndUnlinkFrame(FrameInfo *param_1)

{
  FrameInfo *pFVar1;
  _ptiddata p_Var2;
  FrameInfo *pFVar3;
  
  p_Var2 = __getptd();
  if (param_1 == p_Var2->_curexception) {
    p_Var2 = __getptd();
    p_Var2->_curexception = *(void **)(param_1 + 4);
    return;
  }
  p_Var2 = __getptd();
  pFVar1 = p_Var2->_curexception;
  do {
    pFVar3 = pFVar1;
    if (*(int *)(pFVar3 + 4) == 0) {
      _inconsistency();
      return;
    }
    pFVar1 = *(FrameInfo **)(pFVar3 + 4);
  } while (param_1 != *(FrameInfo **)(pFVar3 + 4));
  *(undefined4 *)(pFVar3 + 4) = *(undefined4 *)(param_1 + 4);
  return;
}

