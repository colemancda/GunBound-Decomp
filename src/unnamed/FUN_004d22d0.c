/* FUN_004d22d0 - 0x004d22d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004d22d0(int param_1)

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
      FUN_004e5590();
      _free(_Memory);
    }
    *(undefined4 *)(param_1 + 0x84e0) = 0;
  }
  if (*(int *)(param_1 + 700) != 0) {
    FUN_0040a240();
    FUN_0040b540(auStack_14);
  }
  local_4 = 0xffffffff;
  if (*(int *)(param_1 + 0x98) != 0) {
    FUN_0040a240();
    FUN_0040b540(auStack_14);
  }
  *unaff_FS_OFFSET = uStack_c;
  return;
}

