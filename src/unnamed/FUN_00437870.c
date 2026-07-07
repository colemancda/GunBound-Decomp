/* FUN_00437870 - 0x00437870 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00437870(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4,
                 undefined4 param_5,char param_6)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  char *pcVar5;
  code *pcVar6;
  int *piVar7;
  code *pcVar8;
  undefined4 *unaff_FS_OFFSET;
  char *pcVar9;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ca9b;
  *unaff_FS_OFFSET = &local_c;
  cVar1 = FUN_004065a0();
  if (cVar1 != '\0') goto LAB_00437acb;
  iVar2 = FUN_00437490();
  while (iVar2 == -1) {
    FUN_00437500();
    iVar2 = FUN_00437490();
  }
  piVar3 = operator_new(0x4420);
  local_4 = 0;
  piVar7 = (int *)0x0;
  if (piVar3 != (int *)0x0) {
    FUN_004977c0(piVar3);
    piVar3[0x1107] = 0;
    *piVar3 = (int)&PTR_FUN_00556380;
    piVar7 = piVar3;
  }
  pcVar6 = EnterCriticalSection_exref;
  local_4 = 0xffffffff;
  piVar7[6] = 0x17ca;
  piVar7[0xe] = 0x17cb;
  piVar7[0xe25] = 0x200e;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined1 *)(piVar7 + 0xfed) = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_4 = param_4 & 0x80000007;
  piVar7[0xfe7] = iVar2;
  if ((int)param_4 < 0) {
    param_4 = (param_4 - 1 | 0xfffffff8) + 1;
  }
  *(char *)(piVar7 + 0xf) = (char)param_4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004064a0(param_5);
  pcVar8 = LeaveCriticalSection_exref;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar7[0xfea] = (uint)(param_6 != '\0');
  if (*(char *)(DAT_005b3484 + 0x45578) == '\0') {
    pcVar9 = s_srayonmine_00553c0c;
LAB_004379f7:
    iVar2 = FindPreloadedTextureByName(pcVar9);
    pcVar6 = EnterCriticalSection_exref;
    pcVar8 = LeaveCriticalSection_exref;
    piVar7[7] = iVar2;
  }
  else if (*(char *)(DAT_005b3484 + 0x45578) == '\x01') {
    pcVar9 = s_rayonevent1_00553c20;
    goto LAB_004379f7;
  }
  (**(code **)(*piVar7 + 4))(s_active_00551e58);
  (*pcVar6)(&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  (*pcVar8)(&DAT_005a9068);
  (*pcVar6)(&DAT_005a9068);
  EncodeOutgoingPacketField(uVar4);
  (*pcVar8)(&DAT_005a9068);
  piVar7[0xe26] = s_flame73_00553c04._0_4_;
  piVar7[0xe27] = s_flame73_00553c04._4_4_;
  pcVar9 = (char *)((int)piVar7 + 0x3813);
  pcVar5 = PTR_s_72blast_xes_0056d328;
  do {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    *pcVar9 = cVar1;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  FUN_0041da80(DAT_005b3484,piVar7,1,1,1);
  (*pcVar6)(&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  (*pcVar8)(&DAT_005a9068);
  piVar7[0xfeb] = iVar2;
  RegisterActiveObject();
LAB_00437acb:
  *unaff_FS_OFFSET = local_c;
  return;
}

