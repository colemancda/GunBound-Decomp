/* FUN_00503e30 - 0x00503e30 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * THE HASH SLOT (2026-08-25).  The original passes the find `&param_1` for
 * its hash out-parameter -- reusing the incoming parameter slot, whose value
 * it has already cached in EBP -- and then reads the hash back out of that
 * slot for the insert while EBP still holds the original key.  A C port
 * cannot alias param_1 that way without losing the key, so the hash gets a
 * local of its own and param_1 keeps meaning what it means at the entry.
 *
 * DROPPED REGISTERS ANALYSED, BLOCKED ON THE CALLER (2026-08-27).
 * ESI is the DESTINATION and EDI the SOURCE (the body copies
 * `*(uVar2 + unaff_ESI) = *(uVar2 + unaff_EDI)` for up to 12 bytes, then
 * stores the length at ESI+0xd) -- this is a 13-byte name-field copy.
 *
 * Every call site is in FUN_00501770, and the pairing is settled: VA order
 * matches source order and each site is separated by its own neighbouring
 * call (FUN_004fe5d0 before, FUN_00503e30 or FUN_004fcd80 after, with
 * distinct arguments).
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
 * FUN_00503e30's `local_48f0`; and `[esp+0x338]` is `local_4658`.  The
 * pending-push term is what makes the first two agree -- without it they
 * disagree by exactly 4.
 *
 * WHAT BLOCKS IT.  The destinations resolve (site 1 is
 * `param_1 + 0x179c`, i.e. the local_4980 the line above assigns; the rest
 * are esp+0x90 = an unnamed 14-byte buffer in the 0x11-byte gap Ghidra left
 * between local_4902 and local_48f0, which only these argless calls write).
 * The SOURCES do not: they are `ebx + 4` and `ebx + 0x10`, and EBX is a
 * packet-parse CURSOR that FUN_00501770 builds with a chain of a dozen
 * incremental adds (`lea ebx,[edi - 0x2c8]` at 0x50184d, then `add ebx,2`,
 * `add ebx,4`, `add ebx,0xc`, `add ebx,0x10` ... through 0x5021e3).  Ghidra
 * dropped that entire walk, because its only consumers were these argless
 * calls -- the same shape as FUN_0044c630's dropped pointer walk, but across
 * a 3372-byte function.
 *
 * So this is a caller reconstruction, not an argument recovery, and it
 * unblocks FUN_00503e30 in the same move -- that function's six sites are in
 * the same caller and want the same cursor.
 */
#include "ghidra_types.h"


void FUN_00503e30(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *unaff_ESI;
  int *unaff_EDI;
  uint local_hash;
  undefined4 local_8;
  undefined1 local_4 [4];
  
  iVar2 = StringMap_Find_28((char *)param_1,&local_hash,(undefined4 *)local_4,unaff_EDI,(uint *)&local_8);
  if (iVar2 == 0) {
    if (*unaff_EDI == 0) {
      cVar1 = HashMap_InitHashTable(unaff_EDI,unaff_EDI[2],1);
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
    }
    iVar2 = StringMap_Insert_28(local_8,local_hash,(undefined4 *)param_1,unaff_EDI);
  }
  *(undefined4 *)(iVar2 + 0x12) = *unaff_ESI;
  *(undefined4 *)(iVar2 + 0x16) = unaff_ESI[1];
  *(undefined4 *)(iVar2 + 0x1a) = unaff_ESI[2];
  *(undefined2 *)(iVar2 + 0x1e) = *(undefined2 *)(unaff_ESI + 3);
  return;
}

