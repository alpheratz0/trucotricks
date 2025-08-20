// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <stddef.h>
#include <nanovg.h>
#include <stddef.h>
#include <trucotricks/gallery_switcher.h>
#include <trucotricks/cursor.h>
#include <trucotricks/mouse.h>
#include <trucotricks/rect.h>
#include <trucotricks/resources.h>
#include <trucotricks/time.h>
#include <trucotricks/util.h>
#include <trucotricks/window.h>

#define CORNER_RADIUS (5.0f)
#define SHADOW_COLOR (nvgRGBA(0x00, 0x00, 0x00, 0x7f))
#define UNSELECTED_COLOR (nvgRGBA(0xcc, 0xcc, 0x33, 0xee))
#define SELECTED_COLOR (nvgRGBA(0xff, 0xff, 0xff, 0xee))
#define HOVER_THRESHOLD (3)

void Tt_Gallery_Switcher_Update(Tt_Gallery_Switcher *gs)
{
	float spacing = (float)(gs->w - gs->h) / (gs->buttonCount - 1);

	float radius = (float)gs->h / 2;
	float x = gs->x + radius;
	float y = gs->y + radius;

	int nothingHovered = 1;

	for (size_t i = 0; i < gs->buttonCount; ++i) {
		nvgBeginPath(gVg);
		nvgFillColor(gVg, SHADOW_COLOR);
		nvgArc(gVg, x, y+2, radius, 0, M_PI * 2, NVG_CW);
		nvgFill(gVg);

		nvgBeginPath(gVg);
		nvgFillColor(gVg, i == gs->selectedIndex ? UNSELECTED_COLOR : SELECTED_COLOR);
		nvgArc(gVg, x, y, radius, 0, M_PI * 2, NVG_CW);
		nvgFill(gVg);

		if (Tt_Mouse_Distance_To_Mouse(x, y) <= (radius + HOVER_THRESHOLD)) {
			nothingHovered = 0;
			if (gs->selectedIndex != i) {
				Tt_Cursor_Request(CURSOR_SHAPE_HAND);
				if (Tt_Mouse_Is_Button_Just_Pressed(MOUSE_BUTTON_LEFT)) {
					gs->selectedIndex = (int)i;
					if (NULL != gs->onClick)
						gs->onClick(gs, (int)i);
				}
			}

			if (gs->hoverTime > 0.5f) {
				nvgBeginPath(gVg);
				float padding = 10.0f;
				nvgFontFaceId(gVg, gFontTerminus);
				nvgFontSize(gVg, 16.0f);
				float tw = nvgTextBounds(gVg, 0, 0, gs->buttonTooltips[i], NULL, NULL);

				float tooltipY = y - 45.0f - gs->h;
				float tooltipX = x - tw/2 - padding;

				float fade = (gs->hoverTime - 0.5f) / 0.5f;

				if (fade > 1.0f) fade = 1.0f;

				nvgFillColor(gVg, nvgRGBA(0xff, 0xff, 0xff, (fade * 0.8f) * 0xff));
				nvgRoundedRect(gVg, tooltipX, tooltipY + 5.0f * (1.0f - fade), tw + padding * 2.0f, 30.0f, CORNER_RADIUS);
				nvgFill(gVg);

				nvgBeginPath(gVg);
				nvgFillColor(gVg, nvgRGBA(0x00, 0x00, 0x00, fade * 0xff));
				nvgTextAlign(gVg, NVG_ALIGN_LEFT|NVG_ALIGN_MIDDLE);
				nvgText2(gVg, tooltipX + padding, tooltipY + 15.0f + 5.0f * (1.0f - fade), gs->buttonTooltips[i], NULL);
				nvgFill(gVg);
			}
		}

		x += spacing;
	}

	if (nothingHovered) {
		gs->hoverTime = 0;
	} else {
		gs->hoverTime += gDeltaTime;
	}
}
