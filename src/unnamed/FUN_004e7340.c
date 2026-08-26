/* FUN_004e7340 - 0x004e7340 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED and the CALL SITES RE-SLOTTED (2026-08-25).  The source
 * passed ZERO arguments to a function declared with two, so appending the
 * register would have put it in param_1's slot; every slot is written here.
 *
 * EAX is &g_replayContext at all four sites -- three load the address as an
 * immediate, the fourth reaches it through ESI, which traces to the same
 * address.  ECX (param_1) is a phantom (`mov ecx,edx` before any read), so it
 * takes 0.
 *
 * EDX (param_2) is the slot index, and its pairing is free at three of the
 * four sites: each has PeekChecksumStateUnderLock on the line immediately
 * above the call, and `call 0x40a4d0; mov edx,eax; call 0x4e7340` is exactly
 * that call's return value being handed over -- a result the port was
 * discarding.  At the fourth (WriteReplayEventRecord) EDX is
 * `movzx edx,[esp+0x17]`, and that slot is local_d71, established three ways:
 * 0x41052b takes `lea eax,[esp+0x1f]` with two pushes pending and hands it to
 * fwrite -- the source's `_fwrite(&local_d71,...)` -- while 0x410532 writes 0
 * to [esp+0x27] with FOUR pending, and both resolve to the same slot, base+0x17
 * (`local_d71 = 0` on the line above that fwrite).  0x410e0d then writes
 * `param_3[4]` there, which is the source's `local_d71 = param_3[4]`, and the
 * loop-carried local_d61 lives at base+0x27 instead (0x410e32, inside the loop
 * that starts at 0x410e30).
 */
#include "ghidra_types.h"


void __fastcall FUN_004e7340(undefined4 param_1,uint param_2,int regEax)

{
  uint *puVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  
  if ((int)param_2 < 8) {
    *(uint *)(regEax + 0x14c) = param_2;
    if (7 < param_2) {
                    /* WARNING: Subroutine does not return */
      FUN_00426460();
    }
    puVar1 = (uint *)(regEax + 0x140 + (param_2 >> 5) * 4);
    *puVar1 = *puVar1 | 1 << ((byte)param_2 & 0x1f);
    *(undefined4 *)(regEax + 0x18 + param_2 * 4) = *(undefined4 *)(regEax + 0x150);
    *(undefined2 *)(regEax + 0x58 + param_2 * 2) = *(undefined2 *)(regEax + 0x158);
    *(undefined4 *)(regEax + 0x38 + param_2 * 4) = *(undefined4 *)(regEax + 0x154);
    *(undefined2 *)(regEax + 0x68 + param_2 * 2) = *(undefined2 *)(regEax + 0x15a);
    pcVar3 = (char *)(regEax + 0x15d);
    iVar4 = (regEax + (param_2 * 3 + 0xf) * 8) - (int)pcVar3;
    do {
      cVar2 = *pcVar3;
      pcVar3[iVar4] = cVar2;
      pcVar3 = pcVar3 + 1;
    } while (cVar2 != '\0');
    *(undefined1 *)(param_2 + 0x3c8 + regEax) = 0;
    *(undefined1 *)(param_2 + 0x3c0 + regEax) = 0;
    *(undefined4 *)(regEax + 0x454c4 + param_2 * 4) = 0xffffffff;
  }
  return;
}

