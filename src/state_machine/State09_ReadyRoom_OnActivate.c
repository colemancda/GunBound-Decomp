/* State09_ReadyRoom_OnActivate - 0x004d54c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall State09_ReadyRoom_OnActivate(undefined4 param_1,int param_2)

{
  if (param_2 == 1) {
    RefreshReadyRoomControls(param_1,1,0);
  }
  return;
}

