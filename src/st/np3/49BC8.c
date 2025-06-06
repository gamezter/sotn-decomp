// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"
#include "sfx.h"

void EntityZombie(Entity* self) {
    Entity* newEntity;
    s32 temp_a0;

    if ((self->flags & FLAG_DEAD) && (self->step < 4)) {
        PlaySfxPositional(SFX_EXPLODE_SMALL);
        self->hitboxState = 0;
        // Spawn Zombie explosion
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLODE_PUFF_OPAQUE, self, newEntity);
            newEntity->zPriority = self->zPriority + 1;
            newEntity->params = 3;
            newEntity->posY.i.hi += 12;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitZombie);
        self->hitboxWidth = 8;
        self->hitboxOffY = 0x10;
        self->hitboxHeight = 0;
        self->zPriority += 4;
        if (g_Timer & 1) {
            self->palette++;
        }
        if (Random() & 1) {
            self->palette++;
        }
        self->animCurFrame = 0;
        break;

    case 1:
        if (UnkCollisionFunc3(D_801825BC) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step++;
        }
        break;

    case 2:
        if (AnimateEntity(D_80182594, self) == 0) {
            SetStep(3);
        }
        if (self->poseTimer == 0) {
            self->hitboxOffY -= 2;
            self->hitboxHeight += 2;
        }
        break;

    case 3:
        AnimateEntity(D_8018258C, self);
        temp_a0 = UnkCollisionFunc2(&D_801825CC);
        if (self->facingLeft != 0) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }

        if (temp_a0 & 0xC0) {
            self->hitboxState = 0;
            SetStep(4);
        }
        break;

    case 4:
        if (AnimateEntity(D_801825A8, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

/*
 * An invisible entity that is responsible for spawning the "floor
 * zombies" that come up from the ground and swarm the player.
 * Every 32 to 95 frames, it will alternate spawning a zombie
 * on the right side or left side of the screen.
 * The exact position a zombie is spawned in is also randomized.
 */
void EntityZombieSpawner(Entity* self) {
    s32 distCameraEntity;
    Entity* newEntity;
    s32 rnd;

    if (self->step == 0) {
        InitializeEntity(g_EInitSpawner);
        self->ext.zombieSpawner.spawnDelay = 1;
        self->flags &= FLAG_UNK_2000;
    }

    if (g_CastleFlags[CASTLE_TURNED_ON]) {
        self->posX.i.hi = 128;
        if (--self->ext.zombieSpawner.spawnDelay == 0) {
            newEntity = AllocEntity(g_Entities + 160, g_Entities + 168);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_ZOMBIE, self, newEntity);
                rnd = (Random() & 0x3F) + 96;

                if (self->ext.zombieSpawner.spawnSide != 0) {
                    newEntity->posX.i.hi += rnd;
                } else {
                    newEntity->posX.i.hi -= rnd;
                }
                newEntity->posY.i.hi -= 48;
                self->ext.zombieSpawner.spawnSide ^= 1;

                // Zombies are prevented from spawning too close to the
                // edges of the room.
                distCameraEntity =
                    g_Tilemap.scrollX.i.hi + newEntity->posX.i.hi;
                if ((distCameraEntity < (g_Tilemap.x + 128)) ||
                    ((g_Tilemap.width - 128) < distCameraEntity)) {
                    DestroyEntity(newEntity);
                }
            }
            self->ext.zombieSpawner.spawnDelay = (Random() & 0x3F) + 32;
        }
    }
}
