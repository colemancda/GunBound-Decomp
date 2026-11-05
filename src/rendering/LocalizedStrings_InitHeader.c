/* LocalizedStrings_InitHeader - 0x004154c0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004154c0 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: the only
 * caller is LocalizedStrings_Construct (0x40d160), which passes the map in
 * EAX and EDX = 10. It zeroes header words 0-3 and 5 (root, count, free
 * list, block chain, nil) and stores 10 in word 4.
 * LocalizedStrings_BuyNode (0x43e150) later reads that word as the node-
 * pool block size (it mallocs word4*0x18+4 and threads word4 nodes), and
 * word 5 as the lazily allocated nil sentinel, which this zeroes. The
 * 'header' wording is a description of the six-word map header, not a
 * library member name.
 *
 * EAX RECOVERED (2026-08-25): the map object, from FUN_0040d160's `mov
 * eax,esi` (its `this`); ECX (param_1) is a phantom there and EDX (param_2)
 * is the literal 10, the initial bucket count.
 */
#include "ghidra_types.h"


void __fastcall LocalizedStrings_InitHeader(undefined4 param_1,undefined4 param_2,undefined4 *regEax)

{
  *regEax = 0;
  regEax[1] = 0;
  regEax[2] = 0;
  regEax[3] = 0;
  regEax[4] = param_2;
  regEax[5] = 0;
  return;
}

