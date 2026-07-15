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
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433940
     * (`0x433933: lea edi,[esi + 0xf54]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0xf54. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0xf54),param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433967
     * (`0x433961: lea edi,[esi + 0x3b48]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x3b48. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x3b48),uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433982
     * (`0x43397c: lea edi,[esi + 0x1178]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x1178. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x1178),0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4339a0
     * (`0x43399d: lea edi,[esi + 0x40]`) the cell is piVar3 (the newly-allocated
     * object from operator_new/InitProjectile above) plus byte offset 0x40. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x40),param_2 << 8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4339bb
     * (`0x4339b5: lea edi,[esi + 0x264]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x264. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x264),0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4339d6
     * (`0x4339d0: lea edi,[esi + 0x488]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x488. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x488),0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4339f1
     * (`0x4339eb: lea edi,[esi + 0x8d0]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x8d0. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x8d0),0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433a25
     * (`0x433a1f: lea edi,[esi + 0x6ac]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x6ac. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x6ac),uVar5);
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
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433ad0
     * (`0x433ac9: lea edi,[esi + 0xaf4]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0xaf4. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0xaf4),(iVar6 << 8) / iVar4);
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
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433b83
     * (`0x433b7c: lea edi,[esi + 0xd18]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0xd18. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0xd18),((0x62 - iVar6) * 0x100) / iVar4);
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
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433caa
     * (`0x433c9d: lea edi,[esi + 0x17e4]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x17e4. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x17e4),uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433ccb
     * (`0x433cc5: lea edi,[esi + 0x1a08]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x1a08. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x1a08),uVar5);
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
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433dcc
     * (`0x433dc6: lea edi,[esi + 0x3920]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x3920. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x3920),0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)((int)piVar3 + 0x3813) = SUBFIELD(s_bombblast_xes_00553cb8,0,undefined4);
    *(undefined4 *)((int)piVar3 + 0x3817) = SUBFIELD(s_bombblast_xes_00553cb8,4,undefined4);
    *(undefined4 *)((int)piVar3 + 0x381b) = SUBFIELD(s_bombblast_xes_00553cb8,8,undefined4);
    *(undefined2 *)((int)piVar3 + 0x381f) = SUBFIELD(s_bombblast_xes_00553cb8,12,undefined2);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433e10
     * (`0x433e0a: lea edi,[esi + 0x1e54]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x1e54. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x1e54),100);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433e2b
     * (`0x433e25: lea edi,[esi + 0x2078]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x2078. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x2078),100);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433e46
     * (`0x433e40: lea edi,[esi + 0x229c]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x229c. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x229c),100);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433e61
     * (`0x433e5b: lea edi,[esi + 0x24c0]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x24c0. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x24c0),0x38);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433e7c
     * (`0x433e76: lea edi,[esi + 0x26e4]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x26e4. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x26e4),0x38);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433e97
     * (`0x433e91: lea edi,[esi + 0x2908]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x2908. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x2908),0x38);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433eb5
     * (`0x433eaf: lea edi,[esi + 0x2b2c]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x2b2c. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x2b2c),0x82);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433ed3
     * (`0x433ecd: lea edi,[esi + 0x2d50]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x2d50. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x2d50),0x82);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433ef1
     * (`0x433eeb: lea edi,[esi + 0x2f74]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x2f74. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x2f74),0x82);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x433f25
     * (`0x433f1f: lea edi,[esi + 0x3198]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x3198. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x3198),uVar5);
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
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x434104
     * (`0x4340fe: lea edi,[esi + 0x33c8]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x33c8. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x33c8),0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x43411f
     * (`0x434119: lea edi,[esi + 0x35ec]`) the cell is piVar3 (the newly-
     * allocated object from operator_new/InitProjectile above) plus byte offset
     * 0x35ec. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((void *)((int)piVar3 + 0x35ec),0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

