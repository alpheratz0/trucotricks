// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <math.h>
#include <trucotricks/time.h>
#include <trucotricks/window.h>
#include <trucotricks/gallery_switcher.h>
#include <trucotricks/scene.h>
#include <trucotricks/all_scenes.h>
#include <nanovg.h>

static Tt_Gallery_Switcher sceneSwitcher;

static void sceneSwitcherClicked(Tt_Gallery_Switcher *sender, int index)
{
	(void) sender;

	switch (index) {
	case 0: Tt_Scene_Switch(SCENE_GAMEMODE_SPEED); break;
	case 1: Tt_Scene_Switch(SCENE_GAMEMODE_DECODE); break;
	case 2: Tt_Scene_Switch(SCENE_GAMEMODE_ENCODE); break;
	case 3: Tt_Scene_Switch(SCENE_GAMEMODE_MEMORIZE); break;
	default: break;
	}
}

void Tt_Scene_Switcher_Init(void)
{
	if (sceneSwitcher.buttonCount > 0)
		return;

	sceneSwitcher.w = 200;
	sceneSwitcher.h = 8;
	sceneSwitcher.selectedIndex = 0;
	sceneSwitcher.buttonTooltips[sceneSwitcher.buttonCount++] = "Speed";
	sceneSwitcher.buttonTooltips[sceneSwitcher.buttonCount++] = "Decode";
	sceneSwitcher.buttonTooltips[sceneSwitcher.buttonCount++] = "Encode";
	sceneSwitcher.buttonTooltips[sceneSwitcher.buttonCount++] = "Memorize";
	sceneSwitcher.onClick = sceneSwitcherClicked;
}

void Tt_Scene_Switcher_Start(int selected)
{
	sceneSwitcher.selectedIndex = selected;
	sceneSwitcher.hoverTime = 0.0f;
}

void Tt_Scene_Switcher_Layout_Change(void)
{
	sceneSwitcher.x = (gWindowWidth - sceneSwitcher.w) / 2;
	sceneSwitcher.y = gWindowHeight - sceneSwitcher.h - 30;
}

void Tt_Scene_Switcher_Update(void)
{
	Tt_Gallery_Switcher_Update(&sceneSwitcher);
}
