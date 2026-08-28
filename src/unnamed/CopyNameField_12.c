/* CopyNameField_12 - 0x004fe5d0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED REGISTERS RECOVERED (2026-08-28).  ESI is the DESTINATION and EDI
 * the SOURCE: 0x4fe5d5 `mov dl,[ecx+edi]` reads EDI before anything writes it,
 * 0x4fe5e0 `mov [ecx+esi],dl` and 0x4fe5e5 `mov [esi+0x11],al` write through
 * ESI.  A bounded 16-character copy into an 18-byte field, length byte at
 * dest+0x11 and a NUL at dest+len -- the buddy-list id field.  Bare ret and no
 * ESP-relative access, so zero stack parameters: an append, not a re-slot.
 *
 * All four call sites are in FUN_00501770: the 0x1011 record loop (dest
 * local_48f0, src pcVar12), the 0x2021 arm (dest local_4958, src
 * &local_4668), the 0x3001 arm (dest local_48f0, src &local_496c) and the
 * 0x4001 record loop (dest &local_4944, src iVar7).
 *
 * CAVEAT on the 0x2021 site: the original writes 18 bytes at esp_base+0x38,
 * but the port declares that slot as `undefined1 local_4958 [4]` with
 * local_4954/local_4950/local_494c modelling what are really its +4/+8/+0xc
 * fields.  The argument is right; the declaration is a pre-existing
 * split-struct defect in the caller and is not fixed here.
 *
 * NAMED (2026-08-28): one of three copies of the same fixed-width name
 * field assignment, distinguished by the width of the record they write.
 * The suffix is that record width in hex, on the container-stride
 * convention: CopyNameField_12 writes 0x12 = 18 bytes (up to 16
 * characters, NUL at dest+len, length byte at +0x11), CopyNameField_e
 * writes 0xe = 14 (12 characters, length at +0xd) and CopyNameField_a
 * writes 0xa = 10 (8 characters, length at +9). Note the suffix is the
 * BYTE COUNT, not the character count - CopyNameField_e is the one that
 * takes 12 characters.
 *
 * The record shape is corroborated from outside these three functions.
 * Vector_CopyElement_1e (0x503770) already carries the same `char text[N]; byte
 * len at the end` layout for a 0x11-byte key, and StringMap_SetAt_28
 * (0x503e30) upserts entries whose KEY is an 18-byte record of this
 * exact shape and whose VALUE is a 14-byte one - the value being, at
 * five of its six call sites, the buffer the immediately preceding
 * CopyNameField_e call has just filled. Vector_CopyElement_34 copies a
 * record made of three of these fields end to end (18 + 22 + 10 + 2 =
 * 0x34), which is a third independent sighting of the layout.
 *
 * The trio's call sites are all in FUN_00501770, the CBuddy2 buddy-list
 * packet handler, where the 18-byte field is the account id, the
 * 14-byte one the nickname and the 10-byte one the 8-character guild
 * field.
 *
 * NOT the only emission of the 18-byte copy: FUN_004fdc50 is the same
 * routine again with the destination in EAX and the source in ESI
 * instead of ESI/EDI. It is left unnamed deliberately - the only thing
 * separating the two is which registers carry the arguments, and a
 * register allocation is not a semantic discriminator, so a second
 * CopyNameField_12-shaped name would be indistinguishable from this one.
 */
#include "ghidra_types.h"


void CopyNameField_12(int regEsi,int regEdi)

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
  } while (bVar1 < 0x10);
  *(byte *)(unaff_ESI + 0x11) = bVar1;
  *(undefined1 *)((uint)bVar1 + unaff_ESI) = 0;
  return;
}

