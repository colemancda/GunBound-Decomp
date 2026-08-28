/* CopyNameField_e - 0x00503e10 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED REGISTERS RECOVERED (2026-08-28).
 * ESI is the DESTINATION and EDI the SOURCE (the body copies
 * `*(uVar2 + unaff_ESI) = *(uVar2 + unaff_EDI)` for up to 12 bytes, then
 * stores the length at ESI+0xd) -- a 14-byte name field: up to 12 characters,
 * a NUL at dest+len (0x503e2b `mov [eax+esi],0`), and the length byte at
 * dest+0xd (0x503e25 `mov [esi+0xd],al`), so bytes 0..0xd inclusive.
 *
 * Every call site is in FUN_00501770, and the pairing is settled: VA order
 * matches source order and each site is separated by its own neighbouring
 * call (CopyNameField_12 before, StringMap_SetAt_28 or FUN_004fcd80
 * after, with distinct arguments).
 *
 * THE FRAME KEY for FUN_00501770, which cost the most to derive and is worth
 * keeping.  Despite the `and esp,0xfffffff8` alignment, Ghidra's names map
 * linearly onto esp:
 *
 *     local_N  lives at  esp_base + (0x4990 - N)
 *
 * confirmed four independent ways: `mov [esp+0x10],esi` right after
 * `lea esi,[edi+0x179c]` is the source's own
 * `local_4980 = (char *)(param_1 + 0x179c)`; `lea ecx,[esp+0x80]` with ONE
 * push pending (the 0x11) is FUN_004fcd80's `local_4914`; `[esp+0xa0]` is
 * StringMap_SetAt_28's `local_48f0`; and `[esp+0x338]` is `local_4658`.  The
 * pending-push term is what makes the first two agree -- without it they
 * disagree by exactly 4.
 *
 * THE CALLER'S CURSOR.  The earlier note said Ghidra dropped FUN_00501770's
 * whole EBX packet walk.  It did not.  EBX survives as a named local in every
 * branch that feeds these helpers -- `pcVar12` on the 0x1011 path, `iVar7` on
 * the 0x4001 path, plain `param_2` offsets on the 0x3001 path -- and only the
 * incremental `add ebx,N` steps were folded into the offsets of the reads the
 * decompiler kept.  Src line 364's `pcVar12 + 0x18` IS 0x50190b
 * `mov ax,[ebx+8]` taken with ebx = pcVar12 + 0x10.  So every dropped source
 * is an offset off a cursor variable that is already declared:
 *
 *   0x1011 pre-loop   ESI = local_4980 (= param_1+0x179c)  EDI = pcVar12 + 4
 *   0x1011 per-record ESI = local_4900 (esp_base+0x90)     EDI = pcVar12 + 0x10
 *   0x2021            ESI = local_4900                     EDI = &local_4668+0x10
 *   0x3001            ESI = local_4900                     EDI = param_2 + 0x16
 *   0x4001            ESI = local_4900                     EDI = iVar7 + 0x10
 *
 * The esp+0x90 destination is the 14-byte gap buffer described above, now
 * declared in the caller as `local_4900`.  The `lea ebx,[edi - 0x2c8]` at
 * 0x50184d that the old note read as the head of the walk is not part of it:
 * 0x501853 stores it to local_4970 and 0x501857 consumes it as FUN_00503bb0's
 * regEbx, and EBX is reloaded from local_4980 at 0x50188b before the first
 * helper call.
 *
 * NAMED (2026-08-28): the 0xe = 14-byte member of the fixed-width name
 * field trio - up to 12 characters, a NUL at dest+len and the length
 * byte at dest+0xd. See CopyNameField_12 for what the suffix means, for
 * the outside corroboration of the record layout, and for the caution
 * that the suffix is the byte count and not the character count.
 *
 * The 14-byte width is confirmed by a consumer rather than by this loop:
 * StringMap_SetAt_28 copies exactly 14 bytes - three dwords and a word -
 * out of the buffer that the immediately preceding CopyNameField_e call
 * has just filled, into the map entry at +0x12.
 */
#include "ghidra_types.h"


void CopyNameField_e(int regEsi,int regEdi)

{
  byte bVar1;
  uint uVar2;
  int unaff_ESI = regEsi;
  int unaff_EDI = regEdi;
  
  uVar2 = 0;
  do {
    bVar1 = (byte)uVar2;
    if (*(char *)(uVar2 + unaff_EDI) == '\0') break;
    bVar1 = bVar1 + 1;
    *(char *)(uVar2 + unaff_ESI) = *(char *)(uVar2 + unaff_EDI);
    uVar2 = (uint)bVar1;
  } while (bVar1 < 0xc);
  *(byte *)(unaff_ESI + 0xd) = bVar1;
  *(undefined1 *)((uint)bVar1 + unaff_ESI) = 0;
  return;
}

