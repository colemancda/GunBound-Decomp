/* FUN_004ef3a0 - 0x004ef3a0 in the original binary.
 *
 * DROPPED REGISTER ARGUMENT (unaff_ESI): Ghidra read the object being
 * initialized (a freshly operator_new'd 0x50-byte struct, per the sole
 * caller InitDirectSound.c) as an uninitialized local instead of a real
 * parameter. Confirmed via objdump at 0x4ee77e (`mov esi,eax; call
 * 0x4ef3a0` right after `operator_new(0x50)`). Promoted to a real
 * parameter, forwarded to FUN_004ef7e0 (also confirmed via objdump at
 * 0x4ef3a1: `mov ebx,esi` before that call).
 *
 * RETURN VALUE: Ghidra emitted a bare `return;` (MSVC falls through
 * with whatever's in EAX; gcc rejects it as -Wreturn-mismatch), but
 * objdump at 0x4ef434 shows the real function ends with `mov eax,esi`
 * before its `ret` - it returns the same object pointer it was passed,
 * which the caller stores into DAT_00793554[]. Fixed to match.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 *FUN_004ef3a0(undefined4 *unaff_ESI)

{
  uintptr_t uVar1;

  FUN_004ef7e0(unaff_ESI);
  *unaff_ESI = &PTR_LAB_005574e8;
  unaff_ESI[5] = 0;
  unaff_ESI[0xe] = 0xffffffff;
  *(undefined1 *)(unaff_ESI + 0x13) = 0;
  InitializeCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 8));
  *(undefined1 *)(unaff_ESI + 4) = 1;
  uVar1 = __beginthread(FUN_004ef870,0,unaff_ESI);
  unaff_ESI[1] = uVar1;
  if (uVar1 == 0) {
    *(undefined1 *)(unaff_ESI + 4) = 0;
  }
  return unaff_ESI;
}

