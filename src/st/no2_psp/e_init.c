// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no2/no2.h"

void EntityUnkBreakable(Entity* self);
void EntityExplosion(Entity* self);
void EntityPrizeDrop(Entity* self);
void EntityDamageDisplay(Entity* self);
void OVL_EXPORT(EntityRedDoor)(Entity* self);
void EntityIntenseExplosion(Entity* self);
void EntitySoulStealOrb(Entity* self);
void EntityRoomForeground(Entity* self);
void EntityStageNamePopup(Entity* self);
void EntityEquipItemDrop(Entity* self);
void EntityRelicOrb(Entity* self);
void EntityHeartDrop(Entity* self);
void OVL_EXPORT(EntityBackgroundBlock)(Entity* self);
void OVL_EXPORT(EntityLockCamera)(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void EntitySkelerang(Entity* self);
void EntitySkelerangBoomerang(Entity* self);
void EntitySkelerangUnknown(Entity* self);
void func_pspeu_092575D8(Entity* self);
void func_pspeu_09257810(Entity* self);
void func_pspeu_09257B10(Entity* self);
void func_pspeu_09257B78(Entity* self);
void func_pspeu_09257C00(Entity* self);
void func_pspeu_09259E40(Entity* self);
void func_pspeu_09259D40(Entity* self);
void func_pspeu_0925A248(Entity* self);
void func_us_801C3D44(Entity* self);
void func_pspeu_0925BBA8(Entity* self);
void func_us_801C379C(Entity* self);
void func_pspeu_092556A0(Entity* self);
void func_pspeu_09256348(Entity* self);
void func_pspeu_09255EF0(Entity* self);
void EntityBigRedFireball(Entity* self);
void func_pspeu_0925A988(Entity* self);
void EntityOwlKnight(Entity* self);
void EntityOwl(Entity* self);
void EntityOwlKnightSword(Entity* self);
void EntityOwlTarget(Entity* self);
void EntityBloodyZombie(Entity* self);
void EntityBloodDrips(Entity* self);
void EntityBloodSplatter(Entity* self);
void func_pspeu_0925B730(Entity* self);
void func_us_801C3ED8(Entity* self);
void func_pspeu_0925B278(Entity* self);
void func_pspeu_09257ED8(Entity* self);
void func_pspeu_0923D188(Entity* self);
void func_pspeu_0923DCC0(Entity* self);
void func_pspeu_0923DE98(Entity* self);
void func_pspeu_09253010(Entity* self);
void func_pspeu_09254098(Entity* self);
void func_pspeu_09254520(Entity* self);
void func_pspeu_092515D0(Entity* self);
void func_pspeu_092529B0(Entity* self);
void func_pspeu_0924F990(Entity* self);
void func_pspeu_09250ED0(Entity* self);
void func_pspeu_0924AB98(Entity* self);
void func_pspeu_0924BE50(Entity* self);
void func_pspeu_0924BF68(Entity* self);
void func_801A8328(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityUnkBreakable,
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    OVL_EXPORT(EntityRedDoor),
    EntityIntenseExplosion,
    EntitySoulStealOrb,
    EntityRoomForeground,
    EntityStageNamePopup,
    EntityEquipItemDrop,
    EntityRelicOrb,
    EntityHeartDrop,
    EntityEnemyBlood,
    EntityMessageBox,
    EntityDummy,
    EntityDummy,
    OVL_EXPORT(EntityBackgroundBlock),
    OVL_EXPORT(EntityLockCamera),
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    EntitySkelerang,
    EntitySkelerangBoomerang,
    EntitySkelerangUnknown,
    func_pspeu_092575D8,
    func_pspeu_09257810,
    func_pspeu_09257B10,
    func_pspeu_09257B78,
    func_pspeu_09257C00,
    func_pspeu_09259E40,
    func_pspeu_09259D40,
    func_pspeu_0925A248,
    func_us_801C3D44,
    func_pspeu_0925BBA8,
    func_us_801C379C,
    func_pspeu_092556A0,
    func_pspeu_09256348,
    func_pspeu_09255EF0,
    EntityBigRedFireball,
    func_pspeu_0925A988,
    EntityOwlKnight,
    EntityOwl,
    EntityOwlKnightSword,
    EntityOwlTarget,
    EntityBloodyZombie,
    EntityBloodDrips,
    EntityBloodSplatter,
    func_pspeu_0925B730,
    func_us_801C3ED8,
    func_pspeu_0925B278,
    func_pspeu_09257ED8,
    func_pspeu_0923D188,
    func_pspeu_0923DCC0,
    func_pspeu_0923DE98,
    func_pspeu_09253010,
    func_pspeu_09254098,
    func_pspeu_09254520,
    func_pspeu_092515D0,
    func_pspeu_092529B0,
    func_pspeu_0924F990,
    func_pspeu_09250ED0,
    func_pspeu_0924AB98,
    func_pspeu_0924BE50,
    func_pspeu_0924BF68,
    func_801A8328,
};

EInit D_pspeu_09266618 = {ANIMSET_DRA(0x03), 0x00, 0x00, PAL_NONE, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(0x03), 0x00, 0x00, PAL_NONE, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(0x03), 0x00, 0x00, PAL_NONE, 0x002};
EInit D_pspeu_09266648 = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, 0x003};
EInit g_EInitSkelerang = {ANIMSET_OVL(0x01), 0x01, 0x48, PAL_SKELERANG, 0x00B};
EInit g_EInitSkelerangBoomerang = {
    ANIMSET_OVL(0x01), 0x2B, 0x48, PAL_SKELERANG, 0x00C};
EInit D_pspeu_092666C8 = {ANIMSET_OVL(0x02), 0x0B, 0x00, PAL_NONE, 0x003};
EInit D_pspeu_092666D8 = {ANIMSET_OVL(0x03), 0x01, 0x49, PAL_UNK_203, 0x003};
EInit g_EInitOwlKnight = {ANIMSET_OVL(0x08), 0x10, 0x49, PAL_OWL_KNIGHT, 0x014};
EInit g_EInitOwlKnightSword = {
    ANIMSET_OVL(0x08), 0x00, 0x49, PAL_OWL_KNIGHT_SWORD, 0x015};
EInit g_EInitOwl = {ANIMSET_OVL(0x08), 0x01, 0x49, PAL_OWL_KNIGHT, 0x016};
EInit g_EInitBloodyZombie = {
    ANIMSET_OVL(0x09), 0x01, 0x4A, PAL_BLOODY_ZOMBIE, 0x00D};
EInit D_pspeu_09266728 = {ANIMSET_OVL(0x02), 0x0E, 0x00, PAL_NONE, 0x005};
EInit D_pspeu_09266738 = {ANIMSET_OVL(0x05), 0x01, 0x4C, PAL_UNK_207, 0x085};
EInit D_pspeu_09266748 = {ANIMSET_OVL(0x05), 0x01, 0x4C, PAL_UNK_207, 0x003};
EInit D_pspeu_09266758 = {ANIMSET_OVL(0x00), 0x00, 0x00, PAL_NONE, 0x086};
EInit D_pspeu_09266768 = {ANIMSET_OVL(0x00), 0x00, 0x00, PAL_NONE, 0x087};
EInit D_pspeu_09266778 = {ANIMSET_OVL(0x06), 0x02, 0x4C, PAL_UNK_23E, 0x0BA};
EInit D_pspeu_09266788 = {ANIMSET_OVL(0x06), 0x12, 0x4C, PAL_UNK_23E, 0x0BB};
EInit D_pspeu_09266798 = {ANIMSET_OVL(0x06), 0x02, 0x4C, PAL_UNK_23B, 0x0BC};
EInit D_pspeu_092667A8 = {ANIMSET_OVL(0x06), 0x14, 0x4C, PAL_UNK_23B, 0x0BD};
EInit D_pspeu_092667B8 = {ANIMSET_OVL(0x06), 0x02, 0x4C, PAL_UNK_238, 0x0BE};
EInit D_pspeu_092667C8 = {ANIMSET_OVL(0x06), 0x13, 0x4C, PAL_UNK_238, 0x0BF};
EInit D_pspeu_092667D8 = {ANIMSET_OVL(0x04), 0x00, 0x50, PAL_UNK_241, 0x081};
EInit D_pspeu_092667E8 = {ANIMSET_OVL(0x04), 0x00, 0x50, PAL_UNK_241, 0x002};
EInit D_pspeu_092667F8 = {ANIMSET_OVL(0x04), 0x00, 0x50, PAL_UNK_241, 0x082};
