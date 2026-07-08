/* FUN_00418dc0 - 0x00418dc0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00418dc0(int param_1)

{
  int *piVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_0053b742;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_4 = 0x5f;
  g_clientContext = 0;
  FUN_004f0d70();
  if (*(int *)(&DAT_006aa8b4 + param_1) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x5e;
  if (*(int *)(&DAT_006aa690 + param_1) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x5d;
  _eh_vector_destructor_iterator_(&DAT_006aa630 + param_1,4,10,FUN_00405320);
  FUN_00415560();
  FUN_00415560();
  local_4._0_1_ = 0x5a;
  if (*(int *)(&DAT_006aa1f8 + param_1) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x59;
  if (*(int *)(&DAT_006a9fd4 + param_1) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x58;
  if (*(int *)(&DAT_006a9db0 + param_1) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x57;
  if (*(int *)(&DAT_006a9b8c + param_1) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x56;
  _eh_vector_destructor_iterator_(&DAT_006a8e90 + param_1,0x224,6,FUN_0040a2a0);
  local_4._0_1_ = 0x55;
  _eh_vector_destructor_iterator_(&DAT_006a81b8 + param_1,0x224,6,FUN_0040a2a0);
  local_4._0_1_ = 0x54;
  if (*(int *)(&DAT_006a7fa8 + param_1) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4 = CONCAT31(local_4._1_3_,0x53);
  *(undefined ***)(&DAT_006a7f88 + param_1) = &PTR_FUN_00557534;
  FUN_004f3060(&DAT_006a7f88 + param_1);
  if (*(undefined4 **)(&DAT_006a7f8c + param_1) != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)(&DAT_006a7f8c + param_1))(1);
  }
  if (*(void **)(&DAT_006a7f78 + param_1) != (void *)0x0) {
    _free(*(void **)(&DAT_006a7f78 + param_1));
  }
  local_4 = CONCAT31(local_4._1_3_,0x51);
  FUN_004e38f0(&DAT_006a7708 + param_1);
  if (*(void **)(&DAT_006a76f4 + param_1) != (void *)0x0) {
    _free(*(void **)(&DAT_006a76f4 + param_1));
  }
  local_4._0_1_ = 0x4f;
  FUN_004e1e90(&DAT_006a64c4 + param_1);
  local_4._0_1_ = 0x4e;
  _eh_vector_destructor_iterator_(&DAT_0069ec74 + param_1,0x18,0x400,FUN_00401370);
  local_4._0_1_ = 0x4d;
  iVar5 = *(int *)(&DAT_0067ec60 + param_1);
  if (iVar5 != 0) {
    uVar2 = *(uint *)(&DAT_0067ec64 + param_1);
    uVar4 = 0;
    if (uVar2 != 0) {
      do {
        iVar6 = *(int *)(iVar5 + uVar4 * 4);
        puVar3 = (undefined4 *)(iVar6 + -0x10);
        piVar1 = (int *)(iVar6 + -4);
        LOCK();
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 + -1 < 1) {
          (**(code **)(*(int *)*puVar3 + 4))(puVar3);
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < uVar2);
    }
    _free(*(void **)(&DAT_0067ec60 + param_1));
  }
  local_4._0_1_ = 0x4c;
  if (*(int *)(&DAT_0067ea50 + param_1) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x4b;
  if (*(int *)(&DAT_0067e82c + param_1) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x4a;
  if (*(int *)(&DAT_0067e608 + param_1) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x49;
  if (*(int *)(&DAT_0067e3e4 + param_1) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x48;
  _eh_vector_destructor_iterator_(&DAT_005f5348 + param_1,0x224,0x400,FUN_0040a2a0);
  local_4._0_1_ = 0x47;
  _eh_vector_destructor_iterator_(&DAT_005f4ab8 + param_1,0x224,4,FUN_0040a2a0);
  local_4._0_1_ = 0x46;
  if (*(int *)(&DAT_005f48a8 + param_1) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x45;
  _eh_vector_destructor_iterator_(&DAT_005f3774 + param_1,0x224,8,FUN_0040a2a0);
  local_4._0_1_ = 0x44;
  _eh_vector_destructor_iterator_(&DAT_005c7fb8 + param_1,0x157c,0x20,FUN_00418b90);
  local_4._0_1_ = 0x43;
  _eh_vector_destructor_iterator_((void *)((int)&PTR_DAT_0058b248 + param_1),0x9bc,100,FUN_00418910)
  ;
  local_4._0_1_ = 0x42;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x1a1e48),0x7d28,0x80,FUN_004186b0);
  local_4._0_1_ = 0x41;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0xf0384),0xb1ac,0x10,FUN_004174c0);
  local_4._0_1_ = 0x40;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0xef254),0x224,8,FUN_0040a2a0);
  local_4._0_1_ = 0x3f;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0xee134),0x224,8,FUN_0040a2a0);
  local_4._0_1_ = 0x3e;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0xed014),0x224,8,FUN_0040a2a0);
  local_4._0_1_ = 0x3d;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0xebef4),0x224,8,FUN_0040a2a0);
  local_4._0_1_ = 0x3c;
  if (*(int *)(param_1 + 0xebcd0) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x3b;
  if (*(int *)(param_1 + 0xebaac) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x3a;
  if (*(int *)(param_1 + 0xeb868) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x39;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x62854),0x224,0x400,FUN_0040a2a0);
  local_4._0_1_ = 0x38;
  if (*(int *)(param_1 + 0x62644) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x37;
  if (*(int *)(param_1 + 0x62420) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x36;
  if (*(int *)(param_1 + 0x621fc) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x35;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x61020),0x224,8,FUN_0040a2a0);
  local_4._0_1_ = 0x34;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x5ff00),0x224,8,FUN_0040a2a0);
  local_4._0_1_ = 0x33;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x5ede0),0x224,8,FUN_0040a2a0);
  local_4._0_1_ = 0x32;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x5dcc0),0x224,8,FUN_0040a2a0);
  local_4._0_1_ = 0x31;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x5cba0),0x224,8,FUN_0040a2a0);
  local_4._0_1_ = 0x30;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x5ba80),0x224,8,FUN_0040a2a0);
  local_4._0_1_ = 0x2f;
  if (*(int *)(param_1 + 0x5b870) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x2e;
  if (*(int *)(param_1 + 0x5b608) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x2d;
  if (*(int *)(param_1 + 0x5b3e4) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x2c;
  if (*(int *)(param_1 + 0x5b1c0) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x2b;
  if (*(int *)(param_1 + 0x5af9c) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x2a;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x595d8),0x224,0xc,FUN_0040a2a0);
  local_4._0_1_ = 0x29;
  if (*(int *)(param_1 + 0x593c8) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x28;
  if (*(int *)(param_1 + 0x591a4) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x27;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x50240),0x224,0x40,FUN_0040a2a0);
  local_4._0_1_ = 0x26;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x49a4c),0x224,0x30,FUN_0040a2a0);
  local_4._0_1_ = 0x25;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x477ec),0x224,0x10,FUN_0040a2a0);
  local_4._0_1_ = 0x24;
  if (*(int *)(param_1 + 0x475dc) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x23;
  if (*(int *)(param_1 + 0x473b4) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x22;
  if (*(int *)(param_1 + 0x45590) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x21;
  if (*(int *)(param_1 + 0x45368) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x20;
  if (*(int *)(param_1 + 0x45140) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x1f;
  if (*(int *)(param_1 + 0x44f10) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x1e;
  iVar5 = *(int *)(param_1 + 0x44e50);
  if (iVar5 != 0) {
    for (iVar6 = *(int *)(param_1 + 0x44e54); iVar6 != 0; iVar6 = iVar6 + -1) {
      FUN_00426810(iVar5);
      iVar5 = iVar5 + 0x450;
    }
    _free(*(void **)(param_1 + 0x44e50));
  }
  local_4._0_1_ = 0x1d;
  iVar5 = *(int *)(param_1 + 0x44e40);
  if (iVar5 != 0) {
    for (iVar6 = *(int *)(param_1 + 0x44e44); iVar6 != 0; iVar6 = iVar6 + -1) {
      FUN_00426810(iVar5);
      iVar5 = iVar5 + 0x450;
    }
    _free(*(void **)(param_1 + 0x44e40));
  }
  local_4._0_1_ = 0x1c;
  iVar5 = *(int *)(param_1 + 0x44e30);
  if (iVar5 != 0) {
    for (iVar6 = *(int *)(param_1 + 0x44e34); iVar6 != 0; iVar6 = iVar6 + -1) {
      FUN_00426810(iVar5);
      iVar5 = iVar5 + 0x450;
    }
    _free(*(void **)(param_1 + 0x44e30));
  }
  local_4._0_1_ = 0x1b;
  iVar5 = *(int *)(param_1 + 0x44e20);
  if (iVar5 != 0) {
    for (iVar6 = *(int *)(param_1 + 0x44e24); iVar6 != 0; iVar6 = iVar6 + -1) {
      FUN_00426810(iVar5);
      iVar5 = iVar5 + 0x450;
    }
    _free(*(void **)(param_1 + 0x44e20));
  }
  local_4 = CONCAT31(local_4._1_3_,0x1a);
  if (*(int *)(param_1 + 0x44c10) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  if (*(void **)(param_1 + 0x44be8) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x44be8));
  }
  local_4._0_1_ = 0x18;
  if (*(int *)(param_1 + 0x449d8) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x17;
  if (*(int *)(param_1 + 0x41130) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x16;
  if (*(int *)(param_1 + 0x3b6d8) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x15;
  if (*(int *)(param_1 + 0x3b4b0) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x14;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x3ac08),0x224,4,FUN_0040a2a0);
  local_4._0_1_ = 0x13;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x39f30),0x224,6,FUN_0040a2a0);
  local_4._0_1_ = 0x12;
  if (*(int *)(param_1 + 0x39d20) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x11;
  if (*(int *)(param_1 + 0x39afc) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0x10;
  if (*(int *)(param_1 + 0x398d8) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0xf;
  if (*(int *)(param_1 + 0x396b4) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0xe;
  if (*(int *)(param_1 + 0x39490) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0xd;
  if (*(int *)(param_1 + 0x3926c) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 0xc;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x36788),0x224,0x14,FUN_0040a2a0);
  local_4._0_1_ = 0xb;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x33cb8),0x224,0x14,FUN_0040a2a0);
  local_4._0_1_ = 10;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x311e8),0x224,0x14,FUN_0040a2a0);
  local_4._0_1_ = 9;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x2e718),0x224,0x14,FUN_0040a2a0);
  local_4._0_1_ = 8;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x2bc48),0x224,0x14,FUN_0040a2a0);
  local_4._0_1_ = 7;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x29178),0x224,0x14,FUN_0040a2a0);
  local_4._0_1_ = 6;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x266a8),0x224,0x14,FUN_0040a2a0);
  local_4._0_1_ = 5;
  _eh_vector_destructor_iterator_((void *)(param_1 + 0x23bd8),0x224,0x14,FUN_0040a2a0);
  local_4._0_1_ = 4;
  if (*(int *)(param_1 + 0x239c8) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 3;
  if (*(int *)(param_1 + 0x237a4) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4._0_1_ = 2;
  if (*(int *)(param_1 + 0x23580) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  local_4 = CONCAT31(local_4._1_3_,1);
  if (*(int *)(param_1 + 0x2335c) != 0) {
    FUN_0040a240();
    FUN_0040b540(local_14);
  }
  if (*(int *)(param_1 + 0x10728) != -1) {
    FUN_004f0d70();
  }
  *(undefined ***)(param_1 + 0x1fdfc) = &PTR_FUN_005572dc;
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x1fe00));
  *(undefined ***)(param_1 + 0xf6cc) = &PTR_FUN_005572dc;
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 0xf6d0));
  *unaff_FS_OFFSET = uStack_c;
  return;
}

