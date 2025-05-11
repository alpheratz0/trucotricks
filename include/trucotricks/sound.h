// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_SOUND_H
#define TRUCOTRICKS_SOUND_H

#include <trucotricks/resources.h>

void Tt_Sound_Play(Tt_Sound sound);
void Tt_Sound_Play_Music(Tt_Sound sound, /*Value between 0 and 1*/float volume);
void Tt_Sound_Pause_Music(void);
void Tt_Sound_Resume_Music(void);

#endif
