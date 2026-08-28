/* SeedTT800State - 0x00504c10 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-REG FIX (2026-08-28): ESI is the state block being seeded -
 * `mov [esi],0` is the first instruction, and every word the function
 * writes is an index off it. Nothing writes ESI in the body, so it is a
 * read-before-write live-in.
 *
 * All three call sites load it with `lea`, not `mov` - an ADDRESS, which
 * callsite_regs.py renders identically to a load - and each is pinned by
 * the byte store immediately before the call, whose offset the source
 * already spells out one line above:
 *
 *   0x4fd1eb  lea esi,[ebp+0x1d2c]  after `mov byte [ebp+0x1d28],bl`
 *             = the source's `*(undefined1 *)(param_1 + 0x74a) = 0`
 *   0x4fd208  lea esi,[ebp+0x1fb0]  after `mov byte [ebp+0x1fac],bl`
 *             = `*(undefined1 *)(param_1 + 0x7eb) = 0`
 *   0x4fdf1c  lea esi,[edi+0x210]   after `mov byte [edi+0x20c],bl`
 *             = `*(undefined1 *)(unaff_EDI + 0x83) = 0`
 *
 * ConstructCommP2POwner's (was FUN_004fd0f0) EBP is its param_1 (`mov ebp,[esp+0x18]` at 0x4fd107
 * with the SEH triple plus ebx and ebp pushed, i.e. entry+4).
 *
 * NAMED (2026-08-28): this seeds a TT800 generator, and the evidence is
 * the CONSUMER of the block rather than this body. FUN_00504d80, the
 * next function in the image, is TT800's genrand over the very same
 * layout:
 *
 *   `if (*state == 0x19)` - N = 25, the point at which TT800 refills
 *   `x = x >> 1 ^ mag01[x & 1] ^ x[+7]` - M = 7, the twist, with mag01
 *      indexed as state[(x & 1) + 0x1a], i.e. the two words this
 *      function writes last
 *   `y ^= (y & 0x56b64a) << 7` - 0x56b64a << 7 is 0x2b5b2500, TT800's
 *      first tempering mask
 *   `y ^= (y & 0xffffb716) << 15` - the second
 *
 * and the constant this function stores into state[0x1b] is 0x8ebfd028,
 * which is TT800's published mag01[1] verbatim. So the block is
 * state[0] = the index k, state[1..0x19] = the 25 state words, and
 * state[0x1a..0x1b] = mag01[2] = { 0, 0x8ebfd028 } - exactly the
 * assignments below, including the zeroed index and the zeroed mag01[0].
 *
 * What this function does with the 25 words is fill them with
 * process-local entropy: GetTickCount, GetCurrentThreadId,
 * GetCurrentProcessId, time(), clock() and GetVersion, each mixed with a
 * distinct constant and then re-mixed across the remaining words. It is
 * the seeding routine, not the generator.
 */
#include "ghidra_types.h"


void SeedTT800State(undefined4 *regEsi)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  DWORD DVar4;
  DWORD DVar5;
  uint uVar6;
  undefined4 *unaff_ESI = regEsi;
  uint uVar7;
  
  *unaff_ESI = 0;
  DVar4 = GetTickCount();
  unaff_ESI[1] = DVar4 ^ 0x95f24dab;
  DVar4 = GetCurrentThreadId();
  DVar5 = GetTickCount();
  unaff_ESI[2] = DVar4 ^ DVar5 ^ 0xb685215;
  DVar4 = GetCurrentProcessId();
  DVar5 = GetTickCount();
  unaff_ESI[3] = DVar4 ^ DVar5 ^ 0xe76ccae7;
  uVar6 = FID_conflict___time32((__time32_t *)0x0);
  DVar4 = GetTickCount();
  unaff_ESI[4] = uVar6 ^ DVar4 ^ 0xaf3ec239;
  uVar6 = _clock();
  DVar4 = GetVersion();
  DVar5 = GetTickCount();
  uVar7 = uVar6 ^ DVar4 ^ DVar5;
  uVar6 = unaff_ESI[1];
  unaff_ESI[6] = uVar6 ^ 0x24a590ad;
  uVar1 = unaff_ESI[2];
  unaff_ESI[7] = uVar1 ^ 0x69e4b5ef;
  uVar2 = unaff_ESI[3];
  unaff_ESI[8] = uVar2 ^ 0xbf456141;
  uVar3 = unaff_ESI[4];
  unaff_ESI[9] = uVar3 ^ 0x96bc1b7b;
  unaff_ESI[10] = uVar7 ^ 0xd6e25506;
  unaff_ESI[0xb] = uVar6 ^ 0xc1de75b7;
  unaff_ESI[0xc] = uVar1 ^ 0x8858a9c9;
  unaff_ESI[0xd] = uVar2 ^ 0x2da87693;
  unaff_ESI[0xe] = uVar3 ^ 0xb657f9dd;
  unaff_ESI[0xf] = uVar7 ^ 0x8e8327bc;
  unaff_ESI[0x10] = uVar6 ^ 0x8121da71;
  unaff_ESI[0x11] = uVar1 ^ 0x8b823ecb;
  unaff_ESI[0x12] = uVar2 ^ 0x885d05f5;
  unaff_ESI[5] = uVar7 ^ 0x715fad23;
  unaff_ESI[0x13] = uVar3 ^ 0x4e20cd47;
  unaff_ESI[0x19] = uVar7 ^ 0xd7e807f8;
  unaff_ESI[0x14] = uVar7 ^ 0x2bc578fa;
  unaff_ESI[0x15] = uVar6 ^ 0x512c0c03;
  unaff_ESI[0x18] = uVar3 ^ 0x8891a8a1;
  unaff_ESI[0x16] = uVar1 ^ 0xea857ccd;
  unaff_ESI[0x17] = uVar2 ^ 0x4cc1d30f;
  unaff_ESI[0x1a] = 0;
  unaff_ESI[0x1b] = 0x8ebfd028;
  return;
}

