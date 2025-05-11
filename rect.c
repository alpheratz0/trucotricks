// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <trucotricks/util.h>
#include <trucotricks/rect.h>
#include <stdbool.h>

Tt_Rect Tt_Rect_From_All_Points(float x1, float y1, float x2, float y2)
{
	Tt_Rect rect;

	rect.x = Tt_Min(x1, x2);
	rect.y = Tt_Min(y1, y2);
	rect.w = Tt_Max(x1, x2) - rect.x;
	rect.h = Tt_Max(y1, y2) - rect.y;

	return rect;
}

Tt_Rect Tt_Rect_From_Width_And_Height(float x, float y, float w, float h)
{
	return Tt_Rect_From_All_Points(x, y, x + w, y + h);
}

Tt_Rect Tt_Rect_Translate(const Tt_Rect *rect, float x, float y)
{
	return Tt_Rect_From_Width_And_Height(rect->x + x, rect->y + y, rect->w, rect->h);
}

Tt_Rect Tt_Rect_Grow(const Tt_Rect *rect, float w, float h)
{
	return Tt_Rect_From_Width_And_Height(rect->x - w, rect->y - h, rect->w + w * 2, rect->h + h * 2);
}

bool Tt_Rect_Intersects(const Tt_Rect *r1, const Tt_Rect *r2)
{
	if (r1->x + r1->w <= r2->x || r2->x + r2->w <= r1->x) return false;
	if (r1->y + r1->h <= r2->y || r2->y + r2->h <= r1->y) return false;
	return true;
}

bool Tt_Rect_Contains_Point(const Tt_Rect *rect, float x, float y)
{
	if (x <= rect->x) return false;
	if (x >= rect->x + rect->w) return false;
	if (y <= rect->y) return false;
	if (y >= rect->y + rect->h) return false;
	return true;
}
