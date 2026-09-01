/* HashMap_FreeNode_2c - 0x00405290 in the original binary.
 *
 * ATL7 CAtlMap::FreeNode of the 0x2c-node instantiation whose RemoveAll
 * is HashMap_RemoveAll_2c (0x404b90) - the only binary caller, and the
 * source of the stride and prefix derivation (see that file's header).
 * The member is the library shape shared with the named
 * StringMap_FreeNode_ac: push the node onto m_pFree at map+0x2c (link
 * through node+0x24), decrement m_nElements at map+4, Rehash
 * (FUN_00405150) at PickSize (FUN_00500e30) when the count drops under
 * the low threshold at map+0x1c and auto-rehash is unlocked (map+0x20),
 * and free the plex chain at map+0x28 when the map empties.  No key or
 * value destruction - POD elements.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void HashMap_FreeNode_2c(int regEax,int regEsi)

{
  int *piVar1;
  undefined4 uVar2;
  int *_Memory;
  uint uVar3;
  
  thunk_FUN_00405320();
  *(undefined4 *)(regEax + 0x24) = *(undefined4 *)(regEsi + 0x2c);
  uVar3 = *(int *)(regEsi + 4) - 1;
  *(int *)(regEsi + 0x2c) = regEax;
  *(uint *)(regEsi + 4) = uVar3;
  if ((uVar3 < *(uint *)(regEsi + 0x1c)) && (*(int *)(regEsi + 0x20) == 0)) {
    uVar2 = FUN_00500e30();
    FUN_00405150(regEsi,uVar2);
  }
  if (*(int *)(regEsi + 4) == 0) {
    _Memory = *(int **)(regEsi + 0x28);
    *(undefined4 *)(regEsi + 0x2c) = 0;
    if (_Memory != (int *)0x0) {
      do {
        piVar1 = (int *)*_Memory;
        _free(_Memory);
        _Memory = piVar1;
      } while (piVar1 != (int *)0x0);
      *(undefined4 *)(regEsi + 0x28) = 0;
    }
  }
  return;
}

