/* SortIntRange - 0x004dfdb0 in the original binary.
 *
 * MSVC 7.1's std::sort over 4-byte elements (_Sort).  Three constants
 * identify it: the 32-element cutoff to insertion sort, the ideal-depth
 * decay `_Ideal = _Ideal/2 + (_Ideal/2)/2` (three quarters), and the
 * fallback to make_heap + sort_heap once the depth budget reaches zero.
 * It partitions through MedianIntRange/PartitionIntRange and recurses on
 * the smaller half while looping on the larger -- the introsort shape.
 */
#include "ghidra_types.h"


void SortIntRange(int param_1,int param_2,int param_3)

{
  int iVar1;
  int local_8;
  int local_4;
  
  iVar1 = param_2 - param_1;
  do {
    iVar1 = iVar1 >> 2;
    if (iVar1 < 0x21) {
LAB_004dfe33:
      if (1 < iVar1) {
        InsertionSortIntRange(param_2);
      }
      return;
    }
    if (param_3 < 1) {
      if (0x20 < iVar1) {
        MakeHeapIntRange(param_1,param_2);
        SortHeapIntRange(param_2,(undefined4 *)param_1);
        return;
      }
      goto LAB_004dfe33;
    }
    PartitionIntRange(&local_8,param_1,param_2);
    iVar1 = local_4;
    param_3 = param_3 / 2 + (param_3 / 2) / 2;
    if ((int)(local_8 - param_1 & 0xfffffffcU) < (int)(param_2 - local_4 & 0xfffffffcU)) {
      SortIntRange(param_1,local_8,param_3);
      param_1 = iVar1;
    }
    else {
      SortIntRange(local_4,param_2,param_3);
      param_2 = local_8;
    }
    iVar1 = param_2 - param_1;
  } while( true );
}

