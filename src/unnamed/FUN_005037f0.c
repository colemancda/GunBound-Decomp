/* FUN_005037f0 - 0x005037f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTERS RECOVERED (2026-08-28).  ESI is the DESTINATION and EDI
 * the SOURCE: 0x5037f5 `mov dl,[ecx+edi]` reads EDI before anything writes it,
 * 0x503800 `mov [ecx+esi],dl` and 0x503805 `mov [esi+9],al` write through ESI.
 * A bounded 8-character copy into a 10-byte field, length byte at dest+9 and a
 * NUL at dest+len.  Bare ret and no ESP-relative access anywhere in the body,
 * so there are zero stack parameters and this is an append, not a re-slot.
 *
 * All four call sites are in FUN_00501770 under the frame key
 * local_N = esp_base + (0x4990 - N).  Two take packet bytes -- the 8-byte
 * field at pcVar12 + 0x10 (orig 0x5018d1) and at the current pcVar12 inside
 * the buddy-record loop (orig 0x5019c4) -- and two take stack fields the
 * caller has already built, &local_4924 on the 0x3001 path and
 * &local_4944 + 0x12 on the 0x4001 path.
 */
#include "ghidra_types.h"


void FUN_005037f0(int regEsi,int regEdi)

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
  } while (bVar1 < 8);
  *(byte *)(unaff_ESI + 9) = bVar1;
  *(undefined1 *)((uint)bVar1 + unaff_ESI) = 0;
  return;
}

