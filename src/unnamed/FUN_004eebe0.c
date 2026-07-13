/* FUN_004eebe0 - 0x004eebe0 in the original binary.
 *
 * DROPPED REGISTER ARGUMENT (unaff_ESI): Ghidra read the object being
 * initialized (a freshly operator_new'd 0xb8-byte struct, per the sole
 * caller InitDirectSound.c) as an uninitialized local instead of a real
 * parameter. Confirmed via objdump at 0x4ee74d (`mov esi,eax; call
 * 0x4eebe0` right after `operator_new(0xb8)`). Promoted to a real
 * parameter, forwarded to FUN_004ef7e0.
 *
 * RETURN VALUE: Ghidra emitted a bare `return;`, but objdump at
 * 0x4eec6b shows the real function ends with `mov eax,esi` before its
 * `ret` - it returns the same object pointer it was passed, which the
 * caller stores into *DAT_00793554. Fixed to match.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 *FUN_004eebe0(undefined4 *unaff_ESI)

{
  undefined4 uVar1;
  uintptr_t uVar2;

  FUN_004ef7e0(unaff_ESI);
  *unaff_ESI = &PTR_LAB_005574e8;
  unaff_ESI[5] = 0;
  unaff_ESI[0xe] = 0xffffffff;
  *(undefined1 *)(unaff_ESI + 0x13) = 0;
  InitializeCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 8));
  *(undefined1 *)(unaff_ESI + 4) = 1;
  uVar2 = __beginthread(FUN_004ef870,0,unaff_ESI);
  unaff_ESI[1] = uVar2;
  if (uVar2 == 0) {
    *(undefined1 *)(unaff_ESI + 4) = 0;
  }
  uVar1 = DAT_00588f44;
  unaff_ESI[0x14] = 0;
  unaff_ESI[0x26] = 0;
  unaff_ESI[0x27] = 0;
  unaff_ESI[0x29] = 0;
  unaff_ESI[0x2a] = 0;
  unaff_ESI[0x2b] = 0;
  *unaff_ESI = &PTR_LAB_005574cc;
  unaff_ESI[0x28] = 20000;
  unaff_ESI[0x2c] = uVar1;
  unaff_ESI[0x2d] = 0xffffffff;
  return unaff_ESI;
}

