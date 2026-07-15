/* FUN_004a4610 - 0x004a4610 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004a4610(int *param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  (**(code **)(*param_1 + 0x18))();
  AdvanceSpriteAnimation((int)param_1);
  iVar3 = param_1[0xfe9] + 2;
  param_1[0xfe9] = iVar3;
  if (0x1e < iVar3) {
    iVar3 = 0x1e;
  }
  param_1[0xfe9] = iVar3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_1[0xfe7] = (param_1[0xfe8] + param_1[0xfe7]) % iVar3;
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4a46a5
     * (`lea edi,[esi + 0x3920]`, esi = this file's own param_1, preserved
     * across the earlier vtable/AdvanceSpriteAnimation/checksum calls as
     * the fastcall this-pointer): cell is param_1+0x3920. `param_1` is
     * `int *`, so byte offsets use `(int)param_1 + N`. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)param_1 + 0x3920, iVar3 + 1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar3 = param_1[0xed1];
  param_1[0xed1] = iVar3 + 1;
  if (iVar3 + 1 == 5) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4a46de
     * (`lea edi,[esi + 0x3d6c]`, esi = param_1): cell is param_1+0x3d6c -
     * the same offset used as a CValueGuard cell (with
     * CompareChecksumPair/CompareChecksumExceeds) in FUN_004acd10.c. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)param_1 + 0x3d6c, uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  return;
}

