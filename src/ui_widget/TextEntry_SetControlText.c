/* TextEntry_SetControlText - 0x00506f60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): TWO register arguments, not the one the
 * backlog tracked. 0x506f60 takes no stack argument at all - its
 * epilogue is a bare `ret` and the body reads no [esp+N] - so both
 * inputs are registers, and both are read before written.
 *
 * ESI -> regEsi   the text to seed. Null-checked, handed to
 *                 SetWindowTextA (with the empty string at DAT_00551cb1
 *                 substituted when null), then strcpy'd into the
 *                 control's own +0x38 buffer.
 * EDI -> regEdi   the CEditBox itself: +4 is the "has an HWND" flag
 *                 that gates the SetWindowTextA, +0x38 the text buffer,
 *                 +0x13c a cursor field the tail zeroes.
 *
 * Recovering it took three callers with it, because at each site EDI is
 * a value its own function had also dropped:
 *
 *   FUN_005056c0  0x5056ee  EDI = *(*(regEbx + 0xc) + index*4), the
 *                 child widget Widget_FindChildIndex just located in the
 *                 container held in that function's own dropped EBX;
 *                 ESI = its param_1, which `ret 4` says it takes and
 *                 which its caller already passes but which the port
 *                 declared void.
 *   BuildCreateRoomDialog 0x50827d  EDI = the CreateTextEntryWidget
 *                 result (the room-name box); ESI = [esp+0x30] at
 *                 esp = entry-0x20, i.e. entry+0x10 = a FOURTH stack
 *                 parameter that `ret 0x10` accounts for and that the
 *                 C++ twin's signature was missing. Its raw-C caller
 *                 OpenCreateRoomDialog already passes it: DAT_005b3368,
 *                 the "GameName" default.
 *   FUN_00508a50  0x508b2d  EDI = the CreateTextEntryWidget result;
 *                 ESI = [esp+0x24] at esp = entry-0x1c, i.e. entry+8 =
 *                 a SECOND stack parameter that `ret 8` accounts for.
 *                 State09_ReadyRoom_OnCommand already passes it as
 *                 g_clientContext + 0x44e64.
 *
 * Both frame models are confirmed independently: BuildCreateRoomDialog's
 * by `mov eax,[esp+0x24] / mov ecx,[esp+0x28]` at 0x508213, which land
 * on the arg2/arg3 the C++ twin already names, and FUN_00508a50's by
 * `mov ecx,[esp+0x10]` at 0x508b74 landing on the SEH fs:[0] slot the
 * epilogue restores from.
 *
 * Still open next door: Widget_FindChildIndex (0x50e620) takes its
 * container in ECX and two more values in ESI and EDI (0 and 2 at this
 * site), and all 25 of its call sites are argless. Left alone here
 * rather than half-filled.
 */
#include "ghidra_types.h"


void TextEntry_SetControlText(char *regEsi,int regEdi)

{
  char cVar1;
  int iVar2;
  char *unaff_ESI = regEsi;
  int unaff_EDI = regEdi;
  HWND hWnd;
  LPCSTR lpString;
  
  if (*(char *)(unaff_EDI + 4) != '\0') {
    if (unaff_ESI == (char *)0x0) {
      hWnd = *(HWND *)(g_sharedTextInputControl + 4);
      lpString = &DAT_00551cb1;
    }
    else {
      hWnd = *(HWND *)(g_sharedTextInputControl + 4);
      lpString = unaff_ESI;
    }
    SetWindowTextA(hWnd,lpString);
  }
  iVar2 = (unaff_EDI + 0x38) - (int)unaff_ESI;
  do {
    cVar1 = *unaff_ESI;
    unaff_ESI[iVar2] = cVar1;
    unaff_ESI = unaff_ESI + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)(unaff_EDI + 0x13c) = 0;
  return;
}

