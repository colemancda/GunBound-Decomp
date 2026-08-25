/* CString_Empty - 0x00405760 in the original binary.
 *
 * ATL CString Empty(): releases the string's data block.  regEsi is the
 * CString (its +0 is the buffer pointer); the CStringData header sits just
 * below the buffer -- refcount at -4, allocated length at -8, data length at
 * -0xc, manager at -0x10.  Decrements the refcount under LOCK, and when it
 * reaches zero hands the block back through the manager's vtable slot 1
 * (Free) and resets the string through slot 3.  A negative refcount marks a
 * locked buffer, in which case a negative allocated length throws
 * E_INVALIDARG.  Reached from AssignStringBuffer's length == 0 branch, which
 * is exactly where CString::Empty is called from in SetString.
 */
#include "ghidra_types.h"


void CString_Empty(int *regEsi)

{
  undefined4 *puVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = *regEsi;
  puVar1 = (undefined4 *)(iVar4 + -0x10);
  piVar3 = (int *)*puVar1;
  if (*(int *)(iVar4 + -0xc) != 0) {
    piVar2 = (int *)(iVar4 + -4);
    if (*(int *)(iVar4 + -4) < 0) {
      if (*(int *)(iVar4 + -8) < 0) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      *(undefined4 *)(iVar4 + -0xc) = 0;
      *(undefined1 *)*regEsi = 0;
      return;
    }
    LOCK();
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 == 1 || iVar4 + -1 < 0) {
      (**(code **)(*(int *)*puVar1 + 4))(puVar1);
    }
    (**(code **)(*piVar3 + 0xc))();
    *regEsi = iVar4 + 0x10;
  }
  return;
}

