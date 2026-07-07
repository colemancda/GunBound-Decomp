/* FUN_0043ddb0 - 0x0043ddb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043ddb0(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *in_EAX;
  int iVar4;
  int *piVar5;
  int *unaff_EDI;
  
  iVar3 = *unaff_EDI;
  piVar1 = (int *)(*in_EAX + -0x10);
  piVar5 = (int *)(iVar3 + -0x10);
  if (piVar1 != piVar5) {
    piVar2 = (int *)(iVar3 + -4);
    if ((-1 < *(int *)(iVar3 + -4)) && (*piVar1 == *piVar5)) {
      iVar4 = FUN_0043de10();
      LOCK();
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1 || iVar3 + -1 < 0) {
        (**(code **)(*(int *)*piVar5 + 4))(piVar5);
      }
      *unaff_EDI = iVar4 + 0x10;
      return;
    }
    FUN_004056c0(unaff_EDI,*in_EAX);
  }
  return;
}

