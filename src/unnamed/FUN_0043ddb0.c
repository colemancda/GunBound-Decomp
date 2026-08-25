/* FUN_0043ddb0 - 0x0043ddb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * BOTH REGISTERS RECOVERED (2026-08-25).  ATL CSimpleStringT::operator=:
 * regEdi is `this`, regEax the source string; both CStringData headers sit
 * at buffer-0x10 (+0xc refcount/lock).  Sites: GetLocalizedString assigns
 * the found node's string (iVar4 + 4) into local_10; FUN_004e3740 the same
 * shape into local_18.
 */
#include "ghidra_types.h"


void FUN_0043ddb0(int *regEax,int *regEdi)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  iVar3 = *regEdi;
  piVar1 = (int *)(*regEax + -0x10);
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
      *regEdi = iVar4 + 0x10;
      return;
    }
    AssignStringBuffer(regEdi,*regEax);
  }
  return;
}

