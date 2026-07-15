/* FUN_00426780 - 0x00426780 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-15): a string-keyed hash-table lookup (computes the
 * string's hash, then walks the matching bucket's chain for an exact
 * match via __mbscmp). `table` (the hash table object, was `in_EAX`) and
 * `key` (the string being looked up, was `unaff_EBX`) were both dropped
 * registers. Confirmed via angr disassembly of the sole caller,
 * ParseChooseEventLine (0x409cb0-0x409cc7): `mov ebx,eax` at that
 * function's own entry (ebx = its own incoming EAX = param_2, the parsed
 * line/message) is never touched before `mov eax,esi; call 0x426780`
 * (esi = that function's own param_1, the event registry) - i.e. table
 * and key are ParseChooseEventLine's own param_1/param_2, still live in
 * EAX/EBX at the call.
 */
#include "ghidra_types.h"


undefined4 * FUN_00426780(uint *param_1,uint *param_2,undefined4 *param_3,int *table,
                           uchar *key)

{
  uchar *puVar1;
  uchar uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  uchar *puVar7;

  uVar5 = 0;
  uVar2 = *key;
  puVar7 = key;
  while (uVar2 != '\0') {
    uVar5 = uVar5 * 0x21 + (int)(char)uVar2;
    puVar1 = puVar7 + 1;
    puVar7 = puVar7 + 1;
    uVar2 = *puVar1;
  }
  *param_2 = uVar5;
  *param_1 = uVar5 % (uint)table[2];
  if (*table != 0) {
    *param_3 = 0;
    puVar3 = (undefined4 *)0x0;
    puVar4 = *(undefined4 **)(*table + *param_1 * 4);
    while( true ) {
      if (puVar4 == (undefined4 *)0x0) {
        return (undefined4 *)0x0;
      }
      if ((puVar4[3] == *param_2) && (iVar6 = __mbscmp((uchar *)*puVar4,key), iVar6 == 0))
      break;
      puVar3 = puVar4;
      puVar4 = (undefined4 *)puVar4[2];
    }
    *param_3 = puVar3;
    return puVar4;
  }
  return (undefined4 *)0x0;
}

