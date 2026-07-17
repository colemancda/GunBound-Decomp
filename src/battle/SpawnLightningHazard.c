/* SpawnLightningHazard - 0x00435da0 in the original binary.
 *
 * RENAMED (2026-07-16, from FUN_00435da0): spawns a Lightning terrain
 * hazard. operator_new(0x6a8) + InitLightningHazard (the ctor, which
 * stamps layer key 0x1f6) + fields + RegisterActiveObject into the
 * g_clientContext+0x6a7f88 active-object list. Called by
 * SpawnWeatherHazards for the lightning descriptor slot. Identity
 * CONFIRMED: RenderWeatherHazards maps layer 0x1f6 -> s_LightningTexture.
 * (A second lightning layer 0x1f7 -> s_Lightning is spawned by a
 * separate path, InitProjectileLightningHazard/SpawnProjectileLightningHazard, left FUN_* pending its own
 * determination.) Raw/near-verbatim Ghidra body - see src/README.md.
 *
 * PARAM/FIELD MAP: same as SpawnTornadoHazard.c (see its header for the
 * full decode) - param_2 = world-X position, param_3 = width (not
 * damage), param_4 = 10000 = lifetime countdown in ticks. Object cell
 * offsets are +4 vs the Tornado (extra InitGuardedBool field): position
 * +0x3c, width +0x260, lifetime +0x488, frame counter +0x484. Render =
 * InitLightningHazard's vtable slot 3 (0x46e020), animation stride
 * frame*0x6c.
 */
#include "ghidra_types.h"


void SpawnLightningHazard(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

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
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\0') {
    iVar2 = (int)(param_3 + (param_3 >> 0x1f & 3U)) >> 2;
    for (iVar6 = (param_2 - iVar2) + -5; iVar6 <= iVar2 + 5 + param_2; iVar6 = iVar6 + 1) {
      iVar3 = FUN_004511b0(iVar6);
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
        uVar5 = EncodeChecksumDeltaAdd(iVar3 + 0x3c,local_230,param_2);
        local_4 = 0;
        EncodeChecksumDeltaDiv(uVar5,local_454,2);
        local_4 = 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(uVar5);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = 0;
        if ((*(int *)(local_454 + 0x14)) != 0) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_45c);
        }
        local_4 = 0xffffffff;
        if ((*(int *)(local_230 + 0x14)) != 0) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_45c);
        }
        goto LAB_0043604a;
      }
    }
    pvVar4 = operator_new(0x6ac);
    local_4 = 2;
    if (pvVar4 == (void *)0x0) {
      iVar6 = 0;
    }
    else {
      iVar6 = InitLightningHazard(pvVar4);
    }
    local_4 = 0xffffffff;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(iVar6 + 0x484) = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
LAB_0043604a:
  *unaff_FS_OFFSET = local_c;
  return;
}

