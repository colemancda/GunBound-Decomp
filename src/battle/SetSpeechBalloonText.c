/* SetSpeechBalloonText - 0x00450600 in the original binary.
 *
 * Sets the speech balloon's text: copies the string to balloon+0x1d4,
 * clears the 100-dword line buffer at +0x44 that InitSpeechBalloon
 * (0x44fd00) zero-initialised, and word-wraps the text into it via
 * RenderWrappedText (0x41b4b0, a wrap-into-buffer layout routine, not a
 * screen draw) - wrap width 15 chars, 20-byte line slots.  Sole caller is
 * SpawnSpeechBalloon (0x4382d0), whose regEbx is the chat line or
 * localized taunt the balloon displays - see that file's header for the
 * caller-side evidence.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void __fastcall SetSpeechBalloonText(int param_1,char *regEax)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  undefined4 *puVar4;
  
  pcVar2 = regEax;
  do {
    cVar1 = *pcVar2;
    pcVar2[(param_1 + 0x1d4) - (int)regEax] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  puVar4 = (undefined4 *)(param_1 + 0x44);
  for (iVar3 = 100; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  pcVar2 = regEax + 1;
  do {
    cVar1 = *regEax;
    regEax = regEax + 1;
  } while (cVar1 != '\0');
  RenderWrappedText((undefined4 *)(param_1 + 0x44),param_1 + 0x1d4,0x14,0xf,(int)regEax - (int)pcVar2,0);
  return;
}

