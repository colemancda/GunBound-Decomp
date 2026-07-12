/* CButtonWidget - the flat, non-hierarchical button object (vtable
 * 0x551e44, 80-byte object, factory CreateButtonWidget 0x406020).
 *
 * NOT related to CWidget (Widget.h) - that is the tree-structured panel
 * system used by chat logs/world list/buddy list/avatar store. This is a
 * separate, simpler system: every button screen (Server Select, Room
 * List, Avatar Store, Ready Room, Loading) creates a flat set of these
 * directly and registers each one into the shared active-object list
 * (RegisterActiveObject) for per-frame tick/draw - see ARCHITECTURE.md's
 * "CreateButtonWidget" writeup for the full trace.
 *
 * CONFIRMED: the 5-slot vtable order and identities (all four non-dtor
 * slots turned out to be functions shared with OTHER, unrelated classes -
 * see the per-slot comments), the object size, and the fields poked by
 * CreateButtonWidget. GUESSED: the class name and the semantics of a few
 * fields CreateButtonWidget never touches (+0x0c/+0x10/+0x28/+0x2c/+0x40/
 * +0x44/+0x48) - kept as opaque m_unk gaps until traced.
 */
#ifndef GB_CXX_BUTTONWIDGET_H
#define GB_CXX_BUTTONWIDGET_H

#include "gb_common.h"

class CButtonWidget {
public:
    /* Default ctor, inlined into the 0x406020 factory under the null
     * guard (same guarded-ctor + unguarded-pokes split as CLabel/
     * CEditBox's factories - see CreateButtonWidget in ButtonWidget.cpp
     * for the unguarded position/texture/state pokes that follow).
     * m_layer/m_id are set here too (the factory's first two real
     * arguments) even though they're not compile-time constants,
     * because the original writes them inside the same null-guarded
     * block, before the vtable-ptr write - matching that requires
     * passing them through the ctor rather than the factory body. */
    CButtonWidget(int layer, int id)
        : m_layer(layer), m_id(id), m_unk0c(0), m_unk10(0), m_unk14(0),
          m_unk15(0), m_spriteBase(-1), m_texture(0), m_unk20(0),
          m_state(-1), m_unk28(0), m_unk2c(0)
    {}

    /* SLOT 0 +0x00: the scalar-deleting destructor thunk shared with
     * several unrelated classes (Ready Room's base infra, etc.) - see
     * docs/screens/09_ready_room.md's "poisoned vtable" note. */
    virtual void *Delete(int shouldFree);                 /* 0x40ca00 - DeletePoisonedBaseObject */
    /* SLOT 1 +0x04: also shared - the generic named-state string resolver
     * (docs/screens/09_ready_room.md), reused across unrelated classes.
     * CreateButtonWidget calls it via this slot with "active"/"ready"/
     * "disable" to set the button's visual state - this IS the button's
     * SetState(name) equivalent, despite the generic underlying name. */
    virtual void SetState(const char *name);              /* 0x461c60 - ResolveNamedState */
    /* SLOT 2 +0x08: per-frame animation tick - thin forward to the
     * generic sprite-animation ticker (advances +0x30's frame index). */
    virtual void Tick();                                  /* 0x405e90 - TickButtonAnimation */
    /* SLOT 3 +0x0c: draw - reads +0x30 (frame index, skip if negative)
     * and +0x38/+0x3c (position), resolves via FindSpriteFrame, blits. */
    virtual void Draw();                                  /* 0x405ea0 - DrawButtonWidget */
    /* SLOT 4 +0x10: shared bare-RET no-op, reused by many vtables. */
    virtual void NoOp();                                  /* 0x429800 - NoOpMethod */

    /* field offsets confirmed from CreateButtonWidget's own pokes */
    int      m_layer;       /* +0x04: CreateButtonWidget's param_2 - always 0 at every observed
                             * call site; likely a z-order/layer key consumed by
                             * RegisterActiveObject's sorted insert, not confirmed */
    int      m_id;          /* +0x08: button id, reported on click */
    int      m_unk0c;       /* +0x0c: zeroed by the ctor, never read there - untraced */
    int      m_unk10;       /* +0x10: zeroed by the ctor, never read there - untraced */
    u8       m_unk14;       /* +0x14 */
    u8       m_unk15;       /* +0x15 */
    u8       m_unk16[2];    /* +0x16 padding to the next int */
    int      m_spriteBase;  /* +0x18: sprite-set base id passed to CreateButtonWidget */
    int      m_texture;     /* +0x1c: FindPreloadedTextureByName(name) result */
    u8       m_unk20;       /* +0x20 */
    u8       m_unk21[3];    /* +0x21 padding */
    int      m_state;       /* +0x24: visual-state field; -1 initially, compared against 3
                             * (checked before the "active"/"ready" state-string calls) */
    int      m_unk28;       /* +0x28 */
    int      m_unk2c;       /* +0x2c */
    int      m_frameIndex;  /* +0x30: sprite frame index drawn by slot 3; negative = hidden */
    int      m_unk34;       /* +0x34 */
    int      m_x;           /* +0x38 */
    int      m_y;           /* +0x3c */
    int      m_unk40;       /* +0x40 */
    int      m_unk44;       /* +0x44 */
    int      m_unk48;       /* +0x48 */
    u8       m_unk4c[4];    /* +0x4c..+0x4f: pad to the confirmed 0x50 object size */
};

GB_STATIC_ASSERT(sizeof(CButtonWidget) == 0x50, buttonwidget_size);

#endif /* GB_CXX_BUTTONWIDGET_H */
