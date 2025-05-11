// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_APP_ICON_H
#define TRUCOTRICKS_APP_ICON_H

#include <stdint.h>

typedef struct Tt_Icon Tt_Icon;

struct Tt_Icon {
	int width;
	int height;
	uint8_t *pixels;
};

Tt_Icon *Tt_Get_App_Icon(void);

#endif
