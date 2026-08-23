/* SendQueue_ElementAt - 0x004e5c50 in the original binary.
 *
 * Bounds-checked element accessor for a connection's OUTBOUND SEND QUEUE.
 *
 * Returns *param_1 + regEax * 0x4004 after checking regEax against the count
 * at param_1[1], throwing E_INVALIDARG (0x80070057) otherwise -- the ATL
 * array-index idiom, alongside AtlArray_GrowBuffer elsewhere in this tree.
 *
 * What the array holds is settled by the caller rather than by this function.
 * HandleSocketEvent passes the header at conn + 0x24a40, having first checked
 * the count at conn + 0x24a44, then copies 0x4004 bytes out of the returned
 * element and hands them to send().  And 0x4004 is not an arbitrary stride:
 * that file's own destination is `char acStack_401c[16384 + 4]`, a 16 KB
 * payload with a trailing dword length that the send() call uses as its size
 * -- a layout a previous session had already had to reconstruct there.  So an
 * element is one queued outbound packet.
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


int __fastcall SendQueue_ElementAt(int *param_1,uint regEax)

{
  
  if ((uint)param_1[1] <= regEax) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  return regEax * 0x4004 + *param_1;
}

