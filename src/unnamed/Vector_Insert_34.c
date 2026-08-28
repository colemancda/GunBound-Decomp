/* Vector_Insert_34 - 0x00502a20 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-REG FIX (2026-08-28): param_3 declared. It was already being
 * passed - Vector_PushBack_34 calls this with three arguments against a
 * two-parameter declaration - and it is read at 0x502a67
 * (`mov edx,[esp+0x18]` with ebx, ebp and esi pushed, i.e. entry+0xc)
 * to become Vector_InsertN_34's EDX, the element being inserted.
 *
 * The Vector_InsertN_34 call below was mis-slotted as well. The original
 * sets `mov ecx,1` at 0x502a6d, so the __thiscall receiver is the COUNT,
 * and pushes ebx then edi - i.e. param_3 then param_2 in reverse
 * argument order - so the vector and the position are the two stack
 * arguments. The port had passed the vector into ECX.
 *
 * EDI remains this function's own outstanding dropped register: it is
 * the vector, read at 0x502a2b before anything writes it, and its one
 * caller Vector_PushBack_34 holds it in the same register.
 *
 * NAMED (2026-08-28): the PUBLIC one-element
 * std::vector<T>::insert(iterator _P, const T& _X) of VC7.1's <vector>,
 * as distinct from the private _Insert_n it delegates to, which this
 * tree already calls Vector_InsertN_34. The member is three lines and
 * all three are here:
 *
 *   size_type _O = _P - begin();     0x502a52-0x502a65, (_P - _First)/0x34
 *   _Insert_n(_P, 1, _X);            0x502a6b-0x502a72, with `mov ecx,1`
 *                                    at 0x502a6d supplying the count
 *   return (begin() + _O);           0x502a77-0x502a7d, _First + _O*0x34
 *
 * The iterator is returned through the hidden first argument param_1 and
 * `ret 0xc` accounts for exactly the three stack words - that sret slot,
 * the position _P and the element _X. Its one caller Vector_PushBack_34
 * reaches it as insert(end(), _X), which is where a push_back that has
 * run out of capacity grows.
 */
#include "ghidra_types.h"


int * Vector_Insert_34(int *param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  int unaff_EDI;
  
  iVar1 = *(int *)(unaff_EDI + 4);
  if (iVar1 != 0) {
    if ((*(int *)(unaff_EDI + 8) - iVar1) / 0x34 != 0) {
      iVar1 = (param_2 - iVar1) / 0x34;
      goto LAB_00502a67;
    }
  }
  iVar1 = 0;
LAB_00502a67:
  Vector_InsertN_34(1,unaff_EDI,param_2,param_3);
  *param_1 = iVar1 * 0x34 + *(int *)(unaff_EDI + 4);
  return param_1;
}

