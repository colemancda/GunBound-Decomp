/* FUN_00531572 - 0x00531572 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    void __cdecl FindHandlerForForeignException(struct EHExceptionRecord *,struct EHRegistrationNode
   *,struct _CONTEXT *,void *,struct _s_FuncInfo const *,int,int,struct EHRegistrationNode *)
   
   Library: Visual Studio 2003 Release */

void __cdecl
FindHandlerForForeignException
          (EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,void *param_4,
          _s_FuncInfo *param_5,int param_6,int param_7,EHRegistrationNode *param_8)

{
  _ptiddata p_Var1;
  int iVar2;
  _s_TryBlockMapEntry *p_Var3;
  _s_CatchableType *unaff_EBX;
  int unaff_ESI;
  _s_TryBlockMapEntry *unaff_EDI;
  EHRegistrationNode *extraout_var;
  EHRegistrationNode *pEVar4;
  EHRegistrationNode *extraout_var_00;
  EHRegistrationNode *pEVar5;
  
  if ((*(int *)param_1 != -0x7ffffffd) &&
     (((p_Var1 = __getptd(), pEVar4 = extraout_var, pEVar5 = extraout_var_00,
       p_Var1->_NLG_dwCode == 0 ||
       (iVar2 = _CallSETranslator(param_1,param_2,param_3,param_4,param_5,param_7,param_8),
       iVar2 == 0)) &&
      (p_Var3 = _GetRangeOfTrysToCheck
                          (param_5,param_7,param_6,(uint *)&stack0xfffffff8,(uint *)&stack0xfffffff4
                          ), pEVar5 < pEVar4)))) {
    do {
      if (((*(int *)p_Var3 <= param_6) && (param_6 <= *(int *)(p_Var3 + 4))) &&
         ((iVar2 = *(int *)(*(int *)(p_Var3 + 0xc) * 0x10 + *(int *)(p_Var3 + 0x10) + -0xc),
          iVar2 == 0 || (*(char *)(iVar2 + 8) == '\0')))) {
        CatchIt(param_1,(EHRegistrationNode *)param_3,param_4,param_5,(_s_FuncInfo *)param_7,
                (_s_HandlerType *)param_8,unaff_EBX,unaff_EDI,unaff_ESI,pEVar4,(uchar)pEVar5);
      }
      pEVar5 = pEVar5 + 1;
      p_Var3 = p_Var3 + 0x14;
    } while (pEVar5 < pEVar4);
  }
  return;
}

