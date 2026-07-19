/* EncodeGuardedBool - 0x004064a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
/* DROPPED-REGISTER FIX (2026-07-19): the 3-byte obfuscated-bool cell is
 * addressed by ESI, an incoming register argument Ghidra emitted as an
 * uninitialised `unaff_ESI`. Confirmed read-before-write in the original:
 * 0x4064b5 `mov [esi],al` is the first store, with no prior write to ESI.
 * The port therefore wrote three bytes through whatever happened to be in
 * that local - it faulted on a write to 0x00000001 immediately after the
 * world server accepted the login. Promoted to an explicit parameter. */
#include "ghidra_types.h"


void EncodeGuardedBool(int param_1,byte *guardPtr)

{
  int iVar1;
  byte bVar2;
  byte *unaff_ESI = guardPtr;
  
  iVar1 = _rand();
  *unaff_ESI = (byte)iVar1;
  iVar1 = _rand();
  unaff_ESI[1] = (byte)iVar1;
  bVar2 = *unaff_ESI & 7;
  bVar2 = ~('\x01' << bVar2) & (byte)iVar1 | (param_1 != '\0') << bVar2;
  unaff_ESI[1] = bVar2;
  unaff_ESI[2] = (bVar2 + *unaff_ESI) - 0x34;
  return;
}

