/* NextTT800Random - 0x00504d80 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence: SeedTT800State (0x504c10, named from the same layout) fills
 * a state block whose word 0 is the index k, words 1..0x19 the 25-word
 * state and words 0x1a..0x1b the mag01 pair {0, 0x8ebfd028} - TT800's
 * published constant. This function is the generator step over that exact
 * block: it refills when k == 0x19 (N = 25, M = 7 twist through
 * state[(x & 1) + 0x1a]), then returns state[k] tempered with TT800's
 * masks (0x56b64a << 7 and 0xffffb716 << 15) and xor-shifted by 16, and
 * advances k. Its only caller, EncryptStringIntoContext, calls it four
 * times to build the 16-byte key it hands to RijndaelSetKey, i.e. it
 * returns one 32-bit random word per call.
 *
 * Calling convention: the state pointer arrives in EDX (0x504d80 starts
 * `cmp [edx],0x19`); ECX is overwritten before use, so param_1 is a
 * dummy. The sole call site (0x5051f7) does `lea edx,[edi+0x20c]` with
 * EDI = the crypto context, so the argument is context + 0x20c; the port
 * passed nothing and now passes it.
 */
#include "ghidra_types.h"


uint __fastcall NextTT800Random(undefined4 param_1,int *param_2)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  
  if (*param_2 == 0x19) {
    puVar1 = (uint *)(param_2 + 1);
    iVar3 = 3;
    do {
      *puVar1 = *puVar1 >> 1 ^ param_2[(*puVar1 & 1) + 0x1a] ^ puVar1[7];
      puVar1[1] = puVar1[1] >> 1 ^ param_2[(puVar1[1] & 1) + 0x1a] ^ puVar1[8];
      puVar1[2] = puVar1[2] >> 1 ^ param_2[(puVar1[2] & 1) + 0x1a] ^ puVar1[9];
      puVar1[3] = puVar1[3] >> 1 ^ param_2[(puVar1[3] & 1) + 0x1a] ^ puVar1[10];
      puVar1[4] = puVar1[4] >> 1 ^ param_2[(puVar1[4] & 1) + 0x1a] ^ puVar1[0xb];
      puVar1[5] = puVar1[5] >> 1 ^ param_2[(puVar1[5] & 1) + 0x1a] ^ puVar1[0xc];
      puVar1 = puVar1 + 6;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    puVar1 = (uint *)(param_2 + 0x13);
    iVar3 = 7;
    do {
      *puVar1 = *puVar1 >> 1 ^ param_2[(*puVar1 & 1) + 0x1a] ^ puVar1[-0x12];
      puVar1 = puVar1 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    *param_2 = 0;
  }
  uVar2 = param_2[*param_2 + 1] ^ (param_2[*param_2 + 1] & 0x56b64aU) << 7;
  uVar2 = uVar2 ^ (uVar2 & 0xffffb716) << 0xf;
  *param_2 = *param_2 + 1;
  return uVar2 >> 0x10 ^ uVar2;
}

