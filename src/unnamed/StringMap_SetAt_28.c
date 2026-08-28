/* StringMap_SetAt_28 - 0x00503e30 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * THE HASH SLOT (2026-08-25).  The original passes the find `&param_1` for
 * its hash out-parameter -- reusing the incoming parameter slot, whose value
 * it has already cached in EBP -- and then reads the hash back out of that
 * slot for the insert while EBP still holds the original key.  A C port
 * cannot alias param_1 that way without losing the key, so the hash gets a
 * local of its own and param_1 keeps meaning what it means at the entry.
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
 * DROPPED REGISTERS RECOVERED (2026-08-28), and the previous note's reading
 * of them corrected.
 *
 * ESI is NOT a destination and this is not a name-field copy - that
 * paragraph was copy-pasted from CopyNameField_e and does not describe this
 * function. StringMap_SetAt_28 is a string-map upsert. The pushed stack
 * argument is the KEY: it goes straight into StringMap_Find_28 and, on a
 * miss,
 * StringMap_Insert_28. EDI is the MAP OBJECT - 0x503e48 mov eax,edi feeds
 * the find, 0x503e53 cmp dword ptr [edi],0 tests the empty-table case and
 * 0x503e5e push edi builds it. ESI is a 14-byte VALUE RECORD that the
 * function READS, never writes: 0x503e85-0x503e9d copies [esi], [esi+4],
 * [esi+8] and word [esi+0xc] into entry+0x12, entry+0x16, entry+0x1a,
 * entry+0x1e. EAX and EBX are phantoms - both are written before any read
 * (0x503e39 lea eax,[esp+0xc] and 0x503e44 lea ebx,[esp+0x14]).
 *
 * All six call sites are in FUN_00501770 and every one of them passes the
 * map at param_1+0x17cc for EDI. Five of the six pass for ESI the exact
 * buffer that the immediately preceding CopyNameField_e call just filled
 * - that helper writes up to 12 characters, a NUL at dest+len and a
 * length byte at dest+0xd, which is the 14 bytes this function copies
 * out, so the pairing
 * is self-witnessing rather than positional. The sixth site, at 0x501faf on
 * the 0x2010 path, passes esp_base+0x6c, filled by the same
 * 12-characters-plus-length-at-+0xd loop written out inline at
 * 0x501f50-0x501f6e.
 *
 * ret 4 matches the one declared stack parameter, so regEsi and regEdi are a
 * clean append, not a re-slot.
 *
 * THE CALLER'S CURSOR. The earlier note claimed Ghidra dropped
 * FUN_00501770's whole EBX packet walk. It did not. EBX survives as a named
 * local in every branch that feeds these helpers - pcVar12 on the 0x1011
 * path, iVar7 on the 0x4001 path, plain param_2 offsets on the 0x3001 path -
 * and only the incremental add ebx,N steps were folded into the offsets of
 * the reads the decompiler kept. The read at src line 364, pcVar12 + 0x18,
 * IS 0x50190b mov ax,[ebx+8] taken with ebx = pcVar12 + 0x10. So no new
 * cursor local was added: each dropped source is an offset off the cursor
 * variable already in the C, and inserting redundant += steps would have
 * forced rewriting three currently-correct reads for no gain in fidelity.
 * The lea ebx,[edi-0x2c8] at 0x50184d that the old note read as the start of
 * the walk is not part of it - it is local_4970 = param_1 - 0x2c8, stored to
 * [esp+0x20] at 0x501853, and at the same time FUN_00503bb0's
 * already-recovered regEbx argument; EBX is reloaded from local_4980 at
 * 0x50188b before the first helper call.
 *
 * WHAT THE CURSOR WALKS. FUN_00501770 is the CBuddy2 buddy-list packet
 * handler - it creates the window titled CBuddy2 Timer Receiving Window at
 * 0x501a53. On the 0x1011 path the cursor reads a ushort result, a 4-byte
 * field echoed straight back by sendto, a 12-byte owner nick copied to the
 * scratch record at param_1+0x179c, an 8-byte field, a ushort, then a ushort
 * entry count capped at 100, then that many records: 16-byte id, 12-byte
 * nick, one flag byte that is either absent-marker or the first byte of a
 * 20-byte note, an 8-byte field and a ushort status. Each record's nick is
 * upserted into the param_1+0x17cc map under its id. The 0x4001 path walks
 * the same shape without the note field, 0x26 bytes per record.
 *
 * NAMED (2026-08-28): ATL7's CAtlMap<K,V>::SetAt out of VC7.1's
 * atlcoll.h - `find the node for key; if there is none, create one;
 * assign the value into it` - for the 0x28-node instantiation. Every
 * piece of that is already a named neighbour rather than something read
 * off this control flow: the find is StringMap_Find_28, the create is
 * StringMap_Insert_28, the lazy `if (m_ppBins == NULL) InitHashTable(
 * m_nBins, true)` guard is HashMap_InitHashTable with the E_OUTOFMEMORY
 * 0x8007000e that atlcoll.h throws when it fails, and the class itself
 * is settled by HashMap_Construct's identification of the container as
 * CAtlMap.
 *
 * The suffix is the node stride, matching StringMap_Find_28 and
 * StringMap_Insert_28, which are the two members this one calls; the
 * node is payload below +0x20, m_pNext at +0x20, m_nHash at +0x24.
 * Inside that payload the layout falls out of the arguments: the KEY is
 * the pushed 18-byte name record occupying +0 to +0x11, and the VALUE
 * is the 14-byte name record this copies to +0x12 - which is exactly the
 * pair of record widths CopyNameField_12 and CopyNameField_e write.
 */
#include "ghidra_types.h"


void StringMap_SetAt_28(undefined4 param_1,undefined4 *regEsi,int *regEdi)

{
  char cVar1;
  int iVar2;
  undefined4 *unaff_ESI = regEsi;
  int *unaff_EDI = regEdi;
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

