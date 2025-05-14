// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <trucotricks/card.h>
#include <trucotricks/rank.h>
#include <trucotricks/resources.h>
#include <trucotricks/suit.h>

static const char *encodeSuitLUT[] = {"O","A","I","E" };
static const char *encodeRankLUT[] = {"T","B","K","D","P","CH","S","M","N","L"};

Tt_Card Tt_Card_Init(enum Tt_Suit suit, enum Tt_Rank rank)
{
	Tt_Card card = {0};
	card.suit = suit;
	card.rank = rank;
	return card;
}

void Tt_Card_Set(Tt_Card *card, enum Tt_Suit suit, enum Tt_Rank rank)
{
	card->suit = suit;
	card->rank = rank;
}

void Tt_Card_Print(const Tt_Card *card)
{
	assert((card->rank >= 0 && card->rank < RANK_COUNT) && "Invalid rank");
	assert((card->suit >= 0 && card->suit < SUIT_COUNT) && "Invalid suit");

	printf("%s de %s\n",
			Tt_Rank_To_String(card->rank),
			Tt_Suit_To_String(card->suit));
}

Tt_Texture Tt_Card_Get_Texture(const Tt_Card *card)
{
	if (card->rank < 0 || card->rank >= RANK_COUNT ||
			card->suit < 0 || card->suit >= SUIT_COUNT)
		return gTexUnknownCard;

	switch (card->suit) {
	case SUIT_BASTO: return gTexBasto[card->rank];
	case SUIT_ESPADA: return gTexEspada[card->rank];
	case SUIT_ORO: return gTexOro[card->rank];
	case SUIT_COPA: return gTexCopa[card->rank];
	default: return TEXTURE_INVALID;
	}
}

void Tt_Card_Encode(const Tt_Card *card, size_t outCap, char *out)
{
	assert((card->rank >= 0 && card->rank < RANK_COUNT) && "Invalid rank");
	assert((card->suit >= 0 && card->suit < SUIT_COUNT) && "Invalid suit");
	snprintf(&out[0], outCap, "%s%s", encodeRankLUT[card->rank], encodeSuitLUT[card->suit]);
}

Tt_Card Tt_Card_Decode(const char *s)
{
	enum Tt_Rank rank = RANK_INVALID;
	enum Tt_Suit suit = SUIT_INVALID;
	const char *walk = s;

	switch (*walk) {
	case 'T': rank = RANK_UNO; break;
	case 'B': rank = RANK_DOS; break;
	case 'K': rank = RANK_TRES; break;
	case 'D': rank = RANK_CUATRO; break;
	case 'P': rank = RANK_CINCO; break;
	case 'C': if (walk[1] == 'H') { rank = RANK_SEIS; walk += 1; } break;
	case 'S': rank = RANK_SIETE; break;
	case 'M': rank = RANK_DIEZ; break;
	case 'N': rank = RANK_ONCE; break;
	case 'L': rank = RANK_DOCE; break;
	}

	walk += 1;

	if (rank != RANK_INVALID) {
		switch (*walk) {
		case 'O': suit = SUIT_ORO; break;
		case 'A': suit = SUIT_COPA; break;
		case 'I': suit = SUIT_ESPADA; break;
		case 'E': suit = SUIT_BASTO; break;
		}
	}

	return Tt_Card_Init(suit, rank);
}

bool Tt_Card_Equals(const Tt_Card *card, const Tt_Card *other)
{
	if (card == other)
		return true;
	if (NULL == card || NULL == other)
		return false;
	return card->suit == other->suit && card->rank == other->rank;
}
