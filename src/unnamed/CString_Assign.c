/* CString_Assign - 0x0043ddb0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0043ddb0 mean this function.)
 *
 * NAMED (2026-11-05), CERTAIN. Library identity, ATL7
 * CSimpleStringT::operator=(const CSimpleStringT& strSrc), checked against
 * atlsimpstr.h member for member: if the two CStringData headers (buffer -
 * 0x10) differ, and the destination is not locked (refcount at +0xc is non-
 * negative) and both headers carry the same string manager (first dword),
 * it takes CString_CloneData(src) (the CStringData::Clone / AddRef share),
 * releases the old header with an interlocked decrement and a manager Free
 * through vtable slot 1 when the count reaches zero, and attaches the
 * clone; in every other case it falls back to AssignStringBuffer, the
 * SetString(src, length) path. Operand shapes come from outside: both
 * GetLocalizedString (found entry's string at node + 4 into the local
 * result) and FindSoundFileName pass a CString object address in EAX
 * (source) and in EDI (destination), the latter a local constructed to the
 * nil buffer just before. The neighbour CString_CloneData states the same
 * Clone and manager contract.
 *
 * (FUN_004e3740 below is now FindSoundFileName.)
 *
 * BOTH REGISTERS RECOVERED (2026-08-25).  ATL CSimpleStringT::operator=:
 * regEdi is `this`, regEax the source string; both CStringData headers sit
 * at buffer-0x10 (+0xc refcount/lock).  Sites: GetLocalizedString assigns
 * the found node's string (iVar4 + 4) into local_10; FUN_004e3740 the same
 * shape into local_18.
 */
#include "ghidra_types.h"


void CString_Assign(int *regEax,int *regEdi)

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
      iVar4 = CString_CloneData(piVar1);
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

