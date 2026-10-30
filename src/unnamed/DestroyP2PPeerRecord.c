/* DestroyP2PPeerRecord - 0x004ff210 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, LIKELY (was FUN_004ff210).  The destructor paired
 * with ConstructP2PPeerRecord: it frees the +0x80 array buffer, then
 * IntMap_RemoveAll_1768 on +0x50 and IntMap_RemoveAll_14 on +0x20 -
 * the three members that constructor builds, in reverse order.  Its one
 * caller is the 0xac map's node destructor FUN_00500f80, `add eax,0x14;
 * jmp 0x4ff210` - i.e. it destroys the value slot at node+0x14 - reached
 * through thunk_FUN_00500f80 from StringMap_FreeNode_ac.  Same LIKELY
 * basis as ConstructP2PPeerRecord: the role is certain, the "peer
 * record" handle is FindP2PPeerRecord's.
 *
 * RECORD RECOVERED (2026-10-30): the record arrives in EAX (`mov
 * esi,eax` at 0x4ff211, read before any write), now the trailing
 * parameter regEax.  The chain that supplies it: StringMap_FreeNode_ac
 * holds the retiring node in EAX at its `call 0x500f70` (0x500e83, EAX
 * untouched since entry - `mov edi,eax` at 0x500e81 only copies it);
 * thunk_FUN_00500f80 (0x500f70) is a bare `jmp 0x500f80`; FUN_00500f80
 * is `add eax,0x14; jmp 0x4ff210`.  So the record is node+0x14.  All
 * three ports were argless; each now takes and passes EAX.
 */
#include "ghidra_types.h"


void DestroyP2PPeerRecord(int regEax)

{
  int in_EAX = regEax;
  
  if (*(void **)(in_EAX + 0x80) != (void *)0x0) {
    _free(*(void **)(in_EAX + 0x80));
  }
  IntMap_RemoveAll_1768((int *)(in_EAX + 0x50));
  IntMap_RemoveAll_14((int *)(in_EAX + 0x20));
  return;
}

