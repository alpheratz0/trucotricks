// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <trucotricks/keyboard.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stddef.h>
#include <trucotricks/scene.h>
#include <trucotricks/window.h>

static bool ignoreMode;

static int keyTranslationTable[] = {
	[KEY_A] = GLFW_KEY_A,
	[KEY_B] = GLFW_KEY_B,
	[KEY_C] = GLFW_KEY_C,
	[KEY_D] = GLFW_KEY_D,
	[KEY_E] = GLFW_KEY_E,
	[KEY_F] = GLFW_KEY_F,
	[KEY_G] = GLFW_KEY_G,
	[KEY_H] = GLFW_KEY_H,
	[KEY_I] = GLFW_KEY_I,
	[KEY_J] = GLFW_KEY_J,
	[KEY_K] = GLFW_KEY_K,
	[KEY_L] = GLFW_KEY_L,
	[KEY_M] = GLFW_KEY_M,
	[KEY_N] = GLFW_KEY_N,
	[KEY_O] = GLFW_KEY_O,
	[KEY_P] = GLFW_KEY_P,
	[KEY_Q] = GLFW_KEY_Q,
	[KEY_R] = GLFW_KEY_R,
	[KEY_S] = GLFW_KEY_S,
	[KEY_T] = GLFW_KEY_T,
	[KEY_U] = GLFW_KEY_U,
	[KEY_V] = GLFW_KEY_V,
	[KEY_W] = GLFW_KEY_W,
	[KEY_X] = GLFW_KEY_X,
	[KEY_Y] = GLFW_KEY_Y,
	[KEY_Z] = GLFW_KEY_Z,
	[KEY_0] = GLFW_KEY_0,
	[KEY_1] = GLFW_KEY_1,
	[KEY_2] = GLFW_KEY_2,
	[KEY_3] = GLFW_KEY_3,
	[KEY_4] = GLFW_KEY_4,
	[KEY_5] = GLFW_KEY_5,
	[KEY_6] = GLFW_KEY_6,
	[KEY_7] = GLFW_KEY_7,
	[KEY_8] = GLFW_KEY_8,
	[KEY_9] = GLFW_KEY_9,
	[KEY_NUMPAD_0] = GLFW_KEY_KP_0,
	[KEY_NUMPAD_1] = GLFW_KEY_KP_1,
	[KEY_NUMPAD_2] = GLFW_KEY_KP_2,
	[KEY_NUMPAD_3] = GLFW_KEY_KP_3,
	[KEY_NUMPAD_4] = GLFW_KEY_KP_4,
	[KEY_NUMPAD_5] = GLFW_KEY_KP_5,
	[KEY_NUMPAD_6] = GLFW_KEY_KP_6,
	[KEY_NUMPAD_7] = GLFW_KEY_KP_7,
	[KEY_NUMPAD_8] = GLFW_KEY_KP_8,
	[KEY_NUMPAD_9] = GLFW_KEY_KP_9,
	[KEY_SPACE] = GLFW_KEY_SPACE,
	[KEY_APOSTROPHE] = GLFW_KEY_APOSTROPHE,
	[KEY_COMMA] = GLFW_KEY_COMMA,
	[KEY_MINUS] = GLFW_KEY_MINUS,
	[KEY_PERIOD] = GLFW_KEY_PERIOD,
	[KEY_SLASH] = GLFW_KEY_SLASH,
	[KEY_SEMICOLON] = GLFW_KEY_SEMICOLON,
	[KEY_EQUAL] = GLFW_KEY_EQUAL,
	[KEY_LEFT_BRACKET] = GLFW_KEY_LEFT_BRACKET,
	[KEY_BACKSLASH] = GLFW_KEY_BACKSLASH,
	[KEY_RIGHT_BRACKET] = GLFW_KEY_RIGHT_BRACKET,
	[KEY_GRAVE_ACCENT] = GLFW_KEY_GRAVE_ACCENT,
	[KEY_RIGHT_ARROW] = GLFW_KEY_RIGHT,
	[KEY_LEFT_ARROW] = GLFW_KEY_LEFT,
	[KEY_DOWN_ARROW] = GLFW_KEY_DOWN,
	[KEY_UP_ARROW] = GLFW_KEY_UP,
	[KEY_LEFT_SHIFT] = GLFW_KEY_LEFT_SHIFT,
	[KEY_RIGHT_SHIFT] = GLFW_KEY_RIGHT_SHIFT,
	[KEY_LEFT_CONTROL] = GLFW_KEY_LEFT_CONTROL,
	[KEY_RIGHT_CONTROL] = GLFW_KEY_RIGHT_CONTROL,
	[KEY_LEFT_ALT] = GLFW_KEY_LEFT_ALT,
	[KEY_RIGHT_ALT] = GLFW_KEY_RIGHT_ALT,
	[KEY_ESCAPE] = GLFW_KEY_ESCAPE,
	[KEY_TAB] = GLFW_KEY_TAB,
	[KEY_ENTER] = GLFW_KEY_ENTER,
	[KEY_BACKSPACE] = GLFW_KEY_BACKSPACE,
	[KEY_F1] = GLFW_KEY_F1,
	[KEY_F2] = GLFW_KEY_F2,
	[KEY_F3] = GLFW_KEY_F3,
	[KEY_F4] = GLFW_KEY_F4,
	[KEY_F5] = GLFW_KEY_F5,
	[KEY_F6] = GLFW_KEY_F6,
	[KEY_F7] = GLFW_KEY_F7,
	[KEY_F8] = GLFW_KEY_F8,
	[KEY_F9] = GLFW_KEY_F9,
	[KEY_F10] = GLFW_KEY_F10,
	[KEY_F11] = GLFW_KEY_F11,
	[KEY_F12] = GLFW_KEY_F12,
	[KEY_DELETE] = GLFW_KEY_DELETE
};

static inline enum Tt_Key __Tt_Translate_Glfw_Key(int glfwKey)
{
	for (enum Tt_Key key = 0; key < KEY_COUNT; ++key)
		if (keyTranslationTable[key] == glfwKey)
			return key;
	return KEY_INVALID;
}

static inline enum Tt_State __Tt_Translate_Glfw_State(int glfwState)
{
	switch (glfwState) {
	case GLFW_PRESS:
	case GLFW_REPEAT: /*treat GLFW_REPEAT as GLFW_PRESS*/
		return STATE_PRESS;
	case GLFW_RELEASE:
		return STATE_RELEASE;
	default:
		return STATE_INVALID;
	}
}

static inline enum Tt_Mod __Tt_Translate_Glfw_Mod(int glfwMods)
{
	enum Tt_Mod mods = MOD_NONE;
	if (glfwMods & GLFW_MOD_CONTROL) mods |= MOD_CONTROL;
	if (glfwMods & GLFW_MOD_SHIFT) mods |= MOD_SHIFT;
	if (glfwMods & GLFW_MOD_ALT) mods |= MOD_ALT;
	return mods;
}

static void __Tt_Key_Callback(GLFWwindow *window, int key, int scancode, int state, int mods)
{
	if (!ignoreMode)
		Tt_Keyboard_Dispatch_Key_Event(__Tt_Translate_Glfw_Key(key),
			__Tt_Translate_Glfw_State(state), __Tt_Translate_Glfw_Mod(mods));
}

static void __Tt_Text_Input_Callback(GLFWwindow *window, unsigned int codepoint)
{
	if (!ignoreMode && codepoint <= 0x7f)
		Tt_Keyboard_Dispatch_Text_Input_Event((char)codepoint);
}

void Tt_Keyboard_Init(void)
{
	glfwSetKeyCallback(gWindow, __Tt_Key_Callback);
	glfwSetCharCallback(gWindow, __Tt_Text_Input_Callback);
}

void Tt_Keyboard_Dispatch_Key_Event(enum Tt_Key key, enum Tt_State state, enum Tt_Mod mods)
{
	if (!ignoreMode)
		Tt_Scene_Dispatch_Key_Event(key, state, mods);
}

void Tt_Keyboard_Dispatch_Text_Input_Event(char c)
{
	if (!ignoreMode)
		Tt_Scene_Dispatch_Text_Input_Event(c);
}

void Tt_Keyboard_Ignore(bool ignore)
{
	ignoreMode = ignore;
}

bool Tt_Keyboard_Is_Key_Pressed(enum Tt_Key key)
{
	return !ignoreMode && key >= 0 && key < KEY_COUNT &&
		glfwGetKey(gWindow, keyTranslationTable[key]) == GLFW_PRESS;
}

void Tt_Keyboard_Deinit(void)
{
	ignoreMode = false;
	glfwSetKeyCallback(gWindow, NULL);
}
