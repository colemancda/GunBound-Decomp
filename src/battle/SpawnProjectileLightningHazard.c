/* SpawnProjectileLightningHazard - 0x00436150 in the original binary.
 *
 * RENAMED (2026-07-16, from FUN_00436150): spawns the projectile
 * Lightning hazard (layer 0x1f7). operator_new(0x4ac) +
 * InitProjectileLightningHazard + RegisterActiveObject into the
 * g_clientContext+0x6a7f88 active-object list (the same list
 * RenderWeatherHazards walks). Called from a projectile/detonation path
 * (FUN_004a8360), distinct from the turn-descriptor SpawnWeatherHazards
 * path that spawns the layer-0x1f6 SpawnLightningHazard. Identity
 * CONFIRMED transitively via its InitProjectileLightningHazard callee's
 * layer 0x1f7 -> s_Lightning mapping in RenderWeatherHazards. Raw/near-
 * verbatim Ghidra body - see src/README.md.
 */
#include "ghidra_types.h"


void SpawnProjectileLightningHazard(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  void *pvVar2;
  int iVar3;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053ca9b) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\0') {
    pvVar2 = operator_new(0x4ac);
    iVar3 = 0;
    local_4 = 0;
    if (pvVar2 != (void *)0x0) {
      iVar3 = InitProjectileLightningHazard(pvVar2);
    }
    local_4 = 0xffffffff;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x4361bd (`lea edi,[esi + 0x38]`, esi = the object just
     * constructed above via InitProjectileLightningHazard(pvVar2), returned/kept in
     * `iVar3`, not this function's own (unused) param_1): cell is
     * iVar3+0x38, the same checksum-cell offset InitProjectileLightningHazard.c zero-
     * inits for its own `this`. `iVar3` is plain `int`, so byte offsets
     * add directly. Confirmed by the later `*(undefined1 *)(iVar3 +
     * 0x4a8)` use of the same `iVar3` as this object's base. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(iVar3 + 0x38, param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x4361e1 (`lea edi,[esi + 0x25c]`, esi = iVar3, same object as
     * above): cell is iVar3+0x25c, matching InitProjectileLightningHazard.c's second
     * cell offset. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(iVar3 + 0x25c, param_3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined1 *)(iVar3 + 0x4a8) = param_4;
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  return;
}

