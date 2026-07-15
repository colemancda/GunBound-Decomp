/* FUN_004ae0f0 - 0x004ae0f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004ae0f0(int *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_1[0xfe8] == -1) {
    (**(code **)(*param_1 + 0x18))();
    FUN_004585e0();
    AdvanceSpriteAnimation((int)param_1);
    cVar1 = PeekPacketChecksumBool();
    if (cVar1 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x4ae145 (`lea edi,[esi + 0x3920]`, esi = this file's own
       * param_1, preserved across the earlier vtable/
       * AdvanceSpriteAnimation/checksum calls as the fastcall
       * this-pointer): cell is param_1+0x3920. `param_1` is `int *`, so
       * byte offsets use `(int)param_1 + N`. See
       * tools/encodeoutgoingpacketfield_sites.json. */
      EncodeOutgoingPacketField((int)param_1 + 0x3920, iVar2 + 1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    iVar2 = param_1[0xed1];
    param_1[0xed1] = iVar2 + 1;
    if (iVar2 + 1 == 5) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = PeekPacketChecksumState();
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x4ae17e (`lea edi,[esi + 0x3d6c]`, esi = param_1): cell is
       * param_1+0x3d6c - the same offset used as a CValueGuard cell
       * (with CompareChecksumPair/CompareChecksumExceeds) in
       * FUN_004acd10.c. See tools/encodeoutgoingpacketfield_sites.json. */
      EncodeOutgoingPacketField((int)param_1 + 0x3d6c, uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    return;
  }
  FUN_004acd10();
  return;
}

