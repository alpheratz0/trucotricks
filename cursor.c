// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <trucotricks/cursor.h>
#include <trucotricks/debug.h>
#include <trucotricks/util.h>
#include <trucotricks/window.h>
#include <GLFW/glfw3.h>
#include <stddef.h>

// Dictionary (enum Tt_Cursor_Shape, GLFWcursor*)
static GLFWcursor *cursors[CURSOR_SHAPE_COUNT];
// Current visible cursor
static enum Tt_Cursor_Shape currentCursor;
// Requested cursor, to prevent changing the cursor
// multiple times in a same frame, we first mark
// the cursor we want as requested, and when the frame
// ends we check if the requested cursor is different
// from the current cursor, if so we change the cursor
static enum Tt_Cursor_Shape requestedCursor;

void Tt_Cursor_Init(void)
{
	currentCursor = requestedCursor = CURSOR_SHAPE_ARROW;
	cursors[CURSOR_SHAPE_ARROW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
	cursors[CURSOR_SHAPE_HAND] = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
	cursors[CURSOR_SHAPE_IBEAM] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
	cursors[CURSOR_SHAPE_VERTICAL_RESIZE] = glfwCreateStandardCursor(GLFW_RESIZE_NS_CURSOR);
}

inline const char *__Tt_Cursor_Get_Name(enum Tt_Cursor_Shape cursor)
{
	switch (cursor) {
	case CURSOR_SHAPE_ARROW: return "arrow";
	case CURSOR_SHAPE_HAND: return "hand";
	case CURSOR_SHAPE_IBEAM: return "ibeam";
	case CURSOR_SHAPE_VERTICAL_RESIZE: return "vresize";
	default: return "unknown";
	}
}

void Tt_Cursor_Request(enum Tt_Cursor_Shape cursor)
{
	requestedCursor = cursor;
}

void Tt_Cursor_Commit(void)
{
	if (requestedCursor == currentCursor) return;
	currentCursor = requestedCursor;
	glfwSetCursor(gWindow, cursors[currentCursor]);
	V(("Cursor changed to \"%s\" cursor",
				__Tt_Cursor_Get_Name(currentCursor)));
}

void Tt_Cursor_Deinit(void)
{
	for (size_t i = 0; i < Tt_Length(cursors); ++i)
		glfwDestroyCursor(cursors[i]);
}
