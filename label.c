// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <stddef.h>
#include <nanovg.h>
#include <stddef.h>
#include <stdint.h>
#include <trucotricks/label.h>
#include <trucotricks/util.h>
#include <trucotricks/window.h>

static inline NVGcolor __Tt_NVGcolor_From(uint32_t color)
{
	if (color <= 0xffffff)
		return nvgRGB((color>>16)&0xff, (color>>8)&0xff, color&0xff);
	return nvgRGBA((color>>16)&0xff, (color>>8)&0xff, color&0xff, (color>>24)&0xff);
}

void Tt_Label_Update(Tt_Label *label)
{
	nvgFontFaceId(gVg, label->font);
	nvgFontSize(gVg, label->fontSize);
	nvgTextAlign(gVg, label->align);

	if (label->hasShadow) {
		nvgFillColor(gVg, __Tt_NVGcolor_From(label->shadowColor));
		nvgText2(gVg, label->x, label->y+2, label->text, NULL);
	}

	nvgFillColor(gVg, __Tt_NVGcolor_From(label->color));
	nvgText2(gVg, label->x, label->y, label->text, NULL);
}
