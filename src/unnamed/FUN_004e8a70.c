/* FUN_004e8a70 - 0x004e8a70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * WHAT IT IS.  A red-black tree lookup keyed on a ushort: node _Left/_Parent/
 * _Right at +0/+4/+8, the key at +0xc and the _Isnil flag at +0xf, with the
 * header node at map+4.  The descent keeps the last node it turned left at,
 * then returns it only if its key is not GREATER than the target -- i.e. an
 * exact-match find, returning the header (end) when there is none.  Every
 * caller confirms the reading by comparing the result against the header
 * (`cmp eax,[0xe9af14]`, the map's own +4) and treating equality as "absent".
 *
 * REGISTERS PROMOTED (2026-08-27).  All 27 call sites passed nothing, so both
 * the key it compares and the slot it writes its answer into were whatever
 * happened to be in EBX and EAX.  `ret 0` with no stack arguments: ECX is the
 * map, EBX points at the ushort key, and EAX is the caller-allocated result
 * slot that 0x4e8ab6/0x4e8ac7 `mov [eax],ecx` fills -- MSVC returning a
 * 4-byte iterator through a hidden buffer pointer.
 *
 * MSVC __fastcall puts the second parameter in EDX rather than EAX, and the
 * third on the stack; the C semantics are what matter here, not reproducing
 * the original's register allocation.
 */
#include "ghidra_types.h"


void __fastcall FUN_004e8a70(int param_1,undefined4 *regEax,ushort *regEbx)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *in_EAX = regEax;
  ushort *unaff_EBX = regEbx;
  
  puVar3 = *(undefined4 **)(param_1 + 4);
  if (*(char *)((int)puVar3[1] + 0xf) == '\0') {
    puVar1 = (undefined4 *)puVar3[1];
    do {
      if (*(ushort *)(puVar1 + 3) < *unaff_EBX) {
        puVar2 = (undefined4 *)puVar1[2];
      }
      else {
        puVar2 = (undefined4 *)*puVar1;
        puVar3 = puVar1;
      }
      puVar1 = puVar2;
    } while (*(char *)((int)puVar2 + 0xf) == '\0');
  }
  if ((puVar3 != *(undefined4 **)(param_1 + 4)) && (*(ushort *)(puVar3 + 3) <= *unaff_EBX)) {
    *in_EAX = puVar3;
    return;
  }
  *in_EAX = *(undefined4 **)(param_1 + 4);
  return;
}

