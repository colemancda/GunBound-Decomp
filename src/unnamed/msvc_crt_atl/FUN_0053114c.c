/* FUN_0053114c - 0x0053114c in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0053114c(void)

{
  _ptiddata p_Var1;
  
  p_Var1 = __getptd();
  if (0 < (int)p_Var1->_purecall) {
    p_Var1 = __getptd();
    p_Var1->_purecall = (void *)((int)p_Var1->_purecall + -1);
  }
  return;
}

