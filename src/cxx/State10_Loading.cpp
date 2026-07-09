/* CState10Loading - the loading interstitial. Only OnExit is promoted
 * so far (0x43eff0); OnEnter (0x43e840, checksum-state seeding) and
 * PreloadAssets are Phase 3 work - they live deep in g_clientContext.
 * See src/cxx/README.md. */
#include "GameState.h"
#include "ActiveObjects.h"

/* 0x43eff0 - destroy the loading screen's three container buckets:
 * 10000 (the screen sprite set every state uses) plus 10001/10002
 * (the preloaded battle asset buckets PreloadAssets fills). */
void CState10Loading::OnExit()
{
    ActiveObjects_DestroyBucket(10000);
    ActiveObjects_DestroyBucket(0x2711);
    ActiveObjects_DestroyBucket(0x2712);
}
