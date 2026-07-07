/* FUN_00531320 - 0x00531320 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00531320(void)

{
  _ptiddata p_Var1;
  int iVar2;
  int unaff_EBP;
  int *unaff_ESI;
  int unaff_EDI;
  
  *(undefined4 *)(unaff_EDI + -4) = *(undefined4 *)(unaff_EBP + -0x38);
  _FindAndUnlinkFrame(*(FrameInfo **)(unaff_EBP + -0x3c));
  p_Var1 = __getptd();
  p_Var1->_unexpected = *(void **)(unaff_EBP + -0x40);
  p_Var1 = __getptd();
  p_Var1->_translator = *(void **)(unaff_EBP + -0x44);
  if ((((*unaff_ESI == -0x1f928c9d) && (unaff_ESI[4] == 3)) &&
      ((unaff_ESI[5] == 0x19930520 || (unaff_ESI[5] == 0x19930521)))) &&
     ((*(int *)(unaff_EBP + -0x48) == 0 && (*(int *)(unaff_EBP + -0x20) != 0)))) {
    iVar2 = IsExceptionObjectToBeDestroyed((void *)unaff_ESI[6]);
    if (iVar2 != 0) {
      __abnormal_termination();
      ___DestructExceptionObject();
    }
  }
  return;
}

