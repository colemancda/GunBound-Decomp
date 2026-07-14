/* FindXFSEntryIndex - 0x004f11a0 in the original binary.
 *
 * Binary search over an XFS archive's sorted entry table, returning the
 * ENTRY INDEX of a name match (or 0xffffffff if absent). This is the
 * mutable-table twin of FindXFSEntry (0x4f1110), which returns the entry
 * RECORD pointer instead; both share the same search structure and the
 * same CompareXFSEntryName ordering.
 *
 * Dropped registers recovered from disassembly (confirmed via angr):
 *   archive     (EBX)                 - the XFSArchive object; `*(archive+8)`
 *                                       is the entry count, `archive+0x40..`
 *                                       is the chunk-pointer array (0x400
 *                                       records of 0x80 bytes per chunk).
 *   searchName  (1st stack arg)       - loaded into EAX right before each
 *                                       CompareXFSEntryName call; the name
 *                                       being searched for.
 * The record pointer computed in the loop condition (Ghidra discarded it
 * because only its address-taken form was used) is restored so it can be
 * passed as CompareXFSEntryName's second argument, matching FindXFSEntry.
 * Called only by FindOrInsertXFSEntry.
 */
#include "ghidra_types.h"


uint FindXFSEntryIndex(int archive, char *searchName)

{
  bool searchedOnce;
  int chunk;
  int record;
  int cmp;
  uint half;
  uint hi;
  uint mid;
  uint lo;
  uint prevMid;

  hi = *(uint *)(archive + 8);
  mid = hi >> 1;
  searchedOnce = false;
  lo = 0;
  while ((chunk = *(int *)(archive + 0x40 + (mid >> 10) * 4), chunk != 0 &&
         ((mid & 0x3ff) * 0x80 + chunk != 0))) {
    record = (mid & 0x3ff) * 0x80 + chunk;
    cmp = CompareXFSEntryName(searchName, (char *)record);
    if (cmp == 0) {
      return mid;
    }
    prevMid = mid;
    if (cmp < 0) {
      hi = mid;
      prevMid = lo;
    }
    half = hi - prevMid >> 1;
    mid = half + prevMid;
    lo = prevMid;
    if (half == 0) {
      if (searchedOnce) {
        return 0xffffffff;
      }
      searchedOnce = true;
    }
  }
  return 0xffffffff;
}
