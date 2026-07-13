/* FUN_00434ac0 - 0x00434ac0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00434ac0(undefined4 param_1,int param_2)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  byte bVar6;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ca9b;
  *unaff_FS_OFFSET = &local_c;
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\0') {
    piVar2 = operator_new(0x3f9c);
    local_4 = 0;
    if (piVar2 == (int *)0x0) {
      piVar2 = (int *)0x0;
    }
    else {
      InitProjectile(piVar2,0x186a2);
      *piVar2 = (int)&PTR_FUN_00555dec;
    }
    local_4 = 0xffffffff;
    iVar3 = FindPreloadedTextureByName(s_dropcase_00553c84);
    piVar2[7] = iVar3;
    (**(code **)(*piVar2 + 4))(s_normal_00552230);
    piVar2[6] = 0x183a;
    piVar2[0xe] = 0x189e;
    piVar2[0xe25] = 0x1fa6;
    piVar2[0xe26] = SUBFIELD(s_caseflame_00553c78,0,undefined4);
    piVar2[0xe27] = SUBFIELD(s_caseflame_00553c78,4,undefined4);
    *(undefined2 *)(piVar2 + 0xe28) = SUBFIELD(s_caseflame_00553c78,8,undefined2);
    *(undefined1 *)(piVar2 + 0xf) = 0xff;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_2 << 8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = FloatToInt64();
    EncodeOutgoingPacketField((iVar5 << 8) / iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = FloatToInt64();
    EncodeOutgoingPacketField(((0x62 - iVar5) * 0x100) / iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(char *)((int)piVar2 + 0xf3f) = (char)iVar3;
    iVar3 = _rand();
    *(byte *)(piVar2 + 0x3d0) = (byte)iVar3;
    bVar6 = '\x01' << (*(byte *)((int)piVar2 + 0xf3f) & 7);
    bVar6 = ~bVar6 & (byte)iVar3 | bVar6;
    *(byte *)(piVar2 + 0x3d0) = bVar6;
    *(byte *)((int)piVar2 + 0xf41) = bVar6 + *(char *)((int)piVar2 + 0xf3f) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(char *)((int)piVar2 + 0xf45) = (char)iVar3;
    iVar3 = _rand();
    *(byte *)((int)piVar2 + 0xf46) = (byte)iVar3;
    bVar6 = *(byte *)((int)piVar2 + 0xf45) & 7;
    bVar6 = ~('\x01' << bVar6) & (byte)iVar3 | '\0' << bVar6;
    *(byte *)((int)piVar2 + 0xf46) = bVar6;
    *(byte *)((int)piVar2 + 0xf47) = bVar6 + *(char *)((int)piVar2 + 0xf45) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(char *)((int)piVar2 + 0x391b) = (char)iVar3;
    iVar3 = _rand();
    *(byte *)(piVar2 + 0xe47) = (byte)iVar3;
    bVar6 = *(byte *)((int)piVar2 + 0x391b) & 7;
    bVar6 = ~('\x01' << bVar6) & (byte)iVar3 | '\0' << bVar6;
    *(byte *)(piVar2 + 0xe47) = bVar6;
    *(byte *)((int)piVar2 + 0x391d) = bVar6 + *(char *)((int)piVar2 + 0x391b) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)((int)piVar2 + 0x3813) = SUBFIELD(s_caseblast_xes_00553c68,0,undefined4);
    *(undefined4 *)((int)piVar2 + 0x3817) = SUBFIELD(s_caseblast_xes_00553c68,4,undefined4);
    *(undefined4 *)((int)piVar2 + 0x381b) = SUBFIELD(s_caseblast_xes_00553c68,8,undefined4);
    *(undefined2 *)((int)piVar2 + 0x381f) = SUBFIELD(s_caseblast_xes_00553c68,12,undefined2);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

