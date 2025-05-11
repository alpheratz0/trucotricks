// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_RECT_H
#define TRUCOTRICKS_RECT_H

#include <stdbool.h>

typedef struct Tt_Rect Tt_Rect;

struct Tt_Rect {
	float x, y, w, h;
};

Tt_Rect Tt_Rect_From_All_Points(float x1, float y1, float x2, float y2);
Tt_Rect Tt_Rect_From_Width_And_Height(float x, float y, float w, float h);
Tt_Rect Tt_Rect_Translate(const Tt_Rect *rect, float x, float y);
Tt_Rect Tt_Rect_Grow(const Tt_Rect *rect, float x, float y);
bool Tt_Rect_Intersects(const Tt_Rect *rect1, const Tt_Rect *rect2);
bool Tt_Rect_Contains_Point(const Tt_Rect *rect, float x, float y);

#endif
