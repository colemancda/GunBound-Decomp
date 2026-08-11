/* FUN_004f16c0 - 0x004f16c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REGISTER FIX (2026-08-11): a skip-frame-fields helper for the
 * sprite-set loaders (FUN_004f18c0/FUN_004f1a50 call it for every frame
 * they don't want). The open XFS stream arrives in ESI - Ghidra dropped
 * it as `undefined4 unaff_ESI`; promoted to the `stream` parameter.
 * From the original disasm (0x4f16c0-0x4f1747): each of the five
 * FUN_004f08a0 seek calls sets `mov eax,esi` (stream) + `mov edx,N`
 * (byte count) with N = 0x14, 3, 0xc, then twice the dword just read
 * into [esp+4] (local_4); the two ReadXFSEntryByte calls carried their
 * counts in EAX (`mov eax,1` at 0x4f16d5, `mov eax,4` at 0x4f1702 and
 * 0x4f172a) which Ghidra also dropped.
 */
#include "ghidra_types.h"


void FUN_004f16c0(int stream)

{
  int iVar1;
  char local_5;
  int local_4;

  FUN_004f08a0(0,0x14,stream);
  iVar1 = ReadXFSEntryByte(stream,&local_5,1);
  if (iVar1 != -2) {
    FUN_004f08a0(0,3,stream);
    FUN_004f08a0(0,0xc,stream);
    iVar1 = ReadXFSEntryByte(stream,&local_4,4);
    if (iVar1 != -2) {
      FUN_004f08a0(0,local_4,stream);
      if (local_5 != '\0') {
        iVar1 = ReadXFSEntryByte(stream,&local_4,4);
        if (iVar1 != -2) {
          FUN_004f08a0(0,local_4,stream);
        }
      }
    }
  }
  return;
}
