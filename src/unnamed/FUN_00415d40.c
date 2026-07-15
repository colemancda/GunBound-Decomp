/* FUN_00415d40 - 0x00415d40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00415d40(int param_1)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  undefined4 *puVar4;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053be60;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *(undefined ***)(param_1 + 0xf6cc) = &PTR_FUN_005572dc;
  InitializeCriticalSection((LPCRITICAL_SECTION)(param_1 + 0xf6d0));
  local_4 = 0;
  *(undefined ***)(param_1 + 0x1fdfc) = &PTR_FUN_005572dc;
  InitializeCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x1fe00));
  puVar4 = (undefined4 *)(param_1 + 0xf728);
  for (iVar1 = 0x400; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  *(undefined4 *)(param_1 + 0x10728) = 0xffffffff;
  *(undefined1 *)(param_1 + 0x1072c) = 0;
  *(undefined1 *)(param_1 + 0x1072d) = 1;
  *(undefined4 *)(param_1 + 0xf6f0) = 0;
  SUBFIELD(local_4,0,undefined1) = 1;
  InitGuardedBool();
  InitGuardedBool();
  *(undefined1 *)(param_1 + 0x23568) = 0;
  *(undefined4 *)(param_1 + 0x2335c) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x415de4
   * (`0x415dd4: lea edi,[ebp + 0x23348]`) the cell is param_1 + 0x23348; tableHandle write at param_1+0x2335c (cell+0x14) and activeFlag write at
   * param_1+0x23568 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x23348, 0);
  SUBFIELD(local_4,0,undefined1) = 2;
  *(undefined1 *)(param_1 + 0x2378c) = 0;
  *(undefined4 *)(param_1 + 0x23580) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x415dfe
   * (`0x415de9: lea edi,[ebp + 0x2356c]`) the cell is param_1 + 0x2356c; tableHandle write at param_1+0x23580 (cell+0x14) and activeFlag write at
   * param_1+0x2378c (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x2356c, 0);
  SUBFIELD(local_4,0,undefined1) = 3;
  *(undefined1 *)(param_1 + 0x239b0) = 0;
  *(undefined4 *)(param_1 + 0x237a4) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x415e18
   * (`0x415e03: lea edi,[ebp + 0x23790]`) the cell is param_1 + 0x23790; tableHandle write at param_1+0x237a4 (cell+0x14) and activeFlag write at
   * param_1+0x239b0 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x23790, 0);
  SUBFIELD(local_4,0,undefined1) = 4;
  *(undefined1 *)(param_1 + 0x23bd4) = 0;
  *(undefined4 *)(param_1 + 0x239c8) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x415e32
   * (`0x415e1d: lea edi,[ebp + 0x239b4]`) the cell is param_1 + 0x239b4; tableHandle write at param_1+0x239c8 (cell+0x14) and activeFlag write at
   * param_1+0x23bd4 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x239b4, 0);
  SUBFIELD(local_4,0,undefined1) = 5;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x23bd8),0x224,0x14,InitGuardSlot,ScrubChecksumGuard)
  ;
  SUBFIELD(local_4,0,undefined1) = 6;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x266a8),0x224,0x14,InitGuardSlot,ScrubChecksumGuard)
  ;
  SUBFIELD(local_4,0,undefined1) = 7;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x29178),0x224,0x14,InitGuardSlot,ScrubChecksumGuard)
  ;
  SUBFIELD(local_4,0,undefined1) = 8;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x2bc48),0x224,0x14,InitGuardSlot,ScrubChecksumGuard)
  ;
  SUBFIELD(local_4,0,undefined1) = 9;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x2e718),0x224,0x14,InitGuardSlot,ScrubChecksumGuard)
  ;
  SUBFIELD(local_4,0,undefined1) = 10;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x311e8),0x224,0x14,InitGuardSlot,ScrubChecksumGuard)
  ;
  SUBFIELD(local_4,0,undefined1) = 0xb;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x33cb8),0x224,0x14,InitGuardSlot,ScrubChecksumGuard)
  ;
  SUBFIELD(local_4,0,undefined1) = 0xc;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x36788),0x224,0x14,InitGuardSlot,ScrubChecksumGuard)
  ;
  SUBFIELD(local_4,0,undefined1) = 0xd;
  *(undefined1 *)(param_1 + 0x39478) = 0;
  *(undefined4 *)(param_1 + 0x3926c) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x415f5c
   * (`0x415f47: lea edi,[ebp + 0x39258]`) the cell is param_1 + 0x39258; tableHandle write at param_1+0x3926c (cell+0x14) and activeFlag write at
   * param_1+0x39478 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x39258, 0);
  SUBFIELD(local_4,0,undefined1) = 0xe;
  *(undefined1 *)(param_1 + 0x3969c) = 0;
  *(undefined4 *)(param_1 + 0x39490) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x415f76
   * (`0x415f61: lea edi,[ebp + 0x3947c]`) the cell is param_1 + 0x3947c; tableHandle write at param_1+0x39490 (cell+0x14) and activeFlag write at
   * param_1+0x3969c (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x3947c, 0);
  SUBFIELD(local_4,0,undefined1) = 0xf;
  *(undefined1 *)(param_1 + 0x398c0) = 0;
  *(undefined4 *)(param_1 + 0x396b4) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x415f90
   * (`0x415f7b: lea edi,[ebp + 0x396a0]`) the cell is param_1 + 0x396a0; tableHandle write at param_1+0x396b4 (cell+0x14) and activeFlag write at
   * param_1+0x398c0 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x396a0, 0);
  SUBFIELD(local_4,0,undefined1) = 0x10;
  *(undefined1 *)(param_1 + 0x39ae4) = 0;
  *(undefined4 *)(param_1 + 0x398d8) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x415faa
   * (`0x415f95: lea edi,[ebp + 0x398c4]`) the cell is param_1 + 0x398c4; tableHandle write at param_1+0x398d8 (cell+0x14) and activeFlag write at
   * param_1+0x39ae4 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x398c4, 0);
  SUBFIELD(local_4,0,undefined1) = 0x11;
  *(undefined1 *)(param_1 + 0x39d08) = 0;
  *(undefined4 *)(param_1 + 0x39afc) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x415fc4
   * (`0x415faf: lea edi,[ebp + 0x39ae8]`) the cell is param_1 + 0x39ae8; tableHandle write at param_1+0x39afc (cell+0x14) and activeFlag write at
   * param_1+0x39d08 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x39ae8, 0);
  SUBFIELD(local_4,0,undefined1) = 0x12;
  *(undefined1 *)(param_1 + 0x39f2c) = 0;
  *(undefined4 *)(param_1 + 0x39d20) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x415fde
   * (`0x415fc9: lea edi,[ebp + 0x39d0c]`) the cell is param_1 + 0x39d0c; tableHandle write at param_1+0x39d20 (cell+0x14) and activeFlag write at
   * param_1+0x39f2c (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x39d0c, 0);
  SUBFIELD(local_4,0,undefined1) = 0x13;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x39f30),0x224,6,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x14;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x3ac08),0x224,4,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x15;
  InitGuardedBool();
  *(undefined1 *)(param_1 + 0x3b6bc) = 0;
  *(undefined4 *)(param_1 + 0x3b4b0) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416047
   * (`0x416037: lea edi,[ebp + 0x3b49c]`) the cell is param_1 + 0x3b49c; tableHandle write at param_1+0x3b4b0 (cell+0x14) and activeFlag write at
   * param_1+0x3b6bc (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x3b49c, 0);
  SUBFIELD(local_4,0,undefined1) = 0x16;
  *(undefined1 *)(param_1 + 0x3b8e4) = 0;
  *(undefined4 *)(param_1 + 0x3b6d8) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416061
   * (`0x41604c: lea edi,[ebp + 0x3b6c4]`) the cell is param_1 + 0x3b6c4; tableHandle write at param_1+0x3b6d8 (cell+0x14) and activeFlag write at
   * param_1+0x3b8e4 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x3b6c4, 0);
  SUBFIELD(local_4,0,undefined1) = 0x17;
  InitGuardedBool();
  *(undefined1 *)(param_1 + 0x4133c) = 0;
  *(undefined4 *)(param_1 + 0x41130) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416086
   * (`0x416076: lea edi,[ebp + 0x4111c]`) the cell is param_1 + 0x4111c; tableHandle write at param_1+0x41130 (cell+0x14) and activeFlag write at
   * param_1+0x4133c (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x4111c, 0);
  SUBFIELD(local_4,0,undefined1) = 0x18;
  *(undefined1 *)(param_1 + 0x44be4) = 0;
  *(undefined4 *)(param_1 + 0x449d8) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4160a0
   * (`0x41608b: lea edi,[ebp + 0x449c4]`) the cell is param_1 + 0x449c4; tableHandle write at param_1+0x449d8 (cell+0x14) and activeFlag write at
   * param_1+0x44be4 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x449c4, 0);
  *(undefined4 *)(param_1 + 0x44be8) = 0;
  *(undefined4 *)(param_1 + 0x44bec) = 0;
  *(undefined4 *)(param_1 + 0x44bf0) = 0;
  *(undefined4 *)(param_1 + 0x44bf4) = 0;
  SUBFIELD(local_4,0,undefined1) = 0x1a;
  *(undefined1 *)(param_1 + 0x44e1c) = 0;
  *(undefined4 *)(param_1 + 0x44c10) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4160d2
   * (`0x4160bd: lea edi,[ebp + 0x44bfc]`) the cell is param_1 + 0x44bfc; tableHandle write at param_1+0x44c10 (cell+0x14) and activeFlag write at
   * param_1+0x44e1c (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x44bfc, 0);
  *(undefined4 *)(param_1 + 0x44e20) = 0;
  *(undefined4 *)(param_1 + 0x44e24) = 0;
  *(undefined4 *)(param_1 + 0x44e28) = 0;
  *(undefined4 *)(param_1 + 0x44e2c) = 0;
  *(undefined4 *)(param_1 + 0x44e30) = 0;
  *(undefined4 *)(param_1 + 0x44e34) = 0;
  *(undefined4 *)(param_1 + 0x44e38) = 0;
  *(undefined4 *)(param_1 + 0x44e3c) = 0;
  *(undefined4 *)(param_1 + 0x44e40) = 0;
  *(undefined4 *)(param_1 + 0x44e44) = 0;
  *(undefined4 *)(param_1 + 0x44e48) = 0;
  *(undefined4 *)(param_1 + 0x44e4c) = 0;
  *(undefined4 *)(param_1 + 0x44e50) = 0;
  *(undefined4 *)(param_1 + 0x44e54) = 0;
  *(undefined4 *)(param_1 + 0x44e58) = 0;
  *(undefined4 *)(param_1 + 0x44e5c) = 0;
  SUBFIELD(local_4,0,undefined1) = 0x1f;
  *(undefined1 *)(param_1 + 0x4511c) = 0;
  *(undefined4 *)(param_1 + 0x44f10) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x41614c
   * (`0x416137: lea edi,[ebp + 0x44efc]`) the cell is param_1 + 0x44efc; tableHandle write at param_1+0x44f10 (cell+0x14) and activeFlag write at
   * param_1+0x4511c (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x44efc, 0);
  SUBFIELD(local_4,0,undefined1) = 0x20;
  *(undefined1 *)(param_1 + 0x4534c) = 0;
  *(undefined4 *)(param_1 + 0x45140) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416166
   * (`0x416151: lea edi,[ebp + 0x4512c]`) the cell is param_1 + 0x4512c; tableHandle write at param_1+0x45140 (cell+0x14) and activeFlag write at
   * param_1+0x4534c (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x4512c, 0);
  SUBFIELD(local_4,0,undefined1) = 0x21;
  *(undefined1 *)(param_1 + 0x45574) = 0;
  *(undefined4 *)(param_1 + 0x45368) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416180
   * (`0x41616b: lea edi,[ebp + 0x45354]`) the cell is param_1 + 0x45354; tableHandle write at param_1+0x45368 (cell+0x14) and activeFlag write at
   * param_1+0x45574 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x45354, 0);
  SUBFIELD(local_4,0,undefined1) = 0x22;
  *(undefined1 *)(param_1 + 0x4579c) = 0;
  *(undefined4 *)(param_1 + 0x45590) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x41619a
   * (`0x416185: lea edi,[ebp + 0x4557c]`) the cell is param_1 + 0x4557c; tableHandle write at param_1+0x45590 (cell+0x14) and activeFlag write at
   * param_1+0x4579c (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x4557c, 0);
  SUBFIELD(local_4,0,undefined1) = 0x23;
  *(undefined4 *)(param_1 + 0x4737c) = 0;
  *(undefined4 *)(param_1 + 0x47380) = 1;
  *(undefined4 *)(param_1 + 0x47384) = 2;
  *(undefined4 *)(param_1 + 0x47388) = 3;
  *(undefined4 *)(param_1 + 0x4738c) = 4;
  *(undefined4 *)(param_1 + 0x47390) = 5;
  *(undefined4 *)(param_1 + 0x47394) = 6;
  *(undefined4 *)(param_1 + 0x47398) = 7;
  *(undefined4 *)(param_1 + 0x4739c) = 0;
  *(undefined1 *)(param_1 + 0x475c0) = 0;
  *(undefined4 *)(param_1 + 0x473b4) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416206
   * (`0x4161f0: lea edi,[ebp + 0x473a0]`) the cell is param_1 + 0x473a0; tableHandle write at param_1+0x473b4 (cell+0x14) and activeFlag write at
   * param_1+0x475c0 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x473a0, 0);
  SUBFIELD(local_4,0,undefined1) = 0x24;
  *(undefined1 *)(param_1 + 0x477e8) = 0;
  *(undefined4 *)(param_1 + 0x475dc) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416220
   * (`0x41620b: lea edi,[ebp + 0x475c8]`) the cell is param_1 + 0x475c8; tableHandle write at param_1+0x475dc (cell+0x14) and activeFlag write at
   * param_1+0x477e8 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x475c8, 0);
  SUBFIELD(local_4,0,undefined1) = 0x25;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x477ec),0x224,0x10,InitGuardSlot,ScrubChecksumGuard)
  ;
  SUBFIELD(local_4,0,undefined1) = 0x26;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x49a4c),0x224,0x30,InitGuardSlot,ScrubChecksumGuard)
  ;
  SUBFIELD(local_4,0,undefined1) = 0x27;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x50240),0x224,0x40,InitGuardSlot,ScrubChecksumGuard)
  ;
  SUBFIELD(local_4,0,undefined1) = 0x28;
  *(undefined1 *)(param_1 + 0x593b0) = 0;
  *(undefined4 *)(param_1 + 0x591a4) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4162a0
   * (`0x41628b: lea edi,[ebp + 0x59190]`) the cell is param_1 + 0x59190; tableHandle write at param_1+0x591a4 (cell+0x14) and activeFlag write at
   * param_1+0x593b0 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x59190, 0);
  SUBFIELD(local_4,0,undefined1) = 0x29;
  *(undefined1 *)(param_1 + 0x595d4) = 0;
  *(undefined4 *)(param_1 + 0x593c8) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4162ba
   * (`0x4162a5: lea edi,[ebp + 0x593b4]`) the cell is param_1 + 0x593b4; tableHandle write at param_1+0x593c8 (cell+0x14) and activeFlag write at
   * param_1+0x595d4 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x593b4, 0);
  SUBFIELD(local_4,0,undefined1) = 0x2a;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x595d8),0x224,0xc,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x2b;
  *(undefined1 *)(param_1 + 0x5b1a8) = 0;
  *(undefined4 *)(param_1 + 0x5af9c) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4162f6
   * (`0x4162e1: lea edi,[ebp + 0x5af88]`) the cell is param_1 + 0x5af88; tableHandle write at param_1+0x5af9c (cell+0x14) and activeFlag write at
   * param_1+0x5b1a8 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x5af88, 0);
  SUBFIELD(local_4,0,undefined1) = 0x2c;
  *(undefined1 *)(param_1 + 0x5b3cc) = 0;
  *(undefined4 *)(param_1 + 0x5b1c0) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416310
   * (`0x4162fb: lea edi,[ebp + 0x5b1ac]`) the cell is param_1 + 0x5b1ac; tableHandle write at param_1+0x5b1c0 (cell+0x14) and activeFlag write at
   * param_1+0x5b3cc (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x5b1ac, 0);
  SUBFIELD(local_4,0,undefined1) = 0x2d;
  *(undefined1 *)(param_1 + 0x5b5f0) = 0;
  *(undefined4 *)(param_1 + 0x5b3e4) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x41632a
   * (`0x416315: lea edi,[ebp + 0x5b3d0]`) the cell is param_1 + 0x5b3d0; tableHandle write at param_1+0x5b3e4 (cell+0x14) and activeFlag write at
   * param_1+0x5b5f0 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x5b3d0, 0);
  SUBFIELD(local_4,0,undefined1) = 0x2e;
  *(undefined1 *)(param_1 + 0x5b814) = 0;
  *(undefined4 *)(param_1 + 0x5b608) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416344
   * (`0x41632f: lea edi,[ebp + 0x5b5f4]`) the cell is param_1 + 0x5b5f4; tableHandle write at param_1+0x5b608 (cell+0x14) and activeFlag write at
   * param_1+0x5b814 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x5b5f4, 0);
  SUBFIELD(local_4,0,undefined1) = 0x2f;
  InitGuardedBool();
  *(undefined1 *)(param_1 + 0x5ba7c) = 0;
  *(undefined4 *)(param_1 + 0x5b870) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416369
   * (`0x416359: lea edi,[ebp + 0x5b85c]`) the cell is param_1 + 0x5b85c; tableHandle write at param_1+0x5b870 (cell+0x14) and activeFlag write at
   * param_1+0x5ba7c (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x5b85c, 0);
  SUBFIELD(local_4,0,undefined1) = 0x30;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x5ba80),0x224,8,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x31;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x5cba0),0x224,8,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x32;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x5dcc0),0x224,8,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x33;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x5ede0),0x224,8,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x34;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x5ff00),0x224,8,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x35;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x61020),0x224,8,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x36;
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  *(undefined1 *)(param_1 + 0x62408) = 0;
  *(undefined4 *)(param_1 + 0x621fc) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x41649c
   * (`0x41648c: lea edi,[ebp + 0x621e8]`) the cell is param_1 + 0x621e8; tableHandle write at param_1+0x621fc (cell+0x14) and activeFlag write at
   * param_1+0x62408 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x621e8, 0);
  SUBFIELD(local_4,0,undefined1) = 0x37;
  *(undefined1 *)(param_1 + 0x6262c) = 0;
  *(undefined4 *)(param_1 + 0x62420) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4164b6
   * (`0x4164a1: lea edi,[ebp + 0x6240c]`) the cell is param_1 + 0x6240c; tableHandle write at param_1+0x62420 (cell+0x14) and activeFlag write at
   * param_1+0x6262c (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x6240c, 0);
  SUBFIELD(local_4,0,undefined1) = 0x38;
  *(undefined1 *)(param_1 + 0x62850) = 0;
  *(undefined4 *)(param_1 + 0x62644) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4164d0
   * (`0x4164bb: lea edi,[ebp + 0x62630]`) the cell is param_1 + 0x62630; tableHandle write at param_1+0x62644 (cell+0x14) and activeFlag write at
   * param_1+0x62850 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x62630, 0);
  SUBFIELD(local_4,0,undefined1) = 0x39;
  _eh_vector_constructor_iterator_
            ((void *)(param_1 + 0x62854),0x224,0x400,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x3a;
  *(undefined1 *)(param_1 + 0xeba74) = 0;
  *(undefined4 *)(param_1 + 0xeb868) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x41650f
   * (`0x4164fa: lea edi,[ebp + 0xeb854]`) the cell is param_1 + 0xeb854; tableHandle write at param_1+0xeb868 (cell+0x14) and activeFlag write at
   * param_1+0xeba74 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0xeb854, 0);
  SUBFIELD(local_4,0,undefined1) = 0x3b;
  *(undefined1 *)(param_1 + 0xebcb8) = 0;
  *(undefined4 *)(param_1 + 0xebaac) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416529
   * (`0x416514: lea edi,[ebp + 0xeba98]`) the cell is param_1 + 0xeba98; tableHandle write at param_1+0xebaac (cell+0x14) and activeFlag write at
   * param_1+0xebcb8 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0xeba98, 0);
  SUBFIELD(local_4,0,undefined1) = 0x3c;
  *(undefined1 *)(param_1 + 0xebedc) = 0;
  *(undefined4 *)(param_1 + 0xebcd0) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416543
   * (`0x41652e: lea edi,[ebp + 0xebcbc]`) the cell is param_1 + 0xebcbc; tableHandle write at param_1+0xebcd0 (cell+0x14) and activeFlag write at
   * param_1+0xebedc (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0xebcbc, 0);
  SUBFIELD(local_4,0,undefined1) = 0x3d;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0xebef4),0x224,8,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x3e;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0xed014),0x224,8,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x3f;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0xee134),0x224,8,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x40;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0xef254),0x224,8,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x41;
  _eh_vector_constructor_iterator_
            ((void *)(param_1 + 0xf0384),0xb1ac,0x10,FUN_00416c20,FUN_004174c0);
  SUBFIELD(local_4,0,undefined1) = 0x42;
  _eh_vector_constructor_iterator_
            ((void *)(param_1 + 0x1a1e48),0x7d28,0x80,FUN_00418540,FUN_004186b0);
  SUBFIELD(local_4,0,undefined1) = 0x43;
  _eh_vector_constructor_iterator_
            ((void *)((int)&g_abItemRecords + param_1),0x9bc,100,InitItemRecord,DestroyItemRecord);
  SUBFIELD(local_4,0,undefined1) = 0x44;
  _eh_vector_constructor_iterator_(&DAT_005c7fb8 + param_1,0x157c,0x20,FUN_00418a10,FUN_00418b90);
  SUBFIELD(local_4,0,undefined1) = 0x45;
  InitGuardedBool();
  _eh_vector_constructor_iterator_(&DAT_005f3774 + param_1,0x224,8,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x46;
  (&DAT_005f4ab4)[param_1] = 0;
  *(undefined4 *)(&DAT_005f48a8 + param_1) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x41669d
   * (`0x416688: lea edi,[ebp + 0x5f4894]`) the cell is (int)&DAT_005f4894 + param_1; tableHandle write at &DAT_005f48a8+param_1 (cell+0x14) and activeFlag
   * write at &DAT_005f4ab4+param_1 (cell+0x220), both just above, confirm
   * the cell; DAT_005f4894 is also used directly as a g_clientContext-
   * relative cell in State07_AvatarStore_ProcessPacket.c.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)&DAT_005f4894 + param_1, 0);
  SUBFIELD(local_4,0,undefined1) = 0x47;
  _eh_vector_constructor_iterator_(&DAT_005f4ab8 + param_1,0x224,4,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x48;
  _eh_vector_constructor_iterator_(&DAT_005f5348 + param_1,0x224,0x400,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x49;
  InitGuardedBool();
  (&DAT_0067e5f0)[param_1] = 0;
  *(undefined4 *)(&DAT_0067e3e4 + param_1) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416709
   * (`0x4166f9: lea edi,[ebp + 0x67e3d0]`) the cell is (int)&DAT_0067e3d0 + param_1; tableHandle write at &DAT_0067e3e4+param_1 (cell+0x14) and activeFlag
   * write at &DAT_0067e5f0+param_1 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)&DAT_0067e3d0 + param_1, 0);
  SUBFIELD(local_4,0,undefined1) = 0x4a;
  (&DAT_0067e814)[param_1] = 0;
  *(undefined4 *)(&DAT_0067e608 + param_1) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416723
   * (`0x41670e: lea edi,[ebp + 0x67e5f4]`) the cell is (int)&DAT_0067e5f4 + param_1; tableHandle write at &DAT_0067e608+param_1 (cell+0x14) and activeFlag
   * write at &DAT_0067e814+param_1 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)&DAT_0067e5f4 + param_1, 0);
  SUBFIELD(local_4,0,undefined1) = 0x4b;
  (&DAT_0067ea38)[param_1] = 0;
  *(undefined4 *)(&DAT_0067e82c + param_1) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x41673d
   * (`0x416728: lea edi,[ebp + 0x67e818]`) the cell is (int)&DAT_0067e818 + param_1; tableHandle write at &DAT_0067e82c+param_1 (cell+0x14) and activeFlag
   * write at &DAT_0067ea38+param_1 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)&DAT_0067e818 + param_1, 0);
  SUBFIELD(local_4,0,undefined1) = 0x4c;
  (&DAT_0067ec5c)[param_1] = 0;
  *(undefined4 *)(&DAT_0067ea50 + param_1) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416757
   * (`0x416742: lea edi,[ebp + 0x67ea3c]`) the cell is (int)&DAT_0067ea3c + param_1; tableHandle write at &DAT_0067ea50+param_1 (cell+0x14) and activeFlag
   * write at &DAT_0067ec5c+param_1 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)&DAT_0067ea3c + param_1, 0);
  *(undefined4 *)(&DAT_0067ec60 + param_1) = 0;
  *(undefined4 *)(&DAT_0067ec64 + param_1) = 0;
  *(undefined4 *)(&DAT_0067ec68 + param_1) = 0;
  *(undefined4 *)(&DAT_0067ec6c + param_1) = 0;
  SUBFIELD(local_4,0,undefined1) = 0x4e;
  _eh_vector_constructor_iterator_(&DAT_0069ec74 + param_1,0x18,0x400,FUN_00401350,FUN_00401370);
  *(undefined4 *)(&DAT_0067ec70 + param_1) = 0;
  puVar4 = (undefined4 *)(&DAT_0067ec74 + param_1);
  for (iVar1 = 0x8000; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = (undefined4 *)(&DAT_0069ec74 + param_1);
  for (iVar1 = 0x1800; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  SUBFIELD(local_4,0,undefined1) = 0x4f;
  *(undefined4 *)(&DAT_006a4c78 + param_1) = 0;
  *(undefined4 *)(&DAT_006a4c74 + param_1) = 0;
  (&DAT_006a6480)[param_1] = 1;
  (&DAT_006a6481)[param_1] = 1;
  *(undefined4 *)(&DAT_006a6484 + param_1) = 0;
  *(undefined4 *)(&DAT_006a6488 + param_1) = 0;
  (&DAT_006a648c)[param_1] = 0;
  (&DAT_006a648d)[param_1] = 0;
  *(undefined4 *)(&DAT_006a6490 + param_1) = 0;
  *(undefined4 *)(&DAT_006a6494 + param_1) = 0;
  (&DAT_006a6498)[param_1] = 0;
  (&DAT_006a6499)[param_1] = 0;
  *(undefined4 *)(&DAT_006a649c + param_1) = 0;
  *(undefined4 *)(&DAT_006a64a0 + param_1) = 0;
  *(undefined4 *)(&DAT_006a64b8 + param_1) = 0;
  FUN_004e1d50(&DAT_006a64c4 + param_1);
  *(undefined4 *)(&DAT_006a76f4 + param_1) = 0;
  *(undefined4 *)(&DAT_006a76f8 + param_1) = 0;
  *(undefined4 *)(&DAT_006a76fc + param_1) = 0;
  *(undefined4 *)(&DAT_006a7700 + param_1) = 0;
  SUBFIELD(local_4,0,undefined1) = 0x51;
  FUN_004e3810(&DAT_006a7708 + param_1);
  FUN_0042b010();
  SUBFIELD(local_4,0,undefined1) = 0x53;
  FUN_004f2e40();
  *(undefined ***)(&DAT_006a7f88 + param_1) = &PTR_FUN_00555b7c;
  SUBFIELD(local_4,0,undefined1) = 0x54;
  InitGuardedBool();
  (&DAT_006a81b4)[param_1] = 0;
  *(undefined4 *)(&DAT_006a7fa8 + param_1) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x41688b
   * (`0x41687b: lea edi,[ebp + 0x6a7f94]`) the cell is (int)&DAT_006a7fa8 + param_1 - 0x14; the tableHandle write two lines above is &DAT_006a7fa8+param_1 (cell+0x14,
   * no direct DAT_006a7f94 symbol exists) and the activeFlag write is
   * &DAT_006a81b4+param_1 (cell+0x220), confirming the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)&DAT_006a7fa8 + param_1 - 0x14, 0);
  SUBFIELD(local_4,0,undefined1) = 0x55;
  _eh_vector_constructor_iterator_(&DAT_006a81b8 + param_1,0x224,6,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x56;
  _eh_vector_constructor_iterator_(&DAT_006a8e90 + param_1,0x224,6,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x57;
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  (&DAT_006a9d98)[param_1] = 0;
  *(undefined4 *)(&DAT_006a9b8c + param_1) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x41690a
   * (`0x4168fa: lea edi,[ebp + 0x6a9b78]`) the cell is (int)&DAT_006a9b8c + param_1 - 0x14; the tableHandle write two lines above is &DAT_006a9b8c+param_1 (cell+0x14,
   * no direct DAT_006a9b78 symbol exists) and the activeFlag write is
   * &DAT_006a9d98+param_1 (cell+0x220), confirming the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)&DAT_006a9b8c + param_1 - 0x14, 0);
  SUBFIELD(local_4,0,undefined1) = 0x58;
  (&DAT_006a9fbc)[param_1] = 0;
  *(undefined4 *)(&DAT_006a9db0 + param_1) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416924
   * (`0x41690f: lea edi,[ebp + 0x6a9d9c]`) the cell is (int)&DAT_006a9db0 + param_1 - 0x14; the tableHandle write two lines above is &DAT_006a9db0+param_1 (cell+0x14,
   * no direct DAT_006a9d9c symbol exists) and the activeFlag write is
   * &DAT_006a9fbc+param_1 (cell+0x220), confirming the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)&DAT_006a9db0 + param_1 - 0x14, 0);
  SUBFIELD(local_4,0,undefined1) = 0x59;
  (&DAT_006aa1e0)[param_1] = 0;
  *(undefined4 *)(&DAT_006a9fd4 + param_1) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x41693e
   * (`0x416929: lea edi,[ebp + 0x6a9fc0]`) the cell is (int)&DAT_006a9fd4 + param_1 - 0x14; the tableHandle write two lines above is &DAT_006a9fd4+param_1 (cell+0x14,
   * no direct DAT_006a9fc0 symbol exists) and the activeFlag write is
   * &DAT_006aa1e0+param_1 (cell+0x220), confirming the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)&DAT_006a9fd4 + param_1 - 0x14, 0);
  SUBFIELD(local_4,0,undefined1) = 0x5a;
  (&DAT_006aa404)[param_1] = 0;
  *(undefined4 *)(&DAT_006aa1f8 + param_1) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416958
   * (`0x416943: lea edi,[ebp + 0x6aa1e4]`) the cell is (int)&DAT_006aa1f8 + param_1 - 0x14; the tableHandle write two lines above is &DAT_006aa1f8+param_1 (cell+0x14,
   * no direct DAT_006aa1e4 symbol exists) and the activeFlag write is
   * &DAT_006aa404+param_1 (cell+0x220), confirming the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)&DAT_006aa1f8 + param_1 - 0x14, 0);
  FUN_004fe420(0x3f400000,0x3e800000,0x40100000);
  FUN_004fe420(0x3f400000,0x3e800000,0x40100000);
  SUBFIELD(local_4,0,undefined1) = 0x5d;
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  _eh_vector_constructor_iterator_(&DAT_006aa630 + param_1,4,10,FUN_00426410,FUN_00405320);
  SUBFIELD(local_4,0,undefined1) = 0x5e;
  InitGuardedBool();
  (&DAT_006aa89c)[param_1] = 0;
  *(undefined4 *)(&DAT_006aa690 + param_1) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416a07
   * (`0x4169f7: lea edi,[ebp + 0x6aa67c]`) the cell is (int)&DAT_006aa67c + param_1; tableHandle write at &DAT_006aa690+param_1 (cell+0x14) and activeFlag
   * write at &DAT_006aa89c+param_1 (cell+0x220), both just above, confirm the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)&DAT_006aa67c + param_1, 0);
  SUBFIELD(local_4,0,undefined1) = 0x5f;
  (&DAT_006aaac0)[param_1] = 0;
  *(undefined4 *)(&DAT_006aa8b4 + param_1) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416a21
   * (`0x416a0c: lea edi,[ebp + 0x6aa8a0]`) the cell is (int)&DAT_006aa8b4 + param_1 - 0x14; the tableHandle write two lines above is &DAT_006aa8b4+param_1 (cell+0x14,
   * no direct DAT_006aa8a0 symbol exists) and the activeFlag write is
   * &DAT_006aaac0+param_1 (cell+0x220), confirming the cell.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)&DAT_006aa8b4 + param_1 - 0x14, 0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x60);
  *(undefined4 *)(param_1 + 0x3f804) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x41340) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x44e60) = 0xffffffff;
  *(undefined4 *)(&DAT_005f2f3c + param_1) = 0;
  puVar4 = (undefined4 *)(&DAT_005f325c + param_1);
  for (iVar1 = 0x140; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  *(undefined4 *)(&DAT_005f375c + param_1) = 0;
  *(undefined4 *)(&DAT_005f3760 + param_1) = 0;
  puVar4 = (undefined4 *)(&DAT_005f2f58 + param_1);
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0xffffffff;
    puVar4 = puVar4 + 1;
  }
  puVar4 = (undefined4 *)(&DAT_005f3058 + param_1);
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0xffffffff;
    puVar4 = puVar4 + 1;
  }
  puVar4 = (undefined4 *)(&DAT_005f3158 + param_1);
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0xffffffff;
    puVar4 = puVar4 + 1;
  }
  *(undefined4 *)(&DAT_005f3258 + param_1) = 0;
  *(undefined1 *)(param_1 + 0xebee4) = 1;
  puVar4 = (undefined4 *)(&DAT_0067e348 + param_1);
  for (iVar1 = 0x20; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  g_clientContext = param_1;
  *(undefined4 *)(&DAT_0067e3c8 + param_1) = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = _rand();
  *(char *)(param_1 + 0x23310) = (char)iVar1;
  iVar1 = _rand();
  *(byte *)(param_1 + 0x23311) = (byte)iVar1;
  bVar2 = *(byte *)(param_1 + 0x23310) & 7;
  bVar2 = ~('\x01' << bVar2) & (byte)iVar1 | '\0' << bVar2;
  *(byte *)(param_1 + 0x23311) = bVar2;
  *(byte *)(param_1 + 0x23312) = bVar2 + *(char *)(param_1 + 0x23310) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (*(void **)(param_1 + 0x44be8) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x44be8));
    *(undefined4 *)(param_1 + 0x44be8) = 0;
  }
  *(undefined4 *)(param_1 + 0x44bec) = 0;
  *(undefined4 *)(param_1 + 0x44bf0) = 0;
  *(undefined4 *)(&g_replayFileHandle + param_1) = 0;
  puVar4 = (undefined4 *)(&DAT_006aa47c + param_1);
  for (iVar1 = 0x60; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  *(undefined4 *)(&DAT_006aa5fc + param_1) = 0;
  (&DAT_006aa600)[param_1] = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = _rand();
  (&DAT_006aa678)[param_1] = (byte)iVar1;
  iVar1 = _rand();
  bVar2 = (&DAT_006aa678)[param_1];
  (&DAT_006aa679)[param_1] = (byte)iVar1;
  bVar3 = bVar2 & 7;
  bVar3 = ~('\x01' << bVar3) & (byte)iVar1 | '\0' << bVar3;
  (&DAT_006aa679)[param_1] = bVar3;
  (&DAT_006aa67a)[param_1] = bVar2 + bVar3 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined1 *)(param_1 + 0x457a0) = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x416bf6
   * (`0x416bf0: lea edi,[ebp + 0x449c4]`) the cell is param_1 + 0x449c4; same cell as the call at 0x4160a0 above (param_1+0x449c4), reused here
   * under the trailing EnterCriticalSection/LeaveCriticalSection pair.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x449c4, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

