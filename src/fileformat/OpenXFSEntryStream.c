/* OpenXFSEntryStream - 0x004f1390 in the original binary.
 *
 * Open an XFS archive entry for reading: look the entry up by name (or
 * insert it), allocate a 0x1024-byte read state, and hand it to
 * ReadXFSEntry, which primes it against the archive's file handle / decode
 * area. Returns the read state (consumed by ReadXFSEntryByte), or 0 if the
 * entry is missing or the allocation fails.
 *
 * This was the root of the FUN_004f0990 (CompareXFSEntryName) NULL-deref
 * crash chain. Ghidra rendered it __thiscall(param_1, param_2) and every
 * caller invoked it as `FUN_004f1390(0)`, which (a) set the ECX flag to 0
 * so it wrongly took the insert branch, and (b) left the name (EAX) and
 * archive (EDI) registers as garbage, so the eventual name compare
 * dereferenced junk. All four inputs are recovered from disassembly
 * (confirmed via angr - every one of the 15 call sites uses flag=1,
 * insertFlag=0):
 *   archive     (EDI)          - the XFSArchive object
 *   name        (EAX)          - the entry name to open
 *   findExisting (CL)          - 1 => FindXFSEntry (read existing);
 *                                0 => FindOrInsertXFSEntry (create)
 *   insertFlag  (1st stack arg) - passed through to FindOrInsertXFSEntry's
 *                                flag; unused on the findExisting path
 *
 * The ReadXFSEntry call was also under-supplied by the raw port (it dropped
 * the operator_new read state entirely and mis-passed the entry as the
 * read-state arg). Restored to the real 5-arg convention recovered from
 * ReadXFSEntry's own entry (readState, handle=*(archive+0x1040), flag,
 * entry, lzhuf=archive+0x1048).
 */
#include "ghidra_types.h"


undefined4 OpenXFSEntryStream(int archive, char *name, char findExisting, undefined4 insertFlag)

{
  int entry;
  void *readState;
  uint index;

  if (findExisting == '\0') {
    if ((*(char *)(archive + 0x1044) == '\0') && (*(char *)(archive + 0x1045) == '\0')) {
      index = FindOrInsertXFSEntry(archive, name, insertFlag);
      *(char *)(archive + 0x1044) = 1;
      readState = operator_new(0x1024);
      if (readState != (void *)0x0) {
        entry = *(int *)(archive + 0x40 + (index >> 10) * 4);
        if (entry == 0) {
          entry = 0;
        }
        else {
          entry = (index & 0x3ff) * 0x80 + entry;
        }
        return ReadXFSEntry(readState, *(undefined4 *)(archive + 0x1040), 0, entry,
                            archive + 0x1048);
      }
    }
  }
  else {
    entry = FindXFSEntry((void *)archive, name);
    if (entry != 0) {
      readState = operator_new(0x1024);
      if (readState != (void *)0x0) {
        return ReadXFSEntry(readState, *(undefined4 *)(archive + 0x1040), 1, entry,
                            archive + 0x1048);
      }
    }
  }
  return 0;
}
