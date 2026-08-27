/* SpawnSuperMine - 0x00437870 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_00437870).  The super variant of SpawnMine
 * (0x4375f0): same class-100003 InitMine construction and the same event-flag
 * texture swap, differing only in operator_new(0x4420) vs 0x441c, the texture
 * name "srayonmine" vs "rayonmine" (the same s- prefix convention as
 * "ssflame" for SpawnSuperFlameEffect), and the initial state - "active"
 * rather than "normal", i.e. it arms immediately.  It has no call sites in
 * the ported tree yet.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 3 argless PeekPacketChecksumState() calls: the turn counter
 * g_clientContext + 0xeba98, the global 0x796aa0, and the freshly built
 * object's own cell (int)piVar7 + 0x35ec.  EBP holds that object for the
 * whole body (it comes straight out of the operator_new/ctor pair), which
 * is the same base the file's already-fixed Encodes spell as
 * `(int)piVar7 + 0x264` / `+ 0x17e4`.
 */
#include "ghidra_types.h"


void SpawnSuperMine(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4,
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
  cVar1 = PeekPacketChecksumBool((byte *)(param_1 + 4));
  if (cVar1 != '\0') goto LAB_00437acb;
  iVar2 = FindFreeMineKey(param_4);
  while (iVar2 == -1) {
    FUN_00437500();
    iVar2 = FindFreeMineKey(param_4);
  }
  piVar3 = operator_new(0x4420);
  local_4 = 0;
  piVar7 = (int *)0x0;
  if (piVar3 != (int *)0x0) {
    InitMine(piVar3);
    piVar3[0x1107] = 0;
    *piVar3 = (int)&PTR_FUN_00556380;
    piVar7 = piVar3;
  }
  pcVar6 = (code *)EnterCriticalSection;
  local_4 = 0xffffffff;
  piVar7[6] = 0x17ca;
  piVar7[0xe] = 0x17cb;
  piVar7[0xe25] = 0x200e;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x43792d
   * (`lea edi,[ebp + 0x40]`, ebp = the constructed projectile object
   * piVar7): piVar7+0x40 matches InitProjectile.c's own cell #1
   * (param_2+0x40, tableHandle(+0x14)=param_2[0x15], activeFlag(+0x220)
   * both zeroed together there), confirming the same CProjectile cell
   * layout here. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar7 + 0x40, param_2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x437951
   * (`lea edi,[ebp + 0x264]`, ebp = piVar7): matches InitProjectile.c's
   * cell #2 (param_2+0x264). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar7 + 0x264, param_3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(undefined1 *)(piVar7 + 0xfed) = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  param_4 = param_4 & 0x80000007;
  piVar7[0xfe7] = iVar2;
  if ((int)param_4 < 0) {
    param_4 = (param_4 - 1 | 0xfffffff8) + 1;
  }
  *(char *)(piVar7 + 0xf) = (char)param_4;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeGuardedBool(param_5,(byte *)GB_GUARD_UNRECOVERED);
  pcVar8 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
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
  (*pcVar6)(&g_valueGuardLock);
  uVar4 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
  (*pcVar8)(&g_valueGuardLock);
  (*pcVar6)(&g_valueGuardLock);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x437a46
   * (`lea edi,[ebp + 0x17e4]`, ebp = piVar7): a later cell on the same
   * projectile object, already initialized during InitProjectile-style
   * construction above and reused here for the checksum-state value.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar7 + 0x17e4, uVar4);
  (*pcVar8)(&g_valueGuardLock);
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
  (*pcVar6)(&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)((int)piVar7 + 0x35ec));
  (*pcVar8)(&g_valueGuardLock);
  piVar7[0xfeb] = iVar2;
  RegisterActiveObject(0, 0, (undefined4 *)0);
LAB_00437acb:
  return;
}

