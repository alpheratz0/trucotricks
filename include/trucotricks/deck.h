// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_DECK_H
#define TRUCOTRICKS_DECK_H

#include <trucotricks/suit.h>
#include <trucotricks/rank.h>
#include <trucotricks/card.h>

#define CARDS_PER_DECK (SUIT_COUNT * RANK_COUNT)

typedef struct Tt_Deck Tt_Deck;

struct Tt_Deck {
	Tt_Card drawPile[CARDS_PER_DECK];
	int drawPosition;
};

// Initializes a deck object
Tt_Deck Tt_Deck_Init(void);

// Initializes a deck object
Tt_Card Tt_Deck_Draw(Tt_Deck *deck, int at);

// Shuffles the deck
Tt_Deck Tt_Deck_Shuffled(void);

#endif
