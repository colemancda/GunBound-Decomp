/* DestroyTextureCache - 0x004f42f0 in the original binary.
 *
 * NAMED (2026-07-16): the named-texture-cache destructor - flushes every
 * cached entry (FlushTextureCache), then COM-Release()s the parent D3D
 * interface at +0x110 (IUnknown vtable slot +8) and zeroes it. Invoked
 * at exit for the g_textureCache singleton via the atexit thunk
 * FUN_00543950, paired with the CRT static-init ctor InitTextureCache.
 * See FlushTextureCache.c's header for the family/identity evidence.
 */
#include "ghidra_types.h"


void DestroyTextureCache(int param_1)

{
  int *piVar1;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537748) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  local_4 = 0;
  /* Cache passed in EBX by the original (`mov ebx,[esp+0x14]` immediately
   * before the call, which esp-tracking through the SEH prologue resolves to
   * this function's own param_1) - see FlushTextureCache.c's header. */
  FlushTextureCache(param_1);
  local_4 = 0xffffffff;
  piVar1 = *(int **)(param_1 + 0x110);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
  }
  *(undefined4 *)(param_1 + 0x110) = 0;
  return;
}

