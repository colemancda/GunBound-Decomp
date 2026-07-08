/* FUN_004e5e00 - 0x004e5e00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_004e5e00(undefined4 *param_1)

{
  int iVar1;
  HANDLE pvVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  uStack_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_00537b24;
  *unaff_FS_OFFSET = &uStack_c;
  param_1[1] = 0;
  local_4 = 0;
  *param_1 = &PTR_FUN_005572f0;
  param_1[0x4e] = 0;
  param_1[0x4f] = 0;
  param_1[0x50] = 0;
  param_1[0x51] = 0;
  param_1[0x52] = 0;
  param_1[0x5e] = &PTR_FUN_005572dc;
  InitializeCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x5f));
  param_1[0x65] = &PTR_FUN_005572dc;
  InitializeCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x66));
  local_4 = 2;
  *(undefined1 *)(param_1 + 0x11480) = 0;
  iVar1 = FUN_004e8e70();
  param_1[0x1148d] = iVar1;
  *(undefined1 *)(iVar1 + 0xf) = 1;
  *(undefined4 *)(param_1[0x1148d] + 4) = param_1[0x1148d];
  *(undefined4 *)param_1[0x1148d] = param_1[0x1148d];
  *(undefined4 *)(param_1[0x1148d] + 8) = param_1[0x1148d];
  param_1[0x1148e] = 0;
  param_1[0x11498] = &PTR_FUN_005572dc;
  InitializeCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x11499));
  param_1[0x11529] = 0;
  param_1[0x1152a] = 0;
  param_1[0x1152b] = 0;
  param_1[0x1152c] = 0;
  param_1[0x1152d] = 0;
  param_1[0x1152e] = 0;
  param_1[0x1152f] = 0;
  param_1[0x11530] = 0;
  pvVar2 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
  param_1[2] = pvVar2;
  uVar3 = WSACreateEvent();
  param_1[3] = uVar3;
  pvVar2 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
  param_1[4] = pvVar2;
  param_1[5] = 0xffffffff;
  param_1[0x11482] = 0xffffffff;
  param_1[0x102f4] = 0;
  param_1[0x102f5] = 0;
  *(undefined1 *)(param_1 + 0x11481) = 0xce;
  *(undefined1 *)(param_1 + 0x57) = 0;
  puVar4 = param_1 + 0x10af6;
  for (iVar1 = 0x80; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = param_1 + 0x102f6;
  for (iVar1 = 0x400; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = param_1 + 0x106f6;
  for (iVar1 = 0x400; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = param_1 + 0xf4;
  for (iVar1 = 0x10000; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = param_1 + 0x100f4;
  for (iVar1 = 0x200; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = param_1 + 0x10b78;
  for (iVar1 = 0x400; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = param_1 + 0x10f78;
  for (iVar1 = 0x400; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  param_1[0xf0] = 0;
  param_1[0xf1] = 0;
  param_1[0xf2] = 0;
  param_1[0xf3] = 0;
  param_1[0x51] = 0;
  *(undefined1 *)(param_1 + 0x10b76) = 0;
  InterlockedExchange(param_1 + 0x11378,0);
  *(undefined1 *)(param_1 + 0x1148a) = 0;
  param_1[0x1137a] = 0;
  param_1[0x114a0] = 0;
  *(undefined1 *)(param_1 + 0x1153e) = 0;
  param_1[0x1148f] = 500;
  param_1[0x11539] = 0;
  param_1[0x1153a] = 0;
  param_1[0x1153b] = 0;
  param_1[0x1153c] = 0;
  param_1[0x1153d] = 0;
  param_1[0x52] = 0;
  *unaff_FS_OFFSET = uStack_c;
  return param_1;
}

