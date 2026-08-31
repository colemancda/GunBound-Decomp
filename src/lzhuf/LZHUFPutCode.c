/* LZHUFPutCode - 0x004ea230 in the original binary.
 *
 * DROPPED-REG FIX (2026-08-31): the LZHUF context arrives in EAX
 * (write-side bit buffer +0xf6b4, bit count +0xf6b6, dest +0xf6bc,
 * cursor +0xf6c8), promoted to a trailing regEax after the __fastcall
 * ECX code / EDX length pair. EAX is never written here, which is what
 * lets EncodeLZHUFBlock's sites hand the same context straight on to
 * LZHUFUpdate after this returns.
 *
 * Classic LZHUF Putcode(): shifts code bits into the bit accumulator
 * (state+0xf6b4), flushing whole bytes to the output while the bit
 * count (state+0xf6b6) >= 8. NAMED (2026-07-18).
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall LZHUFPutCode(uint param_1,int param_2,int regEax)

{
  byte bVar1;
  int iVar2;
  byte bVar3;
  char cVar4;
  
  bVar3 = *(byte *)(regEax + 0xf6b6);
  bVar1 = bVar3 + param_2;
  *(byte *)(regEax + 0xf6b6) = bVar1;
  *(ushort *)(regEax + 0xf6b4) = *(ushort *)(regEax + 0xf6b4) | (ushort)(param_1 >> (bVar3 & 0x1f));
  if (7 < bVar1) {
    *(undefined1 *)(*(int *)(regEax + 0xf6bc) + *(int *)(regEax + 0xf6c8)) =
         *(undefined1 *)(regEax + 0xf6b5);
    bVar3 = *(char *)(regEax + 0xf6b6) - 8;
    iVar2 = *(int *)(regEax + 0xf6c8) + 1;
    *(byte *)(regEax + 0xf6b6) = bVar3;
    *(int *)(regEax + 0xf6c8) = iVar2;
    if (7 < bVar3) {
      *(undefined1 *)(iVar2 + *(int *)(regEax + 0xf6bc)) = *(undefined1 *)(regEax + 0xf6b4);
      cVar4 = *(char *)(regEax + 0xf6b6) + -8;
      *(int *)(regEax + 0xf6c8) = *(int *)(regEax + 0xf6c8) + 1;
      *(char *)(regEax + 0xf6b6) = cVar4;
      *(int *)(regEax + 4) = *(int *)(regEax + 4) + 2;
      *(short *)(regEax + 0xf6b4) = (short)(param_1 << (param_2 - cVar4 & 0x1fU));
      return;
    }
    *(ushort *)(regEax + 0xf6b4) = (ushort)*(byte *)(regEax + 0xf6b4) << 8;
    *(int *)(regEax + 4) = *(int *)(regEax + 4) + 1;
  }
  return;
}

