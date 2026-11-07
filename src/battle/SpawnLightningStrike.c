/* SpawnLightningStrike - 0x00436070 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Name. The candidate was SpawnProjectileLightningEffect, rejected: the
 * sibling SpawnProjectileLightningHazard (0x436150) builds a second object
 * in the same layer 0x1f7, and an Effect/Hazard contrast is not something
 * the tree or the binary establishes. This name says only what this spawn is.
 *
 * Evidence. It allocates 0x4a8 bytes, runs InitLightningStrike (which stamps layer
 * key 0x1f7 and vtable 0x556194), stores the x argument in the guard cell at
 * +0x38 and the y argument, clamped to g_nCameraBoundY, at +0x25c, then
 * RegisterActiveObject links it into the g_clientContext + 0x6a7f88 list.
 * RenderWeatherHazards maps layer 0x1f7 to the texture s_Lightning, and the
 * vtable slot 3 (0x482130) draws with FindTextureCacheEntryByName("Lightning")
 * as a column of 0x100-pixel quads running upward from the screen position of
 * (+0x38, +0x25c), with a per-segment offset array at +0x488, i.e. a bolt
 * anchored at that point. The callers supply that point: the ones read
 * (DetonateProjectile, DetonateShot1_Bullet9_16, FUN_004513b0 and
 * SpawnLightningBlastEffect, of 35 sites) first scan the terrain column at
 * the impact x downward from row 0 for the first solid pixel (10000 if
 * none) and pass the registry cell, the x, and that ground row.
 * SpawnLightningBlastEffect calls it immediately before ApplyBlastDamage
 * at the same point. LIKELY: the name rests on the texture and the draw
 * shape, not on a documented class name.
 */
#include "ghidra_types.h"


void SpawnLightningStrike(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  void *pvVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ca9b;
  *unaff_FS_OFFSET = &local_c;
  cVar1 = PeekPacketChecksumBool((byte *)(param_1 + 4));
  if (cVar1 == '\0') {
    pvVar2 = operator_new(0x4a8);
    local_4 = 0;
    if (pvVar2 != (void *)0x0) {
      InitLightningStrike(pvVar2);
    }
    local_4 = 0xffffffff;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x4360dd (`lea edi,[esi + 0x38]`, esi = the object just
     * constructed above via InitLightningStrike(pvVar2), not this function's
     * own (unused) param_1): cell is pvVar2+0x38, the same checksum-cell
     * offset InitLightningStrike.c/InitTornadoHazard.c zero-init/use for their own
     * `this`. `pvVar2` is `void *`, so byte offsets use
     * `(int)pvVar2 + N`. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)pvVar2 + 0x38, param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (*(int *)(&g_nCameraBoundY + g_clientContext) <= param_3) {
      param_3 = *(int *)(&g_nCameraBoundY + g_clientContext);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x436113 (`lea edi,[esi + 0x25c]`, esi = pvVar2, same object as
     * above): cell is pvVar2+0x25c, matching InitLightningStrike.c's second
     * cell offset. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)pvVar2 + 0x25c, param_3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    /* EDX = ctx+0x6a7f88 (the battle entity registry), EDI = the object just
       * built; the port had passed (0,0,NULL). */
RegisterActiveObject(0,(int)g_clientContext + 0x6a7f88,(undefined4 *)pvVar2);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

