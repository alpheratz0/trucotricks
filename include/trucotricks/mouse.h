// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_MOUSE_H
#define TRUCOTRICKS_MOUSE_H

#include <trucotricks/rect.h>
#include <stdbool.h>

enum Tt_Mouse_Button {
	MOUSE_BUTTON_LEFT,
	MOUSE_BUTTON_RIGHT,
	MOUSE_BUTTON_MIDDLE,
};

void Tt_Mouse_Init(void);
void Tt_Mouse_Update(void);
void Tt_Mouse_Reset(void);
void Tt_Mouse_Deinit(void);
double Tt_Mouse_Get_X(void);
double Tt_Mouse_Get_Y(void);
double Tt_Mouse_Get_Scroll(void);
void Tt_Mouse_Ignore(bool ignore);

bool Tt_Mouse_Is_Over_Rect(const Tt_Rect *rect);
bool Tt_Mouse_Is_Button_Just_Pressed(enum Tt_Mouse_Button button);
bool Tt_Mouse_Is_Button_Pressed(enum Tt_Mouse_Button button);
bool Tt_Mouse_Is_Button_Just_Released(enum Tt_Mouse_Button button);

#endif
