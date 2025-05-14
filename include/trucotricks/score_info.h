// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_SCORE_INFO_H
#define TRUCOTRICKS_SCORE_INFO_H

typedef struct Tt_Score_Info Tt_Score_Info;

struct Tt_Score_Info {
	float playTime;
	float worstResponseTime;
	float lastResponseTime;
	float bestResponseTime;
	float averageResponseTime;
	int correctGuesses;
	int score;
};

void Tt_Score_Info_Reset(Tt_Score_Info *scoreInfo);

void Tt_Score_Info_Increase_Score(Tt_Score_Info *scoreInfo);

void Tt_Score_Info_Increase_Time(Tt_Score_Info *scoreInfo, double time);

#endif
