/* ReleaseStageResources - 0x004e4220 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (LIKELY). Its only caller is State11_InBattle_OnExit, which
 * calls it with the stage object (ctx+0x6a7708) in the middle of the
 * battle-exit teardown, right after the per-slot arrays are zeroed.
 * Callee-side: it frees and nulls stage +0x34 and +0x38, the two buffers
 * LoadStageLandFile allocates (the land mask and its twin; +0x34 is the
 * per-pixel terrain mask the Simulate bodies read at ctx+0x6a773c), plus
 * +0x3c and +0x44; then it runs the virtual deleting destructor
 * (slot 0, flag 1) over every node of layer 60000 and over each of the
 * 1000 layers from 60000 up, clears the two registries
 * (FUN_004f3060 on &DAT_00eb168c and on stage+0x85c, the registry
 * TickStage ticks) and flushes g_textureCache. So it is the unload
 * counterpart of the stage loader and the stage tick. The +0x3c and +0x44
 * buffers are not allocated anywhere visible in the loader, so their role
 * is not established. Release, not Destroy: the stage object itself is
 * embedded in the client context and survives.
 *
 * FIX (2026-11-03): the two layer-flush loops (0x4e4299-0x4e42ad for layer
 * 60000, 0x4e42fd-0x4e4311 for the 1000-layer sweep) called
 * `(*(code *)*vtbl)(1)`, dropping `this`.  The asm is `mov ecx,[esi+0x10]`
 * (first node), `mov edx,[ecx]` (its vtable), `mov edi,[ecx+0x10]` (next
 * node), `push 1`, `call [edx]` with ECX still the node; the port had
 * advanced past the node and kept only its vtable.  Now the node is kept
 * and passed as `this`.
 */
#include "ghidra_types.h"

/* Node destructor: `mov edx,[ecx] / push 1 / call [edx]` - ECX is the node,
 * the flag is pushed.  Targets are raw C ports (erased __thiscall = cdecl,
 * this first), as in State01_Title_OnExit. */
typedef void (*ListNodeVirtualFn)(void *thisPtr, undefined4 a1);


void ReleaseStageResources(int param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  
  iVar4 = param_1;
  if (*(void **)(param_1 + 0x34) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x34));
    *(undefined4 *)(param_1 + 0x34) = 0;
  }
  if (*(void **)(param_1 + 0x38) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x38));
    *(undefined4 *)(param_1 + 0x38) = 0;
  }
  if (*(void **)(param_1 + 0x3c) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x3c));
    *(undefined4 *)(param_1 + 0x3c) = 0;
  }
  if (*(void **)(param_1 + 0x44) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x44));
    *(undefined4 *)(param_1 + 0x44) = 0;
  }
  puVar6 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar5 = puVar6[1];
  while( true ) {
    if (60000 < uVar5) goto LAB_004e42b5;
    if (uVar5 == 60000) break;
    puVar6 = (undefined4 *)puVar6[7];
    uVar5 = puVar6[1];
  }
  puVar2 = (undefined4 *)puVar6[4];
  while (puVar2 != puVar6) {
    puVar3 = puVar2;
    puVar2 = (undefined4 *)puVar2[4];
    (*(ListNodeVirtualFn *)*puVar3)(puVar3, 1);
  }
  puVar6[3] = puVar6;
  puVar6[4] = puVar6;
LAB_004e42b5:
  FUN_004f3060(&DAT_00eb168c);
  /* Container passed in EBX by the original (`mov ebx,0xeb1bd8` immediately
   * before the call) - see src/rendering/FlushTextureCache.c's header. */
  FlushTextureCache((int)&g_textureCache);
  uVar5 = 60000;
  param_1 = 1000;
  while( true ) {
    puVar6 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar1 = puVar6[1];
    if (uVar1 <= uVar5) break;
LAB_004e4319:
    uVar5 = uVar5 + 1;
    param_1 = param_1 + -1;
    if (param_1 == 0) {
      FUN_004f3060(iVar4 + 0x85c);
      return;
    }
  }
LAB_004e42ef:
  if (uVar1 != uVar5) goto code_r0x004e42f1;
  puVar2 = (undefined4 *)puVar6[4];
  while (puVar2 != puVar6) {
    puVar3 = puVar2;
    puVar2 = (undefined4 *)puVar2[4];
    (*(ListNodeVirtualFn *)*puVar3)(puVar3, 1);
  }
  puVar6[3] = puVar6;
  puVar6[4] = puVar6;
  goto LAB_004e4319;
code_r0x004e42f1:
  puVar6 = (undefined4 *)puVar6[7];
  uVar1 = puVar6[1];
  if (uVar5 < uVar1) goto LAB_004e4319;
  goto LAB_004e42ef;
}

