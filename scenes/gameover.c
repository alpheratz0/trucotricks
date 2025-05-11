// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <trucotricks/keyboard.h>
#include <trucotricks/label.h>
#include <trucotricks/parallax.h>
#include <trucotricks/resources.h>
#include <trucotricks/scene.h>
#include <trucotricks/score_info.h>
#include <trucotricks/util.h>
#include <trucotricks/window.h>

#define STATS_BUF_SIZE 256
#define MARGIN_GAME_OVER_LABEL 40
#define MARGIN_STATS_LABELS 18
#define MARGIN_GUIDE_LABEL 20

Tt_Score_Info gameOverScore;
static Tt_Label gameOverLabel;
static Tt_Label statsLabels[5];
static Tt_Label guideLabel;
static Tt_Parallax backgroundParallax;

void Tt_Game_Over(Tt_Score_Info _gameOverScore)
{
	gameOverScore = _gameOverScore;
	Tt_Scene_Switch(SCENE_GAME_OVER);
}

static void awake(void)
{
	backgroundParallax.x = 0;
	backgroundParallax.y = 0;

	backgroundParallax.nTextures = Tt_Length(gTexBackgroundParallax);
	memcpy(&backgroundParallax.textures[0], &gTexBackgroundParallax[0],
			sizeof(Tt_Texture) * backgroundParallax.nTextures);

	gameOverLabel.h = 80;
	gameOverLabel.fontSize = 80;
	gameOverLabel.align = ALIGN_CENTER | ALIGN_TOP;
	gameOverLabel.font = gFontAttackOfMonster;
	gameOverLabel.text = "Game Over";
	gameOverLabel.hasShadow = true;
	gameOverLabel.shadowColor = 0x000000;
	gameOverLabel.color = 0x7fffff00;

	for (size_t i = 0; i < Tt_Length(statsLabels); ++i) {
		statsLabels[i].h = 20;
		statsLabels[i].fontSize = 20;
		statsLabels[i].align = ALIGN_CENTER | ALIGN_TOP;
		statsLabels[i].font = gFontAttackOfMonster;
		statsLabels[i].hasShadow = true;
		statsLabels[i].shadowColor = 0x000000;
		statsLabels[i].color = 0xffffff;
		statsLabels[i].text = malloc(STATS_BUF_SIZE);
	}

	guideLabel.h = 15;
	guideLabel.fontSize = 15;
	guideLabel.align = ALIGN_CENTER | ALIGN_TOP;
	guideLabel.font = gFontAttackOfMonster;
	guideLabel.text = "Press space to start again...";
	guideLabel.hasShadow = true;
	guideLabel.shadowColor = 0x000000;
	guideLabel.color = 0xcccccc;
}

static void layoutChange(void)
{
	float heightUsed = gameOverLabel.h + MARGIN_GAME_OVER_LABEL + (statsLabels[0].h + MARGIN_STATS_LABELS) * Tt_Length(statsLabels) + MARGIN_GUIDE_LABEL + guideLabel.h;

	float y = (gWindowHeight - heightUsed) * 0.5f;

	backgroundParallax.w = gWindowWidth;
	backgroundParallax.h = gWindowHeight;

	gameOverLabel.x = gWindowWidth * 0.5f;
	gameOverLabel.y = y;

	y += gameOverLabel.h + MARGIN_GAME_OVER_LABEL;

	for (size_t i = 0; i < Tt_Length(statsLabels); ++i) {
		statsLabels[i].x = gWindowWidth * 0.5f;
		statsLabels[i].y = y;
		y += statsLabels[i].h + MARGIN_STATS_LABELS;
	}

	y += MARGIN_GUIDE_LABEL;

	guideLabel.x = gWindowWidth * 0.5f;
	guideLabel.y = y;
}

static void enter(void)
{
	int minutes = (int)(gameOverScore.playTime) / 60;
	int seconds = (int)(gameOverScore.playTime) % 60;
	int ms = (gameOverScore.playTime - minutes * 60 - seconds) * 1000;

	snprintf(&statsLabels[0].text[0], STATS_BUF_SIZE, "Score: %d", gameOverScore.score);
	snprintf(&statsLabels[1].text[0], STATS_BUF_SIZE, "Ellapsed time: %02d:%02d.%03d", minutes, seconds, ms);

	if (gameOverScore.score == 0) {
		snprintf(&statsLabels[2].text[0], STATS_BUF_SIZE, "Average response time: N/A");
		snprintf(&statsLabels[3].text[0], STATS_BUF_SIZE, "Best response time: N/A");
		snprintf(&statsLabels[4].text[0], STATS_BUF_SIZE, "Worst response time: N/A");
	} else {
		snprintf(&statsLabels[2].text[0], STATS_BUF_SIZE, "Average response time: %.3f s", gameOverScore.averageResponseTime);
		snprintf(&statsLabels[3].text[0], STATS_BUF_SIZE, "Best response time: %.3f s", gameOverScore.bestResponseTime);
		snprintf(&statsLabels[4].text[0], STATS_BUF_SIZE, "Worst response time: %.3f s", gameOverScore.worstResponseTime);
	}
}

static void update(double dt)
{
	Tt_Parallax_Update(&backgroundParallax);
	Tt_Label_Update(&gameOverLabel);
	for (size_t i = 0; i < Tt_Length(statsLabels); ++i)
		Tt_Label_Update(&statsLabels[i]);
	Tt_Label_Update(&guideLabel);
}

static void keyPress(enum Tt_Key key, enum Tt_Mod mods)
{
	switch (key) {
	case KEY_1:
		Tt_Scene_Switch(SCENE_GAMEMODE_ENCODE); break;
		break;
	case KEY_2:
		Tt_Scene_Switch(SCENE_GAMEMODE_DECODE); break;
		break;
	case KEY_3:
		Tt_Scene_Switch(SCENE_GAMEMODE_MEMORIZE); break;
		break;
	case KEY_SPACE:
		Tt_Scene_Switch_To_Previous();
		break;
	default:
		break;
	}
}

Tt_Scene Tt_Get_Game_Over_Scene(void)
{
	return (Tt_Scene) {
		.name           = "game over",
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
