// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <stddef.h>
#include <nanovg.h>
#include <stddef.h>
#include <trucotricks/parallax.h>
#include <trucotricks/time.h>
#include <trucotricks/window.h>

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

	nvgBeginPath(gVg);
	nvgRect(gVg, 0, 0, gWindowWidth, gWindowHeight);
	nvgFillColor(gVg, nvgRGBA(0x00, 0x00, 0x00, 0x42));
	nvgFill(gVg);
}
