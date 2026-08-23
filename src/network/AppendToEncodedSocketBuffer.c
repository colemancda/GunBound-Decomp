/* AppendToEncodedSocketBuffer - 0x004d34f0 in the original binary.
 *
 * Appends bytes to the encoded outgoing socket buffer at its write cursor.
 *
 * The producer for exactly the buffer FlushEncodedSocketBuffer drains: it
 * copies param_2 bytes from param_3 to regEax + 0x44da + *(regEax + 0x84d8)
 * and advances that cursor, while FlushEncodedSocketBuffer reads the same
 * base (+0x44da) with the write cursor at +0x84d8 and the read cursor at
 * +0x84dc.  regEax is the client-context arena (g_connectionContextA at both call
 * sites), and it is returned unchanged - see the note at the return.
 *
 * ARGUMENTS RE-SLOTTED AND EAX RECOVERED.  `ret 4` gives one stack argument,
 * so param_1 is ECX -- a PHANTOM, written by `mov ecx,edx` before any read --
 * param_2 is EDX and param_3 is the push.  Both call sites agree:
 *
 *   0x00410685  mov eax,[0x7934e8] / mov edx,esi / push edx / mov edx,0x10
 *   0x004106cd  lea eax,[esp+0x44] / push eax / mov eax,[0x7934e8] / mov edx,0x10
 *
 * The two push DIFFERENT registers for the same value: ESI at the first site
 * was loaded `lea esi,[esp+0x44]` at 0x00410642, the very stack local the
 * second site takes the address of inline.  So param_3 is &local_d44 at both,
 * which is the value the port was already passing -- in param_1's slot.
 *
 * Reading EDX at the CALL rather than at the PUSH makes the first site look
 * as though it passes 0x10 as the buffer pointer, because EDX is reloaded
 * with the length in between.  A pointer of value sixteen is the kind of
 * wrong answer that looks like an answer.
 *
 * The body copies param_2 bytes from param_3 to regEax + 0x44da +
 * *(regEax + 0x84d8) -- an append at a stored write offset -- so regEax is
 * the destination buffer object, and it was uninitialised.
 */
#include "ghidra_types.h"


undefined4 __fastcall AppendToEncodedSocketBuffer(undefined4 param_1,uint param_2,undefined4 *param_3,
                                   int regEax)

{
  uint uVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(regEax + 0x44da + *(int *)(regEax + 0x84d8));
  for (uVar1 = param_2 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar2 = *param_3;
    param_3 = param_3 + 1;
    puVar2 = puVar2 + 1;
  }
  for (uVar1 = param_2 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined1 *)puVar2 = *(undefined1 *)param_3;
    param_3 = (undefined4 *)((int)param_3 + 1);
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  }
  *(uint *)(regEax + 0x84d8) = *(int *)(regEax + 0x84d8) + param_2;
  /* Ghidra emitted a bare `return;` here, and the port returned 0 rather
   * than invent a value.  The value is no longer invented: EAX is only ever
   * READ in this function (`mov edi,[eax+0x84d8]`, `lea edi,[eax+edi+0x44da]`,
   * `mov [eax+0x84d8],ecx`) and never written, so at `ret 4` it still holds
   * the incoming argument.  The original "returns" its EAX argument by not
   * touching it, and the caller depends on that -- 0x00410685 does
   * `push eax; call 0x4d3530`, i.e. FlushEncodedSocketBuffer(arena).
   * Returning 0 was flushing the buffer through a null pointer.  Expressible
   * only because regEax is now a named parameter. */
  return (undefined4)regEax;
}

