/* CString_Destruct - 0x00405320 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): the paired element destructor of the eh-
 * vector in Panel_BaseConstructor and
 * ClientContext_Constructor/Destructor, whose element constructor is
 * CString_Construct (0x426410). Other callers (CStringPair_Destroy,
 * ClearMuteList, AtlArray_RemoveAt_CString, FUN_00543870) release CString
 * handles through it, ECX = the handle. It is ATL7 ~CSimpleStringT: lock-
 * decrement the header refcount at data-4 and, when it drops to zero or
 * below, Free through the string manager (header[0] vtable +4). Header =
 * data - 0x10.
 */
#include "ghidra_types.h"


void __fastcall CString_Destruct(int *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)(*param_1 + -0x10);
  piVar1 = (int *)(*param_1 + -4);
  LOCK();
  iVar2 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar2 == 1 || iVar2 + -1 < 0) {
    (**(code **)(*(int *)*puVar3 + 4))(puVar3);
  }
  return;
}

