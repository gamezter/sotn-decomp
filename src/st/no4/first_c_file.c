// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C0FC8);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C123C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C12B0);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C15F8);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C1844);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C1C94);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C1EE4);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C21AC);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C2474);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C2850);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C2B78);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C2E60);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C3160);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C34EC);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C37C8);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C3A04);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C3CC4);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C3FB0);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4228);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4520);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4738);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4980);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4BD8);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4D2C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5020);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C50FC);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5134);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5268);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C542C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5518);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5628);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C582C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5868);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C58A0);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C59E0);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5AD4);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5C7C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C6CEC);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C6DA8);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C7204);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C726C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C789C);

void func_us_801C7FA4(void) {}

extern u16 D_us_801817E8;

void func_us_801C7FAC(void) {
    s32 i;
    Tilemap* tileMap = &g_Tilemap;
    s16 offset = 0x595;
    u16* var_a2 = &D_us_801817E8;

    for (i = 0; i < 7; i++) {
        *(tileMap->fg + offset) = *var_a2++;
        offset++;
        *(tileMap->fg + offset) = *var_a2++;
        offset = offset + 0xCF;
    }
}

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C801C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C8248);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C82B8);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C86F4);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C89F4);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C8CC4);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C8E4C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C9130);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C9460);

void func_us_801C9538(void) {
    D_us_801DF788 = 2;
    D_us_801DF78A = 0;
    D_us_801DF78E = 0;
    D_us_801DF78F = 8;
}

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C9568);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", CutsceneUnk3);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C9764);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C9800);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", ScaleCutsceneAvatar);

INCLUDE_RODATA("st/no4/nonmatchings/first_c_file", D_us_801C0A70);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C9A54);
