// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <trucotricks/card.h>
#include <trucotricks/deck.h>
#include <trucotricks/rank.h>
#include <trucotricks/suit.h>
#include <trucotricks/util.h>

static enum Tt_Suit __Tt_Suit_By_Card_Index(int i)
{
	switch (i / RANK_COUNT) {
	case 0: return SUIT_ESPADA;
	case 1: return SUIT_ORO;
	case 2: return SUIT_BASTO;
	case 3: return SUIT_COPA;
	default: assert(false && "Should not happen");
	}
}

Tt_Deck Tt_Deck_Init(void)
{
	Tt_Deck ret = {0};

	for (int i = 0; i < Tt_Length(ret.drawPile); ++i)
		Tt_Card_Set(&ret.drawPile[i],
				__Tt_Suit_By_Card_Index(i), i % RANK_COUNT);

	return ret;
}

Tt_Deck Tt_Deck_Shuffled(void)
{
	Tt_Deck orderedDeck = Tt_Deck_Init();
	Tt_Deck deck = {0};

	for (size_t i = 0; i < Tt_Length(deck.drawPile); ++i)
		deck.drawPile[i] = Tt_Deck_Draw(&orderedDeck,
				rand() % (Tt_Length(deck.drawPile) - i));

	return deck;
}

Tt_Card Tt_Deck_Draw(Tt_Deck *deck, int at)
{
	assert(at < Tt_Length(deck->drawPile) - deck->drawPosition &&
			"Drawing card outside bounds");

	if (at > 0)
		Tt_Swap(Tt_Card, deck->drawPile[deck->drawPosition],
				deck->drawPile[deck->drawPosition + at]);

	return deck->drawPile[deck->drawPosition++];
}
