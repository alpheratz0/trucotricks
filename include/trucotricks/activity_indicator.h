// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_ACTIVITY_INDICATOR_H
#define TRUCOTRICKS_ACTIVITY_INDICATOR_H

typedef struct Tt_Activity_Indicator Tt_Activity_Indicator;

struct Tt_Activity_Indicator {
	float x, y;
};

void Tt_Activity_Indicator_Update(Tt_Activity_Indicator *activityIndicator);

#endif
