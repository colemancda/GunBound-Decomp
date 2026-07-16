/* InitFirewallHazard - 0x00471320 in the original binary.
 *
 * RENAMED (2026-07-16, from FUN_00471320): constructor for the Firewall
 * terrain-hazard object. Sets the vtable (PTR_FUN_00555edc), the
 * active-object layer key (param_1[1] = 0x1f5), and the standard node
 * links. Called only by SpawnFirewallHazard. Identity CONFIRMED:
 * RenderWeatherHazards maps layer 0x1f5 -> s_FirewallTexture. Raw/near-
 * verbatim Ghidra body - see src/README.md.
 */
#include "ghidra_types.h"


undefined4 * InitFirewallHazard(undefined4 *param_1)

{
  byte bVar1;
  int iVar2;
  byte bVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_00537eb1;
  *unaff_FS_OFFSET = &local_c;
  param_1[1] = 0x1f5;
  param_1[2] = 0xffffffff;
  param_1[3] = 0;
  param_1[4] = 0;
  *(undefined1 *)(param_1 + 5) = 0;
  *(undefined1 *)((int)param_1 + 0x15) = 0;
  param_1[6] = 0xffffffff;
  param_1[7] = 0;
  *(undefined1 *)(param_1 + 8) = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[9] = 0xffffffff;
  local_4 = 0;
  *param_1 = &PTR_FUN_00555edc;
  InitGuardedBool();
  *(undefined1 *)(param_1 + 0x97) = 0;
  param_1[0x14] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x47138b
   * (`lea edi,[esi + 0x3c]`, esi = this file's own param_1): the cell is
   * param_1+0x3c; tableHandle(+0x14)=param_1+0x50 (== param_1[0x14],
   * `undefined4 *` scales by 4) is zeroed immediately above. `param_1` is
   * `undefined4 *`, so byte offsets use `(int)param_1 + N`. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x3c, 0);
  SUBFIELD(local_4,0,undefined1) = 1;
  *(undefined1 *)(param_1 + 0x120) = 0;
  param_1[0x9d] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4713a5
   * (`lea edi,[esi + 0x260]`, esi = param_1): cell is param_1+0x260;
   * tableHandle(+0x14)=param_1+0x274 (== param_1[0x9d]) is zeroed just
   * above. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x260, 0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  *(undefined1 *)(param_1 + 0x1aa) = 0;
  param_1[0x127] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4713bf
   * (`lea edi,[esi + 0x488]`, esi = param_1): cell is param_1+0x488;
   * tableHandle(+0x14)=param_1+0x49c (== param_1[0x127]) is zeroed just
   * above. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x488, 0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *(byte *)(param_1 + 0xe) = (byte)iVar2;
  iVar2 = _rand();
  bVar1 = *(byte *)(param_1 + 0xe);
  *(byte *)((int)param_1 + 0x39) = (byte)iVar2;
  bVar3 = bVar1 & 7;
  bVar3 = ~('\x01' << bVar3) & (byte)iVar2 | '\0' << bVar3;
  *(byte *)((int)param_1 + 0x39) = bVar3;
  *(byte *)((int)param_1 + 0x3a) = bVar3 + bVar1 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

