/* FUN_005374e0 - 0x005374e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    ___ascii_memicmp
   
   Library: Visual Studio 2003 Release */

int __cdecl ___ascii_memicmp(void *_Buf1,void *_Buf2,size_t _Size)

{
  byte bVar1;
  byte bVar2;
  uint uVar4;
  undefined2 uVar3;
  
  do {
    if (_Size == 0) {
      return 0;
    }
    bVar2 = *(byte *)_Buf1;
    _Buf1 = (void *)((int)_Buf1 + 1);
    bVar1 = *(byte *)_Buf2;
    uVar4 = (uint)CONCAT11(bVar2,bVar1);
    _Buf2 = (void *)((int)_Buf2 + 1);
    if (bVar2 != bVar1) {
      if ((0x40 < bVar2) && (bVar2 < 0x5b)) {
        uVar4 = (uint)CONCAT11(bVar2 + 0x20,bVar1);
      }
      uVar3 = (undefined2)uVar4;
      bVar2 = (byte)uVar4;
      if ((0x40 < bVar2) && (bVar2 < 0x5b)) {
        uVar3 = (undefined2)CONCAT31((int3)(uVar4 >> 8),bVar2 + 0x20);
      }
      bVar2 = (byte)((ushort)uVar3 >> 8);
      if (bVar2 != (byte)uVar3) {
        if (bVar2 < (byte)uVar3) {
          return -1;
        }
        return 1;
      }
    }
    _Size = _Size - 1;
  } while( true );
}

