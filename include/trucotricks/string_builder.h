// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_STRING_BUILDER_H
#define TRUCOTRICKS_STRING_BUILDER_H

#include <stddef.h>

typedef struct Tt_String_Builder Tt_String_Builder;

struct Tt_String_Builder {
	size_t len, maxSize;
	char data[128];
};

void Tt_String_Builder_Append(Tt_String_Builder *sb, char c);

void Tt_String_Builder_Remove_Last_Character(Tt_String_Builder *sb);

void Tt_String_Builder_Clear(Tt_String_Builder *sb);

#endif
