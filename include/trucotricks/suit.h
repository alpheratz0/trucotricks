// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_SUIT_H
#define TRUCOTRICKS_SUIT_H

#define Tt_Suit_To_String(suit) \
	suit == SUIT_ORO ? "oro" : \
		suit == SUIT_COPA ? "copa" : \
			suit == SUIT_ESPADA ? "espada" : \
				"basto"

enum Tt_Suit {
	SUIT_ORO,
	SUIT_COPA,
	SUIT_ESPADA,
	SUIT_BASTO,
	SUIT_COUNT,
	SUIT_INVALID
};

#endif
