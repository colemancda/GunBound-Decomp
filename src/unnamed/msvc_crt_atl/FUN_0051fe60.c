/* FUN_0051fe60 - 0x0051fe60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    public: __thiscall ATL::CComCritSecLock<class ATL::CComCriticalSection>::~CComCritSecLock<class
   ATL::CComCriticalSection>(void)
   
   Library: Visual Studio 2003 Release */

void __thiscall
ATL::CComCritSecLock<ATL::CComCriticalSection>::~CComCritSecLock<ATL::CComCriticalSection>
          (CComCritSecLock<ATL::CComCriticalSection> *this)

{
  if (this[4] != (CComCritSecLock<ATL::CComCriticalSection>)0x0) {
    LeaveCriticalSection(*(LPCRITICAL_SECTION *)this);
    this[4] = (CComCritSecLock<ATL::CComCriticalSection>)0x0;
  }
  return;
}

