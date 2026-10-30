/* FUN_00415600 - 0x00415600 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * HashMap_PickSize ARGS RECOVERED (2026-10-29): the call at 0x41566c
 * passed only a literal 0.  ECX = `mov ecx,esi` (the map), EAX = 0 (`xor
 * eax,eax`): RemoveAll's `InitHashTable(PickSize(0), false)`; witness: the
 * same esi is pushed as HashMap_InitHashTable's map right after (call at
 * 0x415673).  Now passes (in_EAX, 0).
 *
 * MAP PROMOTED TO A PARAMETER (2026-10-30): the map arrives in EAX
 * (`push esi; mov esi,eax` at 0x415600/0x415601, then every field access
 * is off ESI), but the port was declared (void) and read an uninitialised
 * in_EAX.  It is now (int *regEax).  The only binary caller is the jmp
 * thunk at 0x40d1b0 (thunk_FUN_00415600, `jmp 0x415600`, EAX passed
 * through), whose only caller is the atexit destructor FUN_00543300
 * (`mov eax,0xe9bea8; jmp 0x40d1b0` at 0x543300/0x543305), registered by
 * the static initialiser FUN_00540f20 (`push 0x543300; call _atexit` at
 * 0x540f2a/0x540f2f) right after it constructs the same global
 * (`mov eax,0xe9bea8; call 0x40d180`).  So the map is DAT_00e9bea8, the
 * ChooseEvent.txt table, and this is its RemoveAll run at exit.  A byte
 * scan of .text finds no other call/jmp to 0x415600 or 0x40d1b0.
 */
#include "ghidra_types.h"


void FUN_00415600(int *regEax)

{
  int iVar1;
  int node;
  int *piVar2;
  int *in_EAX = regEax;
  undefined4 uVar3;
  int *_Memory;
  uint uVar4;
  undefined4 uVar5;
  
  in_EAX[8] = in_EAX[8] + 1;
  if ((*in_EAX != 0) && (uVar4 = 0, in_EAX[2] != 0)) {
    do {
      iVar1 = *(int *)(*in_EAX + uVar4 * 4);
      while (iVar1 != 0) {
        node = iVar1;                      /* the node to release: captured before the advance */
        iVar1 = *(int *)(iVar1 + 8);
        HashTable_OnNodeRemoved(node,(int)in_EAX);
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < (uint)in_EAX[2]);
  }
  _free((void *)*in_EAX);
  *in_EAX = 0;
  in_EAX[1] = 0;
  if (in_EAX[8] == 0) {
    uVar5 = 0;
    uVar3 = HashMap_PickSize(in_EAX,0);
    HashMap_InitHashTable(in_EAX,uVar3,uVar5);
  }
  in_EAX[0xb] = 0;
  _Memory = (int *)in_EAX[10];
  if ((int *)in_EAX[10] != (int *)0x0) {
    do {
      piVar2 = (int *)*_Memory;
      _free(_Memory);
      _Memory = piVar2;
    } while (piVar2 != (int *)0x0);
    in_EAX[10] = 0;
  }
  in_EAX[8] = in_EAX[8] + -1;
  return;
}

