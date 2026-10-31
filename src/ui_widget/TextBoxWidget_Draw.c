/* TextBoxWidget_Draw - 0x0040ca20 in the original binary.
 *
 * The text box's draw: slot 3 of its vtable 0x55208c (words 0x40ca00
 * 0x461c60 0x429800 0x40ca20 0x429800). Ghidra never carved it, so this
 * port is written from the disassembly. The body runs from 0x40ca20 to
 * the `ret` at 0x40cc42 (547 bytes; 0x40cc50 is the next function,
 * FUN_0040cc50). `mov ebp,ecx` at 0x40ca29 and a plain `ret`, so `this`
 * arrives in ECX and there are no stack arguments. Its only reference is
 * the vtable, and DrawActiveObjectRegistry (0x4062b0) dispatches slot 3
 * as __fastcall(this), so the port takes that shape.
 *
 * Fields, as InitTextBoxWidget (0x40c980) stores them: +0x38 x, +0x3c y,
 * +0x40 w, +0x44 h, +0x48 the text (0x400 bytes), +0x448 the mode,
 * +0x44c the length limit, +0x450 the masked flag, +0x454 the horizontal
 * scroll in pixels.
 *
 *   0x40ca3c SetClipRect(ECX = x, EAX = x+w, ESI = y+h, EDI = y)
 *   0x40ca44 len = strlen(text) -> [esp+0x14]
 *   0x40ca60 a loop counts i up to strlen(text) and stores nothing; then
 *            0x40ca7c `mov byte [esp+edx+0x24],0` terminates buf at i.
 *            So buf (the masked text drawn when +0x450 is set) holds
 *            whatever was on the stack below the terminator. The port
 *            keeps that: buf is left uninitialised except buf[i].
 *   0x40ca73 switch on +0x448:
 *     2 (focused): 0x40cab2 TextEntry_FetchSelectionAndPlaceImeCaret
 *            (push scroll, y, x; EDI = [0x7934e4]; EAX = &selEnd
 *            [esp+0x18]; ESI = &selStart [esp+0x20]). caret =
 *            (selStart == -1 ? strlen(text) : selStart) * 6. If caret <
 *            scroll then scroll = caret (0x40cae2); if caret > scroll + w
 *            then scroll = caret - w (0x40caf9). Then the selection box:
 *            width = (selEnd == -1 ? strlen : selEnd)*6 - caret + 2,
 *            left = caret - scroll + x. Two DrawHLine (EAX = left,
 *            EDX = width, EDI = y and y+0xb, push 0xf800) at 0x40cb67 and
 *            0x40cb7a, and two DrawVLine (EDI = left and left+width-1,
 *            EAX = y, ECX = 0xc, EBX = 0xf800) at 0x40cb92 and 0x40cba8.
 *            Then the text in 0xffe0 if masked (buf), else 0xffff (text).
 *     1: the text in 0x7bef, buf if masked (0x40cbd8).
 *     0: the text in 0xffff, buf if masked (0x40cbf5).
 *     any other value: no text.
 *   0x40cc1d BlitRLESprite(ECX = x - scroll, push y, push colour,
 *            EAX = the string)
 *   0x40cc33 SetClipRect(0, 0x31f, 0x257, 0), the full screen
 *
 * Every callee takes its register arguments as parameters in the port:
 * SetClipRect (x1 = ECX, x2 = EAX, y1 = ESI, y2 = EDI),
 * TextEntry_FetchSelectionAndPlaceImeCaret (regEdi/regEax/regEsi),
 * DrawHLine (EDX length, stack colour, regEax x, regEdi y), DrawVLine
 * (ECX length, regEax y, regEbx colour, regEdi x) and BlitRLESprite
 * (rleData = EAX).
 *
 * NAMED 2026-10-31, CERTAIN (was FUN_0040ca20). Vtable 0x55208c is
 * stored only by InitTextBoxWidget (at 0x40c9f0); its slot 0 adapter is
 * the already-named TextBoxWidget_ScalarDelete. Slot 3 is the draw slot
 * of this five-slot active-object family: DrawActiveObjectRegistry
 * dispatches `call [eax+0xc]` (0x4062e4) over the registry these boxes
 * live in, and the sibling vtable 0x551e44 (CButtonWidget) holds
 * DrawButtonWidget in the same slot. The prefix pairs it with
 * TextBoxWidget_ScalarDelete.
 */
#include "ghidra_types.h"


void __fastcall TextBoxWidget_Draw(int this_)

{
  char *text;
  int len;
  int i;
  int selEnd;
  int selStart;
  int caret;
  int left;
  int width;
  int x;
  int y;
  int colour;
  char *str;
  char buf[0x3f0];

  x = *(int *)(this_ + 0x38);
  y = *(int *)(this_ + 0x3c);
  SetClipRect(x,*(int *)(this_ + 0x40) + x,*(int *)(this_ + 0x44) + y,y);
  text = (char *)(this_ + 0x48);
  len = (int)strlen(text);
  i = 0;
  if (len != 0) {
    do {
      i = i + 1;
    } while ((uint)i < strlen(text));
  }
  buf[i] = '\0';
  switch (*(int *)(this_ + 0x448)) {
  case 2:
    TextEntry_FetchSelectionAndPlaceImeCaret(x,y,*(int *)(this_ + 0x454),
                                             (int)g_sharedTextInputControl,
                                             (undefined4 *)&selEnd,&selStart);
    if (selStart == -1) {
      caret = (int)strlen(text) * 6;
    }
    else {
      caret = selStart * 6;
    }
    if (caret < *(int *)(this_ + 0x454)) {
      *(int *)(this_ + 0x454) = caret;
    }
    if (*(int *)(this_ + 0x454) + *(int *)(this_ + 0x40) < caret) {
      *(int *)(this_ + 0x454) = caret - *(int *)(this_ + 0x40);
    }
    if (selStart == -1) {
      caret = (int)strlen(text) * 6;
    }
    else {
      caret = selStart * 6;
    }
    if (selEnd == -1) {
      selEnd = (int)strlen(text);
    }
    width = selEnd * 6 - caret + 2;
    left = (caret - *(int *)(this_ + 0x454)) + *(int *)(this_ + 0x38);
    y = *(int *)(this_ + 0x3c);
    DrawHLine(0,width,0xf800,left,y);
    DrawHLine(0,width,0xf800,left,y + 0xb);
    DrawVLine(0xc,y,0xf800,left);
    DrawVLine(0xc,y,0xf800,left + width + -1);
    if (*(int *)(this_ + 0x450) != 0) {
      colour = 0xffe0;
      str = buf;
    }
    else {
      colour = 0xffff;
      str = text;
    }
    break;
  case 1:
    colour = 0x7bef;
    str = (*(int *)(this_ + 0x450) != 0) ? buf : text;
    break;
  case 0:
    colour = 0xffff;
    str = (*(int *)(this_ + 0x450) != 0) ? buf : text;
    break;
  default:
    SetClipRect(0,0x31f,0x257,0);
    return;
  }
  BlitRLESprite(*(int *)(this_ + 0x38) - *(int *)(this_ + 0x454),*(int *)(this_ + 0x3c),colour,
                (byte *)str);
  SetClipRect(0,0x31f,0x257,0);
  return;
}
