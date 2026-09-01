/* UpdateBuddyStatus - 0x00401fa0 in the original binary.
 *
 * Finds the buddy node named by the regEcx key (via FUN_00401bb0's
 * case-insensitive walk over the registry regEax points at) and stores
 * the incoming status block regEsi into it: the presence byte
 * regEsi[0] always goes to node+0x30, and the 16-byte location payload
 * at regEsi+8 goes to node+0x31..+0x40 only when the 6-byte checksum
 * over regEsi[8..0xd] (each byte XORed with the 'c','o','m','s','i','k'
 * key constants) matches the short at regEsi+0xe.
 *
 * The buddy identity is external, on both sides.  Callers: two of the
 * four binary sites (0x411fcc/0x412118 in FUN_00411b40, the
 * 0xa2xx-opcode messenger handler) pass regEax = &DAT_00e53e88, the
 * registry CBuddyPanel::Update iterates with
 * FindActiveObjectByIndex(&DAT_00e53e88, row); the other two are
 * DispatchDirectLinkPacket's case 0x1001 and the FUN_00403d20 vtable
 * twin.  Consumer: RenderBuddyRow (0x505f10) draws exactly the fields
 * written here - node+0x30 selects the state icon and, for state 0x12,
 * the shorts at +0x31/+0x33 become the row's "%3d" room numbers.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void UpdateBuddyStatus(int regEax,char *regEcx,undefined1 *regEsi)

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

