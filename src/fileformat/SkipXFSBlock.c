/* SkipXFSBlock - 0x004f0650 in the original binary.
 *
 * NAMED (batch 41). Skips one size-prefixed block of an open XFS entry
 * stream without decoding it. The stream context arrives in ESI (the body
 * reads it at +0x1000 file handle, +0x1010 file position, +0x100c
 * in-block offset). It seeks to the position, reads a 4-byte block size,
 * advances the position past size + 8 bytes (the 4-byte size, the payload
 * and 4 more bytes of framing) and zeroes the in-block offset, returning
 * true in AL; false if the seek or the 4-byte read fails. It is the
 * no-decode twin of DecodeXFSEntryBlock (0x4f03f0), which opens with the
 * same SetFilePointer/ReadFile of the 4-byte size.
 *
 * Evidence (outside the body): the sole caller, SkipXFSEntryBytes
 * (0x4f08a0), loops it once per whole 0x1000 bytes of a skip that crosses
 * block boundaries, adding 0x1000 to its logical position each time, and
 * finishes with DecodeXFSEntryBlock for the final partial block. Its
 * `mov esi,eax` at 0x4f08a1 makes ESI the stream the call at 0x4f0910
 * inherits.
 *
 * The 8 byte framing is inferred from the arithmetic only; whether the
 * extra 4 bytes are a trailer is not confirmed. ESI promoted to the
 * trailing parameter `stream` (SkipXFSEntryBytes passes its own).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


uint SkipXFSBlock(int stream)

{
  uint uVar1;
  int iVar2;
  int unaff_ESI = stream;
  DWORD local_8;
  int local_4;
  
  uVar1 = SetFilePointer(*(HANDLE *)(unaff_ESI + 0x1000),*(LONG *)(unaff_ESI + 0x1010),(PLONG)0x0,0)
  ;
  if (uVar1 != 0xffffffff) {
    uVar1 = ReadFile(*(HANDLE *)(unaff_ESI + 0x1000),&local_4,4,&local_8,(LPOVERLAPPED)0x0);
    if (local_8 == 4) {
      iVar2 = *(int *)(unaff_ESI + 0x1010) + local_4 + 8;
      *(int *)(unaff_ESI + 0x1010) = iVar2;
      *(undefined4 *)(unaff_ESI + 0x100c) = 0;
      return CONCAT31((int3)((uint)iVar2 >> 8),1);
    }
  }
  return uVar1 & 0xffffff00;
}

