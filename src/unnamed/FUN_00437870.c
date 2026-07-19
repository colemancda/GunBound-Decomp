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
  char *pcVar9;
  undefined4 local_c;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler
   * body wasn't included in this function's own decompile. Same
   * rationale as entry/InitGame.c - see src/README.md. */
  cVar1 = PeekPacketChecksumBool();
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
  pcVar6 = (code *)EnterCriticalSection;
  local_4 = 0xffffffff;
  piVar7[6] = 0x17ca;
  piVar7[0xe] = 0x17cb;
  piVar7[0xe25] = 0x200e;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x43792d
   * (`lea edi,[ebp + 0x40]`, ebp = the constructed projectile object
   * piVar7): piVar7+0x40 matches InitProjectile.c's own cell #1
   * (param_2+0x40, tableHandle(+0x14)=param_2[0x15], activeFlag(+0x220)
   * both zeroed together there), confirming the same CProjectile cell
   * layout here. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar7 + 0x40, param_2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x437951
   * (`lea edi,[ebp + 0x264]`, ebp = piVar7): matches InitProjectile.c's
   * cell #2 (param_2+0x264). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar7 + 0x264, param_3);
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
  EncodeGuardedBool(param_5,(byte *)GB_GUARD_UNRECOVERED);
  pcVar8 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar7[0xfea] = (uint)(param_6 != '\0');
  if (*(char *)(g_clientContext + 0x45578) == '\0') {
    pcVar9 = s_srayonmine_00553c0c;
LAB_004379f7:
    iVar2 = FindPreloadedTextureByName(pcVar9);
    pcVar6 = (code *)EnterCriticalSection;
    pcVar8 = (code *)LeaveCriticalSection;
    piVar7[7] = iVar2;
  }
  else if (*(char *)(g_clientContext + 0x45578) == '\x01') {
    pcVar9 = s_rayonevent1_00553c20;
    goto LAB_004379f7;
  }
  (**(code **)(*piVar7 + 4))(s_active_00551e58);
  (*pcVar6)(&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  (*pcVar8)(&DAT_005a9068);
  (*pcVar6)(&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x437a46
   * (`lea edi,[ebp + 0x17e4]`, ebp = piVar7): a later cell on the same
   * projectile object, already initialized during InitProjectile-style
   * construction above and reused here for the checksum-state value.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar7 + 0x17e4, uVar4);
  (*pcVar8)(&DAT_005a9068);
  piVar7[0xe26] = SUBFIELD(s_flame73_00553c04,0,undefined4);
  piVar7[0xe27] = SUBFIELD(s_flame73_00553c04,4,undefined4);
  pcVar9 = (char *)((int)piVar7 + 0x3813);
  pcVar5 = PTR_s_72blast_xes_0056d328;
  do {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    *pcVar9 = cVar1;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  FUN_0041da80(g_clientContext,piVar7,1,1,1);
  (*pcVar6)(&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  (*pcVar8)(&DAT_005a9068);
  piVar7[0xfeb] = iVar2;
  RegisterActiveObject(0, 0, (undefined4 *)0);
LAB_00437acb:
  return;
}

