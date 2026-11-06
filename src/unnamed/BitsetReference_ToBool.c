/* BitsetReference_ToBool - 0x00426430 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): library shape, corroborated by the callers.
 * Both call sites in ProcessUdpProbeDatagram (0x4e633d, 0x4e6529) first
 * build a two-dword temporary on the stack - [esp+0x10] = a pointer to the
 * bitset word (`lea ecx,[ebx+0x148]` / `lea esi,[ebx+0x144]`), [esp+0x14] =
 * the bit index (a byte-sized slot id) - then `lea ecx,[esp+0x10] / call`
 * and test AL against 1.  That {bitset pointer, position} pair is exactly
 * MSVC 7.1 `std::bitset<N>::reference` (its _Pbitset and _Mypos members),
 * and the body is `reference::operator bool`: `_Pbitset->test(_Mypos)`,
 * which on `pos >= N` (here N = 8: `cmp eax,8 / jb`, else jmp 0x426460)
 * reaches Bitset_ThrowInvalidPosition (_Xinv), and otherwise returns
 * bit (pos & 0x1f) of dword (pos >> 5) of the bitset storage.  The
 * caller's own next lines are the matching write side `word |= 1 << pos`
 * under the same `local_243 < 8` guard.  ECX = &reference is the hidden
 * this; the ports of both callers currently pass nothing in it.
 */
#include "ghidra_types.h"


undefined4 __fastcall BitsetReference_ToBool(int *param_1)

{
  uint uVar1;
  
  uVar1 = param_1[1];
  if (7 < uVar1) {
                    /* WARNING: Subroutine does not return */
    Bitset_ThrowInvalidPosition();
  }
  return CONCAT31((uint3)(uVar1 >> 0xd),
                  (*(uint *)(*param_1 + (uVar1 >> 5) * 4) & 1 << ((byte)uVar1 & 0x1f)) != 0);
}

