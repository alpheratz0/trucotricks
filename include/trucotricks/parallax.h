// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_PARALLAX_H
#define TRUCOTRICKS_PARALLAX_H

#include <trucotricks/resources.h>
#include <stdbool.h>

typedef struct Tt_Parallax Tt_Parallax;

struct Tt_Parallax {
	// Parallax position & size
	float x, y, w, h;
	size_t nTextures;
	double speeds[12];
	float deltaX[12];
	Tt_Texture textures[12];
};

void Tt_Parallax_Update(Tt_Parallax *parallax);

#endif
