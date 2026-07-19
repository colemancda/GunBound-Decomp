/* SpawnSuperShot - 0x0042de70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x0042e5f3) */

void SpawnSuperShot(undefined1 param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7,undefined4 param_8,undefined4 param_9,undefined4 param_10,int param_11)

{
  byte *pbVar1;
  undefined *puVar2;
  byte bVar3;
  char cVar4;
  int *piVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  char *pcVar9;
  int *piVar10;
  byte bVar11;
  undefined4 unaff_EBP;
  char *pcVar12;
  code *pcVar13;
  undefined4 unaff_EDI;
  undefined4 *unaff_FS_OFFSET;
  byte unaff_retaddr;
  undefined4 local_8b4;
  int *piStack_8b0;
  int *local_8ac;
  uint uStack_8a8;
  float fStack_8a4;
  undefined1 auStack_8a0 [12];
  int iStack_894;
  int iStack_88c;
  undefined1 auStack_680 [4];
  undefined1 auStack_67c [12];
  int iStack_670;
  int iStack_668;
  undefined1 auStack_464 [32];
  int iStack_444;
  undefined1 auStack_23c [28];
  int iStack_220;
  undefined1 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  uStack_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053db1e;
  *unaff_FS_OFFSET = &uStack_c;
  ComputeShotViewBounds();
  piVar5 = local_8ac;
  switch(param_3) {
  case 0:
    local_8b4 = operator_new(0x3fa0);
    piVar5 = (int *)0x0;
    local_4 = 0;
    if (local_8b4 != (void *)0x0) {
      piVar5 = (int *)FUN_0044d970();
    }
    local_4 = 0xffffffff;
    local_8ac = piVar5;
    iVar6 = FindPreloadedTextureByName(s_bullet1p_00553e20);
    piVar5[7] = iVar6;
    piVar5[0xfe4] = 3;
    break;
  case 1:
    local_8b4 = operator_new(0x3f9c);
    local_4 = 1;
    if (local_8b4 == (void *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)FUN_0048d8c0();
    }
    local_4 = 0xffffffff;
    local_8ac = piVar5;
    iVar6 = FindPreloadedTextureByName(s_bullet2p_00553e14);
    piVar5[7] = iVar6;
    piVar5[0xfe4] = 6;
    break;
  case 2:
    local_8b4 = operator_new(0x3fa8);
    local_4 = 2;
    if (local_8b4 == (void *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)FUN_0048b3f0();
    }
    local_4 = 0xffffffff;
    local_8ac = piVar5;
    iVar6 = FindPreloadedTextureByName(s_bullet3p_00553e08);
    piVar5[7] = iVar6;
    piVar5[0xfe4] = 1;
    SetGuardedBool(0,GB_GUARD_UNRECOVERED);
    break;
  case 3:
    local_8b4 = operator_new(0x3fa4);
    local_4 = 3;
    if (local_8b4 == (void *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)FUN_004accf0();
    }
    local_4 = 0xffffffff;
    local_8ac = piVar5;
    iVar6 = FindPreloadedTextureByName(s_bullet4p_00553dfc);
    piVar5[7] = iVar6;
    piVar5[0xfe4] = 1;
    break;
  case 4:
    local_8b4 = operator_new(0x3f9c);
    local_4 = 4;
    if (local_8b4 == (void *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)FUN_0048de40();
    }
    local_4 = 0xffffffff;
    local_8ac = piVar5;
    iVar6 = FindPreloadedTextureByName(s_bullet5p_00553df0);
    piVar5[7] = iVar6;
    piVar5[0xfe4] = 7;
    break;
  case 5:
    local_8b4 = operator_new(0x3fb0);
    local_4 = 5;
    if (local_8b4 == (void *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)FUN_00452c80();
    }
    local_4 = 0xffffffff;
    local_8ac = piVar5;
    iVar6 = FindPreloadedTextureByName(s_bullet6p_00553de4);
    piVar5[7] = iVar6;
    piVar5[0xfe4] = 1;
    SetGuardedBool(0,GB_GUARD_UNRECOVERED);
    break;
  case 6:
    local_8b4 = operator_new(0x3f9c);
    local_4 = 6;
    if (local_8b4 == (void *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)FUN_00499ed0();
    }
    local_4 = 0xffffffff;
    local_8ac = piVar5;
    iVar6 = FindPreloadedTextureByName(s_bullet7p_00553dd8);
    piVar5[7] = iVar6;
    piVar5[0xfe4] = 0xff;
    break;
  case 7:
    local_8b4 = operator_new(0x3f9c);
    local_4 = 7;
    if (local_8b4 == (void *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)FUN_004837c0();
    }
    local_4 = 0xffffffff;
    local_8ac = piVar5;
    iVar6 = FindPreloadedTextureByName(s_bullet8p_00553dcc);
    piVar5[7] = iVar6;
    piVar5[0xfe4] = 4;
    break;
  case 8:
    local_8b4 = operator_new(0x3f9c);
    local_4 = 8;
    if (local_8b4 == (void *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)FUN_004907d0();
    }
    local_4 = 0xffffffff;
    local_8ac = piVar5;
    iVar6 = FindPreloadedTextureByName(s_bullet9p_00553dc0);
    piVar5[7] = iVar6;
    piVar5[0xfe4] = 0xff;
    break;
  case 9:
    local_8b4 = operator_new(0x3fa0);
    local_4 = 9;
    if (local_8b4 == (void *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)FUN_0044f000();
    }
    local_4 = 0xffffffff;
    local_8ac = piVar5;
    iVar6 = FindPreloadedTextureByName(s_bullet10p_00553db4);
    piVar5[7] = iVar6;
    piVar5[0xfe4] = 0xff;
    break;
  case 10:
    local_8b4 = operator_new(0x3f9c);
    local_4 = 10;
    if (local_8b4 == (void *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)FUN_00475990();
    }
    local_4 = 0xffffffff;
    local_8ac = piVar5;
    iVar6 = FindPreloadedTextureByName(s_bullet11p_00553da8);
    piVar5[7] = iVar6;
    piVar5[0xfe4] = 0xff;
    break;
  case 0xb:
    local_8b4 = operator_new(0x3fa0);
    local_4 = 0xb;
    if (local_8b4 == (void *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)FUN_004ae370();
    }
    local_4 = 0xffffffff;
    local_8ac = piVar5;
    iVar6 = FindPreloadedTextureByName(s_bullet12p_00553d9c);
    piVar5[7] = iVar6;
    piVar5[0xfe4] = 0xff;
    break;
  case 0xc:
    local_8b4 = operator_new(0x42d8);
    local_4 = 0xc;
    if (local_8b4 == (void *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)FUN_004856d0(local_8b4);
    }
    local_4 = 0xffffffff;
    piVar5[0x10b5] = 0xf80ffff;
    local_8ac = piVar5;
    iVar6 = FindPreloadedTextureByName(s_bullet13p_00553d90);
    piVar5[7] = iVar6;
    piVar5[0xfe4] = 6;
    break;
  case 0xd:
    local_8b4 = operator_new(0x3f9c);
    local_4 = 0xd;
    if (local_8b4 == (void *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)FUN_0046ca40();
    }
    local_4 = 0xffffffff;
    local_8ac = piVar5;
    iVar6 = FindPreloadedTextureByName(s_bullet14p_00553d84);
    piVar5[7] = iVar6;
    piVar5[0xfe4] = 0xff;
    break;
  case 0xe:
    local_8b4 = operator_new(0x3fa0);
    local_4 = 0xe;
    if (local_8b4 == (void *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)FUN_0047de30();
    }
    local_4 = 0xffffffff;
    local_8ac = piVar5;
    iVar6 = FindPreloadedTextureByName(s_bullet15p_00553d78);
    piVar5[7] = iVar6;
    piVar5[0xfe4] = 0xff;
    break;
  case 0xf:
    local_8b4 = operator_new(0x3f9c);
    local_4 = 0xf;
    if (local_8b4 == (void *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)FUN_00467a50();
    }
    local_4 = 0xffffffff;
    local_8ac = piVar5;
    iVar6 = FindPreloadedTextureByName(s_bullet16p_00553d6c);
    piVar5[7] = iVar6;
    piVar5[0xfe4] = 0xf1;
  }
  if (*(char *)(g_clientContext + 0x45578) == '\0') {
    piVar5[6] = param_3 * 2 + 0x1a2c;
    piVar5[0xe25] = param_3 + 0x2008;
    _sprintf((char *)(piVar5 + 0xe26),s_flame_d3_00553d60,param_3 + 1);
  }
  else if (*(char *)(g_clientContext + 0x45578) == '\x01') {
    piVar5[6] = 6000;
    piVar5[0xe25] = 8000;
    iVar6 = FindPreloadedTextureByName(s_bulletevent1p_00553d50);
    piVar5[7] = iVar6;
    piVar5[0xe26] = SUBFIELD(s_flameevent1_00553e2c,0,undefined4);
    piVar5[0xe27] = SUBFIELD(s_flameevent1_00553e2c,4,undefined4);
    piVar5[0xe28] = SUBFIELD(s_flameevent1_00553e2c,8,undefined4);
  }
  piVar5 = local_8ac;
  (**(code **)(*local_8ac + 4))(s_normal_00552230);
  *(byte *)(piVar5 + 0xf) = unaff_retaddr & 7;
  piVar5[0xe] = piVar5[6] + 1;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42e61d
   * (`lea edi,[ebx + 0xf54]`, ebx = this file's own local object pointer
   * `piVar5`, objdump-verified at 0x42e644/0x42e665/0x42e686/0x42e6aa
   * which reuse the same `ebx` for the following 4 sites): the cell is
   * piVar5+0x3d5 (== piVar5+0xf54 bytes). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(piVar5 + 0x3d5,param_4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42e644
   * (`lea edi,[ebx + 0x3b48]`): cell is piVar5+0xed2 (== piVar5+0x3b48
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar5 + 0xed2,uVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42e665
   * (`lea edi,[ebx + 0x1178]`): cell is piVar5+0x45e (== piVar5+0x1178
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar5 + 0x45e,param_5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42e686
   * (`lea edi,[ebx + 0x40]`): cell is piVar5+0x10 (== piVar5+0x40 bytes).
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar5 + 0x10,param_4 << 8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42e6aa
   * (`lea edi,[ebx + 0x264]`): cell is piVar5+0x99 (== piVar5+0x264
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar5 + 0x99,param_5 << 8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = (param_6 + 0x5a) % 0x168;
  if (iVar6 < 0) {
    iVar6 = iVar6 + 0x168;
  }
  local_8ac = *(int **)(&g_sineTable360 + iVar6 * 4);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  fStack_8a4 = (float)param_7;
  iVar8 = FloatToInt64();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42e71f
   * (`lea edi,[ebx + 0x488]`): cell is piVar5+0x122 (== piVar5+0x488
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar5 + 0x122,(iVar8 << 8) / iVar6);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42e740
   * (`lea edi,[ebx + 0x8d0]`): cell is piVar5+0x234 (== piVar5+0x8d0
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar5 + 0x234,uVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = FloatToInt64();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42e7a9
   * (`lea edi,[ebx + 0x6ac]`): cell is piVar5+0x1ab (== piVar5+0x6ac
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar5 + 0x1ab,-((iVar8 << 8) / iVar6));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = (iVar6 + 0x5a) % 0x168;
  if (iVar6 < 0) {
    iVar6 = iVar6 + 0x168;
  }
  local_8ac = *(int **)(&g_sineTable360 + iVar6 * 4);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42e834
   * (`lea edi,[ebx + 0xaf4]`, same lea also reused for the very next
   * EncodeOutgoingPacketField below - both edi_src at 0x42e81e): cell is
   * piVar5+0x2bd (== piVar5+0xaf4 bytes) - the same cell just passed to
   * FUN_0040b090/EncodeChecksumDeltaDiv below. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = FloatToInt64();
  EncodeOutgoingPacketField(piVar5 + 0x2bd,uVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8ac = (int *)FUN_0040b090(piVar5 + 0x2bd,auStack_67c,8);
  puStack_8 = (undefined1 *)0x10;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaDiv(local_8ac,auStack_8a0,uVar7);
  puStack_8 = 0x11;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(piVar5 + 0x2bd,uVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_8 = (undefined1 *)0x10;
  if (iStack_88c != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&local_8ac);
    piVar5 = piStack_8b0;
  }
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_668 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&local_8ac);
    piVar5 = piStack_8b0;
  }
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed via objdump at
   * 0x42e95c (`mov edi,ebx` at 0x42e95a; ebx reloaded from a stack spill
   * right after `add ebx,0xd18`, i.e. ebx = piVar5+0xd18 in byte units =
   * piVar5+0x346 in int* units - the same cell explicitly passed to
   * FUN_0040b090(piVar5 + 0x346, ...) a few lines below). The same
   * unchanged register value (re-read via a fresh `mov edi,ebx` each time
   * since edi itself gets clobbered by the intervening
   * PeekPacketChecksumState calls) is reused for this and the next 2
   * EncodeOutgoingPacketField sites (0x42e9ed, 0x42ea5d). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(piVar5 + 0x346,uVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = iVar6 % 0x168;
  if (iVar6 < 0) {
    iVar6 = iVar6 + 0x168;
  }
  local_8ac = *(int **)(&g_sineTable360 + iVar6 * 4);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  iVar8 = FloatToInt64();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42e9ed
   * (`mov edi,ebx` at 0x42e9eb): same reused ebx value as above, cell is
   * piVar5+0x346. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar5 + 0x346,iVar6 - iVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = FUN_0040b090(piVar5 + 0x346,auStack_8a0,8);
  puStack_8 = (undefined1 *)0x12;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaDiv(uVar7,auStack_67c,iVar8);
  puStack_8 = 0x13;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42ea5d
   * (`mov edi,ebx` at 0x42ea5b): same reused ebx value as above, cell is
   * piVar5+0x346 (the same cell just passed to FUN_0040b090/
   * EncodeChecksumDeltaDiv above). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(piVar5 + 0x346,uVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = iStack_668;
  puStack_8 = (undefined1 *)0x12;
  if (iStack_668 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&local_8ac);
    iVar8 = iVar6;
  }
  iVar6 = iStack_88c;
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_88c != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&local_8ac);
    iVar8 = iVar6;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  piVar5 = piStack_8b0;
  *(char *)((int)piStack_8b0 + 0xf3f) = (char)iVar6;
  iVar6 = _rand();
  bVar3 = *(byte *)((int)piVar5 + 0xf3f);
  local_8b4 = (void *)CONCAT13(bVar3,(undefined3)local_8b4);
  *(byte *)(piVar5 + 0x3d0) = (byte)iVar6;
  bVar11 = ~('\x01' << (bVar3 & 7)) & (byte)iVar6 | '\0' << (bVar3 & 7);
  *(byte *)(piVar5 + 0x3d0) = bVar11;
  *(byte *)((int)piVar5 + 0xf41) = bVar3 + bVar11 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *(char *)((int)piVar5 + 0xf45) = (char)iVar6;
  iVar6 = _rand();
  bVar3 = *(byte *)((int)piVar5 + 0xf45);
  local_8b4 = (void *)CONCAT13(bVar3,(undefined3)local_8b4);
  *(byte *)((int)piVar5 + 0xf46) = (byte)iVar6;
  bVar11 = ~('\x01' << (bVar3 & 7)) & (byte)iVar6 | '\0' << (bVar3 & 7);
  *(byte *)((int)piVar5 + 0xf46) = bVar11;
  *(byte *)((int)piVar5 + 0xf47) = bVar3 + bVar11 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool(param_9,(byte *)GB_GUARD_UNRECOVERED);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42ebfb
   * (`lea edi,[ebx + 0x17e4]`): cell is piVar5+0x5f9 (== piVar5+0x17e4
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(piVar5 + 0x5f9,param_8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool(param_3,(byte *)GB_GUARD_UNRECOVERED);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42ec43
   * (`lea edi,[ebx + 0x1a08]`): cell is piVar5+0x682 (== piVar5+0x1a08
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(piVar5 + 0x682,param_10);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar5[0xfe5] = param_11;
  if (param_6 < 0x46) {
LAB_0042ec76:
    fStack_8a4 = (float)((uint)fStack_8a4 & 0xffffff00);
  }
  else {
    fStack_8a4 = (float)CONCAT31(SUBFIELD(fStack_8a4,1,undefined3),1);
    if (0x6e < param_6) goto LAB_0042ec76;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool(fStack_8a4,(byte *)GB_GUARD_UNRECOVERED);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42ecac
   * (`lea edi,[ebx + 0x3920]`): cell is piVar5+0xe48 (== piVar5+0x3920
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(piVar5 + 0xe48,0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  pcVar9 = (&PTR_s_12blast_xes_0056d310)[param_2];
  pcVar12 = (char *)((int)piVar5 + 0x3813);
  do {
    cVar4 = *pcVar9;
    pcVar9 = pcVar9 + 1;
    *pcVar12 = cVar4;
    pcVar12 = pcVar12 + 1;
  } while (cVar4 != '\0');
  pcVar13 = (code *)LeaveCriticalSection;
  if (DAT_0079352a != '\0') {
    QueueBroadcastEvent(0xf000);
    (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 2;
    pbVar1 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *pbVar1 = unaff_retaddr;
    puVar2 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar2 = param_1;
    puVar2 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar2 = (undefined1)param_2;
    puVar2 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar2 = 0xff;
    piVar10 = (int *)(&DAT_00e9aacd + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *piVar10 = param_4;
    piVar10 = (int *)(&DAT_00e9aad0 + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    *piVar10 = param_5;
    piVar10 = (int *)(&DAT_00e9aad0 + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    *piVar10 = param_6;
    piVar10 = (int *)(&DAT_00e9aad0 + g_dwBroadcastEventCursor);
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    *piVar10 = param_7;
    puVar2 = &DAT_00e9aad0 + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    *puVar2 = (undefined1)param_8;
    puVar2 = &DAT_00e9aacd + g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    *puVar2 = (undefined1)param_9;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    pcVar13 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar7;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar7;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar7;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar7;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar7;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar7;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    BroadcastQueuedEvent();
  }
  if (param_2 != 5) {
    if (param_2 == 0xc) {
      param_11 = 0x1e;
    }
    goto LAB_0042f0e2;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  local_8b4 = (void *)CONCAT13(iVar6 < 1,(undefined3)local_8b4);
  (*pcVar13)(&DAT_005a9068);
  if ((char)((uint)iVar8 >> 0x18) == '\0') {
LAB_0042efc6:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    if (-1 < iVar6) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      (*pcVar13)(&DAT_005a9068);
      if (0 < iVar6) goto LAB_0042f012;
    }
    uStack_8a8 = 1;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    if (-1 < iVar6) goto LAB_0042efc6;
LAB_0042f012:
    uStack_8a8 = uStack_8a8 & 0xffffff00;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool(uStack_8a8,(byte *)GB_GUARD_UNRECOVERED);
  (*pcVar13)(&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  unaff_EBP = CONCAT13(iVar6 == 0,(int3)unaff_EBP);
  (*pcVar13)(&DAT_005a9068);
  if (SUBFIELD(local_8b4,3,undefined1) != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = _rand();
    *(byte *)(piVar5 + 0xfe8) = (byte)iVar6;
    iVar6 = _rand();
    bVar3 = *(byte *)(piVar5 + 0xfe8);
    local_8b4 = (void *)CONCAT13(bVar3,(undefined3)local_8b4);
    *(byte *)((int)piVar5 + 0x3fa1) = (byte)iVar6;
    bVar11 = ~('\x01' << (bVar3 & 7)) & (byte)iVar6 | '\0' << (bVar3 & 7);
    *(byte *)((int)piVar5 + 0x3fa1) = bVar11;
    *(byte *)((int)piVar5 + 0x3fa2) = bVar3 + bVar11 + -0x34;
    (*pcVar13)(&DAT_005a9068);
  }
LAB_0042f0e2:
  FUN_0041da80(g_clientContext,piVar5,1,param_11,1);
  cVar4 = PeekPacketChecksumBool();
  if (cVar4 == '\x01') {
    local_8ac = (int *)EncodeChecksumDeltaMul(piVar5 + 0x930,auStack_8a0,3);
    puStack_8 = (undefined1 *)0x14;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    pcVar13 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaDiv(local_8ac,auStack_67c,uVar7);
    puStack_8 = 0x15;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_8ac = (int *)PeekPacketChecksumState();
    iVar6 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42f187
     * (`lea edi,[ebx + 0x24c0]`): cell is piVar5+0x930 (== piVar5+0x24c0
     * bytes) - the same cell explicitly passed to EncodeChecksumDeltaMul
     * above. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(piVar5 + 0x930,iVar6 + (int)local_8ac);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0x14;
    if (iStack_668 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&local_8ac);
      piVar5 = piStack_8b0;
    }
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_88c != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&local_8ac);
      piVar5 = piStack_8b0;
      pcVar13 = (code *)LeaveCriticalSection;
    }
    local_8ac = (int *)EncodeChecksumDeltaMul(piVar5 + 0x9b9,auStack_8a0,3);
    puStack_8 = (undefined1 *)0x16;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    piVar10 = (int *)PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    EncodeChecksumDeltaDiv(piStack_8b0,auStack_680,unaff_EBP);
    uStack_c = 0x17;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    piStack_8b0 = (int *)PeekPacketChecksumState();
    iVar6 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42f290
     * (`lea edi,[ebx + 0x26e4]`): cell is piVar5+0x9b9 (== piVar5+0x26e4
     * bytes) - the same cell explicitly passed to EncodeChecksumDeltaMul
     * above (piVar5 unchanged since then). See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(piVar5 + 0x9b9,iVar6 + (int)piStack_8b0);
    (*pcVar13)(&DAT_005a9068);
    uStack_10 = 0x16;
    if (iStack_670 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&local_8b4);
      piVar5 = piVar10;
      pcVar13 = (code *)LeaveCriticalSection;
    }
    uStack_10 = 0xffffffff;
    if (iStack_894 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&local_8b4);
      piVar5 = piVar10;
      pcVar13 = (code *)LeaveCriticalSection;
    }
    local_8b4 = (void *)EncodeChecksumDeltaMul(piVar5 + 0xa42,auStack_23c,3);
    uStack_10 = 0x18;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar13)(&DAT_005a9068);
    EncodeChecksumDeltaDiv(piVar10,auStack_464,unaff_EDI);
    uStack_14 = 0x19;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    iVar8 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42f39c
     * (`lea edi,[ebx + 0x2908]`): cell is piVar5+0xa42 (== piVar5+0x2908
     * bytes) - the same cell explicitly passed to EncodeChecksumDeltaMul
     * above (piVar5 unchanged since then). See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(piVar5 + 0xa42,iVar8 + iVar6);
    (*pcVar13)(&DAT_005a9068);
    puStack_8 = (undefined1 *)0x18;
    if (iStack_444 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&local_8ac);
    }
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_220 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&local_8ac);
    }
  }
  RegisterActiveObject(0, 0, (undefined4 *)0);
  *unaff_FS_OFFSET = uStack_10;
  return;
}

