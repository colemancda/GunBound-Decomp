/* FUN_00437f70 - 0x00437f70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00437f70(undefined4 param_1,int param_2,int param_3,uint param_4,undefined4 param_5)

{
  void *pvVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053795b;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  FUN_0043c4f0();
  pvVar1 = operator_new(0x3fe4);
  piVar4 = (int *)0x0;
  local_4 = 0;
  if (pvVar1 != (void *)0x0) {
    piVar4 = (int *)FUN_0047f9e0();
  }
  local_4 = 0xffffffff;
  piVar4[6] = 0x17ce;
  piVar4[0xe] = 0x17cf;
  piVar4[0xe25] = 0x1f4d;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x437ff0
   * (`lea edi,[ebp + 0x40]`, ebp = the constructed projectile object
   * piVar4): piVar4+0x40 matches InitProjectile.c's own cell #1
   * (param_2+0x40, whose tableHandle(+0x14)=param_2+0x54==param_2[0x15]
   * and activeFlag(+0x220)=param_2+0x260 are zeroed together there),
   * confirming the same CProjectile cell layout here. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar4 + 0x40, param_2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x438014
   * (`lea edi,[ebp + 0x264]`, ebp = piVar4): matches InitProjectile.c's
   * cell #2 (param_2+0x264, tableHandle==param_2[0x9e], activeFlag at
   * param_2+0x121*4). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar4 + 0x264, param_3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_4 = param_4 & 0x80000007;
  piVar4[0xfee] = param_3;
  if ((int)param_4 < 0) {
    param_4 = (param_4 - 1 | 0xfffffff8) + 1;
  }
  *(char *)(piVar4 + 0xf) = (char)param_4;
  piVar4[0xfea] = param_2;
  piVar4[0xfeb] = param_3 + 200;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool(param_5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = FindPreloadedTextureByName(s_laserion_00553be8);
  piVar4[7] = iVar2;
  (**(code **)(*piVar4 + 4))(s_normal_00552230);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4380cb
   * (`lea edi,[ebp + 0x17e4]`, ebp = piVar4): a later cell on the same
   * projectile object, already initialized during the InitProjectile-
   * equivalent construction above and reused here for the checksum-
   * state value. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar4 + 0x17e4, uVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  RegisterActiveObject(0, 0, (undefined4 *)0);
  *unaff_FS_OFFSET = pvVar1;
  return;
}

