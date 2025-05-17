// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <stddef.h>
#include <nanovg.h>
#include <stdbool.h>
#include <stddef.h>
#include <trucotricks/activity_indicator.h>
#include <trucotricks/rank.h>
#include <trucotricks/resource_loader.h>
#include <trucotricks/resources.h>
#include <trucotricks/scene.h>
#include <trucotricks/sound.h>
#include <trucotricks/util.h>
#include <trucotricks/window.h>

static bool done;
static Tt_Resource_Loader *resourceLoader;
static Tt_Activity_Indicator activityIndicator;

static void awake(void)
{
	static Tt_Resource_Info resources[] = {
		Tt_Resource_Font     ("resources/attack-of-monster.otf",      &gFontAttackOfMonster),
		Tt_Resource_Font     ("resources/terminus.ttf",               &gFontTerminus),
		Tt_Resource_Texture  ("resources/gold_coin.png",              &gTexGoldCoin),
		Tt_Resource_Texture  ("resources/clouds/1.png",               &gTexBackgroundParallax[0]),
		Tt_Resource_Texture  ("resources/clouds/2.png",               &gTexBackgroundParallax[1]),
		Tt_Resource_Texture  ("resources/clouds/3.png",               &gTexBackgroundParallax[2]),
		Tt_Resource_Texture  ("resources/clouds/4.png",               &gTexBackgroundParallax[3]),
		Tt_Resource_Texture  ("resources/clouds/5.png",               &gTexBackgroundParallax[4]),
		Tt_Resource_Texture  ("resources/cards/unknown.jpg",          &gTexUnknownCard),
		Tt_Resource_Texture  ("resources/cards/basto/1.jpg",          &gTexBasto[RANK_UNO]),
		Tt_Resource_Texture  ("resources/cards/basto/2.jpg",          &gTexBasto[RANK_DOS]),
		Tt_Resource_Texture  ("resources/cards/basto/3.jpg",          &gTexBasto[RANK_TRES]),
		Tt_Resource_Texture  ("resources/cards/basto/4.jpg",          &gTexBasto[RANK_CUATRO]),
		Tt_Resource_Texture  ("resources/cards/basto/5.jpg",          &gTexBasto[RANK_CINCO]),
		Tt_Resource_Texture  ("resources/cards/basto/6.jpg",          &gTexBasto[RANK_SEIS]),
		Tt_Resource_Texture  ("resources/cards/basto/7.jpg",          &gTexBasto[RANK_SIETE]),
		Tt_Resource_Texture  ("resources/cards/basto/10.jpg",         &gTexBasto[RANK_DIEZ]),
		Tt_Resource_Texture  ("resources/cards/basto/11.jpg",         &gTexBasto[RANK_ONCE]),
		Tt_Resource_Texture  ("resources/cards/basto/12.jpg",         &gTexBasto[RANK_DOCE]),
		Tt_Resource_Texture  ("resources/cards/oro/1.jpg",            &gTexOro[RANK_UNO]),
		Tt_Resource_Texture  ("resources/cards/oro/2.jpg",            &gTexOro[RANK_DOS]),
		Tt_Resource_Texture  ("resources/cards/oro/3.jpg",            &gTexOro[RANK_TRES]),
		Tt_Resource_Texture  ("resources/cards/oro/4.jpg",            &gTexOro[RANK_CUATRO]),
		Tt_Resource_Texture  ("resources/cards/oro/5.jpg",            &gTexOro[RANK_CINCO]),
		Tt_Resource_Texture  ("resources/cards/oro/6.jpg",            &gTexOro[RANK_SEIS]),
		Tt_Resource_Texture  ("resources/cards/oro/7.jpg",            &gTexOro[RANK_SIETE]),
		Tt_Resource_Texture  ("resources/cards/oro/10.jpg",           &gTexOro[RANK_DIEZ]),
		Tt_Resource_Texture  ("resources/cards/oro/11.jpg",           &gTexOro[RANK_ONCE]),
		Tt_Resource_Texture  ("resources/cards/oro/12.jpg",           &gTexOro[RANK_DOCE]),
		Tt_Resource_Texture  ("resources/cards/copa/1.jpg",           &gTexCopa[RANK_UNO]),
		Tt_Resource_Texture  ("resources/cards/copa/2.jpg",           &gTexCopa[RANK_DOS]),
		Tt_Resource_Texture  ("resources/cards/copa/3.jpg",           &gTexCopa[RANK_TRES]),
		Tt_Resource_Texture  ("resources/cards/copa/4.jpg",           &gTexCopa[RANK_CUATRO]),
		Tt_Resource_Texture  ("resources/cards/copa/5.jpg",           &gTexCopa[RANK_CINCO]),
		Tt_Resource_Texture  ("resources/cards/copa/6.jpg",           &gTexCopa[RANK_SEIS]),
		Tt_Resource_Texture  ("resources/cards/copa/7.jpg",           &gTexCopa[RANK_SIETE]),
		Tt_Resource_Texture  ("resources/cards/copa/10.jpg",          &gTexCopa[RANK_DIEZ]),
		Tt_Resource_Texture  ("resources/cards/copa/11.jpg",          &gTexCopa[RANK_ONCE]),
		Tt_Resource_Texture  ("resources/cards/copa/12.jpg",          &gTexCopa[RANK_DOCE]),
		Tt_Resource_Texture  ("resources/cards/espada/1.jpg",         &gTexEspada[RANK_UNO]),
		Tt_Resource_Texture  ("resources/cards/espada/2.jpg",         &gTexEspada[RANK_DOS]),
		Tt_Resource_Texture  ("resources/cards/espada/3.jpg",         &gTexEspada[RANK_TRES]),
		Tt_Resource_Texture  ("resources/cards/espada/4.jpg",         &gTexEspada[RANK_CUATRO]),
		Tt_Resource_Texture  ("resources/cards/espada/5.jpg",         &gTexEspada[RANK_CINCO]),
		Tt_Resource_Texture  ("resources/cards/espada/6.jpg",         &gTexEspada[RANK_SEIS]),
		Tt_Resource_Texture  ("resources/cards/espada/7.jpg",         &gTexEspada[RANK_SIETE]),
		Tt_Resource_Texture  ("resources/cards/espada/10.jpg",        &gTexEspada[RANK_DIEZ]),
		Tt_Resource_Texture  ("resources/cards/espada/11.jpg",        &gTexEspada[RANK_ONCE]),
		Tt_Resource_Texture  ("resources/cards/espada/12.jpg",        &gTexEspada[RANK_DOCE]),
		Tt_Resource_Sound    ("resources/swipe.ogg",                  &gSoundSwipe),
		Tt_Resource_Sound    ("resources/gameover.ogg",               &gSoundGameOver),
		Tt_Resource_Sound    ("resources/bgm.ogg",                    &gSoundBackgroundMusic),
		Tt_Resource_Sound    ("resources/scene-switching.ogg",        &gSoundSceneSwitching),
	};

	resourceLoader = Tt_Resource_Loader_New( Tt_Length(resources), resources, gVg);
	Tt_Resource_Loader_Start(resourceLoader);
}

static void layoutChange(void)
{
	activityIndicator.x = gWindowWidth / 2;
	activityIndicator.y = gWindowHeight / 2;
}

static void update(double dt)
{
	if (done) {
		Tt_Scene_Switch(SCENE_GAMEMODE_ENCODE);
		return;
	}

	if (NULL == resourceLoader) return;

	Tt_Activity_Indicator_Update(&activityIndicator);

	if (resourceLoader->isLoading) return;

	Tt_Resource_Loader_Generate_Textures(resourceLoader);
	Tt_Resource_Loader_Free(resourceLoader);
	resourceLoader = NULL;

	Tt_Scene_Switch(SCENE_GAMEMODE_ENCODE);
	Tt_Sound_Play_Music(gSoundBackgroundMusic, 0.35f);
	done = true;
}

Tt_Scene Tt_Get_Loading_Scene(void)
{
	return (Tt_Scene) {
		.name           = "loading",
		.cbAwake        = awake,
		.cbEnter        = NULL,
		.cbUpdate       = update,
		.cbLeave        = NULL,
		.cbKeyPress     = NULL,
		.cbKeyRelease   = NULL,
		.cbLayoutChange = layoutChange,
	};
}
