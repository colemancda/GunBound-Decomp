/* FUN_00420600 - 0x00420600 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NOT FIXED (2026-08-13, CValueGuard sweep - deliberately left argless):
 * the cell is `ctx + 0x39d0c + slot*0x224` (`imul eax,esi,0x224 / lea
 * [eax+ecx+0x39d0c]` at 0x42061b, esi = the live-in slot the C models
 * as unaff_ESI) - but ecx is `mov ecx,[esp+8]` at 0x420615, a CONTEXT
 * ARGUMENT this decompile dropped entirely: the function is really
 * (ctx) with the slot in ESI, and the C signature is `(void)`.  Naming
 * the cell means promoting the prototype and fixing the caller, which
 * is the flip task's def-promotion pass, not a call-site sweep.  Its
 * twin FUN_004dc0f0 loads ctx from [0x5b3484] directly and IS fixed.
 */
#include "ghidra_types.h"


int FUN_00420600(void)

{
  int iVar1;
  int iVar2;
  int unaff_ESI;
  
  if (unaff_ESI == 0) {
    return 0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = unaff_ESI + -1;
  if (iVar1 != 0xff) {
    iVar2 = unaff_ESI;
  }
  return iVar2;
}

