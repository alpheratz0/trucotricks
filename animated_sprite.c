// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <nanovg.h>
#include <trucotricks/animated_sprite.h>
#include <trucotricks/time.h>
#include <trucotricks/window.h>

void Tt_Animated_Sprite_Update(Tt_Animated_Sprite *animatedSprite)
{
	int tileSetW, tileSetH;
	nvgImageSize(gVg, animatedSprite->tileSet, &tileSetW, &tileSetH);
	float tileWidth = tileSetW / animatedSprite->nTiles;
	float tileX = tileWidth * (animatedSprite->frame % animatedSprite->nTiles);
	float scaleHorizontal = animatedSprite->w / tileWidth;
	float scaleVertical = animatedSprite->h / tileSetH;

	animatedSprite->timeSinceAdvancingFrame += gDeltaTime;

	if (animatedSprite->timeSinceAdvancingFrame > 0.1f) {
		animatedSprite->timeSinceAdvancingFrame = 0.0f;
		animatedSprite->frame = (animatedSprite->frame + 1) % animatedSprite->nTiles;
	}

	// Draw sprite
	nvgBeginPath(gVg);
	nvgRect(gVg, animatedSprite->x, animatedSprite->y, animatedSprite->w, animatedSprite->h);
	nvgFillPaint(gVg, nvgImagePattern(gVg, animatedSprite->x - tileX * scaleHorizontal,
				animatedSprite->y, tileSetW*scaleHorizontal, tileSetH * scaleVertical,
				0.0, animatedSprite->tileSet, 1.0));
	nvgFill(gVg);
}
