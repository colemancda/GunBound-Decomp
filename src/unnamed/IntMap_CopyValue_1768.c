/* IntMap_CopyValue_1768 - 0x004ff240 in the original binary.
 *
 * Copies one value record into a node of the 0x1768-stride integer-keyed
 * map: three header dwords, the word at +0xc, the length word at +0xe, then
 * that many bytes from +0x10 (rep movsd + rep movsb), then the trailer
 * dwords at +0x174c/+0x1750/+0x1754 and the byte at +0x1758.  It is the
 * value-assignment tail of that map's SetAt wrapper, FUN_004fed40.
 *
 * NAME EVIDENCE.  The suffix is the NODE STRIDE, as it is everywhere else in
 * this family (StringMap_Find_1c/Insert_1c, IntMap_Find_14/Insert_14,
 * IntMap_Find_1768/Insert_1768) -- NOT the 0x175c bytes this function moves.
 * The arithmetic is what ties it to 0x1768:
 *
 *   - Both call sites write to node+4 (`lea eax,[esi+4]`, ESI = the node
 *     IntMap_Find_1768 or IntMap_Insert_1768 just returned), so the value
 *     slot starts 4 bytes in, after the key at node+0.
 *   - The last byte copied is +0x1758, so the value is 0x1759 bytes, 0x175c
 *     padded.  4 + 0x175c = 0x1760 -- exactly the next pointer
 *     IntMap_Find_1768 walks (`puVar2[0x5d8]`) -- and +0x1764 is the hash it
 *     compares (`puVar2[0x5d9]`).  4 + 0x175c + 4 + 4 = 0x1768, the stride
 *     IntMap_Insert_1768 carves at (`regEsi[9] * 0x1768 + 4`).
 *
 * So this is the map's record, not the 0x1750 array's: the two share a
 * 0x174c prefix but the map's has an extra FILETIME + dword + byte, which is
 * the trailer copied here.  Compare the twin CArray_CopyElement_1750, which
 * really does copy an array element.
 *
 * Parameters keep Ghidra's names, as CArray_CopyElement_1750's do, so the
 * family stays uniform: param_1 is the ECX phantom (`mov ecx,edx` kills it
 * before any read -- both call sites pass 0), param_2 is EDX, the source
 * record, and regEax is the destination node+4.
 *
 * EAX RECOVERED (2026-08-25): the DESTINATION of a ~0x1758-byte record copy.
 * Both call sites are in FUN_004fed40 -- one on the hot path, one in the cold
 * block past its epilogue -- and both set it with `lea eax,[esi+4]` where ESI
 * is the node the map find or insert just returned, i.e. the source's iVar2.
 * EDX (param_2) is the copy SOURCE and is FUN_004fed40's own second stack
 * parameter, read at [esp+0x20] on the hot path and [esp+0x1c] on the cold
 * one -- different offsets, the same E+8 slot.  ECX is a phantom.
 */
#include "ghidra_types.h"


void __fastcall IntMap_CopyValue_1768(undefined4 param_1,undefined4 *param_2,undefined4 *regEax)

{
  ushort uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  *regEax = *param_2;
  regEax[1] = param_2[1];
  regEax[2] = param_2[2];
  *(undefined2 *)(regEax + 3) = *(undefined2 *)(param_2 + 3);
  uVar1 = *(ushort *)((int)param_2 + 0xe);
  *(ushort *)((int)regEax + 0xe) = uVar1;
  puVar3 = param_2 + 4;
  puVar4 = regEax + 4;
  for (uVar2 = (uint)(uVar1 >> 2); uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  for (uVar2 = uVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined1 *)puVar4 = *(undefined1 *)puVar3;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  }
  regEax[0x5d3] = param_2[0x5d3];
  regEax[0x5d4] = param_2[0x5d4];
  regEax[0x5d5] = param_2[0x5d5];
  *(undefined1 *)(regEax + 0x5d6) = *(undefined1 *)(param_2 + 0x5d6);
  return;
}

