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
#include <trucotricks/resources.h>
#include <trucotricks/scene.h>
#include <trucotricks/score_info.h>
#include <trucotricks/sound.h>
#include <trucotricks/string_builder.h>
#include <trucotricks/util.h>
#include <trucotricks/window.h>

#define MARGIN_CARD_BUTTON 50
#define MARGIN_CARD_ENCODED_BUTTON 30
#define MARGIN_CUSTOM_GUESS_LABEL 20
#define SCORE_LABEL_CAPACITY 32
#define MAX_NUMBER_OF_CARDS_TO_MEMORIZE 24
#define MIN_NUMBER_OF_CARDS_TO_MEMORIZE 5

static int askingDirection;
static bool isMemorizing;
static bool autoAcceptGuess = true;
static int numberOfCardsToMemorize = 6;
static Tt_Score_Info scoreInfo;
static Tt_Label customGuessLabel;
static Tt_Label scoreLabel;
static Tt_Label memorizingGuides[2];
static Tt_Label questionLabel;
static Tt_Animated_Sprite coinSprite;
static Tt_String_Builder customGuess;
static Tt_Parallax backgroundParallax;
static int anchorCardIndex;
static Tt_Card_Button anchorCardButton;
static Tt_Button cardsToMemorizeButtons[MAX_NUMBER_OF_CARDS_TO_MEMORIZE];
static Tt_Deck deck;

static void newMemorizingRound(void)
{
	deck = Tt_Deck_Shuffled();

	for (size_t i = 0; i < Tt_Length(cardsToMemorizeButtons); ++i) {
		Tt_Card card = Tt_Deck_Draw(&deck, 0);
		Tt_Card_Encode(&card, sizeof(cardsToMemorizeButtons[i].text),
				&cardsToMemorizeButtons[i].text[0]);
	}
}

static void newRound(void)
{
	int oldAnchorCardIndex = anchorCardIndex;

	anchorCardIndex = rand() % numberOfCardsToMemorize;

	if (scoreInfo.score != 0)
		while (oldAnchorCardIndex == anchorCardIndex)
			anchorCardIndex = rand() % numberOfCardsToMemorize;

	isMemorizing = false;

	askingDirection = anchorCardIndex == 0 ? 1 :
		(anchorCardIndex == numberOfCardsToMemorize - 1) ? -1 :
			(rand() % 3 == 0) ? 1 : -1; // more probability for asking the left card

	anchorCardButton.card = Tt_Card_Decode(cardsToMemorizeButtons[anchorCardIndex].text);

	questionLabel.text = askingDirection == -1 ? "Which card was to the left?" : "Which card was to the right?";

	Tt_String_Builder_Clear(&customGuess);
}

static void submitGuess(const char *guess)
{
	Tt_Card guessCard = Tt_Card_Decode(guess);
	Tt_Card correctCard = Tt_Card_Decode(&cardsToMemorizeButtons[anchorCardIndex+askingDirection].text[0]);

	if (Tt_Card_Equals(&guessCard, &correctCard)) {
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

	customGuess.maxSize = 3;

	customGuessLabel.h = 30;
	customGuessLabel.text = &customGuess.data[0];
	customGuessLabel.color = 0xffffff;
	customGuessLabel.hasShadow = true;
	customGuessLabel.shadowColor = 0x000000;
	customGuessLabel.font = gFontAttackOfMonster;
	customGuessLabel.fontSize = 20;
	customGuessLabel.align = ALIGN_TOP|ALIGN_CENTER;

	memorizingGuides[0].text = "Press +/- to increase/decrease the cards you have to memorize";
	memorizingGuides[1].text = "Press space when you are done memorizing...";

	for (size_t i = 0; i < Tt_Length(memorizingGuides); ++i) {
		memorizingGuides[i].h = 30;
		memorizingGuides[i].color = 0xffffff;
		memorizingGuides[i].hasShadow = true;
		memorizingGuides[i].shadowColor = 0x000000;
		memorizingGuides[i].font = gFontAttackOfMonster;
		memorizingGuides[i].fontSize = 15;
		memorizingGuides[i].align = ALIGN_TOP|ALIGN_CENTER;
	}

	questionLabel.h = 20;
	questionLabel.color = 0xcccccc;
	questionLabel.hasShadow = true;
	questionLabel.shadowColor = 0x000000;
	questionLabel.font = gFontAttackOfMonster;
	questionLabel.fontSize = 20;
	questionLabel.align = ALIGN_TOP|ALIGN_CENTER;

	backgroundParallax.x = 0;
	backgroundParallax.y = 0;

	backgroundParallax.nTextures = Tt_Length(gTexBackgroundParallax);
	memcpy(&backgroundParallax.textures[0], &gTexBackgroundParallax[0],
			sizeof(Tt_Texture) * backgroundParallax.nTextures);

	anchorCardButton.w = 177;
	anchorCardButton.h = 264;

	for (size_t i = 0; i < Tt_Length(cardsToMemorizeButtons); ++i) {
		cardsToMemorizeButtons[i].w = 100;
		cardsToMemorizeButtons[i].h = 100;
	}
}

static void layoutChange(void)
{

	backgroundParallax.w = gWindowWidth;
	backgroundParallax.h = gWindowHeight;

	anchorCardButton.x = (gWindowWidth - anchorCardButton.w) * 0.5f;
	anchorCardButton.y = (gWindowHeight - anchorCardButton.h) * 0.5f;

	customGuessLabel.x = gWindowWidth * 0.5f;
	customGuessLabel.y = anchorCardButton.y - MARGIN_CUSTOM_GUESS_LABEL - MARGIN_CARD_BUTTON - customGuessLabel.h;

	int extraRow = (numberOfCardsToMemorize % 6) > 0 ? 1 : 0;
	int left = Tt_Min(numberOfCardsToMemorize, 6);
	float cardsToMemorizeButtonsX = (gWindowWidth - cardsToMemorizeButtons[0].w * left - 30 * (left-1)) / 2;
	float cardsToMemorizeButtonsY = (gWindowHeight - 60 - cardsToMemorizeButtons[0].h * (numberOfCardsToMemorize/6+extraRow) - 30 * ((numberOfCardsToMemorize/6+extraRow)-1)) / 2;

	for (size_t i = 0; i < numberOfCardsToMemorize; ++i) {
		cardsToMemorizeButtons[i].x = cardsToMemorizeButtonsX;
		cardsToMemorizeButtons[i].y = cardsToMemorizeButtonsY;
		cardsToMemorizeButtonsX += cardsToMemorizeButtons[i].w + 30;

		if ((i+1) % 6 == 0) {
			left = Tt_Min(numberOfCardsToMemorize-i-1, 6);
			cardsToMemorizeButtonsY += cardsToMemorizeButtons[0].h + 30;
			cardsToMemorizeButtonsX = (gWindowWidth - cardsToMemorizeButtons[0].w * left - 30 * (left-1)) / 2;
		}
	}

	memorizingGuides[0].x = gWindowWidth / 2.0f;
	memorizingGuides[0].y = cardsToMemorizeButtons[numberOfCardsToMemorize-1].y + cardsToMemorizeButtons[numberOfCardsToMemorize-1].h + MARGIN_CARD_ENCODED_BUTTON;

	memorizingGuides[1].x = gWindowWidth / 2.0f;
	memorizingGuides[1].y = memorizingGuides[0].h + cardsToMemorizeButtons[numberOfCardsToMemorize-1].y + cardsToMemorizeButtons[numberOfCardsToMemorize-1].h + MARGIN_CARD_ENCODED_BUTTON;

	questionLabel.x = gWindowWidth * 0.5f;
	questionLabel.y = anchorCardButton.y + anchorCardButton.h + MARGIN_CARD_BUTTON;
}

static void enter(void)
{
	isMemorizing = true;
	Tt_String_Builder_Clear(&customGuess);
	Tt_Score_Info_Reset(&scoreInfo);
	newMemorizingRound();
}

static void update(double dt)
{
	Tt_Parallax_Update(&backgroundParallax);

	if (isMemorizing) {
		for (size_t i = 0; i < numberOfCardsToMemorize; ++i)
			Tt_Button_Update(&cardsToMemorizeButtons[i]);

		Tt_Label_Update(&memorizingGuides[0]);
		Tt_Label_Update(&memorizingGuides[1]);
	} else {
		Tt_Score_Info_Increase_Time(&scoreInfo, dt);

		if (scoreInfo.score > 0) {
			Tt_Animated_Sprite_Update(&coinSprite);
			Tt_Label_Update(&scoreLabel);
		}

		Tt_Label_Update(&customGuessLabel);
		Tt_Card_Button_Update(&anchorCardButton);
		Tt_Label_Update(&questionLabel);
	}
}

static void textInput(char c)
{
	if (isMemorizing) {
		if (c == '+') {
			if (numberOfCardsToMemorize >= MAX_NUMBER_OF_CARDS_TO_MEMORIZE)
				return;
			numberOfCardsToMemorize += 1;
			layoutChange();
		} else if (c == '-') {
			if (numberOfCardsToMemorize <= MIN_NUMBER_OF_CARDS_TO_MEMORIZE)
				return;
			numberOfCardsToMemorize -= 1;
			layoutChange();
		}
	}
}

static void keyPress(enum Tt_Key key, enum Tt_Mod mods)
{
	switch (key) {
	case KEY_1:
		Tt_Scene_Switch(SCENE_GAMEMODE_ENCODE);
		break;
	case KEY_2:
		Tt_Scene_Switch(SCENE_GAMEMODE_DECODE);
		break;
	case KEY_4:
		Tt_Scene_Switch(SCENE_GAMEMODE_SPEED);
		break;
	case KEY_A...KEY_Z:
		if (isMemorizing)
			break;
		Tt_String_Builder_Append(&customGuess, 'A' + (key - KEY_A));
		if (autoAcceptGuess && (customGuess.len == (customGuess.data[0] == 'C' ? 3 : 2)))
			submitGuess(&customGuess.data[0]);
		break;
	case KEY_BACKSPACE:
		if (isMemorizing)
			break;
		Tt_String_Builder_Remove_Last_Character(&customGuess);
		break;
	case KEY_SPACE:
	case KEY_ENTER:
		if (isMemorizing)
			newRound();
		else if (customGuess.len != 0)
			submitGuess(&customGuess.data[0]);
		break;
	case KEY_F5:
		Tt_Scene_Switch(SCENE_GAMEMODE_MEMORIZE);
		break;
	default:
		break;
	}

}

Tt_Scene Tt_Get_Gamemode_Memorize_Scene(void)
{
	return (Tt_Scene) {
		.name           = "gamemode: memorize",
		.cbAwake        = awake,
		.cbEnter        = enter,
		.cbUpdate       = update,
		.cbLeave        = NULL,
		.cbKeyPress     = keyPress,
		.cbKeyRelease   = NULL,
		.cbTextInput    = textInput,
		.cbLayoutChange = layoutChange
	};
}
