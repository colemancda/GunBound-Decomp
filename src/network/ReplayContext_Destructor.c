/* ReplayContext_Destructor - 0x004e6050 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-26), CERTAIN. src/unnamed/msvc_crt_atl/FUN_005432a0.c
 * (the CRT's atexit-table dispatch thunk, left as-is per this sweep's
 * scope) is a bare `void FUN_005432a0(void) { FUN_004e6050(&g_replayContext);
 * return; }` - an argument-free call that names the global directly,
 * matching the stock MSVC static-object-destructor idiom exactly (compare
 * ValueGuardMap_Destructor's identical atexit-only shape). The body itself
 * is the textbook C++ base-destructor pattern: it installs the
 * "being-destroyed" vtable (`*param_1 = &PTR_FUN_005572f0`), tears down the
 * object's OS handles/critical sections, frees the two 0x206-byte-stride
 * CArray buffers this sweep's siblings (PopDirectBattleAction at +0x454a4/
 * +0x454a8, PopBroadcastBattleAction at +0x454b4/+0x454b8) walk, and
 * finally swaps in the terminal "destroyed" vtable (`&PTR_LAB_0055755c`)
 * before restoring the SEH frame - this is g_replayContext's own
 * destructor, not a generic cleanup helper.
 */
#include "ghidra_types.h"


void ReplayContext_Destructor(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_10 [4];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;

  puStack_8 = &LAB_00537b24;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_FUN_005572f0;
  local_4 = 2;
  SetEvent((HANDLE)param_1[2]);
  Sleep(0x32);
  CloseHandle((HANDLE)param_1[2]);
  CloseHandle((HANDLE)param_1[3]);
  CloseHandle((HANDLE)param_1[4]);
  if ((void *)param_1[0x1152d] != (void *)0x0) {
    _free((void *)param_1[0x1152d]);
  }
  if ((void *)param_1[0x11529] != (void *)0x0) {
    _free((void *)param_1[0x11529]);
  }
  param_1[0x11498] = &PTR_FUN_005572dc;
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x11499));
  FUN_004e8db0(local_10,*(undefined4 *)param_1[0x1148d],(undefined4 *)param_1[0x1148d],(int)(param_1 + 0x1148c));
  _free((void *)param_1[0x1148d]);
  param_1[0x1148d] = 0;
  param_1[0x1148e] = 0;
  param_1[0x65] = &PTR_FUN_005572dc;
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x66));
  param_1[0x5e] = &PTR_FUN_005572dc;
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x5f));
  *param_1 = &PTR_LAB_0055755c;
  *unaff_FS_OFFSET = local_c;
  return;
}
