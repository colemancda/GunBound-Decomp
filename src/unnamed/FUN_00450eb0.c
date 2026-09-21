/* FUN_00450eb0 - 0x00450eb0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-ARGUMENT FIX (2026-09-20): the FUN_0045db20(iVar3,param_2,
 * param_3,param_6,param_7) call was missing its own leading `this` stack
 * arg. Orig 0x450ee9-0x450f01: `mov edi,[esp+0x24]` / `mov ebx,[esp+0x2c]`
 * (this function's own param_6/param_7, pulled once before the loop),
 * `mov ecx,[esp+0x1c]` / `mov edx,[esp+0x18]` (this function's own
 * param_3/param_2), then `push ebx; push edi; push ecx; push edx; push
 * esi; mov ecx,ebp; call 0x45db20` - esi is the per-node iVar3 walked by
 * the loop and ebp is `[esp+0x14]` read once at entry = this function's
 * own param_4 (constant across every loop iteration, unlike iVar3). So
 * the callee's true param_1(this) is this function's own param_4; the
 * previously-passed 5 args already land in the correct positions once
 * that's prepended.
 *
 * DROPPED-ARGUMENT FIX (2026-09-20, this function's OWN callers): __thiscall
 * with 7 real params (ECX=`this` + ret 0x18 = 6 stack dwords, disasm
 * 0x450eb0-0x45101b). All 24 call sites tree-wide had no prototype in
 * functions.h and wrote only 6 args (missing `this` entirely, not a
 * trailing one) - confirmed independently at 3 sites: DetonateShot1_
 * Bullet9_16 (orig 0x46ee98 `mov ecx,[0x5b3484]; add ecx,0x6a7f88; call
 * 0x450eb0`, pushes edi/eax/ecx/1/0/0 matching the callers' existing
 * (piStack_ae0,1,0,0) tail plus 2 leading peek values unaffected),
 * ExplodeMine (orig 0x497e0a-0x497e1f, same `[0x5b3484]+0x6a7f88`
 * constant in ECX, pushes 0/0/0/ebx/edi/eax = the callers' existing
 * (param_1,1,0,0) tail plus uVar3/uVar4 in the leading 2 stack slots),
 * and DetonateShot2_Bullet11 (orig 0x474f66-0x474f73, same ECX constant,
 * pushes &uStack_ad4/1/1/edi/ecx/edx matching (piVar9,1,1,&uStack_ad4)
 * plus 2 leading values). At all 3 sites `this` is the SAME global
 * constant `g_clientContext + 0x6a7f88` - the active-object layer
 * registry already named `&DAT_006a7f88 + g_clientContext` elsewhere in
 * the tree (SpawnFirewallHazard.c, SimulateShot_Bullet7n_9s_7p_9p.c,
 * FindActiveObjectLayer.c) - and every existing argument keeps its
 * position, just shifted one slot right. Fix: prepend
 * `(int)(&DAT_006a7f88 + g_clientContext)` at all 24 sites, unchanged
 * otherwise.
 */
#include "ghidra_types.h"


void __thiscall
FUN_00450eb0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,char param_5,
            undefined4 param_6,undefined4 param_7)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = *(int *)(*(int *)(param_1 + 4) + 0x1c);
  uVar2 = *(uint *)(iVar3 + 4);
  while( true ) {
    if (0x186a1 < uVar2) goto LAB_00450f11;
    if (uVar2 == 0x186a1) break;
    iVar3 = *(int *)(iVar3 + 0x1c);
    uVar2 = *(uint *)(iVar3 + 4);
  }
  iVar3 = *(int *)(iVar3 + 0x10);
  cVar1 = *(char *)(iVar3 + 0x15);
  while (cVar1 == '\0') {
    FUN_0045db20(param_4,iVar3,param_2,param_3,param_6,param_7);
    iVar3 = *(int *)(iVar3 + 0x10);
    cVar1 = *(char *)(iVar3 + 0x15);
  }
LAB_00450f11:
  iVar3 = *(int *)(*(int *)(param_1 + 4) + 0x1c);
  uVar2 = *(uint *)(iVar3 + 4);
  if (uVar2 < 0x186a7) {
LAB_00450f26:
    if (uVar2 != 0x186a6) goto code_r0x00450f28;
    iVar3 = *(int *)(iVar3 + 0x10);
    cVar1 = *(char *)(iVar3 + 0x15);
    while (cVar1 == '\0') {
      if (*(char *)(iVar3 + 0x14) == '\0') {
        FUN_00478cb0(iVar3,param_2,param_3,param_4);
      }
      iVar3 = *(int *)(iVar3 + 0x10);
      cVar1 = *(char *)(iVar3 + 0x15);
    }
  }
LAB_00450f65:
  if (param_5 != '\0') {
    iVar3 = *(int *)(*(int *)(param_1 + 4) + 0x1c);
    uVar2 = *(uint *)(iVar3 + 4);
    while (uVar2 < 0x186a4) {
      if (uVar2 == 0x186a3) {
        iVar3 = *(int *)(iVar3 + 0x10);
        cVar1 = *(char *)(iVar3 + 0x15);
        while (cVar1 == '\0') {
          if (*(char *)(iVar3 + 0x14) == '\0') {
            FUN_00499650(iVar3,param_2,param_3,param_4);
          }
          iVar3 = *(int *)(iVar3 + 0x10);
          cVar1 = *(char *)(iVar3 + 0x15);
        }
        break;
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar2 = *(uint *)(iVar3 + 4);
    }
  }
  iVar3 = *(int *)(*(int *)(param_1 + 4) + 0x1c);
  uVar2 = *(uint *)(iVar3 + 4);
  if (uVar2 < 0x30d43) {
    while (uVar2 != 0x30d42) {
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar2 = *(uint *)(iVar3 + 4);
      if (0x30d42 < uVar2) {
        return;
      }
    }
    iVar3 = *(int *)(iVar3 + 0x10);
    cVar1 = *(char *)(iVar3 + 0x15);
    while (cVar1 == '\0') {
      FUN_00477650(iVar3,param_2,param_3,param_4);
      iVar3 = *(int *)(iVar3 + 0x10);
      cVar1 = *(char *)(iVar3 + 0x15);
    }
  }
  return;
code_r0x00450f28:
  iVar3 = *(int *)(iVar3 + 0x1c);
  uVar2 = *(uint *)(iVar3 + 4);
  if (0x186a6 < uVar2) goto LAB_00450f65;
  goto LAB_00450f26;
}

