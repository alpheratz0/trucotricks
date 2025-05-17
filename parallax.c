// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <stddef.h>
#include <nanovg.h>
#include <stdlib.h>
#include <stddef.h>
#include <trucotricks/parallax.h>
#include <trucotricks/time.h>
#include <trucotricks/window.h>

#define MAX_RAINDROPS 250

typedef struct {
    float x, y, length, speed, width;
	NVGcolor color;
} Tt_Raindrop;

static Tt_Raindrop drops[MAX_RAINDROPS];
static int rainInitialized = 0;

void Tt_Parallax_Update(Tt_Parallax *parallax)
{
	for (size_t i = 0; i < parallax->nTextures; ++i) {
		float delta = parallax->deltaX[i];
		parallax->deltaX[i] += gDeltaTime * 5.0f * i;
		if (parallax->deltaX[i] > 1000000) {
			parallax->deltaX[i] -= 1000000;
		}
		NVGpaint paint = nvgImagePattern(gVg, parallax->x + delta, parallax->y, parallax->w, parallax->h, 0.0, parallax->textures[i], 1.0);
		nvgBeginPath(gVg);
		nvgRect(gVg, parallax->x, parallax->y, parallax->w, parallax->h);
		nvgFillPaint(gVg, paint);
		nvgFill(gVg);
	}

	// Rain
	if (!rainInitialized) {
		for (int i = 0; i < MAX_RAINDROPS; i++) {
			drops[i].x = rand() % (int)gWindowWidth;
			drops[i].y = rand() % (int)gWindowHeight;
			drops[i].length = 20 + rand() % 10;
			drops[i].speed = 400 + rand() % 300;
			drops[i].width = 0.8f + (rand() % 3) * 0.1f;
			drops[i].color = nvgRGBAf(0.6f, 0.8f, 1.0f, 0.4f + (rand() % 6) * 0.10f);
		}
		rainInitialized = 1;
	}

    for (int i = 0; i < MAX_RAINDROPS; i++) {
        drops[i].x += gDeltaTime * 5.0f * (parallax->nTextures - 1);
        drops[i].y += gDeltaTime * drops[i].speed;

		if (drops[i].x > gWindowWidth)
			drops[i].x -= gWindowWidth;

        if (drops[i].y > gWindowHeight) {
            drops[i].y = -drops[i].length;
            drops[i].x = rand() % (int)gWindowWidth;
        }

		nvgBeginPath(gVg);
        nvgMoveTo(gVg, drops[i].x, drops[i].y);
        nvgLineTo(gVg, drops[i].x - 5, drops[i].y + drops[i].length);
		nvgStrokeColor(gVg, drops[i].color);
		nvgStrokeWidth(gVg, drops[i].width);
		nvgStroke(gVg);
    }

	nvgBeginPath(gVg);
	nvgRect(gVg, 0, 0, gWindowWidth, gWindowHeight);
	nvgFillColor(gVg, nvgRGBA(0x00, 0x00, 0x00, 0x42));
	nvgFill(gVg);
}
