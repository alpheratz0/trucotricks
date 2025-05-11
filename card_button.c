// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <nanovg.h>
#include <trucotricks/card.h>
#include <trucotricks/card_button.h>
#include <trucotricks/cursor.h>
#include <trucotricks/mouse.h>
#include <trucotricks/rect.h>
#include <trucotricks/resources.h>
#include <trucotricks/time.h>
#include <trucotricks/util.h>
#include <trucotricks/window.h>

#define SHADOW_SIZE (5.0f)
#define CLICK_ANIMATION_SPEED (8.0f)
#define NORMAL_CORNER_RADIUS (25.0f)

void Tt_Card_Button_Update(Tt_Card_Button *cardButton)
{
	Tt_Texture texture = Tt_Card_Get_Texture(&cardButton->card);
	float ratio = cardButton->w / 354.0f;
	int deltaX = ratio * 15;
	int deltaY = ratio * 10;
	Tt_Rect rect = Tt_Rect_From_Width_And_Height(cardButton->x, cardButton->y, cardButton->w, cardButton->h);

	if (Tt_Mouse_Is_Over_Rect(&rect)) {
		Tt_Cursor_Request(CURSOR_SHAPE_HAND);
		if (Tt_Mouse_Is_Button_Pressed(MOUSE_BUTTON_LEFT)) {
			cardButton->clickAnimT += CLICK_ANIMATION_SPEED * gDeltaTime;
		} else if (Tt_Mouse_Is_Button_Just_Released(MOUSE_BUTTON_LEFT)) {
			if (cardButton->onClick)
				cardButton->onClick(cardButton);
		} else {
			cardButton->clickAnimT -= CLICK_ANIMATION_SPEED * gDeltaTime;
		}
	} else {
		cardButton->clickAnimT -= CLICK_ANIMATION_SPEED * gDeltaTime;
	}

	cardButton->clickAnimT = Tt_Clamp(cardButton->clickAnimT, 0.0f, 1.0f);

	// Solid shadow at the bottom
	Tt_Rect bottomShadowRect = Tt_Rect_Translate(&rect, 0, SHADOW_SIZE);
	nvgBeginPath(gVg);
	nvgRoundedRect(gVg, bottomShadowRect.x, bottomShadowRect.y, bottomShadowRect.w, bottomShadowRect.h, NORMAL_CORNER_RADIUS * ratio);
	nvgFillPaint(gVg, nvgBoxGradient(gVg, bottomShadowRect.x, bottomShadowRect.y, bottomShadowRect.w, bottomShadowRect.h,
				NORMAL_CORNER_RADIUS * ratio, 2, nvgRGBA(0, 0, 0, 128), nvgRGBA(0, 0, 0, 0)));
	nvgFill(gVg);

	// Card
	Tt_Rect buttonRect = Tt_Rect_Translate(&rect, 0, cardButton->clickAnimT * SHADOW_SIZE);
	nvgBeginPath(gVg);
	nvgRoundedRect(gVg, buttonRect.x, buttonRect.y, buttonRect.w, buttonRect.h, NORMAL_CORNER_RADIUS * ratio);
	Tt_Rect cardPaintRect = Tt_Rect_Grow(&buttonRect, deltaX, deltaY);
	nvgFillPaint(gVg, nvgImagePattern(gVg, cardPaintRect.x, cardPaintRect.y, cardPaintRect.w, cardPaintRect.h, 0.0, texture, 1.0));
	nvgFill(gVg);

	// Shadow over the button (less transparent if not hovered)
	nvgFillColor(gVg, nvgRGBA(0, 0, 0, Tt_Mouse_Is_Over_Rect(&rect) ? 10 : 40));
	nvgFill(gVg);
}
