/* SpawnWeatherHazards - 0x0041ebf0 in the original binary.
 *
 * RENAMED (2026-07-16, from FUN_0041ebf0): the per-turn terrain-hazard
 * spawn dispatcher. Reads a hazard-descriptor record (Ghidra dropped
 * its EAX pointer arg; the caller State11_InBattle_ProcessBattleAction
 * passes packet+0x22) with three slots - Firewall, Tornado, Lightning,
 * each (marker byte, position short, strength) - and spawns each whose
 * marker != -1 via SpawnFirewallHazard/SpawnTornadoHazard/
 * SpawnLightningHazard. Counterpart of RenderWeatherHazards (the draw
 * side that walks the same g_clientContext+0x6a7f88 active-object list).
 *
 * Identity CONFIRMED transitively: the three spawn callees construct
 * objects whose layer key (node+4) is 0x1f5/500/0x1f6, which
 * RenderWeatherHazards maps 1:1 to s_FirewallTexture/s_TornadoTexture/
 * s_LightningTexture. Hazard spawns are packet-driven (server emits the
 * descriptor), which is why the client's own decoded stage.dat hazard
 * fields (FILEFORMATS.md 회오리/증폭/전기) are never consumed here.
 * Raw/near-verbatim Ghidra body, not hand-verified - see src/README.md. *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call
 * ((void *)(g_clientContext + 0x45354)), from tools/guard_cell_resolve.py.
 */
#include "ghidra_types.h"


void SpawnWeatherHazards(int param_1,char *regEax)

{
  char cVar1;
  byte bVar2;
  short sVar3;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  byte bVar7;
  char *pcVar8;
  char *pcVar9;
  byte *pbVar10;
  
  cVar1 = *regEax;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField((int)cVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  sVar3 = *(short *)(regEax + 1);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField((int)sVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  cVar1 = regEax[3];
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField((int)cVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  cVar1 = regEax[4];
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField((int)cVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  pcVar8 = regEax + 7;
  if (regEax[6] != -1) {
    cVar1 = *pcVar8;
    pcVar8 = regEax + 10;
    SpawnFirewallHazard(&DAT_006a7f70 + param_1,*(undefined2 *)(regEax + 8),cVar1,10000);
  }
  pcVar9 = pcVar8 + 1;
  if (*pcVar8 != -1) {
    cVar1 = *pcVar9;
    pcVar9 = pcVar8 + 4;
    SpawnTornadoHazard(&DAT_006a7f70 + param_1,*(undefined2 *)(pcVar8 + 2),cVar1,10000);
  }
  pcVar8 = pcVar9 + 1;
  if (*pcVar9 != -1) {
    cVar1 = *pcVar8;
    pcVar8 = pcVar9 + 4;
    SpawnLightningHazard(&DAT_006a7f70 + param_1,*(undefined2 *)(pcVar9 + 2),cVar1,10000);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar6 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar5 = g_clientContext;
  if ((iVar6 == 3) && (*pcVar8 != -1)) {
    pbVar10 = &DAT_006a7f90 + g_clientContext;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar6 = _rand();
    *pbVar10 = (byte)iVar6;
    iVar6 = _rand();
    bVar2 = *pbVar10;
    (&DAT_006a7f91)[iVar5] = (byte)iVar6;
    bVar7 = '\x01' << (bVar2 & 7);
    bVar7 = ~bVar7 & (byte)iVar6 | bVar7;
    bVar2 = *pbVar10;
    (&DAT_006a7f91)[iVar5] = bVar7;
    (&DAT_006a7f92)[iVar5] = bVar7 + bVar2 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    cVar1 = pcVar8[1];
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField(cVar1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar4 = *(undefined2 *)(pcVar8 + 2);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  return;
}

