// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_RESOURCES_H
#define TRUCOTRICKS_RESOURCES_H

#include <stdbool.h>
#include <SDL_mixer.h>

#define TEXTURE_INVALID (-1)
#define FONT_INVALID (-1)
#define SOUND_INVALID (NULL)

#define Tt_Texture_Is_Valid(texture) (texture != TEXTURE_INVALID)
#define Tt_Font_Is_Valid(font) (font != FONT_INVALID)
#define Tt_Sound_Is_Valid(sound) (sound != SOUND_INVALID)

typedef int Tt_Texture;
typedef int Tt_Font;
typedef Mix_Chunk * Tt_Sound;

extern Tt_Texture gTexBackgroundParallax[5];
extern Tt_Texture gTexUnknownCard;
extern Tt_Texture gTexBasto[10];
extern Tt_Texture gTexOro[10];
extern Tt_Texture gTexEspada[10];
extern Tt_Texture gTexCopa[10];
extern Tt_Texture gTexGoldCoin;
extern Tt_Font gFontTerminus;
extern Tt_Font gFontAttackOfMonster;
extern Tt_Sound gSoundSwipe;
extern Tt_Sound gSoundGameOver;
extern Tt_Sound gSoundBackgroundMusic;
extern Tt_Sound gSoundSceneSwitching;

#endif
