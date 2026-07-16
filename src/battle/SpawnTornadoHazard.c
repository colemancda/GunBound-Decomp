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
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  int local_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053aed4;
  *unaff_FS_OFFSET = &local_c;
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\0') {
    iVar2 = (int)(param_3 + (param_3 >> 0x1f & 3U)) >> 2;
    for (iVar6 = (param_2 - iVar2) + -5; iVar6 <= iVar2 + 5 + param_2; iVar6 = iVar6 + 1) {
      iVar3 = FUN_00451030(iVar6);
      if (iVar3 != 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(param_4);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (param_3 < iVar6) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          param_3 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField((param_3 * 0xf) / 10);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = EncodeChecksumDeltaAdd(iVar3 + 0x38,local_230,param_2);
        local_4 = 0;
        EncodeChecksumDeltaDiv(uVar5,local_454,2);
        local_4 = 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(uVar5);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = 0;
        if (local_440 != 0) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_45c);
        }
        local_4 = 0xffffffff;
        if (local_21c != 0) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_45c);
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
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(iVar6 + 0x480) = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
LAB_00435aaa:
  *unaff_FS_OFFSET = local_c;
  return;
}

