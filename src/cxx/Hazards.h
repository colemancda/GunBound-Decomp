/* The weather terrain-hazard objects: CTornadoHazard / CFirewallHazard /
 * CLightningHazard - the packet-driven stage hazards (the server sends a
 * descriptor at packet+0x22; stage.dat's hazard fields go unconsumed - see
 * the weather-hazard spawn-chain notes in the Spawn*Hazard.c headers).
 *
 * Tier-1 coverage promotion (2026-08-18): every slot of all three vtables
 * is ported (docs/vtable_coverage.txt), the spawn chain was fully renamed
 * 2026-07-16, and the field map was angr-decoded in SpawnTornadoHazard.c's
 * header - this file turns that evidence into declared classes.
 *
 * ABI: the SAME flat 5-slot active-object vtable as CButtonWidget /
 * CFlameEffect (ButtonWidget.h / Effects.h), and the hazards REFINE what
 * slot 4 means: it is not inherently a no-op - it is the LIFETIME hook
 * (TickWeatherHazardLifetime / TickTornadoHazardLifetime decrement the
 * +0x484-family countdown and mark the object dead); the button/effect
 * classes simply stub it with NoOpMethod.
 *
 *   CTornadoHazard    0x6a8  ctor InitTornadoHazard   (0x4ac5xx)  vtable 0x5565e4
 *     Tick 0x4ac750 TickTornadoHazardFrame   Draw 0x4ac760 RenderTornadoHazard
 *     Lifetime 0x4acc90 TickTornadoHazardLifetime      layer key 500
 *   CFirewallHazard   0x6ac  ctor InitFirewallHazard  (0x4713xx)  vtable 0x555edc
 *     Tick 0x46e010 TickWeatherHazardFrame   Draw 0x471550 RenderFirewallHazard
 *     Lifetime 0x471a90 TickWeatherHazardLifetime
 *   CLightningHazard  0x6ac  ctor InitLightningHazard (0x46dexx)  vtable 0x555e74
 *     Tick 0x46e010 (SHARED with Firewall)   Draw 0x46e020 RenderLightningHazard
 *     Lifetime 0x471a90 (SHARED with Firewall)
 *
 * LAYOUT (from SpawnTornadoHazard.c's angr-decoded reference map): after
 * the active-object header the body is THREE full CValueGuard cells -
 * the anti-cheat treatment of the hazard's whole state:
 *     +0x38  position   (1D world-X; Y implicit from terrain height)
 *     +0x25c extent     (width; /4 = merge radius, *2 = draw span)
 *     +0x484 lifetime   (ticks; 10000 at the spawn site; slot 4 counts it
 *                        down)  [a 4-byte field sits at +0x480 between
 *                        cells 2 and 3]
 * Firewall/Lightning shift every cell +4 (their ctors run an extra
 * InitGuardedBool), hence 0x6ac vs the Tornado's 0x6a8.  The GuardedBool
 * and per-cell interior mapping is not done, so the bodies stay opaque
 * m_raw tails with the documented offsets above - sizeof() is what the
 * asserts pin (checked in cxx_selftest.cpp).
 */
#ifndef GB_CXX_HAZARDS_H
#define GB_CXX_HAZARDS_H

#include "gb_common.h"

#pragma pack(push, 1)

class CTornadoHazard {
public:
    virtual void *Delete(int shouldFree);        /* 0x4ac650 - scalar-deleting dtor */
    virtual void SetState(const char *name);     /* 0x461c60 - ResolveNamedState (shared) */
    virtual int Tick();                          /* 0x4ac750 - TickTornadoHazardFrame */
    virtual void Draw();                         /* 0x4ac760 - RenderTornadoHazard
                                                  * (screenX = pos - cameraX + 400) */
    virtual void TickLifetime();                 /* 0x4acc90 - TickTornadoHazardLifetime */

    u8 m_raw[0x6a8 - 4];    /* +0x04 layer key 500; CValueGuard cells at
                             * +0x38 position / +0x25c extent / +0x484
                             * lifetime (see the header comment) */
};
GB_STATIC_ASSERT(sizeof(CTornadoHazard) == 0x6a8, tornadohazard_size);

class CFirewallHazard {
public:
    virtual void *Delete(int shouldFree);        /* 0x471450 - scalar-deleting dtor */
    virtual void SetState(const char *name);     /* 0x461c60 - ResolveNamedState (shared) */
    virtual int Tick();                          /* 0x46e010 - TickWeatherHazardFrame
                                                  * (shared with CLightningHazard) */
    virtual void Draw();                         /* 0x471550 - RenderFirewallHazard */
    virtual void TickLifetime();                 /* 0x471a90 - TickWeatherHazardLifetime
                                                  * (shared with CLightningHazard) */

    u8 m_raw[0x6ac - 4];    /* the Tornado layout with every guard cell
                             * shifted +4 (extra InitGuardedBool in the ctor):
                             * position +0x3c / extent +0x260 / lifetime +0x488 */
};
GB_STATIC_ASSERT(sizeof(CFirewallHazard) == 0x6ac, firewallhazard_size);

class CLightningHazard {
public:
    virtual void *Delete(int shouldFree);        /* 0x46df10 - scalar-deleting dtor */
    virtual void SetState(const char *name);     /* 0x461c60 - ResolveNamedState (shared) */
    virtual int Tick();                          /* 0x46e010 - TickWeatherHazardFrame */
    virtual void Draw();                         /* 0x46e020 - RenderLightningHazard */
    virtual void TickLifetime();                 /* 0x471a90 - TickWeatherHazardLifetime */

    u8 m_raw[0x6ac - 4];    /* same +4-shifted layout as CFirewallHazard */
};
GB_STATIC_ASSERT(sizeof(CLightningHazard) == 0x6ac, lightninghazard_size);

#pragma pack(pop)

#endif /* GB_CXX_HAZARDS_H */
