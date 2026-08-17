/* ExplodeSuperShot_Bullet4 - 0x004ad230 in the original binary.
 *
 * RENAMED (2026-08-16, from FUN_004ad230): CProjectile virtual slot 8 -
 * the post-detonation effect that the slot-6 Detonate override dispatches
 * right after marking the projectile dead (`param_1[5] = 1; (**(code
 * **)(*param_1 + 0x20))()`), only super-shot classes have it. "Explode" is
 * a descriptive label for that role, not a recovered name for mobile type
 * 3's super shot (texture bullet4p; vtable 0x5565f8, ctor FUN_004accf0
 * reached only through SpawnSuperShot's case 3). Type/role CONFIRMED via
 * vtable geometry (tools/projectile_class_map.py); the mobile NAME is not
 * confirmable (no mobile-type->name map in the repo).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 3 argless PeekPacketChecksumState() calls (3 C : 3 orig,
 * goto-free zip) - the first is the chained return of the EncodeChecksumPairSum
 * that opens the function (0x4ad26c -> frame[0x10]), discarded and now
 * captured in a new uVar8; the other two are the +0x1178/+0xf54 pair
 * that same PairSum takes as operands.
 */
#include "ghidra_types.h"


void __fastcall ExplodeSuperShot_Bullet4(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar8;
  int iVar3;
  int iVar4;
  void *pvVar5;
  int *piVar6;
  code *pcVar7;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_238 [8];
  undefined1 local_230 [548];
  undefined4 uStack_14;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053df6b;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *(undefined4 *)(param_1 + 0x3fa0) = 0;
  uVar8 = EncodeChecksumPairSum(param_1 + 0xf54,local_230,param_1 + 0x1178);
  pcVar7 = (code *)EnterCriticalSection;
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)uVar8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x3f9c) = uVar2;
  if ((*(int *)(local_230 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_238);
    pcVar7 = (code *)EnterCriticalSection;
  }
  (*pcVar7)(&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (*pcVar7)(&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\0') {
    pvVar5 = operator_new(0x54);
    if (pvVar5 == (void *)0x0) {
      piVar6 = (int *)0x0;
    }
    else {
      piVar6 = (int *)FUN_0047e940();
    }
    piVar6[0xe] = iVar4;
    piVar6[0xf] = iVar3;
    piVar6[0x11] = 0;
    *(undefined1 *)(piVar6 + 0x14) = 0;
    piVar6[6] = 0x206f;
    iVar3 = FindPreloadedTextureByName(s_ssflame4_00555170);
    piVar6[7] = iVar3;
    (**(code **)(*piVar6 + 4))(s_flame_00553d2c);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  *unaff_FS_OFFSET = uStack_14;
  return;
}

