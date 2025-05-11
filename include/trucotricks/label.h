// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_LABEL_H
#define TRUCOTRICKS_LABEL_H

#include <stdbool.h>
#include <stdint.h>
#include <trucotricks/resources.h>

typedef struct Tt_Label Tt_Label;

enum Tt_Align {
	ALIGN_LEFT = 1<<0,
	ALIGN_CENTER = 1<<1,
	ALIGN_RIGHT = 1<<2,
	ALIGN_TOP = 1<<3,
	ALIGN_MIDDLE = 1<<4,
	ALIGN_BOTTOM = 1<<5,
	ALIGN_BASELINE = 1<<6,
};

struct Tt_Label {
	// Button position & size
	float x, y, h;
	char *text;
	uint32_t color;
	bool hasShadow;
	uint32_t shadowColor;
	Tt_Font font;
	float fontSize;
	enum Tt_Align align;
};

void Tt_Label_Update(Tt_Label *label);

#endif
