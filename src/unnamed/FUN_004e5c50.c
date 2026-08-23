/* FUN_004e5c50 - 0x004e5c50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * A BOUNDS-CHECKED ARRAY INDEXER.  `ret 0` puts nothing on the stack, so
 * param_1 (ECX) and EAX are the whole input, and its one call site supplied
 * neither.  It returns *param_1 + regEax * 0x4004 after checking regEax
 * against the count at param_1[1], throwing E_INVALIDARG (0x80070057)
 * otherwise -- so regEax is the element index and the elements are 0x4004
 * bytes each.
 *
 * From the call site at 0x004e5901:
 *   lea ecx, [esi + 0x24a40]   -> param_1  (the ADDRESS of the array header)
 *   xor eax, eax               -> regEax = 0
 *
 * ESI there is HandleSocketEvent's own param_1, which the port already shows
 * independently: the source writes param_1 + 0x24a58 where the binary has
 * `lea edi,[esi+0x24a58]` two instructions earlier.  So the header address is
 * param_1 + 0x24a40 in the caller's own terms, with no spill to resolve.
 *
 * Reading a bounds-checked index out of an uninitialised register meant the
 * check was against garbage: either a spurious throw, or a pointer 0x4004
 * bytes times nonsense past the array.
 */
#include "ghidra_types.h"


int __fastcall FUN_004e5c50(int *param_1,uint regEax)

{
  
  if ((uint)param_1[1] <= regEax) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  return regEax * 0x4004 + *param_1;
}

