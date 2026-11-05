/* StringMap_RemoveAll_IntThunk - 0x0040d1b0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say thunk_FUN_00415600 mean this function.)
 *
 * NAMED (2026-11-05), CERTAIN. The five bytes at 0x40d1b0 are a bare `jmp
 * 0x415600`, i.e. a tail-jump thunk to StringMap_RemoveAll_Int
 * (FUN_00415600 in the paragraph below is that function), with the map
 * still in EAX. Its only caller is the atexit destructor FUN_00543300 (`mov
 * eax,0xe9bea8; jmp 0x40d1b0`), so it is the ChooseEvent.txt table's
 * destructor stub. The Thunk suffix follows CString_DestructThunk and
 * PanelManager_BaseDestructorThunk.
 *
 * MAP PASSED THROUGH (2026-10-30): 0x40d1b0 is a bare `jmp 0x415600`, so
 * the map FUN_00415600 reads from EAX is whatever this thunk's caller put
 * there.  Its one caller, FUN_00543300 (the atexit destructor), sets
 * `mov eax,0xe9bea8` at 0x543300.  The port now takes the map as
 * (int *regEax) and forwards it instead of calling FUN_00415600() with
 * nothing.
 */
#include "ghidra_types.h"


void StringMap_RemoveAll_IntThunk(int *regEax)

{
  StringMap_RemoveAll_Int(regEax);
  return;
}

