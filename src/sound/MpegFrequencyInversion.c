/* MpegFrequencyInversion - 0x0051c568 in the original binary.
 *
 * Layer III frequency inversion: negate every odd sample of every odd
 * subband.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Reached through MpegFrequencyInversionThunk (0x5180b0) from 0x514cc0,
 * which calls it on the buffer 0x5ada3c with the line count right before
 * the polyphase synthesis call through PTR_FUN_00563da0. The buffer is 32
 * floats per time slot: the nine loops start at byte offsets 0x84, 0x184,
 * ... (odd slots 1, 3, ..., 17) and step 8 bytes (odd subbands), for (n +
 * 17) / 18 / 2 subbands, which is the ISO 11172-3 frequency inversion (odd
 * samples of odd subbands negated).
 *
 * SIGNATURE CORRECTED (2026-08-25).  Same hand-written-asm shape as
 * FUN_0051f456 and its two siblings: entry `push ebp; lea ebp,[esp+8];
 * pushal`, exit `popal; pop ebp; ret`, ret 0 with the caller cleaning up.
 * Every general register is saved and restored, so ECX, EDX and EAX are all
 * written before any read -- phantoms, not arguments -- and Ghidra's
 * `return CONCAT44(param_2,in_EAX)` is popal restoring EDX:EAX, not a value.
 * The real arguments are the 2 stack slot(s) its caller already passes.
 */
#include "ghidra_types.h"


void __cdecl MpegFrequencyInversion(int param_3,int param_4)
{
  uint uVar1;
  int iVar2;
  
  uVar1 = (uint)((ulonglong)(longlong)(param_4 + 0x11) / 0x12) >> 1;
  if (uVar1 != 0) {
    iVar2 = 0;
    do {
      *(float *)(param_3 + 0x84 + iVar2 * 8) = -*(float *)(param_3 + 0x84 + iVar2 * 8);
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)uVar1);
    iVar2 = 0;
    do {
      *(float *)(param_3 + 0x184 + iVar2 * 8) = -*(float *)(param_3 + 0x184 + iVar2 * 8);
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)uVar1);
    iVar2 = 0;
    do {
      *(float *)(param_3 + 0x284 + iVar2 * 8) = -*(float *)(param_3 + 0x284 + iVar2 * 8);
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)uVar1);
    iVar2 = 0;
    do {
      *(float *)(param_3 + 900 + iVar2 * 8) = -*(float *)(param_3 + 900 + iVar2 * 8);
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)uVar1);
    iVar2 = 0;
    do {
      *(float *)(param_3 + 0x484 + iVar2 * 8) = -*(float *)(param_3 + 0x484 + iVar2 * 8);
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)uVar1);
    iVar2 = 0;
    do {
      *(float *)(param_3 + 0x584 + iVar2 * 8) = -*(float *)(param_3 + 0x584 + iVar2 * 8);
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)uVar1);
    iVar2 = 0;
    do {
      *(float *)(param_3 + 0x684 + iVar2 * 8) = -*(float *)(param_3 + 0x684 + iVar2 * 8);
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)uVar1);
    iVar2 = 0;
    do {
      *(float *)(param_3 + 0x784 + iVar2 * 8) = -*(float *)(param_3 + 0x784 + iVar2 * 8);
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)uVar1);
    iVar2 = 0;
    do {
      *(float *)(param_3 + 0x884 + iVar2 * 8) = -*(float *)(param_3 + 0x884 + iVar2 * 8);
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)uVar1);
  }
  return;
}

