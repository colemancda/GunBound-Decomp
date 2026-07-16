/* AnimateProjectileTick - 0x0048f1c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall AnimateProjectileTick(int *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  (**(code **)(*param_1 + 0x18))();
  FUN_004585e0();
  AdvanceSpriteAnimation((int)param_1);
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    /* FIXED (2026-07-16): dropped `self` arg - angr-confirmed at 0x48f208:
     * self is esi+0x3920 (param_1 is `int *`, so 0x3920 bytes = 0xe48
     * ints); esi = param_1 (`mov esi,ecx` in the prologue). Value
     * (iVar2 + 1) was already correct. */
    EncodeOutgoingPacketField((void *)(param_1 + 0xe48), iVar2 + 1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar2 = param_1[0xed1];
  param_1[0xed1] = iVar2 + 1;
  if (iVar2 + 1 == 5) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    /* FIXED (2026-07-16): dropped `self` arg - angr-confirmed at 0x48f241:
     * self is esi+0x3d6c (0x3d6c bytes = 0xf5b ints), esi = param_1.
     * Value (uVar3) was already correct. */
    EncodeOutgoingPacketField((void *)(param_1 + 0xf5b), uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  return;
}

