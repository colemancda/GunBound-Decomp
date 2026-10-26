/* FindRecentWhisperIndex - 0x004023b0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * EBX PROMOTED TO A REAL PARAMETER (2026-10-26, hand-verified via
 * disassembly). Ghidra read the base as `unaff_EBX`, an unconstrained
 * incoming register, but it is not: this function's sole caller,
 * ProcessIncomingWhisper (FUN_00402300), sets EBX to its own ECX
 * (`this`, the direct-link messenger context object) at entry
 * (`mov ebx,ecx` at 0x40230a) and never rewrites it before the
 * `call 0x4023b0` at 0x40235d - confirmed by disassembling the whole
 * span 0x402300-0x40239e, no intervening write to EBX. This function
 * scans the exact 13-byte-stride table at that object's +0xf28, with
 * count at +0x15a8, that ProcessIncomingWhisper itself appends a new
 * sender name to immediately after this call returns -1 - the recent-
 * whisper dedup table that gates ProcessIncomingWhisper's dedup-append
 * on whether the sender's name is already recorded.
 */
#include "ghidra_types.h"


int FindRecentWhisperIndex(int regEbx,char *param_1)

{
  int iVar1;
  int iVar2;
  char *_Str2;

  iVar2 = 0;
  if (0 < *(int *)(regEbx + 0x15a8)) {
    _Str2 = (char *)(regEbx + 0xf28);
    do {
      iVar1 = __stricmp(param_1,_Str2);
      if (iVar1 == 0) {
        return iVar2;
      }
      iVar2 = iVar2 + 1;
      _Str2 = _Str2 + 0xd;
    } while (iVar2 < *(int *)(regEbx + 0x15a8));
  }
  return -1;
}

