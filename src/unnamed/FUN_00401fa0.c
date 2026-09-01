/* FUN_00401fa0 - 0x00401fa0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00401fa0(int regEax,char *regEcx,undefined1 *regEsi)

{
  int iVar1;
  (void)regEcx; /* the name key: mov ebx,ecx at 0x401fa2 feeds FUN_00401bb0's
                   still-dropped unaff_EBX (__stricmp key at 0x401bd5); pass it
                   through when FUN_00401bb0 is promoted. */
  
  iVar1 = FUN_00401bb0(regEax);
  if (iVar1 != 0) {
    *(undefined1 *)(iVar1 + 0x30) = *regEsi;
    if (*(short *)(regEsi + 0xe) ==
        (ushort)((ushort)(regEsi[0xb] ^ 0x73) + (ushort)(regEsi[0xd] ^ 0x6b) +
                 (ushort)(regEsi[9] ^ 0x6f) + (ushort)(regEsi[10] ^ 0x6d) +
                 (ushort)(regEsi[0xc] ^ 0x69) + (ushort)(regEsi[8] ^ 99))) {
      *(undefined4 *)(iVar1 + 0x31) = *(undefined4 *)(regEsi + 8);
      *(undefined4 *)(iVar1 + 0x35) = *(undefined4 *)(regEsi + 0xc);
      *(undefined4 *)(iVar1 + 0x39) = *(undefined4 *)(regEsi + 0x10);
      *(undefined4 *)(iVar1 + 0x3d) = *(undefined4 *)(regEsi + 0x14);
    }
  }
  return;
}

