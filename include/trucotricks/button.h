// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_BUTTON_H
#define TRUCOTRICKS_BUTTON_H

#include <stdbool.h>

typedef struct Tt_Button Tt_Button;

// Event handlers defs
typedef void (*Tt_Button_Click_Event_Handler)(Tt_Button *sender);

struct Tt_Button {
	// Button position & size
	float x, y, w, h;
	char text[20];
	// For hover animation
	float clickAnimT;
	// Event handlers
	Tt_Button_Click_Event_Handler onClick;
};

void Tt_Button_Update(Tt_Button *btn);

#endif
