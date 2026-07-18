/* The active-object registry (PLAN.md Phase 5.1) - the key->intrusive-
 * list container every screen's sprites/widgets register with. There are
 * several instances of the SAME structure: the sprite cache DAT_00ea0e18
 * (primed per-screen by LoadSpriteSet), and the two flat-widget registries
 * DAT_00e9be90 / DAT_00e9c0fc that the CButtonWidget / CScrollBar / CLabel
 * objects register into (see RegisterActiveObject.c / CreateActiveObjectLayer.c).
 *
 * PROMOTED (2026-07-18): the full node/layer link structure - recovered
 * this session while making the ServerSelect buttons register + draw - is
 * now modeled as real structs with GB_STATIC_ASSERTs, and the destroy walk
 * is rewritten against named fields instead of raw `bucket[1]/[3]/[4]/[7]`
 * indices. The registry operations themselves (0x4f2fb0 RegisterActiveObject,
 * 0x4f2f00 CreateActiveObjectLayer, 0x406280 TickActiveObjectRegistry,
 * 0x4062b0 DrawActiveObjectRegistry) stay as their extern-"C" raw ports for
 * now - their many C callers reference them by name, so they are documented
 * here against this layout rather than re-expressed as C++ methods (that
 * caller switch is the byte-verify-gated follow-up).
 */
#ifndef GB_CXX_ACTIVEOBJECTS_H
#define GB_CXX_ACTIVEOBJECTS_H

#include "gb_common.h"

extern "C" {
extern unsigned char DAT_00ea0e18[0x20];  /* sprite-cache registry storage - sized, see globals.c */
extern unsigned int  DAT_00ea0e1c;  /* its head field (registry+4) - aliased to &DAT_00ea0e18 at
                                        startup, see crt_shims_msvc.c; Ghidra split it out */
}

/* ---------------------------------------------------------------------------
 * The registered-object header contract.
 *
 * Every object placed in a registry (a CButtonWidget, a CDisplayObject
 * sprite, ...) begins with this 5-field header. RegisterActiveObject sorts
 * on `layerKey` to pick a layer, then on `id` within the layer's inner
 * circular list; CButtonWidget's m_layer/m_id/m_unk0c/m_unk10 alias
 * layerKey/id/innerPrev/innerNext exactly (see ButtonWidget.h).
 * ------------------------------------------------------------------------- */
struct ActiveObjectNode {
    void *vtable;                 /* +0x00: slot 0 dtor, slot 2 Tick, slot 3 Draw */
    u32   layerKey;               /* +0x04: which layer/bucket this sorts into */
    u32   id;                     /* +0x08: sort key within the layer (0xffffffff on a layer) */
    ActiveObjectNode *innerPrev;  /* +0x0c: intrusive list, prev in the layer */
    ActiveObjectNode *innerNext;  /* +0x10: intrusive list, next in the layer */
};
GB_STATIC_ASSERT(sizeof(ActiveObjectNode) == 0x14, activeobjectnode_size);

/* ---------------------------------------------------------------------------
 * A layer (bucket): one 0x20-byte node per distinct layerKey, allocated by
 * CreateActiveObjectLayer (0x4f2f00) with vtable PTR_FUN_00557530. Its `id`
 * field is the 0xffffffff sentinel that terminates an inner-list walk, so a
 * layer is walkable as an ActiveObjectNode too. Layers form their own sorted
 * circular list threaded through outerPrev/outerNext.
 * ------------------------------------------------------------------------- */
struct ActiveObjectLayer {
    void *vtable;                  /* +0x00: &PTR_FUN_00557530 */
    u32   layerKey;                /* +0x04: this layer's key */
    u32   sentinelId;              /* +0x08: always 0xffffffff - the inner-walk terminator */
    ActiveObjectNode *innerPrev;   /* +0x0c: tail of the inner list (self when empty) */
    ActiveObjectNode *innerNext;   /* +0x10: head of the inner list (self when empty) */
    u8    flag14;                  /* +0x14: 0 */
    u8    flag15;                  /* +0x15: 1 */
    u8    pad16[2];                /* +0x16 */
    ActiveObjectLayer *outerPrev;  /* +0x18: prev layer in the sorted outer list */
    ActiveObjectLayer *outerNext;  /* +0x1c: next layer in the sorted outer list */
};
GB_STATIC_ASSERT(sizeof(ActiveObjectLayer) == 0x20, activeobjectlayer_size);

/* ---------------------------------------------------------------------------
 * The registry container itself (0x20 bytes: DAT_00e9be90, DAT_00e9c0fc,
 * DAT_00ea0e18). gb_init_widget_registry (crt_shims_msvc.c) makes it its own
 * head/outer sentinel: `head` (+0x04) and outerPrev/outerNext (+0x18/+0x1c)
 * all point back at the container, so an empty registry's outer list is the
 * container looping to itself - which is why RegisterActiveObject reaches the
 * first layer via `(registry->head)->outerNext` and CreateActiveObjectLayer
 * links new layers through the container's own +0x18/+0x1c.
 * ------------------------------------------------------------------------- */
struct CActiveObjectRegistry {
    void *pad00;                   /* +0x00 */
    ActiveObjectLayer *head;       /* +0x04: the outer-list sentinel (== this) */
    u8    pad08[0x10];             /* +0x08 */
    ActiveObjectLayer *outerPrev;  /* +0x18: last layer (self when empty) */
    ActiveObjectLayer *outerNext;  /* +0x1c: first layer (self when empty) */
};
GB_STATIC_ASSERT(sizeof(CActiveObjectRegistry) == 0x20, activeobjectregistry_size);

/* Walk the sorted layer list of the DAT_00ea0e18 sprite registry to `key`;
 * if that layer exists, run every registered object's vtable-slot-0
 * destructor with free=1, then reset the layer's inner list to empty. The
 * outer list is sorted, so the walk bails as soon as it passes `key`. The
 * identical inlined copy appears in Title (0x4e53a0), Logo1 (0x443430), Logo2
 * (0x4432c0) and Loading (0x43eff0) - an inline helper in the original, kept
 * inline here (MSVC 7.1 re-inlines it at /O2 into the same shape).
 *
 * DAT_00ea0e1c is the registry's `head` field (registry+4), whose value is
 * the container itself, so `(CActiveObjectRegistry*)DAT_00ea0e1c` is that
 * container and its ->outerNext is the first layer - identical to the raw
 * port's `*(DAT_00ea0e1c + 0x1c)`.
 *
 * The per-object dtor is really __thiscall (this in ECX); the raw port kept
 * the code* cdecl shape and it works here only because the sprite element
 * class is itself a raw-C port (also erased to cdecl - see
 * State02_ServerSelect_ProcessPacket.c's convention note). */
__forceinline void ActiveObjects_DestroyBucket(unsigned int key)
{
    CActiveObjectRegistry *reg = (CActiveObjectRegistry *)DAT_00ea0e1c;
    ActiveObjectLayer *layer = reg->outerNext;
    if (key < layer->layerKey) {
        return;                     /* sorted list already past the key */
    }
    while (layer->layerKey != key) {
        layer = layer->outerNext;
        if (key < layer->layerKey) {
            return;
        }
    }
    ActiveObjectNode *node = layer->innerNext;
    while (node != (ActiveObjectNode *)layer) {
        void **vtable = (void **)node->vtable;   /* = *node in the raw port */
        node = node->innerNext;
        ((void (__cdecl *)(int))vtable[0])(1);   /* slot 0 dtor, free=1 */
    }
    layer->innerPrev = (ActiveObjectNode *)layer;
    layer->innerNext = (ActiveObjectNode *)layer;
}

#endif /* GB_CXX_ACTIVEOBJECTS_H */
