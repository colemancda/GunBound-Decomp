/* CopyNameField_16 - 0x005037d0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_005037d0).  A fourth width of the
 * CopyNameField_12 / _e / _a fixed-width counted-string assignment, same
 * body and same ESI = destination / EDI = source convention: copy up to
 * 0x14 characters, stop at a NUL, store the length byte at dest+0x15
 * and a NUL at dest+len. The suffix is the record width in hex on that
 * trio's convention - 0x16 = 22 bytes (char[0x15] + length byte) - not
 * the character count.
 *
 * The record width is corroborated from outside. Its one call site,
 * 0x5019bf in CommP2POwner_ProcessPacket, writes &local_48de =
 * local_48f0 + 0x12, in the block that assembles the 0x34-byte element
 * local_48f0 field by field - CopyNameField_12 at +0, this at +0x12,
 * CopyNameField_a at +0x28 (local_48c8), the word at +0x32 - and then
 * hands it to Vector_PushBack_34. Vector_CopyElement_34 copies that
 * element as char[0x11]/len +0x11, char[0x15]/len +0x27, char[9]/len
 * +0x31: the middle field is exactly a 0x16-byte record at +0x12 with
 * its length byte at +0x12+0x15 = +0x27.
 *
 * CALLER DEFECT, NOT FIXED: CommP2POwner_ProcessPacket declares that
 * element as separate locals (local_48f0[18], a one-byte local_48de,
 * local_48c9, local_48c8[10], local_48be), so this call writes 22 bytes
 * into a 1-byte local and MSVC need not lay the pieces out contiguously
 * for the push_backs that read local_48f0 as one 0x34-byte record. The
 * same split-struct class as the 0x2021-site caveat in CopyNameField_12;
 * the fix is to coalesce the element into one 0x34-byte buffer.
 *
 * ESI and EDI RECOVERED (2026-08-25) from the single site in CommP2POwner_ProcessPacket, under the
 * -0x4990 frame constant that function's earlier recoveries established and
 * that four independent slots agree on: `lea esi,[esp+0xb2]` = &local_48de and
 * `lea edi,[esp+0x4c]` = &local_4944.
 */
#include "ghidra_types.h"


void CopyNameField_16(int regEsi,int regEdi)

{
  byte bVar1;
  uint uVar2;
  
  uVar2 = 0;
  do {
    bVar1 = (byte)uVar2;
    if (*(char *)(uVar2 + regEdi) == '\0') break;
    bVar1 = bVar1 + 1;
    *(char *)(uVar2 + regEsi) = *(char *)(uVar2 + regEdi);
    uVar2 = (uint)bVar1;
  } while (bVar1 < 0x14);
  *(byte *)(regEsi + 0x15) = bVar1;
  *(undefined1 *)((uint)bVar1 + regEsi) = 0;
  return;
}

