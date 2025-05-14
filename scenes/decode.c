// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <trucotricks/animated_sprite.h>
#include <trucotricks/button.h>
#include <trucotricks/card.h>
#include <trucotricks/card_button.h>
#include <trucotricks/deck.h>
#include <trucotricks/gameover.h>
#include <trucotricks/keyboard.h>
#include <trucotricks/label.h>
#include <trucotricks/parallax.h>
#include <trucotricks/rank.h>
#include <trucotricks/resources.h>
#include <trucotricks/scene.h>
#include <trucotricks/score_info.h>
#include <trucotricks/sound.h>
#include <trucotricks/suit.h>
#include <trucotricks/util.h>
#include <trucotricks/window.h>

#define MARGIN_CARD_BUTTON 20
#define MARGIN_CARD_ENCODED_BUTTON 30
#define SCORE_LABEL_CAPACITY 32

static bool showHints;
static Tt_Score_Info scoreInfo;
static Tt_Label scoreLabel;
static Tt_Animated_Sprite coinSprite;
static Tt_Label hintLabels[RANK_COUNT+SUIT_COUNT+1/*separator*/];
static Tt_Parallax backgroundParallax;
static Tt_Card_Button cardButtons[3];
static Tt_Button cardEncodedButton;
static Tt_Deck deck;

static void newRound(void)
{
	deck = Tt_Deck_Shuffled();

	for (size_t i = 0; i < Tt_Length(cardButtons); ++i)
		cardButtons[i].card = Tt_Deck_Draw(&deck, 0);

	Tt_Card_Encode(&cardButtons[rand() % Tt_Length(cardButtons)].card,
			sizeof(cardEncodedButton.text), &cardEncodedButton.text[0]);
}

static void cardButtonClicked(Tt_Card_Button *sender)
{
	Tt_Card correctCard = Tt_Card_Decode(&cardEncodedButton.text[0]);

	if (Tt_Card_Equals(&sender->card, &correctCard)) {
		newRound();
		Tt_Sound_Play(gSoundSwipe);
		Tt_Score_Info_Increase_Score(&scoreInfo);
		snprintf(&scoreLabel.text[0], SCORE_LABEL_CAPACITY, "%d", scoreInfo.score);
	} else {
		Tt_Game_Over(scoreInfo, false);
	}
}

static void awake(void)
{
	coinSprite.x = 30;
	coinSprite.y = 30;
	coinSprite.w = 70;
	coinSprite.h = 70;
	coinSprite.nTiles = 8;
	coinSprite.tileSet = gTexGoldCoin;

	scoreLabel.h = 30;
	scoreLabel.fontSize = 30;
	scoreLabel.align = ALIGN_LEFT | ALIGN_MIDDLE;
	scoreLabel.font = gFontAttackOfMonster;
	scoreLabel.text = malloc(SCORE_LABEL_CAPACITY);
	scoreLabel.hasShadow = true;
	scoreLabel.shadowColor = 0x000000;
	scoreLabel.color = 0xffff00;
	scoreLabel.x = coinSprite.x + coinSprite.w + 8;
	scoreLabel.y = coinSprite.y + coinSprite.h * 0.5f - 7;

	static const char *hints[] = { "Oro - O", "Copa - A", "Espada - I", "Basto - E", "",
		"1 - T", "2 - B", "3 - K", "4 - D", "5 - P", "6 - CH",
		"7 - S", "10 - M", "11 - N", "12 - L" };

	for (size_t i = 0; i < Tt_Length(hintLabels); ++i) {
		hintLabels[i].h = 20;
		hintLabels[i].color = 0x7fffffff;
		hintLabels[i].hasShadow = false;
		hintLabels[i].shadowColor = 0x000000;
		hintLabels[i].font = gFontTerminus;
		hintLabels[i].fontSize = 20;
		hintLabels[i].align = ALIGN_TOP|ALIGN_LEFT;
		hintLabels[i].text = (char *)hints[i];
	}

	backgroundParallax.x = 0;
	backgroundParallax.y = 0;

	backgroundParallax.nTextures = Tt_Length(gTexBackgroundParallax);
	memcpy(&backgroundParallax.textures[0], &gTexBackgroundParallax[0],
			sizeof(Tt_Texture) * backgroundParallax.nTextures);

	cardEncodedButton.w = 100;
	cardEncodedButton.h = 100;

	for (size_t i = 0; i < Tt_Length(cardButtons); ++i) {
		cardButtons[i].w = 177;
		cardButtons[i].h = 264;
		cardButtons[i].onClick = cardButtonClicked;
	}
}

static void layoutChange(void)
{
	float hintsHeight = hintLabels[0].h * Tt_Length(hintLabels);

	float hintsY = (gWindowHeight - hintsHeight) * 0.5f;

	for (size_t i = 0; i < Tt_Length(hintLabels); ++i) {
		hintLabels[i].x = 45;
		hintLabels[i].y  = hintsY;
		hintsY += hintLabels[i].h;
	}

	backgroundParallax.w = gWindowWidth;
	backgroundParallax.h = gWindowHeight;

	float heightUsed = cardEncodedButton.h + MARGIN_CARD_ENCODED_BUTTON + MARGIN_CARD_BUTTON + cardButtons[0].h;

	float y = (gWindowHeight - heightUsed) * 0.5f;

	cardEncodedButton.y = y;
	cardEncodedButton.x = (gWindowWidth - cardEncodedButton.w) * 0.5f;

	y += cardEncodedButton.h + MARGIN_CARD_ENCODED_BUTTON + MARGIN_CARD_BUTTON;

	float cardButtonsX = (gWindowWidth - cardButtons[0].w * Tt_Length(cardButtons) -
			MARGIN_CARD_BUTTON * (Tt_Length(cardButtons) - 1)) * 0.5f;

	for (size_t i = 0; i < Tt_Length(cardButtons); ++i) {
		cardButtons[i].y = y;
		cardButtons[i].x = cardButtonsX;
		cardButtonsX += cardButtons[0].w + MARGIN_CARD_BUTTON;
	}
}

static void enter(void)
{
	Tt_Score_Info_Reset(&scoreInfo);
	newRound();
}

static void update(double dt)
{
	Tt_Score_Info_Increase_Time(&scoreInfo, dt);

	Tt_Parallax_Update(&backgroundParallax);

	if (scoreInfo.score > 0) {
		Tt_Animated_Sprite_Update(&coinSprite);
		Tt_Label_Update(&scoreLabel);
	}

	for (size_t i = 0; showHints && i < Tt_Length(hintLabels); ++i)
		Tt_Label_Update(&hintLabels[i]);

	Tt_Button_Update(&cardEncodedButton);

	for (size_t i = 0; i < Tt_Length(cardButtons); ++i)
		Tt_Card_Button_Update(&cardButtons[i]);
}

static void keyPress(enum Tt_Key key, enum Tt_Mod mods)
{
	switch (key) {
	case KEY_1:
		Tt_Scene_Switch(SCENE_GAMEMODE_ENCODE);
		break;
	case KEY_3:
		Tt_Scene_Switch(SCENE_GAMEMODE_MEMORIZE);
		break;
	case KEY_4:
		Tt_Scene_Switch(SCENE_GAMEMODE_SPEED);
		break;
	case KEY_F1:
		showHints = !showHints;
		break;
	case KEY_F5:
		Tt_Scene_Switch(SCENE_GAMEMODE_DECODE);
		break;
	default: break;
	}
}

Tt_Scene Tt_Get_Gamemode_Decode_Scene(void)
{
	return (Tt_Scene) {
		.name           = "gamemode: decode",
		.cbAwake        = awake,
		.cbEnter        = enter,
		.cbUpdate       = update,
		.cbLeave        = NULL,
		.cbKeyPress     = keyPress,
		.cbKeyRelease   = NULL,
		.cbTextInput    = NULL,
		.cbLayoutChange = layoutChange
	};
}
