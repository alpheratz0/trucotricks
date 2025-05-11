// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_ANIMATED_SPRITE_H
#define TRUCOTRICKS_ANIMATED_SPRITE_H

#include <trucotricks/resources.h>

typedef struct Tt_Animated_Sprite Tt_Animated_Sprite;

struct Tt_Animated_Sprite {
	// AnimatedSprite position & size
	float x, y, w, h;
	// Animation configuration
	int frame;
	int nTiles;
	Tt_Texture tileSet;
	float timeSinceAdvancingFrame;
};

void Tt_Animated_Sprite_Update(Tt_Animated_Sprite *animatedSprite);

#endif
