/* InitSpeechBalloon - 0x0044fd00 in the original binary.
 *
 * Constructor for the speech-balloon entity: stamps class id 500000 at
 * obj+4 and the slot/id (regEax) at obj+8 - the battle entity registry
 * convention (class at +4, index key at +8) documented for
 * InitJewel/InitMobile - installs the 0x555b54 vtable, and zeroes the
 * two 100-dword blocks at +0x44 (the wrapped-line buffer
 * SetSpeechBalloonText fills via RenderWrappedText) and +0x2dc.  Sole
 * caller is SpawnSpeechBalloon (0x4382d0), right after
 * operator_new(0x46c); its callers key the balloon by a player/jewel
 * slot, and SpawnJewel evicts the class-500000 registry node at index
 * slot+8 - which is exactly the pair this writes.
 *
 * RECOVERED (2026-09-01): the prerequisite caller promotions landed in
 * the same batch as this note - the regEax parameter below is live and
 * every site passes the verified value; see the commit for the chain.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 * __fastcall InitSpeechBalloon(undefined4 param_1,undefined4 *param_2,undefined4 regEax)

{
  int iVar1;
  undefined4 *puVar2;
  
  param_2[2] = regEax;
  param_2[6] = 0xffffffff;
  param_2[9] = 0xffffffff;
  param_2[3] = 0;
  param_2[4] = 0;
  *(undefined1 *)(param_2 + 5) = 0;
  *(undefined1 *)((int)param_2 + 0x15) = 0;
  param_2[7] = 0;
  *(undefined1 *)(param_2 + 8) = 0;
  param_2[10] = 0;
  param_2[0xb] = 0;
  param_2[0x10] = 0;
  param_2[1] = 500000;
  *param_2 = &PTR_FUN_00555b54;
  puVar2 = param_2 + 0x11;
  for (iVar1 = 100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = param_2 + 0xb7;
  for (iVar1 = 100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_2[0xb5] = 0;
  param_2[0xb6] = 0;
  return param_2;
}

