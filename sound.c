// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <trucotricks/resources.h>
#include <trucotricks/util.h>
#include <SDL_mixer.h>

void Tt_Sound_Play(Tt_Sound sound) { Mix_PlayChannel(1, sound, 0); }
void Tt_Sound_Pause_Music(void) { Mix_Pause(2); }
void Tt_Sound_Resume_Music(void) { Mix_Resume(2); }

void Tt_Sound_Play_Music(Tt_Sound sound, float volume)
{
	Mix_Volume(2, Tt_Clamp(volume, 0.0f, 1.0f) * MIX_MAX_VOLUME);
	Mix_PlayChannel(2, sound, -1);
}
