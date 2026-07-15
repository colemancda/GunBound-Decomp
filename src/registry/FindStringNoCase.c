/* FindStringNoCase - 0x00401610 in the original binary.
 *
 * Case-insensitive linear search for `needle` in `table` (table[0]=count,
 * table[1]=base of a char* array) - returns the matching index, or -1.
 * ResolveNamedState's own name-table lookup (see that file's header).
 *
 * FIXED (2026-07-15): `table` (unaff_EDI) and `needle` (unaff_EBX) were
 * both dropped registers. Recovered via angr disassembly of the sole
 * caller, ResolveNamedState (0x461c64-0x461c70): `mov edi,[esi+0x1c]`
 * (this+0x1c = table) then `mov ebx,[esp+0x10]` (2nd stack arg = needle)
 * right before `call 0x401610`, with neither register touched in between -
 * matches Mobile.h's own already-documented "+0x24 = FindStringNoCase(),
 * sets +0x20/+0x34" comment exactly.
 */
#include "ghidra_types.h"


int FindStringNoCase(int *table, char *needle)

{
  int iVar1;
  int iVar2;

  iVar2 = 0;
  if (0 < *table) {
    do {
      iVar1 = __stricmp(needle,*(char **)(table[1] + iVar2 * 4));
      if (iVar1 == 0) {
        return iVar2;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < *table);
  }
  return -1;
}

