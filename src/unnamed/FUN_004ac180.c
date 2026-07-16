/* FUN_004ac180 - 0x004ac180 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-16): Ghidra dropped this function's OWN incoming
 * parameter (passed via EAX, `mov ebx,eax` at the very top of the real
 * disasm) entirely, so the previous `void FUN_004ac180(void)` read
 * uninitialized memory for every offset off it - a separate, prior bug
 * to the EncodeOutgoingPacketField self-argument fix below. angr-
 * confirmed against the sole real call site (FUN_004ccd10.c, orig
 * 0x4ce1b2): the caller's own `iVar7` (a tree-node pointer from its
 * list-walk loop) is what's live in EAX there, so that's param_1 here.
 * Also fixed the dropped self on the loop's EncodeOutgoingPacketField
 * call - angr-traced to param_1+0x4c (the value cached in [esp+0x18]
 * before `add ebx,0x270` clobbers ebx for the rest of the loop), same
 * cell used for the function's very first PeekPacketChecksumState.
 */
#include "ghidra_types.h"


void FUN_004ac180(int param_1)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  code *pcVar4;
  int local_c;

  pcVar4 = (code *)EnterCriticalSection;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_c = PeekPacketChecksumState((void *)(param_1 + 0x4c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (local_c + -1 < 6) {
    puVar1 = &DAT_00e9cd30 + (local_c + -1) * 0x224;
    do {
      (*pcVar4)(&DAT_005a9068);
      iVar2 = PeekPacketChecksumState((void *)(param_1 + 0x270));
      iVar3 = PeekPacketChecksumState((void *)puVar1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar3 < iVar2) {
        (*pcVar4)(&DAT_005a9068);
        EncodeOutgoingPacketField((void *)(param_1 + 0x4c), local_c);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        pcVar4 = (code *)EnterCriticalSection;
      }
      puVar1 = puVar1 + 0x224;
      local_c = local_c + 1;
    } while ((int)puVar1 < 0xe9da08);
  }
  return;
}

