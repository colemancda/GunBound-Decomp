/* IntMap_Lookup_14 - 0x00500900 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlMap::Lookup(key, VALUE& value) - the
 * bool overload - for the 0x14-node int-keyed maps.  GetNode is
 * IntMap_Find_14 (0x500911; map in ECX, key in EDI); on a miss return
 * false (`xor al,al`), otherwise copy the 8-byte m_value at node+4/+8
 * out through EBX and return true (`mov al,1`).
 *
 * The one binary caller, FUN_004ff770 at 0x4ffa0b, looks up the packet's
 * key ([esp+0x306] in EDI) in the map at peer-record+0x20 (`add esi,
 * 0x20; mov ecx,esi`) with the out-value at `lea ebx,[esp+0x40]`, and
 * drops the packet when it is found (`jne 0x4ffbd1`, the exit).  Only on
 * a miss does it go on to IntMap_SetAt_14 the same key with the current
 * FILETIME (0x4ffb2c) - lookup-then-insert, the bool Lookup's use.
 * FUN_005006f0 (0x5006f0) is the other overload, CPair*
 * Lookup(key), for the 0x1768-node maps.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * ECX and EDI PROMOTED (2026-08-25) on top of the already-recovered EBX: the
 * map and the key, both falling through from this wrapper's own caller.  The
 * find's three out-slots share the 12-byte local_c.
 */
#include "ghidra_types.h"


undefined4 IntMap_Lookup_14(undefined4 *regEbx,int *regEcx,uint regEdi)

{
  int iVar1;
  undefined1 local_c [12];
  
  iVar1 = IntMap_Find_14(regEcx,(undefined4 *)local_c,(uint *)(local_c + 4),(uint *)(local_c + 8),
               regEdi);
  if (iVar1 == 0) {
    return 0;
  }
  *regEbx = *(undefined4 *)(iVar1 + 4);
  regEbx[1] = *(undefined4 *)(iVar1 + 8);
  return 1;
}

