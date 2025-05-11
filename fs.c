// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <trucotricks/fs.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#if defined(_WIN32)
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

long Tt_FS_Get_Size(const char *path)
{
	FILE *fp = fopen(path, "rb");
	if (!fp) return -1;
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fclose(fp);
	return size;
}

char *Tt_FS_Get_Content(const char *path)
{
	FILE *fp = fopen(path, "rb");
	if (!fp) return NULL;
	fseek(fp, 0, SEEK_END);
	long dataLen = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *data = malloc((size_t)dataLen);
	if (!data) {
		fclose(fp);
		return NULL;
	}
	fread(data, 1, dataLen, fp);
	fclose(fp);
	return data;
}

const char *Tt_FS_Get_Filename(const char *path)
{
	const char *ret = path;
	for (const char *p = path; *p; ++p) {
#if defined(_WIN32)
		if (*p == '/' || *p == '\\')
#else
		if (*p == '/')
#endif
			ret = p + 1;
	}
	return ret;
}
