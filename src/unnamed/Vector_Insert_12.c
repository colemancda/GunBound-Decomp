/* Vector_Insert_12 - 0x005029b0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_005029b0).  The public one-element
 * vector<T>::insert(iterator _P, const T& _X) for the 0x12-byte element,
 * the twin of Vector_Insert_34 (0x502a20) and Vector_Insert_1e
 * (0x502b00), which sit beside it in the binary with the same shape:
 *   0x5029bb-0x5029f5  _O = (_P - _Myfirst) / 0x12 (0x38e38e39 divide)
 *   0x5029f7-0x5029ff  _Insert_n(_P, 1, _X) = Vector_InsertN_12
 *   0x502a04-0x502a0d  *sret = _Myfirst + _O*0x12
 *   0x502a15           ret 0xc - sret, _P, _X
 * Its one caller is the push_back FUN_00502750, which reaches it as
 * insert(end(), _X) when size() == capacity() - exactly where
 * Vector_PushBack_34/_1e call their own insert.
 *
 * DROPPED ARGUMENTS RECOVERED (2026-10-30), resolving the note below.
 * param_3 is the element: `mov ecx,[esp+0x18]` at 0x5029f7 with EBX,
 * EBP and ESI pushed is entry+0xc, the third stack word, and it becomes
 * Vector_InsertN_12's ECX. The caller was already pushing it (`push
 * ebx` at 0x5027bc) against a two-parameter declaration. EDI is the
 * vector - read at 0x5029bb (`mov esi,[edi+4]`) before anything writes
 * it, and FUN_00502750 holds the vector in EDI (`mov edi,ecx` at
 * 0x502754) across the call - promoted to the trailing regEdi as in
 * Vector_Insert_1e. The Vector_InsertN_12 call now passes the element
 * where it had a 0 placeholder.
 *
 * The 2026-09-20 note below predates the name and is kept verbatim;
 * its FUN_00502b70 is Vector_InsertN_12.
 *
 * UNRESOLVED (2026-09-20): the FUN_00502b70(unaff_EDI,param_2,1) call is
 * missing FUN_00502b70's own leading `this` (ECX) arg - orig 0x5029f7:
 * `mov ecx,[esp+0x18]` right before the 3 pushes, i.e. this function's
 * OWN third stack argument. That argument isn't represented anywhere in
 * this function's current (buggy, 2-param plus `unaff_EDI`) signature,
 * so it can't be threaded through without also fixing this function's
 * own parameter list, which is a separate, out-of-scope bug. See
 * FUN_00502b70.c's own header for the full reconstruction.
 */
#include "ghidra_types.h"


int * Vector_Insert_12(int *param_1,int param_2,undefined4 *param_3,int regEdi)

{
  int iVar1;
  int unaff_EDI = regEdi;
  
  iVar1 = *(int *)(unaff_EDI + 4);
  if (iVar1 != 0) {
    if ((*(int *)(unaff_EDI + 8) - iVar1) / 0x12 != 0) {
      iVar1 = (param_2 - iVar1) / 0x12;
      goto LAB_005029f7;
    }
  }
  iVar1 = 0;
LAB_005029f7:
  Vector_InsertN_12(param_3,unaff_EDI,param_2,1);
  *param_1 = *(int *)(unaff_EDI + 4) + iVar1 * 0x12;
  return param_1;
}

