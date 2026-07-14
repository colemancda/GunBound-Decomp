/* CompareXFSEntryName - 0x004f0990 in the original binary.
 *
 * Case-insensitive comparison of two XFS entry-name strings, used by the
 * archive binary-search/insert helpers (FindXFSEntry, FindXFSEntryIndex,
 * FindOrInsertXFSEntry) to order and match entry names.
 *
 * Convention recovered from disassembly (confirmed via angr): the two
 * strings arrive in EAX (`a`) and EDX (`b`); Ghidra kept EDX as param_2
 * but dropped EAX. Every caller loads `a` into EAX immediately before the
 * call, so both are promoted to explicit parameters here. Returns
 * (foldcase(*a) - foldcase(*b)) at the first differing byte, 0 if equal.
 */
#include "ghidra_types.h"


int CompareXFSEntryName(char *a, char *b)

{
  int ca;
  int cb;

  while( true ) {
    if ((*a == '\0') && (*b == '\0')) {
      return 0;
    }
    cb = (int)*b;
    ca = (int)*a;
    if ((0x40 < ca) && (ca < 0x5b)) {
      ca = ca + 0x20;
    }
    if ((0x40 < cb) && (cb < 0x5b)) {
      cb = cb + 0x20;
    }
    if (ca - cb != 0) break;
    a = a + 1;
    b = b + 1;
  }
  return ca - cb;
}
