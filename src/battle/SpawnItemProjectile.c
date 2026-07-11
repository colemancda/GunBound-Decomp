/* SpawnItemProjectile - 0x004317b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x00431855) */

void SpawnItemProjectile(undefined4 param_1,int param_2,int param_3)

{
  void *pvVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  byte bVar5;
  int *piVar6;
  undefined4 *unaff_FS_OFFSET;
  byte unaff_retaddr;
  undefined2 in_stack_0000001c;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053795b;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  pvVar1 = operator_new(0x3fa8);
  piVar6 = (int *)0x0;
  local_4 = 0;
  if (pvVar1 != (void *)0x0) {
    piVar6 = (int *)FUN_00476510();
  }
  local_4 = 0xffffffff;
  FUN_004e51f0();
  piVar6[6] = -1;
  piVar6[0xe25] = -1;
  *(undefined2 *)(piVar6 + 0xfe7) = in_stack_0000001c;
  iVar2 = FindPreloadedTextureByName(s_bulletitem_00553d14);
  piVar6[7] = iVar2;
  (**(code **)(*piVar6 + 4))(s_normal_00552230);
  *(byte *)(piVar6 + 0xf) = unaff_retaddr & 7;
  piVar6[0xe] = 0x1965;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_2 << 8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_3 << 8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = FloatToInt64();
  EncodeOutgoingPacketField((iVar4 << 8) / iVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = FloatToInt64();
  EncodeOutgoingPacketField((iVar4 << 8) / iVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = FloatToInt64();
  EncodeOutgoingPacketField(-((iVar4 << 8) / iVar2));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = FloatToInt64();
  EncodeOutgoingPacketField((iVar4 << 8) / iVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = FloatToInt64();
  EncodeOutgoingPacketField(((0x62 - iVar4) * 0x100) / iVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *(char *)((int)piVar6 + 0xf3f) = (char)iVar2;
  iVar2 = _rand();
  *(byte *)(piVar6 + 0x3d0) = (byte)iVar2;
  bVar5 = *(byte *)((int)piVar6 + 0xf3f) & 7;
  bVar5 = ~('\x01' << bVar5) & (byte)iVar2 | '\0' << bVar5;
  *(byte *)(piVar6 + 0x3d0) = bVar5;
  *(byte *)((int)piVar6 + 0xf41) = bVar5 + *(char *)((int)piVar6 + 0xf3f) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(uVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *(char *)((int)piVar6 + 0x391b) = (char)iVar2;
  iVar2 = _rand();
  *(byte *)(piVar6 + 0xe47) = (byte)iVar2;
  bVar5 = *(byte *)((int)piVar6 + 0x391b) & 7;
  bVar5 = ~('\x01' << bVar5) & (byte)iVar2 | '\0' << bVar5;
  *(byte *)(piVar6 + 0xe47) = bVar5;
  *(byte *)((int)piVar6 + 0x391d) = bVar5 + *(char *)((int)piVar6 + 0x391b) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar6[0xfe8] = -1;
  *(undefined2 *)(piVar6 + 0xfe9) = 0xffff;
  piVar6[0xe26] = SUBFIELD(s_itemflame_00553d08,0,undefined4);
  piVar6[0xe27] = SUBFIELD(s_itemflame_00553d08,4,undefined4);
  *(undefined2 *)(piVar6 + 0xe28) = SUBFIELD(s_itemflame_00553d08,8,undefined2);
  *(undefined4 *)((int)piVar6 + 0x3813) = SUBFIELD(s_itemblast_xes_00553cf8,0,undefined4);
  *(undefined4 *)((int)piVar6 + 0x3817) = SUBFIELD(s_itemblast_xes_00553cf8,4,undefined4);
  *(undefined4 *)((int)piVar6 + 0x381b) = SUBFIELD(s_itemblast_xes_00553cf8,8,undefined4);
  *(undefined2 *)((int)piVar6 + 0x381f) = SUBFIELD(s_itemblast_xes_00553cf8,12,undefined2);
  RegisterActiveObject();
  *unaff_FS_OFFSET = pvVar1;
  return;
}

