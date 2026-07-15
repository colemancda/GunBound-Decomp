/* InitProjectile - 0x00454dc0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * __thiscall InitProjectile(undefined4 param_1,undefined4 *param_2,undefined4 param_3)

{
  int iVar1;
  byte bVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_0053ab3b;
  *unaff_FS_OFFSET = &local_c;
  param_2[1] = param_3;
  param_2[2] = param_1;
  param_2[3] = 0;
  param_2[4] = 0;
  *(undefined1 *)(param_2 + 5) = 0;
  *(undefined1 *)((int)param_2 + 0x15) = 0;
  param_2[6] = 0xffffffff;
  param_2[7] = 0;
  *(undefined1 *)(param_2 + 8) = 0;
  param_2[10] = 0;
  param_2[0xb] = 0;
  param_2[9] = 0xffffffff;
  local_4 = 0;
  *param_2 = &PTR_FUN_00555c34;
  *(undefined1 *)(param_2 + 0x98) = 0;
  param_2[0x15] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454e21
   * (`0x454e0e: lea edi,[esi + 0x40]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x40 - confirmed by the zero-writes to the matching
   * tableHandle (+0x14) and activeFlag (+0x220) fields just above this call.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x40),0);
  SUBFIELD(local_4,0,undefined1) = 1;
  *(undefined1 *)(param_2 + 0x121) = 0;
  param_2[0x9e] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454e3b
   * (`0x454e26: lea edi,[esi + 0x264]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x264 - confirmed by the zero-writes to the matching
   * tableHandle (+0x14) and activeFlag (+0x220) fields just above this call.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x264),0);
  SUBFIELD(local_4,0,undefined1) = 2;
  *(undefined1 *)(param_2 + 0x1aa) = 0;
  param_2[0x127] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454e55
   * (`0x454e40: lea edi,[esi + 0x488]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x488 - confirmed by the zero-writes to the matching
   * tableHandle (+0x14) and activeFlag (+0x220) fields just above this call.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x488),0);
  SUBFIELD(local_4,0,undefined1) = 3;
  *(undefined1 *)(param_2 + 0x233) = 0;
  param_2[0x1b0] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454e6f
   * (`0x454e5a: lea edi,[esi + 0x6ac]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x6ac - confirmed by the zero-writes to the matching
   * tableHandle (+0x14) and activeFlag (+0x220) fields just above this call.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x6ac),0);
  SUBFIELD(local_4,0,undefined1) = 4;
  *(undefined1 *)(param_2 + 700) = 0;
  param_2[0x239] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454e89
   * (`0x454e74: lea edi,[esi + 0x8d0]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x8d0 - confirmed by the zero-writes to the matching
   * tableHandle (+0x14) and activeFlag (+0x220) fields just above this call.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x8d0),0);
  SUBFIELD(local_4,0,undefined1) = 5;
  *(undefined1 *)(param_2 + 0x345) = 0;
  param_2[0x2c2] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454ea3
   * (`0x454e8e: lea edi,[esi + 0xaf4]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0xaf4 - confirmed by the zero-writes to the matching
   * tableHandle (+0x14) and activeFlag (+0x220) fields just above this call.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0xaf4),0);
  SUBFIELD(local_4,0,undefined1) = 6;
  *(undefined1 *)(param_2 + 0x3ce) = 0;
  param_2[0x34b] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454ebd
   * (`0x454ea8: lea edi,[esi + 0xd18]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0xd18 - confirmed by the zero-writes to the matching
   * tableHandle (+0x14) and activeFlag (+0x220) fields just above this call.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0xd18),0);
  SUBFIELD(local_4,0,undefined1) = 7;
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  *(undefined1 *)(param_2 + 0x45d) = 0;
  param_2[0x3da] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454f0e
   * (`0x454efe: lea edi,[esi + 0xf54]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0xf54 - confirmed by the zero-writes to the matching
   * tableHandle (+0x14) and activeFlag (+0x220) fields just above this call.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0xf54),0);
  SUBFIELD(local_4,0,undefined1) = 8;
  *(undefined1 *)(param_2 + 0x4e6) = 0;
  param_2[0x463] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454f28
   * (`0x454f13: lea edi,[esi + 0x1178]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x1178 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x1178),0);
  SUBFIELD(local_4,0,undefined1) = 9;
  *(undefined1 *)(param_2 + 0x56f) = 0;
  param_2[0x4ec] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454f42
   * (`0x454f2d: lea edi,[esi + 0x139c]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x139c - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x139c),0);
  SUBFIELD(local_4,0,undefined1) = 10;
  *(undefined1 *)(param_2 + 0x5f8) = 0;
  param_2[0x575] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454f5c
   * (`0x454f47: lea edi,[esi + 0x15c0]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x15c0 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x15c0),0);
  SUBFIELD(local_4,0,undefined1) = 0xb;
  *(undefined1 *)(param_2 + 0x681) = 0;
  param_2[0x5fe] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454f76
   * (`0x454f61: lea edi,[esi + 0x17e4]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x17e4 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x17e4),0);
  SUBFIELD(local_4,0,undefined1) = 0xc;
  *(undefined1 *)(param_2 + 0x70a) = 0;
  param_2[0x687] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454f90
   * (`0x454f7b: lea edi,[esi + 0x1a08]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x1a08 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x1a08),0);
  SUBFIELD(local_4,0,undefined1) = 0xd;
  *(undefined1 *)(param_2 + 0x793) = 0;
  param_2[0x710] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454faa
   * (`0x454f95: lea edi,[esi + 0x1c2c]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x1c2c - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x1c2c),0);
  SUBFIELD(local_4,0,undefined1) = 0xe;
  *(undefined1 *)(param_2 + 0x81d) = 0;
  param_2[0x79a] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454fc4
   * (`0x454faf: lea edi,[esi + 0x1e54]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x1e54 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x1e54),0);
  SUBFIELD(local_4,0,undefined1) = 0xf;
  *(undefined1 *)(param_2 + 0x8a6) = 0;
  param_2[0x823] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454fde
   * (`0x454fc9: lea edi,[esi + 0x2078]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x2078 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x2078),0);
  SUBFIELD(local_4,0,undefined1) = 0x10;
  *(undefined1 *)(param_2 + 0x92f) = 0;
  param_2[0x8ac] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x454ff8
   * (`0x454fe3: lea edi,[esi + 0x229c]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x229c - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x229c),0);
  SUBFIELD(local_4,0,undefined1) = 0x11;
  *(undefined1 *)(param_2 + 0x9b8) = 0;
  param_2[0x935] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x455012
   * (`0x454ffd: lea edi,[esi + 0x24c0]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x24c0 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x24c0),0);
  SUBFIELD(local_4,0,undefined1) = 0x12;
  *(undefined1 *)(param_2 + 0xa41) = 0;
  param_2[0x9be] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x45502c
   * (`0x455017: lea edi,[esi + 0x26e4]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x26e4 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x26e4),0);
  SUBFIELD(local_4,0,undefined1) = 0x13;
  *(undefined1 *)(param_2 + 0xaca) = 0;
  param_2[0xa47] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x455046
   * (`0x455031: lea edi,[esi + 0x2908]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x2908 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x2908),0);
  SUBFIELD(local_4,0,undefined1) = 0x14;
  *(undefined1 *)(param_2 + 0xb53) = 0;
  param_2[0xad0] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x455060
   * (`0x45504b: lea edi,[esi + 0x2b2c]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x2b2c - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x2b2c),0);
  SUBFIELD(local_4,0,undefined1) = 0x15;
  *(undefined1 *)(param_2 + 0xbdc) = 0;
  param_2[0xb59] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x45507a
   * (`0x455065: lea edi,[esi + 0x2d50]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x2d50 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x2d50),0);
  SUBFIELD(local_4,0,undefined1) = 0x16;
  *(undefined1 *)(param_2 + 0xc65) = 0;
  param_2[0xbe2] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x455094
   * (`0x45507f: lea edi,[esi + 0x2f74]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x2f74 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x2f74),0);
  SUBFIELD(local_4,0,undefined1) = 0x17;
  *(undefined1 *)(param_2 + 0xcee) = 0;
  param_2[0xc6b] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4550ae
   * (`0x455099: lea edi,[esi + 0x3198]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x3198 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x3198),0);
  SUBFIELD(local_4,0,undefined1) = 0x18;
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  *(undefined1 *)(param_2 + 0xd7a) = 0;
  param_2[0xcf7] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4550f4
   * (`0x4550e4: lea edi,[esi + 0x33c8]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x33c8 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x33c8),0);
  SUBFIELD(local_4,0,undefined1) = 0x19;
  *(undefined1 *)(param_2 + 0xe03) = 0;
  param_2[0xd80] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x45510e
   * (`0x4550f9: lea edi,[esi + 0x35ec]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x35ec - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x35ec),0);
  SUBFIELD(local_4,0,undefined1) = 0x1a;
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  *(undefined1 *)(param_2 + 0xed0) = 0;
  param_2[0xe4d] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x455149
   * (`0x455139: lea edi,[esi + 0x3920]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x3920 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x3920),0);
  SUBFIELD(local_4,0,undefined1) = 0x1b;
  *(undefined1 *)(param_2 + 0xf5a) = 0;
  param_2[0xed7] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x455163
   * (`0x45514e: lea edi,[esi + 0x3b48]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x3b48 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x3b48),0);
  SUBFIELD(local_4,0,undefined1) = 0x1c;
  *(undefined1 *)(param_2 + 0xfe3) = 0;
  param_2[0xf60] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x45517d
   * (`0x455168: lea edi,[esi + 0x3d6c]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x3d6c - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x3d6c),0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x1d);
  InitGuardedBool();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = _rand();
  *(char *)((int)param_2 + 0xf45) = (char)iVar1;
  iVar1 = _rand();
  *(byte *)((int)param_2 + 0xf46) = (byte)iVar1;
  bVar2 = *(byte *)((int)param_2 + 0xf45) & 7;
  bVar2 = ~('\x01' << bVar2) & (byte)iVar1 | '\0' << bVar2;
  *(byte *)((int)param_2 + 0xf46) = bVar2;
  *(byte *)((int)param_2 + 0xf47) = bVar2 + *(char *)((int)param_2 + 0xf45) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x45521e
   * (`0x455218: lea edi,[esi + 0x139c]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x139c - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x139c),0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x45523c
   * (`0x455236: lea edi,[esi + 0x15c0]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x15c0 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x15c0),0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = _rand();
  *(char *)(param_2 + 0x3d3) = (char)iVar1;
  iVar1 = _rand();
  *(byte *)((int)param_2 + 0xf4d) = (byte)iVar1;
  bVar2 = ~('\x01' << (*(byte *)(param_2 + 0x3d3) & 7)) & (byte)iVar1 |
          '\0' << (*(byte *)(param_2 + 0x3d3) & 7);
  *(byte *)((int)param_2 + 0xf4d) = bVar2;
  *(byte *)((int)param_2 + 0xf4e) = bVar2 + *(char *)(param_2 + 0x3d3) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_2[0x3d2] = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = _rand();
  *(char *)(param_2 + 0xe04) = (char)iVar1;
  iVar1 = _rand();
  *(byte *)((int)param_2 + 0x3811) = (byte)iVar1;
  bVar2 = '\x01' << (*(byte *)(param_2 + 0xe04) & 7);
  bVar2 = ~bVar2 & (byte)iVar1 | bVar2;
  *(byte *)((int)param_2 + 0x3811) = bVar2;
  *(byte *)((int)param_2 + 0x3812) = bVar2 + *(char *)(param_2 + 0xe04) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_2[0x794] = 0;
  *(undefined1 *)(param_2 + 0xf) = 0xff;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = _rand();
  *(char *)(param_2 + 0xe46) = (char)iVar1;
  iVar1 = _rand();
  *(byte *)((int)param_2 + 0x3919) = (byte)iVar1;
  bVar2 = ~('\x01' << (*(byte *)(param_2 + 0xe46) & 7)) & (byte)iVar1 |
          '\0' << (*(byte *)(param_2 + 0xe46) & 7);
  *(byte *)((int)param_2 + 0x3919) = bVar2;
  *(byte *)((int)param_2 + 0x391a) = bVar2 + *(char *)(param_2 + 0xe46) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = _rand();
  *(char *)((int)param_2 + 0x391b) = (char)iVar1;
  iVar1 = _rand();
  *(byte *)(param_2 + 0xe47) = (byte)iVar1;
  bVar2 = *(byte *)((int)param_2 + 0x391b) & 7;
  bVar2 = ~('\x01' << bVar2) & (byte)iVar1 | '\0' << bVar2;
  *(byte *)(param_2 + 0xe47) = bVar2;
  *(byte *)((int)param_2 + 0x391d) = bVar2 + *(char *)((int)param_2 + 0x391b) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x455436
   * (`0x455430: lea edi,[esi + 0x3920]`) the cell is param_2 (the projectile
   * object being constructed - this function's __thiscall explicit pointer
   * arg) plus byte offset 0x3920 - confirmed by the zero-writes to the
   * matching tableHandle (+0x14) and activeFlag (+0x220) fields just above
   * this call. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((void *)((int)param_2 + 0x3920),0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_2[0xed1] = 0;
  param_2[0xfe4] = 3;
  param_2[0x3d4] = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = _rand();
  *(char *)((int)param_2 + 0xf42) = (char)iVar1;
  iVar1 = _rand();
  *(byte *)((int)param_2 + 0xf43) = (byte)iVar1;
  bVar2 = '\x01' << (*(byte *)((int)param_2 + 0xf42) & 7);
  bVar2 = ~bVar2 & (byte)iVar1 | bVar2;
  *(byte *)((int)param_2 + 0xf43) = bVar2;
  *(byte *)(param_2 + 0x3d1) = bVar2 + *(byte *)((int)param_2 + 0xf42) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = _rand();
  *(char *)(param_2 + 0xfe6) = (char)iVar1;
  iVar1 = _rand();
  *(byte *)((int)param_2 + 0x3f99) = (byte)iVar1;
  bVar2 = *(byte *)(param_2 + 0xfe6) & 7;
  bVar2 = ~('\x01' << bVar2) & (byte)iVar1 | '\0' << bVar2;
  *(byte *)((int)param_2 + 0x3f99) = bVar2;
  *(byte *)((int)param_2 + 0x3f9a) = bVar2 + *(byte *)(param_2 + 0xfe6) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *unaff_FS_OFFSET = local_c;
  return param_2;
}

