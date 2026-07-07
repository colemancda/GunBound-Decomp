/* FUN_004ac180 - 0x004ac180 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ac180(void)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  code *pcVar4;
  int local_c;
  
  pcVar4 = EnterCriticalSection_exref;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_c = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (local_c + -1 < 6) {
    puVar1 = &DAT_00e9cd30 + (local_c + -1) * 0x224;
    do {
      (*pcVar4)(&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar3 < iVar2) {
        (*pcVar4)(&DAT_005a9068);
        EncodeOutgoingPacketField(local_c);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        pcVar4 = EnterCriticalSection_exref;
      }
      puVar1 = puVar1 + 0x224;
      local_c = local_c + 1;
    } while ((int)puVar1 < 0xe9da08);
  }
  return;
}

