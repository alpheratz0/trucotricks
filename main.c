// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <GLFW/glfw3.h>
#include <nanovg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <trucotricks/all_scenes.h>
#include <trucotricks/cursor.h>
#include <trucotricks/keyboard.h>
#include <trucotricks/layout.h>
#include <trucotricks/mouse.h>
#include <trucotricks/scene.h>
#include <trucotricks/time.h>
#include <trucotricks/window.h>

int main(void)
{
	int framebufferW, framebufferH;
	int windowW, windowH;
	double lastFrameTime;

	srand(time(NULL));

	Tt_Window_Create();

	Tt_Cursor_Init();
	Tt_Mouse_Init();
	Tt_Keyboard_Init();
	Tt_Layout_Init();

	Tt_Scene_Bind(SCENE_LOADING, Tt_Get_Loading_Scene());
	Tt_Scene_Bind(SCENE_GAMEMODE_ENCODE, Tt_Get_Gamemode_Encode_Scene());
	Tt_Scene_Bind(SCENE_GAMEMODE_DECODE, Tt_Get_Gamemode_Decode_Scene());
	Tt_Scene_Bind(SCENE_GAMEMODE_MEMORIZE, Tt_Get_Gamemode_Memorize_Scene());
	Tt_Scene_Bind(SCENE_GAMEMODE_SPEED, Tt_Get_Gamemode_Speed_Scene());
	Tt_Scene_Bind(SCENE_GAME_OVER, Tt_Get_Game_Over_Scene());

	Tt_Scene_Switch(SCENE_LOADING);

	lastFrameTime = glfwGetTime();

	while (!glfwWindowShouldClose(gWindow)) {
		gRunningTime = glfwGetTime();
		gDeltaTime = gRunningTime - lastFrameTime;
		lastFrameTime = gRunningTime;
		glfwPollEvents();
		glfwGetFramebufferSize(gWindow, &framebufferW, &framebufferH);
		glfwGetWindowSize(gWindow, &windowW, &windowH);
		glViewport(0, 0, framebufferW, framebufferH);
		glClearColor(0.03f, 0.03f, 0.03f, 1);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		nvgBeginFrame(gVg, windowW, windowH, ((float)(framebufferW)) / windowW);
		Tt_Mouse_Update();
		Tt_Cursor_Request(CURSOR_SHAPE_ARROW);
		Tt_Scene_Update(gDeltaTime);
		Tt_Cursor_Commit();
		nvgEndFrame(gVg);
		glEnable(GL_DEPTH_TEST);
		glfwSwapBuffers(gWindow);
	}

	Tt_Layout_Deinit();
	Tt_Keyboard_Deinit();
	Tt_Mouse_Deinit();
	Tt_Cursor_Deinit();

	Tt_Window_Destroy();

	return 0;
}
