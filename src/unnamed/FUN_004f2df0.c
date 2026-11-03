/* FUN_004f2df0 - 0x004f2df0 in the original binary.
 *
 * CARVED (2026-11-03). The only slot of the one-slot vtable 0x55752c, the
 * base-object vtable that a dozen destructors put back as their last step
 * (0x443eab, 0x455b44, 0x4711e0 ScrubObjectVtable, 0x4f1514, 0x4f2e10,
 * 0x4f3426, ...). Its only reference is that .data slot; nothing calls it
 * directly. The whole body, 0x4f2df0-0x4f2e0e (31 bytes; 0x4f2e0f is int3
 * padding and 0x4f2e10 is FUN_004f2e10):
 *
 *   0x4f2df0  test byte ptr [esp+4],1
 *   0x4f2df5  push esi
 *   0x4f2df6  mov  esi,ecx
 *   0x4f2df8  mov  dword ptr [esi],0x55752c
 *   0x4f2dfe  je   0x4f2e09
 *   0x4f2e00  push esi
 *   0x4f2e01  call 0x525546            ; free
 *   0x4f2e06  add  esp,4
 *   0x4f2e09  mov  eax,esi
 *   0x4f2e0b  pop  esi
 *   0x4f2e0c  ret  4
 *
 * So it is a __thiscall scalar-deleting destructor (`this` in ECX, the
 * delete flag on the stack) whose destructor body - the vtable reset that
 * FUN_004f2e10 and ScrubObjectVtable are out-of-line copies of - is
 * inlined. Same shape as DeletePoisonedBaseObject (0x40ca00) and
 * FUN_004f2e20, and ported the same way: __thiscall is erased, so `this`
 * is the first cdecl argument.
 *
 * Every store of 0x55752c in the image is in a destructor tail, so no live
 * object carries this vtable and the slot is not expected to be reached;
 * it is filled so the table is no longer null.
 */
#include "ghidra_types.h"


void * __thiscall FUN_004f2df0(void *param_1,int param_2)

{
  *(void **)param_1 = &PTR_LAB_0055752c;
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}
