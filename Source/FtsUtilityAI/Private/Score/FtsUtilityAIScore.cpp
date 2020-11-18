// (c) 2020 by FreetimeStudio


#include "Score/FtsUtilityAIScore.h"

UFtsUtilityAIScore::UFtsUtilityAIScore()
    : Super()
{
    Weight = 1.f;
}

float UFtsUtilityAIScore::GetScore(UFtsUtilityAIAction* Action) const
{
    return EvaluateScore(Action) * Weight;
}

float UFtsUtilityAIScore::EvaluateScore_Implementation(UFtsUtilityAIAction* Action) const
{
    return 0.f;
}