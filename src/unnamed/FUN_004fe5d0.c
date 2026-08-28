/* FUN_004fe5d0 - 0x004fe5d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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
 */
#include "ghidra_types.h"


void FUN_004fe5d0(int regEsi,int regEdi)

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

