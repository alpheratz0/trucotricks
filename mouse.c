// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <trucotricks/debug.h>
#include <trucotricks/mouse.h>
#include <trucotricks/rect.h>
#include <trucotricks/util.h>
#include <trucotricks/window.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <string.h>

static bool prevState[3] = {0};
static bool currState[3] = {0};
static bool ignoreState[3] = {0};
static bool ignoreMode = false;
static double scroll = 0.0f;
static bool focused = true;
static double xPosition, yPosition;

static void __Tt_Scroll_Callback(GLFWwindow *window, double x, double y)
{
	scroll = y;
}

static void __Tt_Focus_Callback(GLFWwindow *window, int f)
{
	I(("Window focus changed: %s", f ? "on":"off"));
	focused = f;
}

static void __Tt_Cursor_Pos_Callback(GLFWwindow *window, double x, double y)
{
	xPosition = x;
	yPosition = y;
}

void Tt_Mouse_Init(void)
{
	glfwSetScrollCallback(gWindow, __Tt_Scroll_Callback);
	glfwSetWindowFocusCallback(gWindow, __Tt_Focus_Callback);
	glfwSetCursorPosCallback(gWindow, __Tt_Cursor_Pos_Callback);
}

void Tt_Mouse_Update(void)
{
	bool nextState;
	for (size_t i=0; i < Tt_Length(currState); ++i) {
		prevState[i] = currState[i];
		nextState = glfwGetMouseButton(gWindow, i) == GLFW_PRESS;
		if (ignoreState[i]) {
			if (!nextState) {
				ignoreState[i] = false;
			}
		} else {
			currState[i] = nextState;
		}
	}
}

void Tt_Mouse_Reset(void)
{
	memcpy(ignoreState, currState, sizeof(currState));
	memset(prevState, 0, sizeof(prevState));
	memset(currState, 0, sizeof(currState));
	ignoreMode = false;
}

double Tt_Mouse_Get_X(void)
{
	if (ignoreMode || !focused) return -1.0;
	return xPosition;
}

double Tt_Mouse_Get_Y(void)
{
	if (ignoreMode || !focused) return -1.0;
	return yPosition;
}

double Tt_Mouse_Get_Scroll(void)
{
	if (ignoreMode || !focused) return 0.0f;
	double _scroll = scroll;
	scroll = 0.0f;
	return _scroll;
}

void Tt_Mouse_Ignore(bool ignore)
{
	ignoreMode = ignore;
}

bool Tt_Mouse_Is_Over_Rect(const Tt_Rect *rect)
{
	return !ignoreMode && focused && Tt_Rect_Contains_Point(rect, xPosition, yPosition);
}

bool Tt_Mouse_Is_Button_Just_Pressed(enum Tt_Mouse_Button button)
{
	return !ignoreMode && currState[button] && !prevState[button];
}

bool Tt_Mouse_Is_Button_Pressed(enum Tt_Mouse_Button button)
{
	return !ignoreMode && currState[button];
}

bool Tt_Mouse_Is_Button_Just_Released(enum Tt_Mouse_Button button)
{
	return !ignoreMode && prevState[button] && !currState[button];
}

void Tt_Mouse_Deinit(void)
{
	memset(prevState, 0, sizeof(prevState));
	memset(currState, 0, sizeof(currState));
	memset(ignoreState, 0, sizeof(ignoreState));
	focused = ignoreMode = false;
	xPosition = yPosition = scroll = 0.0f;
	glfwSetScrollCallback(gWindow, NULL);
	glfwSetWindowFocusCallback(gWindow, NULL);
	glfwSetCursorPosCallback(gWindow, NULL);
}
