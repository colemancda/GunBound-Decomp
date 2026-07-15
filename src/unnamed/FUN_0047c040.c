/* FUN_0047c040 - 0x0047c040 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0047c040(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int unaff_EBX;
  code *pcVar4;
  int *unaff_ESI;
  undefined4 *unaff_FS_OFFSET;
  int unaff_retaddr;
  int aiStack_464 [2];
  uint uStack_45c;
  undefined4 local_458 [5];
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
    pcVar4 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar3 != 1) {
      *(undefined1 *)(unaff_ESI + 5) = 1;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    pcVar4 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    unaff_ESI[0xfed] = iVar3;
    aiStack_464[0] =
         EncodeChecksumDeltaAdd(iVar2 + 0xb30,auStack_234,
                      (-(uint)((char)unaff_ESI[0xfe8] != '\0') & 0xffffff38) - 200);
    puStack_8 = (undefined1 *)0x0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    aiStack_464[0] = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(int *)(&g_nCameraBoundY + g_clientContext) + iVar3 < aiStack_464[0]) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = *(int *)(&g_nCameraBoundY + g_clientContext) + iVar3;
    }
    else {
      EncodeChecksumDeltaAdd(iVar2 + 0xb30,local_458,
                   (-(uint)((char)unaff_ESI[0xfe8] != '\0') & 0xffffff38) - 200);
      puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
      uStack_45c = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    unaff_ESI[0xfee] = iVar3;
    puStack_8 = (undefined1 *)0x0;
    if (((uStack_45c & 1) != 0) && (iStack_444 != 0)) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(aiStack_464);
    }
    puStack_8 = (undefined1 *)0xffffffff;
    unaff_EBX = iStack_220;
    if (iStack_220 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(aiStack_464);
    }
  }
  unaff_ESI[0xfea] = unaff_retaddr;
  unaff_ESI[0xfeb] = param_1;
  *(undefined1 *)(unaff_ESI + 0xfe8) = param_2;
  unaff_ESI[0xfe9] = param_3;
  *(undefined1 *)(unaff_ESI + 0xff2) = 0;
  if (*(char *)(iVar2 + 0x651c) == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar2 = PeekPacketChecksumState();
  (*pcVar4)(&DAT_005a9068);
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
    (*pcVar4)(&DAT_005a9068);
    iVar2 = iVar2 + iVar3;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x47c3ac
   * (`lea edi,[esi+0x139c]`, esi = this file's own unaff_ESI, confirmed
   * by objdump of orig/GunBound.gme: esi is never reassigned anywhere in
   * this function). unaff_ESI is `int *` (scales by 4), so the byte
   * offset is taken via `(int)unaff_ESI + 0x139c` (same twin-cell offset
   * as FUN_0047fee0.c's identical call site). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)unaff_ESI + 0x139c, iVar2);
  (*pcVar4)(&DAT_005a9068);
  RescrambleGuardedBool();
  *unaff_FS_OFFSET = uStack_18;
  return;
}

