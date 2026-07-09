/* FUN_00436220 - 0x00436220 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00436220(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  byte bVar5;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ca9b;
  *unaff_FS_OFFSET = &local_c;
  cVar1 = FUN_004065a0();
  if (cVar1 == '\0') {
    piVar2 = operator_new(0x3f9c);
    local_4 = 0;
    if (piVar2 == (int *)0x0) {
      piVar2 = (int *)0x0;
    }
    else {
      FUN_00454dc0(piVar2,0x30d42);
      *piVar2 = (int)&PTR_FUN_00555fbc;
    }
    local_4 = 0xffffffff;
    iVar3 = FindPreloadedTextureByName(s_itemcase_00553c38);
    piVar2[7] = iVar3;
    (**(code **)(*piVar2 + 4))(s_normal_00552230);
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
    EncodeOutgoingPacketField(param_3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(char *)((int)piVar2 + 0xf3f) = (char)iVar3;
    iVar3 = _rand();
    *(byte *)(piVar2 + 0x3d0) = (byte)iVar3;
    bVar5 = *(byte *)((int)piVar2 + 0xf3f) & 7;
    bVar5 = ~('\x01' << bVar5) & (byte)iVar3 | '\0' << bVar5;
    *(byte *)(piVar2 + 0x3d0) = bVar5;
    *(byte *)((int)piVar2 + 0xf41) = bVar5 + *(char *)((int)piVar2 + 0xf3f) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x46);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x3c);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x23);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x25);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x27);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x6e);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x6e);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x6e);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(char *)(piVar2 + 0xcef) = (char)iVar3;
    iVar3 = _rand();
    *(byte *)((int)piVar2 + 0x33bd) = (byte)iVar3;
    bVar5 = '\x01' << (*(byte *)(piVar2 + 0xcef) & 7);
    bVar5 = ~bVar5 & (byte)iVar3 | bVar5;
    *(byte *)((int)piVar2 + 0x33bd) = bVar5;
    *(byte *)((int)piVar2 + 0x33be) = bVar5 + (char)piVar2[0xcef] + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(char *)((int)piVar2 + 0x33bf) = (char)iVar3;
    iVar3 = _rand();
    *(byte *)(piVar2 + 0xcf0) = (byte)iVar3;
    bVar5 = *(byte *)((int)piVar2 + 0x33bf) & 7;
    bVar5 = ~('\x01' << bVar5) & (byte)iVar3 | '\0' << bVar5;
    *(byte *)(piVar2 + 0xcf0) = bVar5;
    *(byte *)((int)piVar2 + 0x33c1) = bVar5 + *(char *)((int)piVar2 + 0x33bf) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(char *)((int)piVar2 + 0x33c2) = (char)iVar3;
    iVar3 = _rand();
    *(byte *)((int)piVar2 + 0x33c3) = (byte)iVar3;
    bVar5 = *(byte *)((int)piVar2 + 0x33c2) & 7;
    bVar5 = ~('\x01' << bVar5) & (byte)iVar3 | '\0' << bVar5;
    *(byte *)((int)piVar2 + 0x33c3) = bVar5;
    *(byte *)(piVar2 + 0xcf1) = bVar5 + *(char *)((int)piVar2 + 0x33c2) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(char *)((int)piVar2 + 0x33c5) = (char)iVar3;
    iVar3 = _rand();
    *(byte *)((int)piVar2 + 0x33c6) = (byte)iVar3;
    bVar5 = *(byte *)((int)piVar2 + 0x33c5) & 7;
    bVar5 = ~('\x01' << bVar5) & (byte)iVar3 | '\0' << bVar5;
    *(byte *)((int)piVar2 + 0x33c6) = bVar5;
    *(byte *)((int)piVar2 + 0x33c7) = bVar5 + *(char *)((int)piVar2 + 0x33c5) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    RegisterActiveObject();
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

