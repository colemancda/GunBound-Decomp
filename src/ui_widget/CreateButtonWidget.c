/* CreateButtonWidget - 0x00406020 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


void CreateButtonWidget(undefined4 param_1,int param_2,int param_3,int param_4,undefined4 param_5,
                       int param_6,int param_7,int param_8,int param_9,char param_10,int param_11)

{
  int *piVar1;
  int iVar2;
  char *pcVar3;
  
  piVar1 = operator_new(0x50);
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    piVar1[1] = param_2;
    piVar1[2] = param_3;
    piVar1[3] = 0;
    piVar1[4] = 0;
    *(undefined1 *)(piVar1 + 5) = 0;
    *(undefined1 *)((int)piVar1 + 0x15) = 0;
    piVar1[6] = -1;
    piVar1[7] = 0;
    *(undefined1 *)(piVar1 + 8) = 0;
    piVar1[10] = 0;
    piVar1[0xb] = 0;
    piVar1[9] = -1;
    *piVar1 = (int)&vtable_ButtonWidget;
  }
  piVar1[6] = param_4;
  piVar1[0x10] = param_8;
  piVar1[0xe] = param_6;
  piVar1[0xf] = param_7;
  piVar1[0x11] = param_9;
  piVar1[0x12] = param_11;
  iVar2 = FindPreloadedTextureByName(param_5);
  piVar1[7] = iVar2;
  if (param_10 == '\0') {
    pcVar3 = s_disable_00551e68;
  }
  else {
    if ((piVar1[9] != 3) && (piVar1[9] != -1)) goto LAB_004060f2;
    if ((char)piVar1[0x13] == '\x01') {
      (**(code **)(*piVar1 + 4))(s_active_00551e58);
      goto LAB_004060f2;
    }
    pcVar3 = s_ready_00551e80;
  }
  (**(code **)(*piVar1 + 4))(pcVar3);
LAB_004060f2:
  *(undefined1 *)(piVar1 + 0x13) = 0;
  if (piVar1[9] != 3) {
    (**(code **)(*piVar1 + 4))(s_ready_00551e80);
  }
  RegisterActiveObject();
  return;
}

