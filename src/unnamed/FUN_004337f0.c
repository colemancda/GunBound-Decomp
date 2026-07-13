/* FUN_004337f0 - 0x004337f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004337f0(undefined4 param_1,int param_2)

{
  char cVar1;
  byte bVar2;
  int *piVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
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
    piVar3 = operator_new(0x3f9c);
    local_4 = 0;
    if (piVar3 == (int *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      InitProjectile(piVar3,0x186a2);
      *piVar3 = (int)&PTR_FUN_00555dcc;
    }
    local_4 = 0xffffffff;
    if (*(char *)(g_clientContext + 0x45578) == '\0') {
      iVar4 = FindPreloadedTextureByName(s_dropbomb_00553cd4);
      piVar3[7] = iVar4;
      (**(code **)(*piVar3 + 4))(s_normal_00552230);
      piVar3[6] = 0x1838;
      piVar3[0xe] = 0x189c;
      piVar3[0xe25] = 0x1fa4;
      piVar3[0xe26] = SUBFIELD(s_bombflame_00553cc8,0,undefined4);
      piVar3[0xe27] = SUBFIELD(s_bombflame_00553cc8,4,undefined4);
      *(undefined2 *)(piVar3 + 0xe28) = SUBFIELD(s_bombflame_00553cc8,8,undefined2);
    }
    else if (*(char *)(g_clientContext + 0x45578) == '\x01') {
      iVar4 = FindPreloadedTextureByName(s_bulletevent1_00553e38);
      piVar3[7] = iVar4;
      (**(code **)(*piVar3 + 4))(s_normal_00552230);
      piVar3[6] = 6000;
      piVar3[0xe] = 0x189c;
      piVar3[0xe25] = 8000;
      piVar3[0xe26] = SUBFIELD(s_flameevent1_00553e2c,0,undefined4);
      piVar3[0xe27] = SUBFIELD(s_flameevent1_00553e2c,4,undefined4);
      piVar3[0xe28] = SUBFIELD(s_flameevent1_00553e2c,8,undefined4);
    }
    *(undefined1 *)(piVar3 + 0xf) = 0xff;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
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
    uVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = FloatToInt64();
    EncodeOutgoingPacketField((iVar6 << 8) / iVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = FloatToInt64();
    EncodeOutgoingPacketField(((0x62 - iVar6) * 0x100) / iVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = _rand();
    *(char *)((int)piVar3 + 0xf3f) = (char)iVar4;
    iVar4 = _rand();
    *(byte *)(piVar3 + 0x3d0) = (byte)iVar4;
    bVar2 = '\x01' << (*(byte *)((int)piVar3 + 0xf3f) & 7);
    bVar2 = ~bVar2 & (byte)iVar4 | bVar2;
    *(byte *)(piVar3 + 0x3d0) = bVar2;
    *(byte *)((int)piVar3 + 0xf41) = *(byte *)((int)piVar3 + 0xf3f) + bVar2 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = _rand();
    *(char *)((int)piVar3 + 0xf45) = (char)iVar4;
    iVar4 = _rand();
    *(byte *)((int)piVar3 + 0xf46) = (byte)iVar4;
    bVar2 = *(byte *)((int)piVar3 + 0xf45) & 7;
    bVar2 = ~('\x01' << bVar2) & (byte)iVar4 | '\0' << bVar2;
    *(byte *)((int)piVar3 + 0xf46) = bVar2;
    *(byte *)((int)piVar3 + 0xf47) = *(byte *)((int)piVar3 + 0xf45) + bVar2 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = _rand();
    *(char *)(piVar3 + 0x3cf) = (char)iVar4;
    iVar4 = _rand();
    *(byte *)((int)piVar3 + 0xf3d) = (byte)iVar4;
    bVar2 = ~('\x01' << (*(byte *)(piVar3 + 0x3cf) & 7)) & (byte)iVar4 |
            '\0' << (*(byte *)(piVar3 + 0x3cf) & 7);
    *(byte *)((int)piVar3 + 0xf3d) = bVar2;
    *(byte *)((int)piVar3 + 0xf3e) = bVar2 + (char)piVar3[0x3cf] + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = _rand();
    *(char *)((int)piVar3 + 0x391b) = (char)iVar4;
    iVar4 = _rand();
    *(byte *)(piVar3 + 0xe47) = (byte)iVar4;
    bVar2 = *(byte *)((int)piVar3 + 0x391b) & 7;
    bVar2 = ~('\x01' << bVar2) & (byte)iVar4 | '\0' << bVar2;
    *(byte *)(piVar3 + 0xe47) = bVar2;
    *(byte *)((int)piVar3 + 0x391d) = bVar2 + *(char *)((int)piVar3 + 0x391b) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)((int)piVar3 + 0x3813) = SUBFIELD(s_bombblast_xes_00553cb8,0,undefined4);
    *(undefined4 *)((int)piVar3 + 0x3817) = SUBFIELD(s_bombblast_xes_00553cb8,4,undefined4);
    *(undefined4 *)((int)piVar3 + 0x381b) = SUBFIELD(s_bombblast_xes_00553cb8,8,undefined4);
    *(undefined2 *)((int)piVar3 + 0x381f) = SUBFIELD(s_bombblast_xes_00553cb8,12,undefined2);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(100);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(100);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(100);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x38);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x38);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x38);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x82);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x82);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x82);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = _rand();
    *(char *)(piVar3 + 0xcef) = (char)iVar4;
    iVar4 = _rand();
    *(byte *)((int)piVar3 + 0x33bd) = (byte)iVar4;
    bVar2 = '\x01' << (*(byte *)(piVar3 + 0xcef) & 7);
    bVar2 = ~bVar2 & (byte)iVar4 | bVar2;
    *(byte *)((int)piVar3 + 0x33bd) = bVar2;
    *(byte *)((int)piVar3 + 0x33be) = bVar2 + (char)piVar3[0xcef] + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = _rand();
    *(char *)((int)piVar3 + 0x33bf) = (char)iVar4;
    iVar4 = _rand();
    *(byte *)(piVar3 + 0xcf0) = (byte)iVar4;
    bVar2 = *(byte *)((int)piVar3 + 0x33bf) & 7;
    bVar2 = ~('\x01' << bVar2) & (byte)iVar4 | '\0' << bVar2;
    *(byte *)(piVar3 + 0xcf0) = bVar2;
    *(byte *)((int)piVar3 + 0x33c1) = bVar2 + *(char *)((int)piVar3 + 0x33bf) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = _rand();
    *(char *)((int)piVar3 + 0x33c2) = (char)iVar4;
    iVar4 = _rand();
    *(byte *)((int)piVar3 + 0x33c3) = (byte)iVar4;
    bVar2 = *(byte *)((int)piVar3 + 0x33c2) & 7;
    bVar2 = ~('\x01' << bVar2) & (byte)iVar4 | '\0' << bVar2;
    *(byte *)((int)piVar3 + 0x33c3) = bVar2;
    *(byte *)(piVar3 + 0xcf1) = bVar2 + *(char *)((int)piVar3 + 0x33c2) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = _rand();
    *(char *)((int)piVar3 + 0x33c5) = (char)iVar4;
    iVar4 = _rand();
    *(byte *)((int)piVar3 + 0x33c6) = (byte)iVar4;
    bVar2 = *(byte *)((int)piVar3 + 0x33c5) & 7;
    bVar2 = ~('\x01' << bVar2) & (byte)iVar4 | '\0' << bVar2;
    *(byte *)((int)piVar3 + 0x33c6) = bVar2;
    *(byte *)((int)piVar3 + 0x33c7) = bVar2 + *(char *)((int)piVar3 + 0x33c5) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

