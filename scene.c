// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <stdbool.h>
#include <nanovg.h>
#include <stdio.h>
#include <trucotricks/debug.h>
#include <trucotricks/keyboard.h>
#include <trucotricks/mouse.h>
#include <trucotricks/resources.h>
#include <trucotricks/scene.h>
#include <trucotricks/sound.h>
#include <trucotricks/util.h>
#include <trucotricks/window.h>

float switchingTimer = 0.0f;
bool isSwitching = false;
enum Tt_Fade switchingState = FADE_OUT;
enum Tt_Scene_Id current = SCENE_INVALID;
enum Tt_Scene_Id previous = SCENE_INVALID;
enum Tt_Scene_Id switchTarget = SCENE_INVALID;
Tt_Scene scenes[SCENE_MAX_COUNT];

#ifdef Debug
static const char *__Tt_Scene_Get_Name(const Tt_Scene *scene)
{
	if (scene->name) return scene->name;
	return "unnamed";
}
#endif

static void __Tt_Scene_Layout(enum Tt_Scene_Id sid)
{
	if (scenes[sid].cbLayoutChange)
		scenes[sid].cbLayoutChange();
}

static void __Tt_Scene_Awake(enum Tt_Scene_Id sid)
{
	if (!scenes[sid].awaked) {
		scenes[sid].awaked = true;
		if (scenes[sid].cbAwake) {
			D(("Awakening scene '%s' (id=%d)",
						__Tt_Scene_Get_Name(&scenes[sid]), sid));
			scenes[sid].cbAwake();
		}
	}
}

static void __Tt_Scene_Enter(enum Tt_Scene_Id sid)
{
	D(("Entering scene '%s' (id=%d)", __Tt_Scene_Get_Name(&scenes[sid]), sid));
	if (scenes[sid].cbEnter)
		scenes[sid].cbEnter();
	__Tt_Scene_Layout(sid);
}

static void __Tt_Scene_Leave(enum Tt_Scene_Id sid)
{
	if (sid != SCENE_INVALID) {
		D(("Leaving scene '%s' (id=%d)", __Tt_Scene_Get_Name(&scenes[sid]), sid));
		if (scenes[sid].cbLeave)
			scenes[sid].cbLeave();
	}
}

void Tt_Scene_Switch(enum Tt_Scene_Id sid)
{
	if (current == sid) return;

	if (current == SCENE_INVALID) {
		Tt_Mouse_Reset();
		__Tt_Scene_Leave(current);
		__Tt_Scene_Awake(sid);
		__Tt_Scene_Enter(sid);
		previous = current;
		current = sid;
	} else if (!isSwitching) {
		switchingState = FADE_OUT;
		isSwitching = true;
		switchingTimer = 0.0f;
		switchTarget = sid;
		Tt_Sound_Play(gSoundSceneSwitching);
	}
}

void Tt_Scene_Switch_To_Previous(void)
{
	if (previous != SCENE_INVALID)
		Tt_Scene_Switch(previous);
}

void Tt_Scene_Bind(enum Tt_Scene_Id sid, Tt_Scene scene)
{
	D(("Binding scene '%s' (id=%d)", __Tt_Scene_Get_Name(&scene), sid));
	scene.awaked = false;
	scenes[sid] = scene;
}

void Tt_Scene_Update(double dt)
{
	Tt_Scene *scene = &scenes[current];

	scene->cbUpdate(dt);

	if (isSwitching) {
		switchingTimer += dt * 5;
		if (switchingState == FADE_OUT) {
			nvgBeginPath(gVg);
			nvgFillColor(gVg, nvgRGBA(0x00, 0x00, 0x00, Tt_Min(switchingTimer, 1.0f) * 0xff));
			nvgRect(gVg, 0, 0, gWindowWidth, gWindowHeight);
			nvgFill(gVg);

			if (switchingTimer > 1.0f) {
				switchingTimer = 0.0f;
				switchingState = FADE_IN;
				Tt_Mouse_Reset();
				__Tt_Scene_Leave(current);
				__Tt_Scene_Awake(switchTarget);
				__Tt_Scene_Enter(switchTarget);
				previous = current;
				current = switchTarget;
			}
		} else {
			nvgBeginPath(gVg);
			nvgFillColor(gVg, nvgRGBA(0x00, 0x00, 0x00, (1.0f - Tt_Min(switchingTimer, 1.0f)) * 0xff));
			nvgRect(gVg, 0, 0, gWindowWidth, gWindowHeight);
			nvgFill(gVg);

			if (switchingTimer > 1.0f) {
				isSwitching = false;
				switchingTimer = 0.0f;
			}
		}
	}
}

void Tt_Scene_Dispatch_Key_Event(enum Tt_Key key, enum Tt_State state, enum Tt_Mod mods)
{
	Tt_Scene *scene = &scenes[current];

	switch (state) {
	case STATE_RELEASE:
		if (NULL != scene->cbKeyRelease)
			scene->cbKeyRelease(key, mods);
		break;
	case STATE_PRESS:
		if (NULL != scene->cbKeyPress)
			scene->cbKeyPress(key, mods);
		break;
	default:
		break;
	}
}

void Tt_Scene_Dispatch_Text_Input_Event(char c)
{
	Tt_Scene *scene = &scenes[current];

	if (NULL != scene->cbTextInput)
		scene->cbTextInput(c);
}

void Tt_Scene_Dispatch_Layout_Change_Event(void)
{
	__Tt_Scene_Layout(current);
}
