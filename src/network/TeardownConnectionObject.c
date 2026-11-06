/* TeardownConnectionObject - 0x004d22d0 in the original binary.
 *
 * NAMED (batch 36), LIKELY. The destructor of the outer 0x84f0-byte
 * connection object that InitConnectionObject (0x4d2170) constructs - the
 * counterpart of Init, not of DestroyConnectionObject (0x4e5590), which only
 * destroys the inner 0x24a70-byte session sub-object at +0x84e0 and is
 * called from here. WinMain builds three of the outer objects
 * (operator_new(0x84f0) -> InitConnectionObject) into DAT_005b2b58,
 * DAT_005b2b5c and DAT_005b2b60; Shutdown calls this once on each, with the
 * object as the stack argument, and _free()s the same pointer straight
 * afterwards (Shutdown.c, call sites 0x40ff99, 0x40ffc0, 0x40ffe1), so the
 * block is dead when this returns.
 *
 * What it does to the outer object: frees the buffer at +0x84e8, closes the
 * socket and clears the connected flags (the CloseServerConnection
 * sequence, inlined), clears the worker run flag, SetEvents the worker,
 * runs DestroyConnectionObject on the sub-object and frees it, then
 * scrambles the two value-guard cells at +0x98 and +0x2bc into
 * g_valueGuardMap. The port still carries Ghidra's SEH frame artifact
 * (unaff_FS_OFFSET).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void TeardownConnectionObject(int param_1)

{
  int iVar1;
  void *_Memory;
  undefined4 *unaff_FS_OFFSET;
  undefined1 auStack_14 [8];
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_00537cae;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_4 = 0;
  _free(*(void **)(param_1 + 0x84e8));
  iVar1 = *(int *)(param_1 + 0x84e0);
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 0x22c) = 1;
    if (*(SOCKET *)(iVar1 + 0x24) != 0xffffffff) {
      closesocket(*(SOCKET *)(iVar1 + 0x24));
    }
    *(undefined4 *)(iVar1 + 0x24) = 0xffffffff;
    *(undefined1 *)(iVar1 + 0x22a) = 0;
    *(undefined1 *)(param_1 + 0x84e5) = 0;
  }
  iVar1 = *(int *)(param_1 + 0x84e0);
  if (iVar1 != 0) {
    *(undefined1 *)(iVar1 + 0x18) = 0;
    SetEvent(*(HANDLE *)(iVar1 + 8));
    _Memory = *(void **)(param_1 + 0x84e0);
    if (_Memory != (void *)0x0) {
      /* orig 0x4d2351: ESI = *(param_1+0x84e0) (=_Memory here). */
      DestroyConnectionObject((undefined4 *)_Memory);
      _free(_Memory);
    }
    *(undefined4 *)(param_1 + 0x84e0) = 0;
  }
  if (*(int *)(param_1 + 700) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(param_1 + 700),&g_valueGuardKeyTable);
    TreeInsert(auStack_14,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  if (*(int *)(param_1 + 0x98) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(param_1 + 0x98),&g_valueGuardKeyTable);
    TreeInsert(auStack_14,&g_valueGuardMap);
  }
  *unaff_FS_OFFSET = uStack_c;
  return;
}

