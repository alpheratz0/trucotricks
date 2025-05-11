// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_CARD_H
#define TRUCOTRICKS_CARD_H

#include <stdbool.h>
#include <trucotricks/suit.h>
#include <trucotricks/rank.h>
#include <trucotricks/resources.h>

typedef struct Tt_Card Tt_Card;

struct Tt_Card {
	enum Tt_Suit suit;
	enum Tt_Rank rank;
};

Tt_Card Tt_Card_Init(enum Tt_Suit suit, enum Tt_Rank rank);

void Tt_Card_Set(Tt_Card *card, enum Tt_Suit suit, enum Tt_Rank rank);

void Tt_Card_Print(const Tt_Card *card);

Tt_Texture Tt_Card_Get_Texture(const Tt_Card *card);

void Tt_Card_Encode(const Tt_Card *card, size_t outCap, char *out);

Tt_Card Tt_Card_Decode(const char *s);

bool Tt_Card_Equals(const Tt_Card *card, const Tt_Card *other);

#endif
