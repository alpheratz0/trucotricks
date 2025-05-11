// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <trucotricks/layout.h>
#include <GLFW/glfw3.h>
#include <stddef.h>
#include <trucotricks/scene.h>
#include <trucotricks/window.h>

static void __Tt_Layout_Change_Callback(GLFWwindow *window, int newWidth, int newHeight)
{
	gWindowWidth = newWidth;
	gWindowHeight = newHeight;
	Tt_Layout_Dispatch_Layout_Change_Event();
}

void Tt_Layout_Init(void) { glfwSetFramebufferSizeCallback(gWindow, __Tt_Layout_Change_Callback); }

void Tt_Layout_Dispatch_Layout_Change_Event(void) { Tt_Scene_Dispatch_Layout_Change_Event(); }

void Tt_Layout_Deinit(void) { glfwSetFramebufferSizeCallback(gWindow, NULL); }
