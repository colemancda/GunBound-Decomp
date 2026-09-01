/* HasP2PPeerRecord - 0x00504bb0 in the original binary.
 *
 * NAMED 2026-09-01, LIKELY rather than certain.  Copies a 16-char id
 * into a local and returns whether StringMap_Find_ac finds it in the
 * string map at this+0x290.  What that map is comes from outside this
 * body: HashMap_Construct's header measured it being built at +0x290 of
 * the CCommP2P sub-object inside InitCommP2PNotifyWindow (the `lea` at
 * 0x4fdf3c), and its 0xac-stride records hold the peer's two
 * address/port pairs - FUN_005039a0 compares an incoming (ip,port,
 * ip2,port2) against rec+0x14's fields and FUN_004fe8d0 (re)writes
 * them, feeding the P2P send path next to DispatchP2PMessage.  So the
 * map is the id-keyed P2P peer table and this predicate reports whether
 * a peer entry exists.  "LIKELY" because the sole caller (0x504800, see
 * below) is unported and the record semantics rest on the still-unnamed
 * FUN_004fe860/FUN_005039a0 pair rather than on a named consumer.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * STACK PARAMETER RESTORED (2026-08-25): `ret 4` says one stack argument and
 * Ghidra declared none, leaving the raw `stack0x00000004` artifact where the
 * find's param_3 should be.  [esp+0x30] at 0x504be5 (four pushes pending over
 * `sub esp,0x1c`) is that argument, and the object whose map lives at +0x290.
 * Its one call site, 0x504811, is inside a function that has not been carved,
 * so no source caller needs updating.
 *
 * ESI PROMOTED to regEsi (2026-08-31): the 0x10-char name-string pointer the
 * copy loop reads.  At 0x504811 the caller (0x504800, __thiscall, ret 0x18)
 * sets ESI at 0x50480c via `mov esi,[esp+0x10]` with edi+esi saved, i.e.
 * entry [esp+8] = its SECOND stack argument; param_1 is its raw ECX this
 * (pushed at 0x504810, BEFORE the `add edi,-0x2c` at 0x504816).  When
 * 0x504800 is carved it must pass its second stack argument here.
 */
#include "ghidra_types.h"


bool HasP2PPeerRecord(int param_1,int regEsi)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined1 local_1c [10];
  char local_12 [17];
  byte local_1;
  
  uVar2 = 0;
  do {
    bVar1 = (byte)uVar2;
    if (*(char *)(uVar2 + regEsi) == '\0') break;
    bVar1 = bVar1 + 1;
    local_12[uVar2] = *(char *)(uVar2 + regEsi);
    uVar2 = (uint)bVar1;
  } while (bVar1 < 0x10);
  local_1 = bVar1;
  local_12[bVar1] = '\0';
  iVar3 = StringMap_Find_ac(local_12,(uint *)local_1c,(undefined4 *)&param_1,(int *)(param_1 + 0x290),
                       (uint *)(local_1c + 4));
  return iVar3 != 0;
}

