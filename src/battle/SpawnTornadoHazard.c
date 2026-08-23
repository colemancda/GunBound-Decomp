/* SpawnTornadoHazard - 0x00435800 in the original binary.
 *
 * RENAMED (2026-07-16, from FUN_00435800): spawns a Tornado terrain
 * hazard. operator_new(0x6a8) + InitTornadoHazard (the ctor, which
 * stamps layer key 500) + position/strength fields + RegisterActiveObject
 * into the g_clientContext+0x6a7f88 active-object list. Called by
 * SpawnWeatherHazards for the tornado descriptor slot. Identity CONFIRMED:
 * RenderWeatherHazards maps layer 500 -> s_TornadoTexture. Raw/near-
 * verbatim Ghidra body, not hand-verified - see src/README.md.
 *
 * PARAM/FIELD MAP (decoded 2026-07-16 via angr; this is the reference
 * for the whole Spawn*Hazard/Init*Hazard family - Firewall/Lightning are
 * identical but every object-cell offset is +4 higher, because their
 * ctors call an extra InitGuardedBool):
 *   param_2 = a single 1D WORLD-X coordinate (horizontal ground pos, same
 *             space as the camera scroll g_clientContext+0x6a7710 and
 *             mobiles) - NOT packed x/y; Y is implicit (terrain height at
 *             that X). Stored into the guard cell at object +0x38 (line
 *             "EncodeOutgoingPacketField(param_2)" below; angr self=+0x38
 *             @0x435a35). The render method computes screenX =
 *             pos - cameraX + 400 (400 = half the 800px screen).
 *   param_3 = horizontal EXTENT/WIDTH, NOT damage. Stored at +0x25c
 *             (self=+0x25c @0x435a5c). Uses: strength/4 = the merge/
 *             coverage radius (the +-(strength/4 +5) search window here
 *             and in FUN_00451030); strength*2 = render draw span;
 *             (strength*15)/10 = accumulation when two tornadoes merge
 *             (the existing-object early path above).
 *   param_4 = 10000 at the only call site = LIFETIME/duration countdown
 *             in ticks. Stored at +0x484 (self=+0x484 @0x435a87). The
 *             per-tick vtable slot4 (0x4acc90) reads +0x484, dec's it,
 *             and when it goes negative sets the node dead-flag +0x14=1
 *             -> removed from the list. Not a sentinel/damage.
 *   (also) +0x480 = animation frame counter, zeroed at spawn
 *             ("*(iVar6 + 0x480) = 0" below), inc'd each tick by vtable
 *             slot2 (0x4ac750 = literally `inc [this+0x480]; ret`), read
 *             by the render method for the swirl.
 *   FUN_00451030(tileX) = "is an existing tornado (layer 0x1f4=500)
 *             already covering tileX?" merge/dedup lookup; nonzero ->
 *             update that tornado instead of spawning a duplicate.
 * The per-frame VISUAL is generated entirely in the hazard's own render
 * method = vtable slot 3 (+0xc) = 0x4ac760 (Tornado) - see InitTornado
 * Hazard.c. The ctor creates no sub-sprite list (node+0x10 = 0).
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 4 argless PeekPacketChecksumState() calls and all 5 1-arg
 * EncodeOutgoingPacketField() calls.  Two objects are involved and the
 * decompile names both: iVar3, the EXISTING hazard the merge loop found
 * (ESI/frame[0x10] in the original - confirmed because the C's own
 * `EncodeChecksumDeltaAdd(iVar3 + 0x38, ...)` compiles to `mov edi,
 * [esp+0x10]; add edi,0x38`), and iVar6, the freshly built one from
 * Init*Hazard.  Cells are this hazard type's documented layout: +0x38
 * world-X, +0x25c width/strength, +0x484 lifetime.  The one remaining peek
 * reads local_454, the scratch the EncodeChecksumDeltaDiv above returned
 * (these helpers return their arg2, see tools/sweep_guard_instructions.md).
 */
#include "ghidra_types.h"


void SpawnTornadoHazard(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_45c [8];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053aed4;
  *unaff_FS_OFFSET = &local_c;
  cVar1 = PeekPacketChecksumBool((byte *)(param_1 + 4));
  if (cVar1 == '\0') {
    iVar2 = (int)(param_3 + (param_3 >> 0x1f & 3U)) >> 2;
    for (iVar6 = (param_2 - iVar2) + -5; iVar6 <= iVar2 + 5 + param_2; iVar6 = iVar6 + 1) {
      iVar3 = FUN_00451030(iVar6,(int)(&DAT_006a7f88 + g_clientContext));
      if (iVar3 != 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EncodeOutgoingPacketField((void *)(iVar3 + 0x484), param_4);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar6 = PeekPacketChecksumState((void *)(iVar3 + 0x25c));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        if (param_3 < iVar6) {
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          param_3 = PeekPacketChecksumState((void *)(iVar3 + 0x25c));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EncodeOutgoingPacketField((void *)(iVar3 + 0x25c), (param_3 * 0xf) / 10);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        uVar5 = EncodeChecksumDeltaAdd(iVar3 + 0x38,local_230,param_2);
        local_4 = 0;
        EncodeChecksumDeltaDiv(uVar5,local_454,2);
        local_4 = 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        uVar5 = PeekPacketChecksumState((void *)(local_454));
        EncodeOutgoingPacketField((void *)(iVar3 + 0x38), uVar5);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        local_4 = 0;
        if ((*(int *)(local_454 + 0x14)) != 0) {
          ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&g_valueGuardKeyTable);
          TreeLowerBound(local_45c,&g_valueGuardMap);
        }
        local_4 = 0xffffffff;
        if ((*(int *)(local_230 + 0x14)) != 0) {
          ScrambleChecksumGuardBytes(*(int *)(local_230 + 0x14),&g_valueGuardKeyTable);
          TreeLowerBound(local_45c,&g_valueGuardMap);
        }
        goto LAB_00435aaa;
      }
    }
    pvVar4 = operator_new(0x6a8);
    local_4 = 2;
    if (pvVar4 == (void *)0x0) {
      iVar6 = 0;
    }
    else {
      iVar6 = InitTornadoHazard(pvVar4);
    }
    local_4 = 0xffffffff;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(iVar6 + 0x38), param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(iVar6 + 0x25c), param_3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    *(undefined4 *)(iVar6 + 0x480) = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(iVar6 + 0x484), param_4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
LAB_00435aaa:
  *unaff_FS_OFFSET = local_c;
  return;
}

