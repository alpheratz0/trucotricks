// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_CURSOR_H
#define TRUCOTRICKS_CURSOR_H

enum Tt_Cursor_Shape {
	CURSOR_SHAPE_ARROW = 0,
	CURSOR_SHAPE_HAND = 1,
	CURSOR_SHAPE_IBEAM = 2,
	CURSOR_SHAPE_VERTICAL_RESIZE = 3,
	CURSOR_SHAPE_COUNT = 4
};

void Tt_Cursor_Init(void);

void Tt_Cursor_Request(enum Tt_Cursor_Shape cursor);

void Tt_Cursor_Commit(void);

void Tt_Cursor_Deinit(void);

#endif
