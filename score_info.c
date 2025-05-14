// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <trucotricks/score_info.h>
#include <trucotricks/util.h>

void Tt_Score_Info_Reset(Tt_Score_Info *scoreInfo)
{
	scoreInfo->playTime = 0.0f;
	scoreInfo->worstResponseTime = 0.0f;
	scoreInfo->lastResponseTime = 0.0f;
	scoreInfo->bestResponseTime = 0.0f;
	scoreInfo->averageResponseTime = 0.0f;
	scoreInfo->score = 0;
	scoreInfo->correctGuesses = 0;
}

void Tt_Score_Info_Increase_Score(Tt_Score_Info *scoreInfo)
{
	float tookToRespond = scoreInfo->playTime - scoreInfo->lastResponseTime;

	scoreInfo->lastResponseTime = scoreInfo->playTime;
	scoreInfo->worstResponseTime = scoreInfo->score == 0 ? tookToRespond : Tt_Max(tookToRespond, scoreInfo->worstResponseTime);
	scoreInfo->bestResponseTime = scoreInfo->score == 0 ? tookToRespond : Tt_Min(tookToRespond, scoreInfo->bestResponseTime);
	scoreInfo->correctGuesses += 1;
	scoreInfo->score += 1;

	if (tookToRespond < 0.5f) {
		scoreInfo->score += 3;
	} else if (tookToRespond < 0.8f) {
		scoreInfo->score += 2;
	} else if (tookToRespond < 1.0f) {
		scoreInfo->score += 1;
	}

	scoreInfo->averageResponseTime = scoreInfo->playTime / scoreInfo->correctGuesses;
}

void Tt_Score_Info_Increase_Time(Tt_Score_Info *scoreInfo, double time)
{
	scoreInfo->playTime += time;
}
