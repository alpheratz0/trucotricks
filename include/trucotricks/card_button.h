// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_CARD_BUTTON_H
#define TRUCOTRICKS_CARD_BUTTON_H

#include <trucotricks/card.h>
#include <stdbool.h>

typedef struct Tt_Card_Button Tt_Card_Button;

// Event handlers defs
typedef void (*Tt_Card_Button_Click_Event_Handler)(Tt_Card_Button *sender);

struct Tt_Card_Button {
	// Card button position & size
	float x, y, w, h;
	// For hover animation
	float clickAnimT;
	// Card
	Tt_Card card;
	// Event handlers
	Tt_Card_Button_Click_Event_Handler onClick;
};

void Tt_Card_Button_Update(Tt_Card_Button *card);

#endif
