/* FUN_004fdc50 - 0x004fdc50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * Two register arguments recovered, both proven read-before-written. EAX is
 * the destination record: it is never assigned in the body and is first read
 * at 0x004fdc62 (mov byte ptr [edx+eax], bl), 0x004fdc67 (mov byte ptr
 * [eax+0x11], cl) and 0x004fdc6d (mov byte ptr [ecx+eax], 0). ESI is the
 * source string: first touch is the read at 0x004fdc56 (mov bl, byte ptr
 * [edx+esi]) and nothing writes it. ECX, EDX and EBX are phantoms - ECX's
 * first touch is the write at 0x004fdc50 (xor cl, cl), EDX's is the write at
 * 0x004fdc53 (movzx edx, cl), and EBX is a push/pop callee save whose first
 * real touch is the write at 0x004fdc56. EDI and EBP are never referenced.
 *
 * The function terminates in a bare ret at 0x004fdc72 and contains no
 * esp-relative reads at all - every memory operand is [edx+esi], [edx+eax],
 * [eax+0x11] or [ecx+eax] - so it takes zero stack arguments, matching the
 * previously declared empty list. All four call sites push nothing, so the
 * two parameters are appended rather than re-slotted.
 *
 * Behaviour: copy up to 16 bytes of a NUL-terminated name from ESI to EAX,
 * stopping at the terminator or at 0x10 bytes, then store the copied length
 * in the byte at EAX+0x11 and write a NUL at EAX+length. The destination is
 * therefore an 18-byte record laid out as char name[17] followed by a length
 * byte. MSVC inlined this same routine twice inside the sole caller
 * FUN_00501770 (at 0x501f7c and 0x502443), and Ghidra rendered the second
 * copy as local_4914[i] / local_4903 = len / local_4914[len] = 0, which
 * independently fixes the +0x11 length slot.
 *
 * All four call sites are in FUN_00501770. Each was paired to its source
 * statement by a witness rather than by position: at every site the same lea
 * expression that loads EAX or ESI is re-issued within a few instructions at
 * identical stack depth, and Ghidra named that second occurrence, so the
 * argument can be read off Ghidra's own local names. 0x5018e4 takes
 * local_48ba + 0x40 and local_4914, witnessed by the
 * StringMap_SetAt_28(local_48ba + 0x40) that follows at 0x5018ed and by
 * the FUN_004fcd80(local_4914, ...)
 * that fills the source at 0x5018d4. 0x50209a takes local_48ba + 0x2e and
 * the address of local_496c, witnessed by
 * StringMap_SetAt_28(local_48ba + 0x2e) at 0x5020a3. 0x5020e0 takes
 * local_4914 and the address of local_496c, witnessed by
 * FUN_00502750(..., local_4914) at 0x5020ef. 0x50242c takes
 * local_48ba + 0x1c and the address of local_496c, witnessed by the
 * FUN_00503a50(local_4970, and local_496c) immediately before at 0x50241c
 * and by the [esp+0xd6] equals local_48ba base that Ghidra pinned at
 * 0x501f9b.
 *
 * The three destinations local_48ba + 0x1c, + 0x2e and + 0x40 are
 * consecutive 18-byte records that end exactly at the 82-byte end of char
 * local_48ba[82], which is a further consistency check on the offsets.
 */
#include "ghidra_types.h"


void FUN_004fdc50(int regEax,int regEsi)

{
  int in_EAX = regEax;
  byte bVar1;
  uint uVar2;
  int unaff_ESI = regEsi;
  
  uVar2 = 0;
  do {
    bVar1 = (byte)uVar2;
    if (*(char *)(uVar2 + unaff_ESI) == '\0') break;
    bVar1 = bVar1 + 1;
    *(char *)(uVar2 + in_EAX) = *(char *)(uVar2 + unaff_ESI);
    uVar2 = (uint)bVar1;
  } while (bVar1 < 0x10);
  *(byte *)(in_EAX + 0x11) = bVar1;
  *(undefined1 *)((uint)bVar1 + in_EAX) = 0;
  return;
}

