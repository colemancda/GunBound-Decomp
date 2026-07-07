/* FUN_004ff720 - 0x004ff720 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ff720(void)

{
  int iVar1;
  int *in_EAX;
  int *unaff_EDI;
  
  if (unaff_EDI == (int *)*in_EAX) {
    *in_EAX = *unaff_EDI;
  }
  else {
    *(int *)unaff_EDI[1] = *unaff_EDI;
  }
  if (unaff_EDI == (int *)in_EAX[1]) {
    in_EAX[1] = unaff_EDI[1];
  }
  else {
    *(int *)(*unaff_EDI + 4) = unaff_EDI[1];
  }
  FUN_00500f90();
  *unaff_EDI = in_EAX[4];
  iVar1 = in_EAX[2];
  in_EAX[4] = (int)unaff_EDI;
  in_EAX[2] = iVar1 + -1;
  if (iVar1 + -1 == 0) {
    FUN_004ff6d0();
  }
  return;
}

