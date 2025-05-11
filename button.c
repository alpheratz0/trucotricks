// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <stddef.h>
#include <nanovg.h>
#include <stddef.h>
#include <trucotricks/button.h>
#include <trucotricks/cursor.h>
#include <trucotricks/mouse.h>
#include <trucotricks/rect.h>
#include <trucotricks/resources.h>
#include <trucotricks/time.h>
#include <trucotricks/util.h>
#include <trucotricks/window.h>

#define CORNER_RADIUS (5.0f)
#define CLICK_ANIMATION_SPEED (8.0f)
#define SHADOW_SIZE (5.0f)
#define BACKGROUND_COLOR (nvgRGB(0x2f, 0x5e, 0x85))
#define FOREGROUND_COLOR (nvgRGB(0xff, 0xff, 0xff))

void Tt_Button_Update(Tt_Button *btn)
{
	Tt_Rect rect = Tt_Rect_From_Width_And_Height(btn->x, btn->y, btn->w, btn->h);

	if (Tt_Mouse_Is_Over_Rect(&rect)) {
		Tt_Cursor_Request(CURSOR_SHAPE_HAND);
		if (Tt_Mouse_Is_Button_Pressed(MOUSE_BUTTON_LEFT)) {
			btn->clickAnimT += CLICK_ANIMATION_SPEED * gDeltaTime;
		} else if (Tt_Mouse_Is_Button_Just_Released(MOUSE_BUTTON_LEFT)) {
			if (btn->onClick)
				btn->onClick(btn);
		} else {
			btn->clickAnimT -= CLICK_ANIMATION_SPEED * gDeltaTime;
		}
	} else {
		btn->clickAnimT -= CLICK_ANIMATION_SPEED * gDeltaTime;
	}

	btn->clickAnimT = Tt_Clamp(btn->clickAnimT, 0.0f, 1.0f);

	// Solid shadow at the bottom
	Tt_Rect bottomShadowRect = Tt_Rect_Translate(&rect, 0, SHADOW_SIZE);
	nvgBeginPath(gVg);
	nvgRoundedRect(gVg, bottomShadowRect.x, bottomShadowRect.y, bottomShadowRect.w, bottomShadowRect.h, CORNER_RADIUS);
	nvgFillPaint(gVg, nvgBoxGradient(gVg, bottomShadowRect.x, bottomShadowRect.y, bottomShadowRect.w, bottomShadowRect.h,
				CORNER_RADIUS, 2, nvgRGBA(0, 0, 0, 128), nvgRGBA(0, 0, 0, 0)));
	nvgFill(gVg);

	// Background
	Tt_Rect buttonRect = Tt_Rect_Translate(&rect, 0, btn->clickAnimT * SHADOW_SIZE);
	nvgBeginPath(gVg);
	nvgFillColor(gVg, BACKGROUND_COLOR);
	nvgRoundedRect(gVg, buttonRect.x, buttonRect.y, buttonRect.w, buttonRect.h, CORNER_RADIUS);
	nvgFill(gVg);

	// Label
	nvgFontFaceId(gVg, gFontAttackOfMonster);
	nvgFontSize(gVg, buttonRect.h * 0.3f);
	nvgFillColor(gVg, FOREGROUND_COLOR);
	nvgTextAlign(gVg, NVG_ALIGN_CENTER|NVG_ALIGN_MIDDLE);
	nvgText2(gVg, buttonRect.x + buttonRect.w * 0.5f, buttonRect.y + buttonRect.h * 0.53f, &btn->text[0], NULL);

	// Shadow over the button (less transparent if not hovered)
	nvgFillColor(gVg, nvgRGBA(0,0,0, Tt_Mouse_Is_Over_Rect(&rect) ? 10 : 40));
	nvgFill(gVg);
}
