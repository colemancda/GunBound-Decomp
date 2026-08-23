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
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 4 argless PeekPacketChecksumState() calls and all 5 1-arg
 * EncodeOutgoingPacketField() calls.  Two objects are involved and the
 * decompile names both: iVar3, the EXISTING hazard the merge loop found
 * (ESI/frame[0x10] in the original - confirmed because the C's own
 * `EncodeChecksumDeltaAdd(iVar3 + 0x3c, ...)` compiles to `mov edi,
 * [esp+0x10]; add edi,0x3c`), and iVar6, the freshly built one from
 * Init*Hazard.  Cells are this hazard type's documented layout: +0x3c
 * world-X, +0x260 width/strength, +0x488 lifetime.  The one remaining peek
 * reads local_454, the scratch the EncodeChecksumDeltaDiv above returned
 * (these helpers return their arg2, see tools/sweep_guard_instructions.md).
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
  cVar1 = PeekPacketChecksumBool((byte *)(param_1 + 4));
  if (cVar1 == '\0') {
    iVar2 = (int)(param_3 + (param_3 >> 0x1f & 3U)) >> 2;
    for (iVar6 = (param_2 - iVar2) + -5; iVar6 <= iVar2 + 5 + param_2; iVar6 = iVar6 + 1) {
      iVar3 = FUN_004511b0(iVar6,(int)(&DAT_006a7f88 + g_clientContext));
      if (iVar3 != 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EncodeOutgoingPacketField((void *)(iVar3 + 0x488), param_4);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar6 = PeekPacketChecksumState((void *)(iVar3 + 0x260));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        if (param_3 < iVar6) {
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          param_3 = PeekPacketChecksumState((void *)(iVar3 + 0x260));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EncodeOutgoingPacketField((void *)(iVar3 + 0x260), (param_3 * 0xf) / 10);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        uVar5 = EncodeChecksumDeltaAdd(iVar3 + 0x3c,local_230,param_2);
        local_4 = 0;
        EncodeChecksumDeltaDiv(uVar5,local_454,2);
        local_4 = 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        uVar5 = PeekPacketChecksumState((void *)(local_454));
        EncodeOutgoingPacketField((void *)(iVar3 + 0x3c), uVar5);
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
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(iVar6 + 0x3c), param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(iVar6 + 0x260), param_3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    *(undefined4 *)(iVar6 + 0x484) = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(iVar6 + 0x488), param_4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
LAB_0043604a:
  *unaff_FS_OFFSET = local_c;
  return;
}

