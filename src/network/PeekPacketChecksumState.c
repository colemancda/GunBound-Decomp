/* PeekPacketChecksumState - 0x0040a2e0 in the original binary.
 *
 * Decode a CValueGuard cell's protected value.  This is the C-linkage twin
 * of CValueGuard::Peek() (src/cxx/ValueGuard.cpp, same address); the C++
 * object stays dropped from the bring-up link (tools/msvc-env/
 * bringup_drop.txt) because it also carries the REAL encoder, and the encode
 * flip is deliberately a separate step - so THIS file is what links, and it
 * has to be real on its own.
 *
 * FLIPPED 2026-08-16 (the CValueGuard Peek flip).  Until now this returned 0
 * unconditionally: the cell arrived in EAX and Ghidra dropped it, so there
 * was nothing to decode.  Every one of the ~4,300 call sites tree-wide now
 * passes its cell explicitly (see the sweep commits and
 * tools/sweep_guard_instructions.md), the guard family's own members that
 * peek internally take theirs as parameters, and functions.h declares the
 * parameter - so any straggler is a compile error, not a garbage read.
 *
 * Original 0x40a2e0, instruction for instruction:
 *   mov edi,eax                          ; self
 *   mov esi,[edi+0x14]                   ; tableHandle
 *   test esi,esi / je NODIAG
 *     ; integrity check: FUN_0040b8c0(&root, &handle, &out) and compare
 *     ; *out with DAT_00793774; mismatch -> tamper flag.  Skipped here:
 *     ; it is only reached with a NON-ZERO handle, and while the key
 *     ; table is the zeroed bring-up table every handle ever written is
 *     ; 0 (see winmain_bringup.c).  FUN_0040b8c0 also takes its three
 *     ; operands in ECX/EBX/EAX, all still unrecovered - so wiring it
 *     ; here would pass garbage.  Re-add when the key table goes real.
 *   NODIAG:
 *   key = g_valueGuardKeyTable + esi*0x10       ; the 16-byte key row
 *   for i in 0..3: dec[i] = key[i] ^ enc[i]; if i && dec[0]!=dec[i] -> TAMPER
 *   push dec[0]; call 0x40a380           ; RE-ENCODE the value just read
 *   return dec[0]
 *   TAMPER: DAT_00793514 = 1; return 0
 *
 * The re-encode tail goes through EncodeOutgoingPacketField, which in the
 * bring-up link is still the no-op auto-stub (src_network_
 * EncodeOutgoingPacketField.obj is dropped) - exactly the point of flipping
 * Peek FIRST: with the key table zeroed the encoded copies are the value
 * verbatim, so decoding is exact and the (skipped) re-encode would have
 * written the same bytes back.  When Encode is flipped this line becomes
 * live with no further change here.
 */
#include "ghidra_types.h"
#include <windows.h>


uint PeekPacketChecksumState(void *self)

{
  uint *cell;
  uint *key;
  uint handle;
  uint decoded0;
  uint decodedI;
  int i;

  cell = (uint *)self;
  handle = cell[5];                          /* +0x14 tableHandle */
  key = (uint *)(g_valueGuardKeyTable + handle * 0x10);
  decoded0 = key[0] ^ cell[1];               /* +0x04 enc0 */
  for (i = 1; i < 4; i = i + 1) {
    decodedI = key[i] ^ cell[1 + i];         /* +0x08 / +0x0c / +0x10 */
    if (decodedI != decoded0) {
      g_valueGuardTamperFlag = 1;
      return 0;
    }
  }
  EncodeOutgoingPacketField(self, decoded0);
  return decoded0;
}
