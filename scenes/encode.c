// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <trucotricks/animated_sprite.h>
#include <trucotricks/button.h>
#include <trucotricks/card.h>
#include <trucotricks/card_button.h>
#include <trucotricks/deck.h>
#include <trucotricks/keyboard.h>
#include <trucotricks/label.h>
#include <trucotricks/parallax.h>
#include <trucotricks/rank.h>
#include <trucotricks/resources.h>
#include <trucotricks/scene.h>
#include <trucotricks/score_info.h>
#include <trucotricks/sound.h>
#include <trucotricks/string_builder.h>
#include <trucotricks/suit.h>
#include <trucotricks/util.h>
#include <trucotricks/window.h>
#include <trucotricks/gameover.h>

#define MARGIN_CARD_BUTTON 20
#define MARGIN_CARD_ENCODED_BUTTON 30
#define MARGIN_CUSTOM_GUESS_LABEL 20
#define SCORE_LABEL_CAPACITY 32

static bool autoAcceptGuess = true;
static bool showHints;
static Tt_Score_Info scoreInfo;
static Tt_Label customGuessLabel;
static Tt_Label scoreLabel;
static Tt_Animated_Sprite coinSprite;
static Tt_Label hintLabels[RANK_COUNT+SUIT_COUNT+1/*separator*/];
static Tt_String_Builder customGuess;
static Tt_Parallax backgroundParallax;
static Tt_Card_Button cardButton;
static Tt_Button cardEncodedButtons[3];
static Tt_Deck deck;

static void newRound(void)
{
	Tt_Card cardOptions[Tt_Length(cardEncodedButtons)];

	deck = Tt_Deck_Shuffled();

	for (size_t i = 0; i < Tt_Length(cardOptions); ++i) {
		cardOptions[i] = Tt_Deck_Draw(&deck, 0);

		Tt_Card_Encode(&cardOptions[i], sizeof(cardEncodedButtons[i].text),
				&cardEncodedButtons[i].text[0]);
	}

	cardButton.card = cardOptions[rand() % Tt_Length(cardOptions)];

	Tt_String_Builder_Clear(&customGuess);
}

static void submitGuess(const char *guess)
{
	Tt_Card guessCard = Tt_Card_Decode(guess);

	if (Tt_Card_Equals(&guessCard, &cardButton.card)) {
		newRound();
		Tt_Sound_Play(gSoundSwipe);
		Tt_Score_Info_Increase_Score(&scoreInfo);
		snprintf(&scoreLabel.text[0], SCORE_LABEL_CAPACITY, "%d", scoreInfo.score);
	} else {
		Tt_Game_Over(scoreInfo, false);
	}
}

static void cardEncodedButtonClicked(Tt_Button *sender)
{
	submitGuess(&sender->text[0]);
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

	customGuess.maxSize = 3;

	customGuessLabel.h = 30;
	customGuessLabel.text = &customGuess.data[0];
	customGuessLabel.color = 0xffffff;
	customGuessLabel.hasShadow = true;
	customGuessLabel.shadowColor = 0x000000;
	customGuessLabel.font = gFontAttackOfMonster;
	customGuessLabel.fontSize = 20;
	customGuessLabel.align = ALIGN_TOP|ALIGN_CENTER;

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

	cardButton.w = 177;
	cardButton.h = 264;

	for (size_t i = 0; i < Tt_Length(cardEncodedButtons); ++i) {
		cardEncodedButtons[i].w = 100;
		cardEncodedButtons[i].h = 100;
		cardEncodedButtons[i].onClick = cardEncodedButtonClicked;
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

	customGuessLabel.x = gWindowWidth * 0.5f;

	backgroundParallax.w = gWindowWidth;
	backgroundParallax.h = gWindowHeight;

	float heightUsed = customGuessLabel.h + MARGIN_CUSTOM_GUESS_LABEL + MARGIN_CARD_BUTTON + cardButton.h + MARGIN_CARD_BUTTON + MARGIN_CARD_ENCODED_BUTTON + cardEncodedButtons[0].h;

	float y = (gWindowHeight - heightUsed) * 0.5f;

	customGuessLabel.y = y;

	y += customGuessLabel.h + MARGIN_CUSTOM_GUESS_LABEL + MARGIN_CARD_BUTTON;

	cardButton.y = y;
	cardButton.x = (gWindowWidth - cardButton.w) * 0.5f;

	y += cardButton.h + MARGIN_CARD_BUTTON + MARGIN_CARD_ENCODED_BUTTON;

	float cardEncodedButtonX = (gWindowWidth - cardEncodedButtons[0].w * Tt_Length(cardEncodedButtons) -
			MARGIN_CARD_ENCODED_BUTTON * (Tt_Length(cardEncodedButtons) - 1)) * 0.5f;

	for (size_t i = 0; i < Tt_Length(cardEncodedButtons); ++i) {
		cardEncodedButtons[i].y = y;
		cardEncodedButtons[i].x = cardEncodedButtonX;
		cardEncodedButtonX += cardEncodedButtons[0].w + MARGIN_CARD_ENCODED_BUTTON;
	}
}

static void enter(void)
{
	Tt_String_Builder_Clear(&customGuess);
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

	Tt_Label_Update(&customGuessLabel);

	for (size_t i = 0; showHints && i < Tt_Length(hintLabels); ++i)
		Tt_Label_Update(&hintLabels[i]);

	for (size_t i = 0; i < Tt_Length(cardEncodedButtons); ++i)
		Tt_Button_Update(&cardEncodedButtons[i]);

	Tt_Card_Button_Update(&cardButton);
}

static void keyPress(enum Tt_Key key, enum Tt_Mod mods)
{
	switch (key) {
	case KEY_1:
		Tt_Scene_Switch(SCENE_GAMEMODE_SPEED);
		break;
	case KEY_2:
		Tt_Scene_Switch(SCENE_GAMEMODE_DECODE);
		break;
	case KEY_4:
		Tt_Scene_Switch(SCENE_GAMEMODE_MEMORIZE);
		break;
	case KEY_F1:
		showHints = !showHints;
		break;
	case KEY_F5:
		Tt_Scene_Switch(SCENE_GAMEMODE_ENCODE);
		break;
	case KEY_A...KEY_Z:
		Tt_String_Builder_Append(&customGuess, 'A' + (key - KEY_A));
		if (autoAcceptGuess && (customGuess.len == (customGuess.data[0] == 'C' ? 3 : 2)))
			submitGuess(&customGuess.data[0]);
		break;
	case KEY_BACKSPACE:
		Tt_String_Builder_Remove_Last_Character(&customGuess);
		break;
	case KEY_SPACE:
	case KEY_ENTER:
		if (customGuess.len != 0)
			submitGuess(&customGuess.data[0]);
		break;
	default: break;
	}

}

Tt_Scene Tt_Get_Gamemode_Encode_Scene(void)
{
	return (Tt_Scene) {
		.name           = "gamemode: encode",
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
