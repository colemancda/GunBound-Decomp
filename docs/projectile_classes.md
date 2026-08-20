# Per-weapon projectile classes

Generated 2026-08-20 by the slot-naming pass (see the projectile-class-map memory note).
Each row is one vtable in the CProjectile family, identified by a slot UNIQUE
to it; slots shared between vtables carry no class information and are shown
but were not used to identify anything.

Slot roles come from `src/cxx/Projectile.h`: 0 Delete, 1 SetState, 2 Animate,
3 Publish, 4 no-op, 5 Simulate, 6 Detonate, 7 InBounds, 8 Explode.

| class | vtable | 0 Delete | 2 Animate | 5 Simulate | 6 Detonate | 8 Explode |
|---|---|---|---|---|---|---|
| ItemShot | `0x555f9c` | `DeleteItemShot` | `AnimateProjectileTick` | `SimulateShot_Bullet8n_8s_Item` | `DetonateItemShot` | - |
| Mine | `0x5563f0` | `DeleteMine` | `AnimateMine` | `SimulateProjectileFrame` | `DetonateProjectile` | `ExplodeMine` |
| PrimaryShot_Bullet10 | `0x556160` | `DeletePrimaryShot_Bullet10` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `DetonatePrimaryShot_Bullet10` | - |
| PrimaryShot_Bullet14 | `0x555ea8` | `DeletePrimaryShot_Bullet14` | `AnimateProjectileTick` | `SimulatePrimaryShot_Bullet14` | `DetonateProjectile` | - |
| PrimaryShot_Bullet15 | `0x556058` | `DeletePrimaryShot_Bullet15` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `DetonatePrimaryShot_Bullet15` | - |
| PrimaryShot_Bullet4 | `0x5564d0` | `DeletePrimaryShot_Bullet4` | `AnimatePrimaryShot_Bullet4` | `SimulateProjectileFrame` | `DetonatePrimaryShot_Bullet4` | - |
| Projectile | `0x555c34` | `DeleteProjectile` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `DetonateProjectile` | - |
| Shot1_Bullet12 | `0x556680` | `DeleteShot1_Bullet12` | *uncarved* | `SimulateProjectileFrame` | `DetonateShot1_Bullet12` | - |
| Shot1_Bullet7 | `0x555aa4` | `DeleteShot1_Bullet7` | `AnimateProjectileTick` | `SimulateShot_Bullet7n_9s_7p_9p` | `DetonateShot1_Bullet7` | - |
| Shot1_Bullet8 | `0x5561a8` | `DeleteShot1_Bullet8` | `AnimateProjectileTick` | `SimulateShot_Bullet8n_8s_Item` | `DetonateShot1_Bullet8` | - |
| Shot1_Bullet9_16 | `0x555e88` | `DeleteShot1_Bullet9_16` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `DetonateShot1_Bullet9_16` | - |
| Shot2_Bullet1 | `0x555dac` | `DeleteShot2_Bullet1` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `DetonateShot2_Bullet1` | - |
| Shot2_Bullet11 | `0x555f38` | `DeleteShot2_Bullet11` | `AnimateProjectileTick` | `SimulateShot2_Bullet11` | `DetonateShot2_Bullet11` | - |
| Shot2_Bullet12 | `0x556660` | `DeleteShot2_Bullet12` | *uncarved* | `SimulateProjectileFrame` | `DetonateShot2_Bullet12` | - |
| Shot2_Bullet13 | `0x55649c` | `DeleteShot2_Bullet13` | `AnimateShot2_Bullet13` | `SimulateShot2_Bullet13` | `DetonateShot2_Bullet13` | - |
| Shot2_Bullet16 | `0x5565ac` | `DeleteShot2_Bullet16` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `DetonateShot2_Bullet16` | - |
| Shot2_Bullet2 | `0x5564f0` | `DeleteShot2_Bullet2` | *uncarved* | `SimulateProjectileFrame` | `DetonateShot2_Bullet2` | - |
| Shot2_Bullet3 | `0x5563a8` | `DeleteShot2_Bullet3` | `AnimateProjectileTick` | `SimulateShot2_Bullet3` | `DetonateShot2_Bullet3` | - |
| Shot2_Bullet7 | `0x5563d0` | `DeleteShot2_Bullet7` | *uncarved* | `SimulateProjectileFrame` | `DetonateShot2_Bullet7` | - |
| Shot2_Bullet8 | `0x556524` | `DeleteShot2_Bullet8` | `AnimateProjectileTick` | `SimulateShot_Bullet8n_8s_Item` | `DetonateShot2_Bullet8` | - |
| Shot2_Bullet9 | `0x555d14` | `DeleteShot2_Bullet9` | `AnimateProjectileTick` | `SimulateShot_Bullet7n_9s_7p_9p` | `DetonateShot2_Bullet9` | - |
| SuperMine | `0x556380` | `DeleteSuperMine` | `AnimateSuperMine` | `SimulateProjectileFrame` | `DetonateProjectile` | `ExplodeSuperMine` |
| SuperShot_Bullet1 | `0x555ac4` | `FUN_0044d990` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `DetonateSuperShot_Bullet1` | `ExplodeSuperShot_Bullet1_5_6_12_13_15` |
| SuperShot_Bullet10 | `0x555b18` | `DeleteSuperShot_Bullet10` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `DetonateSuperShot_Bullet10` | - |
| SuperShot_Bullet11 | `0x555f58` | `FUN_0044d990` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `DetonateSuperShot_Bullet2_8_11` | `ExplodeSuperShot_Bullet11` |
| SuperShot_Bullet12 | `0x55661c` | `FUN_0044d990` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `DetonateSuperShot_Bullet12` | `ExplodeSuperShot_Bullet1_5_6_12_13_15` |
| SuperShot_Bullet13 | `0x55620c` | `DeleteSuperShot_Bullet13` | *uncarved* | `SimulateSuperShot_Bullet13` | `DetonateSuperShot_Bullet13` | `ExplodeSuperShot_Bullet1_5_6_12_13_15` |
| SuperShot_Bullet14 | `0x555e30` | `FUN_0044d990` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `DetonateSuperShot_Bullet3_5_14` | `ExplodeSuperShot_Bullet14` |
| SuperShot_Bullet15 | `0x556098` | `FUN_0044d990` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `DetonateSuperShot_Bullet15` | `ExplodeSuperShot_Bullet1_5_6_12_13_15` |
| SuperShot_Bullet16 | `0x555d74` | `FUN_0044d990` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `DetonateSuperShot_Bullet16` | `ExplodeSuperShot_Bullet16` |
| SuperShot_Bullet2 | `0x5562c8` | `FUN_0044d990` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `DetonateSuperShot_Bullet2_8_11` | `ExplodeSuperShot_Bullet2` |
| SuperShot_Bullet3 | `0x556284` | `FUN_0044d990` | `AnimateSuperShot_Bullet3` | `SimulateSuperShot_Bullet3` | `DetonateSuperShot_Bullet3_5_14` | `ExplodeSuperShot_Bullet3` |
| SuperShot_Bullet4 | `0x5565f8` | `FUN_0044d990` | `AnimateSuperShot_Bullet4` | `SimulateProjectileFrame` | `DetonateSuperShot_Bullet4` | `ExplodeSuperShot_Bullet4` |
| SuperShot_Bullet6 | `0x555bf0` | `FUN_0044d990` | *uncarved* | `SimulateProjectileFrame` | `DetonateSuperShot_Bullet6` | `ExplodeSuperShot_Bullet1_5_6_12_13_15` |
| SuperShot_Bullet7 | `0x556424` | `FUN_0044d990` | `AnimateProjectileTick` | `SimulateShot_Bullet7n_9s_7p_9p` | `DetonateSuperShot_Bullet7` | *uncarved* |
| SuperShot_Bullet8 | `0x5561c8` | `FUN_0044d990` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `DetonateSuperShot_Bullet2_8_11` | `ExplodeSuperShot_Bullet8` |
| SuperShot_Bullet9 | `0x556360` | `DeleteSuperShot_Bullet9` | `AnimateProjectileTick` | `SimulateShot_Bullet7n_9s_7p_9p` | `DetonateSuperShot_Bullet9` | - |
| UNIDENTIFIED | `0x555bd0` | `FUN_00451380` | `FUN_00452bf0` | `SimulateProjectileFrame` | `FUN_004513b0` | - |
| UNIDENTIFIED | `0x555cf4` | `FUN_00464440` | *uncarved* | `SimulateProjectileFrame` | `DetonateProjectile` | - |
| UNIDENTIFIED | `0x555dcc` | `FUN_0046a4a0` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `FUN_0046a4d0` | - |
| UNIDENTIFIED | `0x555dec` | `FUN_0046aee0` | `FUN_0046b610` | `SimulateProjectileFrame` | `FUN_0046af10` | - |
| UNIDENTIFIED | `0x555e0c` | `FUN_0046b650` | `FUN_0046c990` | `SimulateProjectileFrame` | `FUN_0046b680` | - |
| UNIDENTIFIED | `0x555fbc` | `FUN_00476f50` | *uncarved* | `SimulateProjectileFrame` | `DetonateProjectile` | - |
| UNIDENTIFIED | `0x556008` | `FUN_0047aad0` | `FUN_0047ab00` | `SimulateProjectileFrame` | `DetonateProjectile` | - |
| UNIDENTIFIED | `0x556078` | `FUN_0047bde0` | `FUN_0047ca40` | `SimulateProjectileFrame` | `DetonateProjectile` | - |
| UNIDENTIFIED | `0x5560d0` | `FUN_0047eb90` | *uncarved* | `SimulateProjectileFrame` | `DetonateProjectile` | - |
| UNIDENTIFIED | `0x556110` | `FUN_0047fa30` | `FUN_00480310` | `SimulateProjectileFrame` | `DetonateProjectile` | - |
| UNIDENTIFIED | `0x55631c` | `FUN_0044d990` | `AnimateProjectileTick` | `SimulateProjectileFrame` | `DetonateSuperShot_Bullet3_5_14` | `ExplodeSuperShot_Bullet1_5_6_12_13_15` |
| UNIDENTIFIED | `0x556340` | `FUN_0048f260` | `FUN_00490780` | `SimulateProjectileFrame` | `DetonateProjectile` | - |
| UNIDENTIFIED | `0x556468` | `FUN_0049cc40` | *uncarved* | `SimulateProjectileFrame` | `FUN_0049d270` | - |
| UNIDENTIFIED | `0x55656c` | `FUN_004aa8c0` | `FUN_004aa8f0` | `SimulateProjectileFrame` | `DetonateProjectile` | - |
| UNIDENTIFIED | `0x55658c` | `FUN_004aac80` | *uncarved* | `SimulateProjectileFrame` | `DetonateProjectile` | - |

52 vtables in the family; 37 identified, 15 not.

The unidentified ones have no slot unique to them - every named slot they
carry appears in several other vtables - so there is nothing to name them by
without guessing. Two of them (`0x55631c`, `0x5560d0`) are each installed by
TWO different destructors, so even a correct vtable mapping could not separate
the classes.
