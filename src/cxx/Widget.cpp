/* CWidget base methods - promoted from the raw C ports under
 * src/ui_widget/ (Widget_HitTest 0x50e9c0, Widget_DispatchKeyToChildren
 * 0x50ea50, Widget_DispatchMouseToChildren 0x50eab0, Widget_DrawChildren
 * 0x50e520). See src/cxx/README.md.
 *
 * The child list goes through Widget.h's bounds-checked ChildAt()
 * accessor - see its comment for the evidence.
 */
#include "Widget.h"

/* 0x50e9c0, vtable slot 4. Rect test against (+0x28..+0x34), then
 * broadcast to every child's HitTest - a child hit counts even when the
 * point misses this widget's own rect. Hidden (+0x1e) short-circuits. */
bool CWidget::HitTest(int x, int y)
{
    if (m_hidden) {
        return false;
    }
    bool hit = m_x < x && x < m_x + m_width &&
               m_y < y && y < m_y + m_height;
    if (m_childCount != 0) {
        unsigned int i = 0;
        do {
            if (ChildAt(this, i)->HitTest(x, y)) {
                hit = true;
            }
            ++i;
        } while (i < (unsigned int)m_childCount);
    }
    return hit;
}

/* 0x50ea50, vtable slot 5. First child that consumes the key wins;
 * the original accumulates into a register and breaks rather than
 * returning from inside the loop. */
bool CWidget::DispatchKey(int key)
{
    if (m_hidden) {
        return false;
    }
    bool consumed = false;
    if (m_childCount != 0) {
        unsigned int i = 0;
        do {
            if (ChildAt(this, i)->DispatchKey(key)) {
                consumed = true;
                break;
            }
            ++i;
        } while (i < (unsigned int)m_childCount);
    }
    return consumed;
}

/* 0x50eab0, vtable slot 6. Same broadcast as DispatchKey over the
 * mouse-message slot; this one does return from inside the loop. */
bool CWidget::DispatchMouse(int msg)
{
    if (m_hidden) {
        return false;
    }
    if (m_childCount != 0) {
        unsigned int i = 0;
        do {
            if (ChildAt(this, i)->DispatchMouse(msg)) {
                return true;
            }
            ++i;
        } while (i < (unsigned int)m_childCount);
    }
    return false;
}

/* 0x50e520, vtable slot 8 (container base). Ghidra typed it __fastcall
 * (this in ECX, no other args) - as a member function the convention is
 * exact. No hidden check in the original: hiding is enforced on the
 * hit-test/input path, not the draw broadcast. */
void CWidget::Draw()
{
    if (m_childCount != 0) {
        unsigned int i = 0;
        do {
            ChildAt(this, i)->Draw();
            ++i;
        } while (i < (unsigned int)m_childCount);
    }
}
