/* FUN_0047fad0 - 0x0047fad0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0047fad0(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int unaff_EBX;
  code *pcVar5;
  int *unaff_ESI;
  undefined4 *unaff_FS_OFFSET;
  int unaff_retaddr;
  int aiStack_464 [2];
  uint uStack_45c;
  undefined4 local_458 [0x89]; /* CValueGuard cell: 0x89*4 = 0x224 bytes (see src/network/SendOutgoingPacket.c) */
  int iStack_444;
  undefined1 auStack_234 [20];
  int iStack_220;
  undefined4 uStack_18;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_00539aad;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_458[0] = 0;
  unaff_ESI[0xfef] = ((char)param_3 != '\0') + 1;
  (**(code **)(*unaff_ESI + 4))(&DAT_00553f90);
  iVar2 = GetPlayerRecordBySlot(g_clientContext);
  if (iVar2 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    pcVar5 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar3 != 1) {
      *(undefined1 *)(unaff_ESI + 5) = 1;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x47fb8d
     * (`lea edi,[esi + 0x40]`, esi = unaff_ESI, the function's own "this"
     * projectile object, e.g. unaff_ESI[0xfef]=... above): unaff_ESI+0x40
     * matches InitProjectile.c's own cell #1 (param_2+0x40, tableHandle
     * (+0x14)=param_2[0x15], activeFlag(+0x220) both zeroed together
     * there), confirming the same CProjectile cell layout. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)unaff_ESI + 0x40, uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    unaff_ESI[0xfed] = iVar3;
    if (((char)unaff_ESI[0xfe8] != '\0') || (uVar4 = 0xffffff38, (char)unaff_ESI[0xff1] != '\0')) {
      uVar4 = 0xfffffdda;
    }
    aiStack_464[0] = EncodeChecksumDeltaAdd(iVar2 + 0xb30,auStack_234,uVar4);
    puStack_8 = (undefined1 *)0x0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    unaff_EBX = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    aiStack_464[0] = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(int *)(&g_nCameraBoundY + g_clientContext) + unaff_EBX < aiStack_464[0]) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      unaff_EBX = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = *(int *)(&g_nCameraBoundY + g_clientContext) + unaff_EBX;
    }
    else {
      if (((char)unaff_ESI[0xfe8] != '\0') || (uVar4 = 0xffffff38, (char)unaff_ESI[0xff1] != '\0'))
      {
        uVar4 = 0xfffffdda;
      }
      EncodeChecksumDeltaAdd(iVar2 + 0xb30,local_458,uVar4);
      puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
      uStack_45c = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x47fce2
     * (`lea edi,[esi + 0x264]`, esi = unaff_ESI): matches InitProjectile.c's
     * cell #2 (param_2+0x264). See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)unaff_ESI + 0x264, iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0x0;
    unaff_ESI[0xfee] = iVar3;
    if (((uStack_45c & 1) != 0) && (iStack_444 != 0)) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(aiStack_464);
      unaff_EBX = iStack_444;
    }
    puStack_8 = (undefined1 *)0xffffffff;
    pcVar5 = (code *)LeaveCriticalSection;
    if (iStack_220 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(aiStack_464);
      pcVar5 = (code *)LeaveCriticalSection;
      unaff_EBX = iStack_220;
    }
  }
  unaff_ESI[0xfea] = unaff_retaddr;
  unaff_ESI[0xfeb] = param_1;
  *(undefined1 *)(unaff_ESI + 0xff1) = 0;
  *(undefined1 *)(unaff_ESI + 0xfe8) = param_2;
  unaff_ESI[0xfe9] = param_3;
  if (*(char *)(iVar2 + 0x651c) == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar2 = PeekPacketChecksumState();
  (*pcVar5)(&DAT_005a9068);
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    iVar2 = iVar2 + (iVar2 * 0x14) / 100;
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    iVar2 = iVar2 + (iVar2 * 0x14) / 100;
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    if (*(char *)(unaff_EBX + 0x651c) == '\x01') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    iVar3 = PeekPacketChecksumState();
    (*pcVar5)(&DAT_005a9068);
    iVar2 = iVar2 + iVar3;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x47fea5
   * (`lea edi,[esi + 0x139c]`, esi = unaff_ESI): a later cell on the same
   * projectile object, already initialized during the object's
   * InitProjectile-style construction and reused here for the final
   * damage value. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)unaff_ESI + 0x139c, iVar2);
  (*pcVar5)(&DAT_005a9068);
  RescrambleGuardedBool();
  *unaff_FS_OFFSET = uStack_18;
  return;
}

