#include <common.h>

// On PSP side this is compared against g_UserLanguage / 0x08B42058
// which is the system language of the console. Used to determine the
// language of various strings to display in-game
typedef enum {
    LANG_JP,
    LANG_EN,
    LANG_FR,
    LANG_SP,
    LANG_GE,
    LANG_IT,
} Language;
u8* GetLangAt(s32 idx, u8* en, u8* fr, u8* sp, u8* ge, u8* it);

// PSP exclusive functions in PS.ELF
void func_892667C(s32 paletteID, u16* palette);
void func_91040A0(u_long** gfxBank);
