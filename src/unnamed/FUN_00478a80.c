/* FUN_00478a80 - 0x00478a80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 5 argless PeekPacketChecksumState() calls.  Three read
 * standalone global cells -- 0x478ad8 / 0x478b85 read 0xe9ba40 (C30, C44)
 * and 0x478c1b reads 0xe55ab8 (C58).  The other two (0x478b14 at C35 and
 * 0x478bb5 at C49) read EBX, which each time was just set from the return
 * value of the delta helper called on the line above (0x40a6e0 at
 * 0x478af9, 0x40a5f0 at 0x478b9a); those helpers RETURN THEIR SECOND
 * ARGUMENT, the caller's stack scratch cell -- here local_454, which
 * Ghidra typed as an int holding `lea eax,[esp+0x24]`.
 */
#include "ghidra_types.h"


char FUN_00478a80(int param_1,int param_2,int param_3)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_45c [8];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  uint local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053ab71) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  if (*(char *)(param_1 + 0x14) == '\x01') {
    return '\0';
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(&DAT_00e9ba40));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaSub(param_1 + 0x25c,local_454,uVar2);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(local_454));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_45c,&g_valueGuardMap);
  }
  if (iVar3 <= param_2) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)(&DAT_00e9ba40));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaAdd(param_1 + 0x25c,local_454,uVar2);
    local_4 = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState((void *)(local_454));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if ((*(int *)(local_454 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&g_valueGuardKeyTable);
      TreeLowerBound(local_45c,&g_valueGuardMap);
    }
    if (param_2 <= iVar3) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)(&DAT_00e55ab8));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = EncodeChecksumDeltaSub(param_1 + 0x480,local_230,uVar2);
      local_4 = 2;
      iVar3 = PeekChecksumStateUnderLock(uVar2);
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      if (iVar3 <= param_3) {
        cVar1 = PacketChecksumLessThan(param_1 + 0x480,param_3);
        cVar1 = '\x01' - (cVar1 != '\0');
        goto LAB_00478c8e;
      }
    }
  }
  cVar1 = '\0';
LAB_00478c8e:
  return cVar1;
}

