/* FUN_004f46b0 - 0x004f46b0 in the original binary.
 *
 * The free/reset method of a sprite/frame-cache container: frees the two
 * heap lists hanging off the container (+0x1b4 chained via +0x98, +0x114
 * chained via +0x114 with a virtual-destructor call per node), then zeroes
 * the list heads and an inline 15-entry table at +0x401bc plus its count
 * at +0x401b8.
 *
 * DROPPED-`this` FIX (2026-07-16): Ghidra emitted the container pointer as
 * an uninitialised `int unaff_EBX` - the object is really passed in EBX by
 * every caller (a custom register convention). Recovered from disassembly:
 * the prologue reads [ebx+0x1b4]/[ebx+0x114] without ever setting EBX, and
 * all five call sites load EBX immediately before the call - four with the
 * container singleton &DAT_00eb1bd8 (ShutdownDirectDraw, FUN_004e4220,
 * State07_AvatarStore_OnExit x2) and FUN_004f42f0 with its own container
 * argument. Promoted to an explicit `int param_1`. Left unfixed this read
 * garbage EBX and faulted at `mov [ebx+0x401bc],edx` under the stricter
 * (Lutris) wine. See globals_sized.c for the matching container sizing.
 */
#include "ghidra_types.h"


void FUN_004f46b0(int param_1)

{
  void *_Memory;
  void *pvVar1;
  int *piVar2;
  void *pvVar3;
  int iVar4;
  undefined4 *puVar5;

  _Memory = *(void **)(param_1 + 0x114);
  pvVar3 = *(void **)(param_1 + 0x1b4);
  while (pvVar3 != (void *)0x0) {
    pvVar1 = *(void **)((int)pvVar3 + 0x98);
    _free(pvVar3);
    pvVar3 = pvVar1;
  }
  while (_Memory != (void *)0x0) {
    piVar2 = *(int **)((int)_Memory + 0x110);
    pvVar3 = *(void **)((int)_Memory + 0x114);
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 8))(piVar2);
    }
    *(undefined4 *)((int)_Memory + 0x110) = 0;
    _free(_Memory);
    _Memory = pvVar3;
  }
  *(undefined4 *)(param_1 + 0x114) = 0;
  *(undefined4 *)(param_1 + 0x118) = 0;
  *(undefined4 *)(param_1 + 0x1b4) = 0;
  puVar5 = (undefined4 *)(param_1 + 0x401bc);
  for (iVar4 = 0xf; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  *(undefined4 *)(param_1 + 0x401b8) = 0;
  return;
}

