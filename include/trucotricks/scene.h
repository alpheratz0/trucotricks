// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_SCENE_H
#define TRUCOTRICKS_SCENE_H

#include <trucotricks/keyboard.h>

#define SCENE_MAX_COUNT 32

enum Tt_Fade {
	FADE_OUT,
	FADE_IN
};

// Here is where all the scenes definitions live. If you want to create
// a new one, first you need to create the source `my-scene.c`,
// there, expose a function `Tt_Scene Tt_Get_My_Scene(void)` which returns
// the scene, then add that definition here.
//
// Now you need to add the scene ID, put it after the last one, with the
// next available ID and bind the scene.
// Call `Tt_Scene_Bind(SCENE_1, Tt_Get_My_Scene())` inside `main.c`
// and you are ready to go.
enum Tt_Scene_Id {
	SCENE_LOADING = 0, // Loading resources scene (startup scene)
	SCENE_GAMEMODE_ENCODE = 1, // Game mode 1 scene
	SCENE_GAMEMODE_DECODE = 2, // Game mode 2 scene
	SCENE_GAMEMODE_MEMORIZE = 3, // Game mode 3 scene
	SCENE_GAME_OVER = 4, // Game over scene
	SCENE_INVALID = 100, // No scene
};

typedef struct Tt_Scene Tt_Scene;

// Event handlers defs
typedef void (*Tt_Scene_Awake_Event_Handler)(void);
typedef void (*Tt_Scene_Enter_Event_Handler)(void);
typedef void (*Tt_Scene_Update_Event_Handler)(double dt);
typedef void (*Tt_Scene_Leave_Event_Handler)(void);
typedef void (*Tt_Scene_Key_Press_Event_Handler)(enum Tt_Key key, enum Tt_Mod mods);
typedef void (*Tt_Scene_Key_Release_Event_Handler)(enum Tt_Key key, enum Tt_Mod mods);
typedef void (*Tt_Scene_Text_Input_Event_Handler)(char c);
typedef void (*Tt_Scene_Layout_Change_Event_Handler)(void);

struct Tt_Scene
{
	// Was the scene awaked?
	bool awaked;
	// Scene name (used for debugging only)
	const char *name;
	// Called only the first time you switch to this scene
	Tt_Scene_Awake_Event_Handler cbAwake;
	// Called every time you switch to this scene
	Tt_Scene_Enter_Event_Handler cbEnter;
	// Called every frame
	Tt_Scene_Update_Event_Handler cbUpdate;
	// Called when you leave the scene
	Tt_Scene_Leave_Event_Handler cbLeave;
	// Called when a key is pressed
	Tt_Scene_Key_Press_Event_Handler cbKeyPress;
	// Called when a key is released
	Tt_Scene_Key_Release_Event_Handler cbKeyRelease;
	// Called when text input is received
	Tt_Scene_Text_Input_Event_Handler cbTextInput;
	// Called when the window size changes
	Tt_Scene_Layout_Change_Event_Handler cbLayoutChange;
};

// Switch to the specified scene
void Tt_Scene_Switch(enum Tt_Scene_Id sid);

// Switch to the previous scene (if any)
void Tt_Scene_Switch_To_Previous(void);

// Binds an id to a scene
void Tt_Scene_Bind(enum Tt_Scene_Id sid, Tt_Scene scene);

// Advances one frame
void Tt_Scene_Update(double dt);

// Dispatches a key event to the active scene
void Tt_Scene_Dispatch_Key_Event(enum Tt_Key key, enum Tt_State state, enum Tt_Mod mods);

// Dispatches a text input event to the active scene
void Tt_Scene_Dispatch_Text_Input_Event(char c);

// Dispatches a layout change event to the active scene
void Tt_Scene_Dispatch_Layout_Change_Event(void);

#endif
