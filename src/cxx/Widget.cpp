/* CWidget base methods - promoted from the raw C ports under
 * src/ui_widget/ (Widget_HitTest 0x50e9c0, Widget_DispatchKeyToChildren
 * 0x50ea50, Widget_DispatchMouseToChildren 0x50eab0, Widget_DrawChildren
 * 0x50e520). See src/cxx/README.md.
 *
 * The child list is an embedded ATL7 CAtlArray<CWidget *> (see
 * AtlArray.h for the identification evidence); the bounds guard in
 * every loop below comes from its checked operator[], exactly as the
 * original object code inlines it.
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
    if (m_children.GetCount() != 0) {
        unsigned int i = 0;
        do {
            if (m_children[i]->HitTest(x, y)) {
                hit = true;
            }
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
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
    if (m_children.GetCount() != 0) {
        unsigned int i = 0;
        do {
            if (m_children[i]->DispatchKey(key)) {
                consumed = true;
                break;
            }
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
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
    if (m_children.GetCount() != 0) {
        unsigned int i = 0;
        do {
            if (m_children[i]->DispatchMouse(msg)) {
                return true;
            }
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
    return false;
}

/* 0x50e2f0 - the shared tail of the leaf press handlers (CLabel's
 * OnMouseDown calls it): clear the +0x38 gate and +0x04 active flags,
 * broadcast mouse-UP to the children, and report consumed-or-inside.
 * +0x38 is in the subclass region (CWidget proper ends at +0x38), so
 * the store is by explicit offset until the field's true home class
 * is pinned. */
bool CWidget::ResetPressState(int x, int y)
{
    ((u8 *)this)[0x38] = 0;
    m_unk04 = 0;
    return MouseUpChildren(x, y) ||
           (!m_hidden &&
            m_x < x && x < m_x + m_width &&
            m_y < y && y < m_y + m_height);
}

/* 0x50e3a0, vtable slot 11 (base drag). While the drag flag is armed,
 * shift by the delta from the last drag point and update it; then the
 * mouse-move child broadcast and the usual consumed-or-inside report.
 * The drag fields (+0x39 flag, +0x3c/+0x40 last point) live in the
 * subclass region - explicit offsets, same caveat as ResetPressState
 * (labels reuse +0x3c as m_spriteId and simply never arm the flag). */
bool CWidget::OnDragMove(int x, int y)
{
    if (((u8 *)this)[0x39] != 0) {
        MoveBy(x - *(int *)((u8 *)this + 0x3c), y - *(int *)((u8 *)this + 0x40));
        *(int *)((u8 *)this + 0x3c) = x;
        *(int *)((u8 *)this + 0x40) = y;
    }
    return MouseMoveChildren(x, y) ||
           (!m_hidden &&
            m_x < x && x < m_x + m_width &&
            m_y < y && y < m_y + m_height);
}

/* 0x50e730. Shift this widget and, recursively, its whole subtree by a
 * delta - the drag-move workhorse. The recursion is a direct (non-
 * virtual) member call in the original. */
void CWidget::MoveBy(int dx, int dy)
{
    m_x += dx;
    m_y += dy;
    if (m_children.GetCount() != 0) {
        unsigned int i = 0;
        do {
            m_children[i]->MoveBy(dx, dy);
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
}

/* 0x50e870 / 0x50e8e0 / 0x50e950 - the slot-1/2/3 child broadcasts.
 * All three share the shape: hidden gate, visit EVERY child (no early
 * exit, unlike DispatchKey/DispatchMouse), accumulate any-consumed. */
bool CWidget::MouseMoveChildren(int x, int y)
{
    if (m_hidden) {
        return false;
    }
    bool any = false;
    if (m_children.GetCount() != 0) {
        unsigned int i = 0;
        do {
            if (m_children[i]->OnMouseMove(x, y)) {
                any = true;
            }
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
    return any;
}

bool CWidget::MouseDownChildren(int x, int y)
{
    if (m_hidden) {
        return false;
    }
    bool any = false;
    if (m_children.GetCount() != 0) {
        unsigned int i = 0;
        do {
            if (m_children[i]->OnMouseDown(x, y)) {
                any = true;
            }
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
    return any;
}

bool CWidget::MouseUpChildren(int x, int y)
{
    if (m_hidden) {
        return false;
    }
    bool any = false;
    if (m_children.GetCount() != 0) {
        unsigned int i = 0;
        do {
            if (m_children[i]->OnMouseUp(x, y)) {
                any = true;
            }
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
    return any;
}

/* 0x50e670. Append a child: grow-or-throw via the CAtlArray (the
 * original open-codes Add's body; E_OUTOFMEMORY on growth failure),
 * shift the child from parent-relative to absolute coordinates, and
 * take ownership of its callback parent pointer. Ghidra shows `this`
 * arriving in EBX. */
void CWidget::AddChild(CWidget *child)
{
    m_children.Add(child);
    child->MoveBy(m_x, m_y);
    child->m_parent = this;
}

/* 0x50e7d0. Recursively enable/disable this subtree (+0x1c); disabling
 * also drops the +0x04 active flag. */
void CWidget::SetEnabled(bool enabled)
{
    m_enabled = (u8)enabled;
    if (m_unk04 != 0) {
        m_unk04 = 0;
    }
    if (m_children.GetCount() != 0) {
        unsigned int i = 0;
        do {
            m_children[i]->SetEnabled(enabled);
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
}

/* 0x50e620. Index of the child matching (typeId, id); child count when
 * absent. The focus mover calls it with typeId 2 (text-entry) and the
 * id of the child that sent the focus event. */
int CWidget::FindChildIndex(int typeId, int id)
{
    unsigned int count = (unsigned int)m_children.GetCount();
    for (unsigned int i = 0; i < count; ++i) {
        if (m_children[i]->m_typeId == typeId && m_children[i]->m_id == id) {
            return (int)i;
        }
    }
    return (int)count;
}

/* 0x50eb10, vtable slot 7 - the leaf/base OnCommand default: the focus
 * mover plus the upward-forwarding tail of the event spine.
 *   0x1100 focus-next: from the sender (the focused type-2 child), scan
 *          forward; SetFocus(0) the loser, SetFocus(1) the winner; if
 *          focus runs off the end, report 0x1000 through our own
 *          (virtual) OnCommand so panel overrides see it.
 *   0x1101 focus-prev / 0x1102 focus-set: same, scanning backward /
 *          from the current position with wraparound. The target-index
 *          arithmetic mirrors the decompile literally.
 *   anything else: forward to m_parent. */
void CWidget::OnCommand(int evt, int id, int arg)
{
    int count = m_children.GetCount();
    if (evt == 0x1100) {
        unsigned int cur = (unsigned int)FindChildIndex(2, id);
        unsigned int i = cur + 1;
        for (; (int)i < count; ++i) {
            if (m_children[i]->m_typeId == 2 && i != cur) {
                m_children[cur]->SetFocus(false);
                m_children[i]->SetFocus(true);
                return;
            }
        }
        if (i == (unsigned int)count) {
            OnCommand(0x1000, id, 0);
        }
    } else if (evt == 0x1101) {
        unsigned int cur = (unsigned int)FindChildIndex(2, id);
        int steps = 0;
        int walk = (int)cur + count;
        if (0 < count) {
            do {
                unsigned int probe = (unsigned int)(walk % count);
                if (m_children[probe]->m_typeId == 2 && probe != cur) {
                    m_children[cur]->SetFocus(false);
                    m_children[(unsigned int)(((int)cur - steps + count) % count)]->SetFocus(true);
                    return;
                }
                ++steps;
                --walk;
            } while (steps < count);
        }
    } else if (evt == 0x1102) {
        unsigned int cur = (unsigned int)FindChildIndex(2, id);
        int steps = 0;
        int walk = (int)cur;
        if (0 < count) {
            do {
                unsigned int probe = (unsigned int)(walk % count);
                if (m_children[probe]->m_typeId == 2 && probe != cur) {
                    m_children[cur]->SetFocus(false);
                    m_children[(unsigned int)((steps + (int)probe) % count)]->SetFocus(true);
                    return;
                }
                ++steps;
                ++walk;
            } while (steps < count);
        }
    } else if (m_parent != 0) {
        m_parent->OnCommand(evt, id, arg);
    }
}

/* 0x50e520, vtable slot 8 (container base). Ghidra typed it __fastcall
 * (this in ECX, no other args) - as a member function the convention is
 * exact. No hidden check in the original: hiding is enforced on the
 * hit-test/input path, not the draw broadcast. */
void CWidget::Draw()
{
    if (m_children.GetCount() != 0) {
        unsigned int i = 0;
        do {
            m_children[i]->Draw();
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
}
