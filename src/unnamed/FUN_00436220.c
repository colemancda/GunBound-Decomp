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
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\0') {
    piVar2 = operator_new(0x3f9c);
    local_4 = 0;
    if (piVar2 == (int *)0x0) {
      piVar2 = (int *)0x0;
    }
    else {
      InitProjectile(piVar2,0x30d42);
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
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4362f8
     * (`0x4362eb: lea edi,[esi + 0xf54]`) the cell is piVar2 (the
     * newly-allocated object from operator_new/InitProjectile above) plus
     * byte offset 0xf54. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0xf54),param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x43631f
     * (`0x436319: lea edi,[esi + 0x3b48]`) the cell is piVar2 + 0x3b48.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x3b48),uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x43633d
     * (`0x436337: lea edi,[esi + 0x1178]`) the cell is piVar2 + 0x1178.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x1178),param_3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x436358
     * (`0x436355: lea edi,[esi + 0x40]`) the cell is piVar2 + 0x40.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x40),param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x436376
     * (`0x436370: lea edi,[esi + 0x264]`) the cell is piVar2 + 0x264.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x264),param_3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x436391
     * (`0x436387: lea edi,[esi + 0xd18]`) the cell is piVar2 + 0xd18.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0xd18),0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4363b2
     * (`0x4363ac: lea edi,[esi + 0xaf4]`) the cell is piVar2 + 0xaf4.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0xaf4),uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4363d7
     * (`0x4363c3: lea edi,[esi + 0x6ac]`) the cell is piVar2 + 0x6ac.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x6ac),uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4363f8
     * (`0x4363f2: lea edi,[esi + 0x488]`) the cell is piVar2 + 0x488.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x488),uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x43641d
     * (`0x436417: lea edi,[esi + 0x8d0]`) the cell is piVar2 + 0x8d0.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x8d0),uVar4);
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
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4364c9
     * (`0x4364bc: lea edi,[esi + 0x17e4]`) the cell is piVar2 + 0x17e4.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x17e4),uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4364ea
     * (`0x4364e4: lea edi,[esi + 0x1a08]`) the cell is piVar2 + 0x1a08.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x1a08),uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x43651e
     * (`0x436518: lea edi,[esi + 0x1e54]`) the cell is piVar2 + 0x1e54.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x1e54),uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x436539
     * (`0x436533: lea edi,[esi + 0x2078]`) the cell is piVar2 + 0x2078.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x2078),0x46);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x436554
     * (`0x43654e: lea edi,[esi + 0x229c]`) the cell is piVar2 + 0x229c.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x229c),0x3c);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x43656f
     * (`0x436569: lea edi,[esi + 0x24c0]`) the cell is piVar2 + 0x24c0.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x24c0),0x23);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x43658a
     * (`0x436584: lea edi,[esi + 0x26e4]`) the cell is piVar2 + 0x26e4.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x26e4),0x25);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4365a5
     * (`0x43659f: lea edi,[esi + 0x2908]`) the cell is piVar2 + 0x2908.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x2908),0x27);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4365c0
     * (`0x4365ba: lea edi,[esi + 0x2b2c]`) the cell is piVar2 + 0x2b2c.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x2b2c),0x6e);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4365db
     * (`0x4365d5: lea edi,[esi + 0x2d50]`) the cell is piVar2 + 0x2d50.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x2d50),0x6e);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4365f6
     * (`0x4365f0: lea edi,[esi + 0x2f74]`) the cell is piVar2 + 0x2f74.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x2f74),0x6e);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x43662a
     * (`0x436624: lea edi,[esi + 0x3198]`) the cell is piVar2 + 0x3198.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x3198),uVar4);
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
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x43680b
     * (`0x436805: lea edi,[esi + 0x33c8]`) the cell is piVar2 + 0x33c8.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x33c8),0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x436826
     * (`0x436820: lea edi,[esi + 0x35ec]`) the cell is piVar2 + 0x35ec.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar2 + 0x35ec),0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

