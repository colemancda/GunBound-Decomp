/* Minimal reconstruction of ATL7's CAtlArray<E> (atlcoll.h, VS2003).
 *
 * Evidence this is what the binary uses (see src/cxx/PLAN.md Phase 1.1):
 * the widget child-array grow helper (FUN_0050ed30, 0x50ed30) matches
 * CAtlArray::GrowBuffer exactly - field layout {m_pData, m_nSize,
 * m_nMaxSize, m_nGrowBy}, the malloc/memmove/free reallocation, and the
 * signature growth policy nGrowBy = clamp(m_nSize/8, 4, 1024) - and the
 * bounds guard inlined into every child-broadcast loop (AtlThrow with
 * E_INVALIDARG, FUN_004010c0) matches CAtlArray's checked element access.
 * The client is ATL-era code elsewhere too (CAtlBaseModule in
 * FUN_00401880).
 *
 * The free VC++ Toolkit 2003 / Platform SDK only ship ATL 3 (no
 * atlcoll.h), so this is a from-evidence reimplementation of the small
 * slice the widget system uses, not the Microsoft header. Method names
 * follow ATL7's for recognizability.
 */
#ifndef GB_CXX_ATLARRAY_H
#define GB_CXX_ATLARRAY_H

#include <stdlib.h>
#include <string.h>
#include "gb_common.h"

extern "C" __declspec(noreturn) void FUN_004010c0(long hr); /* AtlThrow */

template <class E>
class CAtlArray {
public:
    CAtlArray() : m_pData(0), m_nSize(0), m_nMaxSize(0), m_nGrowBy(0) {}

    int GetCount() const { return m_nSize; }

    /* The checked access whose inlined guard is visible in every
     * broadcast loop of the raw ports. */
    E &operator[](unsigned int i)
    {
        if (i >= (unsigned int)m_nSize) {
            FUN_004010c0(0x80070057); /* AtlThrow(E_INVALIDARG) */
        }
        return m_pData[i];
    }

    /* 0x50ed30 (FUN_0050ed30). Ensure capacity for nNewMaxSize elements;
     * returns false only on allocation failure. NOTE: Ghidra shows the
     * original receiving `this` in ESI and the argument in EAX - the
     * custom-register family again; presumably an artifact of how the
     * compiler emitted this out-of-lined template member. */
    bool GrowBuffer(unsigned int nNewMaxSize)
    {
        if (nNewMaxSize <= (unsigned int)m_nMaxSize) {
            return true;
        }
        unsigned int nGrowBy = (unsigned int)m_nGrowBy;
        if (m_pData == 0) {
            unsigned int nAlloc = nNewMaxSize;
            if (nAlloc < nGrowBy) {
                nAlloc = nGrowBy;
            }
            E *p = (E *)malloc(nAlloc * sizeof(E));
            m_pData = p;
            if (p != 0) {
                m_nMaxSize = (int)nAlloc;
                return true;
            }
        } else {
            if (nGrowBy == 0) {
                nGrowBy = (unsigned int)m_nSize >> 3;
                if (nGrowBy < 4) {
                    nGrowBy = 4;
                } else if (0x400 < nGrowBy) {
                    nGrowBy = 0x400;
                }
            }
            unsigned int nAlloc = nGrowBy + (unsigned int)m_nMaxSize;
            if (nAlloc <= nNewMaxSize) {
                nAlloc = nNewMaxSize;
            }
            E *p = (E *)malloc(nAlloc * sizeof(E));
            if (p != 0) {
                memmove(p, m_pData, (unsigned int)m_nSize * sizeof(E));
                free(m_pData);
                m_pData = p;
                m_nMaxSize = (int)nAlloc;
                return true;
            }
        }
        return false;
    }

    bool Add(const E &e)
    {
        if (!GrowBuffer((unsigned int)m_nSize + 1)) {
            return false;
        }
        m_pData[m_nSize] = e;
        ++m_nSize;
        return true;
    }

    /* layout is load-bearing: embedded in CWidget at +0x0c..+0x1b */
    E  *m_pData;    /* +0x00 */
    int m_nSize;    /* +0x04 */
    int m_nMaxSize; /* +0x08 */
    int m_nGrowBy;  /* +0x0c */
};

#endif /* GB_CXX_ATLARRAY_H */
