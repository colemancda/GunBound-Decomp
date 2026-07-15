/* FUN_00477bb0 - 0x00477bb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_00477bb0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  byte bVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_00539e53;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  param_1[2] = param_2;
  param_1[1] = 0x186a6;
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
  *param_1 = &PTR_FUN_00555fdc;
  *(undefined1 *)(param_1 + 0x96) = 0;
  param_1[0x13] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477c16
   * (`0x477c03: lea edi,[esi + 0x38]`) the cell is param_1 (this object being
   * constructed) plus byte offset 0x38 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x38),0);
  local_4 = 1;
  *(undefined1 *)(param_1 + 0x11f) = 0;
  param_1[0x9c] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477c30
   * (`0x477c1b: lea edi,[esi + 0x25c]`) the cell is param_1 (this object being
   * constructed) plus byte offset 0x25c - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x25c),0);
  local_4 = 2;
  *(undefined1 *)(param_1 + 0x1a8) = 0;
  param_1[0x125] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477c4a
   * (`0x477c35: lea edi,[esi + 0x480]`) the cell is param_1 (this object being
   * constructed) plus byte offset 0x480 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x480),0);
  local_4 = 3;
  *(undefined1 *)(param_1 + 0x231) = 0;
  param_1[0x1ae] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477c64
   * (`0x477c4f: lea edi,[esi + 0x6a4]`) the cell is param_1 (this object being
   * constructed) plus byte offset 0x6a4 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x6a4),0);
  local_4 = 4;
  *(undefined1 *)(param_1 + 0x2ba) = 0;
  param_1[0x237] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477c7e
   * (`0x477c69: lea edi,[esi + 0x8c8]`) the cell is param_1 (this object being
   * constructed) plus byte offset 0x8c8 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x8c8),0);
  local_4 = 5;
  *(undefined1 *)(param_1 + 0x344) = 0;
  param_1[0x2c1] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477c98
   * (`0x477c83: lea edi,[esi + 0xaf0]`) the cell is param_1 (this object being
   * constructed) plus byte offset 0xaf0 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0xaf0),0);
  local_4 = 6;
  *(undefined1 *)(param_1 + 0x3cd) = 0;
  param_1[0x34a] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477cb2
   * (`0x477c9d: lea edi,[esi + 0xd14]`) the cell is param_1 (this object being
   * constructed) plus byte offset 0xd14 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0xd14),0);
  local_4 = 7;
  InitGuardedBool();
  InitGuardedBool();
  *(undefined1 *)(param_1 + 0x458) = 0;
  param_1[0x3d5] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477ce2
   * (`0x477cd2: lea edi,[esi + 0xf40]`) the cell is param_1 (this object being
   * constructed) plus byte offset 0xf40 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0xf40),0);
  local_4 = 8;
  *(undefined1 *)(param_1 + 0x4e1) = 0;
  param_1[0x45e] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477cfc
   * (`0x477ce7: lea edi,[esi + 0x1164]`) the cell is param_1 (this object
   * being constructed) plus byte offset 0x1164 - confirmed by the zero-writes
   * to the matching tableHandle (+0x14) and activeFlag (+0x220) fields just
   * above this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x1164),0);
  local_4 = 9;
  *(undefined1 *)(param_1 + 0x56a) = 0;
  param_1[0x4e7] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477d16
   * (`0x477d01: lea edi,[esi + 0x1388]`) the cell is param_1 (this object
   * being constructed) plus byte offset 0x1388 - confirmed by the zero-writes
   * to the matching tableHandle (+0x14) and activeFlag (+0x220) fields just
   * above this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x1388),0);
  local_4 = 10;
  *(undefined1 *)(param_1 + 0x5f3) = 0;
  param_1[0x570] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477d30
   * (`0x477d1b: lea edi,[esi + 0x15ac]`) the cell is param_1 (this object
   * being constructed) plus byte offset 0x15ac - confirmed by the zero-writes
   * to the matching tableHandle (+0x14) and activeFlag (+0x220) fields just
   * above this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x15ac),0);
  local_4 = 0xb;
  *(undefined1 *)(param_1 + 0x67c) = 0;
  param_1[0x5f9] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477d4a
   * (`0x477d35: lea edi,[esi + 0x17d0]`) the cell is param_1 (this object
   * being constructed) plus byte offset 0x17d0 - confirmed by the zero-writes
   * to the matching tableHandle (+0x14) and activeFlag (+0x220) fields just
   * above this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x17d0),0);
  local_4 = 0xc;
  *(undefined1 *)(param_1 + 0x705) = 0;
  param_1[0x682] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477d64
   * (`0x477d4f: lea edi,[esi + 0x19f4]`) the cell is param_1 (this object
   * being constructed) plus byte offset 0x19f4 - confirmed by the zero-writes
   * to the matching tableHandle (+0x14) and activeFlag (+0x220) fields just
   * above this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x19f4),0);
  local_4 = 0xd;
  InitGuardedBool();
  *(undefined1 *)(param_1 + 0x78f) = 0;
  param_1[0x70c] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477d89
   * (`0x477d79: lea edi,[esi + 0x1c1c]`) the cell is param_1 (this object
   * being constructed) plus byte offset 0x1c1c - confirmed by the zero-writes
   * to the matching tableHandle (+0x14) and activeFlag (+0x220) fields just
   * above this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x1c1c),0);
  param_1[0x790] = 0;
  param_1[0x791] = 0;
  param_1[0x792] = 0;
  param_1[0x793] = 0;
  local_4 = 0xf;
  *(undefined1 *)(param_1 + 0x81c) = 0;
  param_1[0x799] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477dbb
   * (`0x477da6: lea edi,[esi + 0x1e50]`) the cell is param_1 (this object
   * being constructed) plus byte offset 0x1e50 - confirmed by the zero-writes
   * to the matching tableHandle (+0x14) and activeFlag (+0x220) fields just
   * above this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x1e50),0);
  local_4 = 0x10;
  *(undefined1 *)(param_1 + 0x8a5) = 0;
  param_1[0x822] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477dd5
   * (`0x477dc0: lea edi,[esi + 0x2074]`) the cell is param_1 (this object
   * being constructed) plus byte offset 0x2074 - confirmed by the zero-writes
   * to the matching tableHandle (+0x14) and activeFlag (+0x220) fields just
   * above this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x2074),0);
  local_4 = 0x11;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477df0
   * (`0x477ded: lea edi,[esi + 0x38]`) the cell is param_1 (this object being
   * constructed) plus byte offset 0x38 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x38),0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477e0e
   * (`0x477e08: lea edi,[esi + 0x480]`) the cell is param_1 (this object being
   * constructed) plus byte offset 0x480 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x480),0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477e37
   * (`0x477e31: lea edi,[esi + 0x25c]`) the cell is param_1 (this object being
   * constructed) plus byte offset 0x25c - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x25c),uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477e55
   * (`0x477e4f: lea edi,[esi + 0x6a4]`) the cell is param_1 (this object being
   * constructed) plus byte offset 0x6a4 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x6a4),0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477e73
   * (`0x477e6d: lea edi,[esi + 0x8c8]`) the cell is param_1 (this object being
   * constructed) plus byte offset 0x8c8 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x8c8),0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_1[699] = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477e97
   * (`0x477e91: lea edi,[esi + 0x19f4]`) the cell is param_1 (this object
   * being constructed) plus byte offset 0x19f4 - confirmed by the zero-writes
   * to the matching tableHandle (+0x14) and activeFlag (+0x220) fields just
   * above this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x19f4),0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *(char *)(param_1 + 0x3ce) = (char)iVar2;
  iVar2 = _rand();
  *(byte *)((int)param_1 + 0xf39) = (byte)iVar2;
  bVar3 = ~('\x01' << (*(byte *)(param_1 + 0x3ce) & 7)) & (byte)iVar2 |
          '\0' << (*(byte *)(param_1 + 0x3ce) & 7);
  *(byte *)((int)param_1 + 0xf39) = bVar3;
  *(byte *)((int)param_1 + 0xf3a) = bVar3 + *(char *)(param_1 + 0x3ce) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *(char *)((int)param_1 + 0xf3b) = (char)iVar2;
  iVar2 = _rand();
  *(byte *)(param_1 + 0x3cf) = (byte)iVar2;
  bVar3 = *(byte *)((int)param_1 + 0xf3b) & 7;
  bVar3 = ~('\x01' << bVar3) & (byte)iVar2 | '\0' << bVar3;
  *(byte *)(param_1 + 0x3cf) = bVar3;
  *(byte *)((int)param_1 + 0xf3d) = *(byte *)((int)param_1 + 0xf3b) + bVar3 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477fa0
   * (`0x477f9a: lea edi,[esi + 0x1164]`) the cell is param_1 (this object
   * being constructed) plus byte offset 0x1164 - confirmed by the zero-writes
   * to the matching tableHandle (+0x14) and activeFlag (+0x220) fields just
   * above this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x1164),0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477fbe
   * (`0x477fb8: lea edi,[esi + 0x1388]`) the cell is param_1 (this object
   * being constructed) plus byte offset 0x1388 - confirmed by the zero-writes
   * to the matching tableHandle (+0x14) and activeFlag (+0x220) fields just
   * above this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x1388),0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477fdc
   * (`0x477fd6: lea edi,[esi + 0x15ac]`) the cell is param_1 (this object
   * being constructed) plus byte offset 0x15ac - confirmed by the zero-writes
   * to the matching tableHandle (+0x14) and activeFlag (+0x220) fields just
   * above this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x15ac),0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477ffa
   * (`0x477ff4: lea edi,[esi + 0x17d0]`) the cell is param_1 (this object
   * being constructed) plus byte offset 0x17d0 - confirmed by the zero-writes
   * to the matching tableHandle (+0x14) and activeFlag (+0x220) fields just
   * above this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x17d0),0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *(char *)(param_1 + 0x706) = (char)iVar2;
  iVar2 = _rand();
  *(byte *)((int)param_1 + 0x1c19) = (byte)iVar2;
  bVar3 = *(byte *)(param_1 + 0x706) & 7;
  bVar3 = ~('\x01' << bVar3) & (byte)iVar2 | '\0' << bVar3;
  *(byte *)((int)param_1 + 0x1c19) = bVar3;
  *(byte *)((int)param_1 + 0x1c1a) = *(byte *)(param_1 + 0x706) + bVar3 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x47808f
   * (`0x478089: lea edi,[esi + 0x1c1c]`) the cell is param_1 (this object
   * being constructed) plus byte offset 0x1c1c - confirmed by the zero-writes
   * to the matching tableHandle (+0x14) and activeFlag (+0x220) fields just
   * above this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_1 + 0x1c1c),0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

