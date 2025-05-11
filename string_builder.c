// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <string.h>
#include <trucotricks/util.h>
#include <trucotricks/string_builder.h>

void Tt_String_Builder_Append(Tt_String_Builder *sb, char c)
{
	if (sb->len + 1 >= Tt_Length(sb->data) || sb->len + 1 > sb->maxSize)
		return;

	sb->data[sb->len] = c;
	sb->len += 1;
	sb->data[sb->len] = '\0';
}

void Tt_String_Builder_Remove_Last_Character(Tt_String_Builder *sb)
{
	if (sb->len > 0) {
		sb->data[sb->len-1] = '\0';
		sb->len -= 1;
	}
}

void Tt_String_Builder_Clear(Tt_String_Builder *sb)
{
	sb->len = 0;
	memset(sb->data, 0, sizeof(sb->data));
}
