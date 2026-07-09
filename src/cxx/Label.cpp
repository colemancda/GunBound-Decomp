/* CLabel methods - promoted from the raw C port
 * src/ui_widget/Label_OnMouseDown.c (0x5052e0). See src/cxx/README.md. */
#include "Widget.h"

/* 0x5052e0, vtable slot 2. If the point lands in the rect and both
 * gate flags (+0x1c base, +0x38 label) are set, report the click
 * through the OnCommand spine: evt 0 ("clicked"), this widget's id.
 * The call goes through this object's OWN slot 7 - the leaf default
 * (0x50eb10) forwards to m_parent, and panel subclasses that override
 * slot 7 see their children's clicks directly.
 *
 * Returns whether the event was consumed: true if the shared
 * mouse-down tail (MouseDownCommon, 0x50e2f0 - drag arming) took it,
 * or if the point was inside this label's rect at all. */
bool CLabel::OnMouseDown(int x, int y)
{
    bool inside = !m_hidden &&
                  m_x < x && x < m_x + m_width &&
                  m_y < y && y < m_y + m_height;
    if (inside && m_unk38 != 0 && m_unk1c != 0) {
        OnCommand(0, m_id, 0);
    }
    if (MouseDownCommon(x, y)) {
        return true;
    }
    return inside;
}
