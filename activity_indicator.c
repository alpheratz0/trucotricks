// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <math.h>
#include <trucotricks/time.h>
#include <trucotricks/window.h>
#include <trucotricks/activity_indicator.h>
#include <nanovg.h>

void Tt_Activity_Indicator_Update(Tt_Activity_Indicator *activityIndicator)
{
	static float t;
	t += gDeltaTime * 0.5f;
	float r = 20.0f;
	float a0 = 0.0f + t*6;
	float a1 = NVG_PI + t*6;
	float r0 = r;
	float r1 = r * 0.75f;
	float ax,ay, bx,by;
	NVGpaint paint;

	nvgSave(gVg);

	nvgBeginPath(gVg);
	nvgArc(gVg, activityIndicator->x,activityIndicator->y, r0, a0, a1, NVG_CW);
	nvgArc(gVg, activityIndicator->x,activityIndicator->y, r1, a1, a0, NVG_CCW);
	nvgClosePath(gVg);
	ax = activityIndicator->x + cosf(a0) * (r0+r1)*0.5f;
	ay = activityIndicator->y + sinf(a0) * (r0+r1)*0.5f;
	bx = activityIndicator->x + cosf(a1) * (r0+r1)*0.5f;
	by = activityIndicator->y + sinf(a1) * (r0+r1)*0.5f;
	paint = nvgLinearGradient(gVg, ax,ay, bx,by, nvgRGBA(0xff,0xff,0xff,0), nvgRGBA(0xff,0xff,0xff,228));
	nvgFillPaint(gVg, paint);
	nvgFill(gVg);

	nvgRestore(gVg);
}
