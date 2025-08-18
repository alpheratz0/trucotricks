// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_GALLERY_SWITCHER_H
#define TRUCOTRICKS_GALLERY_SWITCHER_H

#include <stdbool.h>

typedef struct Tt_Gallery_Switcher Tt_Gallery_Switcher;

// Event handlers defs
typedef void (*Tt_Gallery_Switcher_Event_Handler)(Tt_Gallery_Switcher *sender, int index);

struct Tt_Gallery_Switcher {
	// Gallery switcher position & size
	float x, y, w, h;
	int buttonCount;
	const char *buttonTooltips[16];
	float hoverTime;
	int selectedIndex;
	// Event handlers
	Tt_Gallery_Switcher_Event_Handler onClick;
};

void Tt_Gallery_Switcher_Update(Tt_Gallery_Switcher *gs);

#endif
