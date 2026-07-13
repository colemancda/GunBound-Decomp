/* DecodePacketBlocks - 0x004f7150 in the original binary.
 *
 * FIXED (2026-07-13): `in_EAX` (the byte length used to compute the block
 * count) was declared but never assigned - a genuine, independent 6th
 * argument arriving via EAX. Confirmed via objdump at the sole call site
 * (ProcessIncomingPackets.c, both branches reaching LAB_004d2a90): `mov
 * eax,esi` immediately before `call 0x4f7150`, ESI set from `[ebp-4]`/
 * `[ebp-6]` (EBP = that file's own `local_24e4`), matching its
 * already-computed-but-never-passed `iVar6` local exactly. Promoted to an
 * explicit 6th parameter `byteLen`; the call site now passes `iVar6`.
 *
 * SECOND FIX (2026-07-13): `param_4` looked dead (no direct `param_4`
 * read anywhere in Ghidra's output) but is not - it's the encrypted
 * 16-byte-block source pointer, threaded through the loop purely via
 * register EBP and only ever surfacing as DecodeCipherBlock's 2nd
 * (EDX/fastcall) argument, which Ghidra's decompiler dropped along with
 * DecodeCipherBlock's other 2 arguments (see that function's own header -
 * it's `__fastcall(ecx unused, edx=cipherBlock, stack1=output,
 * stack2=ctx)`). Traced via objdump at 0x4f715f (`mov ebp,[esp+0x24]` in
 * the prologue, before the loop's extra pushes shift that same stack slot
 * to `[esp+0xc]` = this function's own 3rd stack argument, i.e. param_4)
 * and at 0x4f71aa (`mov edx,ebp` right before `call 0x4f5e10`, with EBP
 * advanced by `add ebp,0x10` - one AES block - each iteration at
 * 0x4f71e7). Retyped `param_4` as `uint *`, advanced per iteration, and
 * passed as DecodeCipherBlock's real 2nd argument.
 *
 * THIRD FIX (2026-07-13): `local_10`/`local_c`/`local_8`/`local_4` are
 * the same "separately-declared locals relied on for contiguous
 * pointer-aliased writes" bug class already found and fixed in
 * State05_Logo1_OnExit.c - DecodeCipherBlock writes its 16-byte decrypted
 * block through a single `uint *` output argument (`param_3[0..3]` in
 * that function's own body, confirmed by objdump: `mov [eax],ebx / mov
 * [eax+4],esi / mov [eax+8],edi / mov [eax+0xc],ecx` right before
 * return), but the call site here only ever passed `&local_10` and relied
 * on `local_c`/`local_8`/`local_4` landing contiguously after it - MSVC
 * doesn't guarantee that (confirmed by this file's own C4700 "used
 * without having been initialized" warnings on exactly those 3 locals).
 * Replaced with a real 4-uint array `cipherOutput`. The call was also
 * only passing 2 of DecodeCipherBlock's 4 real arguments (the dropped-
 * argument confusion above meant Ghidra rendered `param_1`/`param_4` as
 * missing entirely) - now passes all 4: an unused dummy for the dead
 * ECX/param_1 slot, the source block pointer, the output array, and the
 * context struct (this function's own param_2, already used elsewhere in
 * this same function via `param_2 + 0x20c`, and matching DecodeCipherBlock's
 * own `param_4 + 0x208` flag-byte access on the identical struct).
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall
DecodePacketBlocks(undefined4 *param_1,int param_2,ushort param_3,uint *param_4,int param_5,
                    uint byteLen)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  uint cipherOutput[4];

  uVar2 = byteLen & 0x8000000f;
  bVar5 = uVar2 == 0;
  if ((int)uVar2 < 0) {
    bVar5 = (uVar2 - 1 | 0xfffffff0) == 0xffffffff;
  }
  if (!bVar5) {
    return 0;
  }
  iVar3 = (int)(byteLen + ((int)byteLen >> 0x1f & 0xfU)) >> 4;
  if (param_5 < iVar3 * 0xc) {
    return 0;
  }
  if (0 < iVar3) {
    iVar4 = 0;
    do {
      sVar1 = DecodeCipherBlock(0,param_4,cipherOutput,param_2);
      if ((sVar1 != 1) || (cipherOutput[0] != (uint)param_3 + *(int *)(param_2 + 0x20c))) {
        return 0;
      }
      *param_1 = cipherOutput[1];
      iVar4 = iVar4 + 1;
      param_1[1] = cipherOutput[2];
      param_1[2] = cipherOutput[3];
      param_1 = param_1 + 3;
      param_4 = (uint *)((char *)param_4 + 0x10);
    } while (iVar4 < iVar3);
  }
  return 1;
}

