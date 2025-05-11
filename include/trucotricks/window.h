// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_WINDOW_H
#define TRUCOTRICKS_WINDOW_H

#include <GLFW/glfw3.h>
#include <nanovg.h>
#include <stdbool.h>

#define WINDOW_TITLE "Truco Tricks"
#define WINDOW_INITIAL_WIDTH (1080)
#define WINDOW_INITIAL_HEIGHT (720)

/** The window */
extern GLFWwindow *gWindow;

/** The window width */
extern double gWindowWidth;

/** The window height */
extern double gWindowHeight;

/** The NVG context */
extern NVGcontext *gVg;

/** Create the window and its nvg context, exit on failure */
void Tt_Window_Create(void);

/** Destroy the window and the nvg context */
void Tt_Window_Destroy(void);

#endif
