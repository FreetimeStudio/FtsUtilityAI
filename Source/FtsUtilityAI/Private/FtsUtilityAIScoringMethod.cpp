// (c) 2020 by FreetimeStudio


#include "FtsUtilityAIScoringMethod.h"

UFtsUtilityAIScoringMethod::UFtsUtilityAIScoringMethod()
    : Super()
{
    Weight = 1.f;
}

float UFtsUtilityAIScoringMethod::GetScore(UFtsUtilityAIAction* Action) const
{
    return EvaluateScore(Action) * Weight;
}

float UFtsUtilityAIScoringMethod::EvaluateScore_Implementation(UFtsUtilityAIAction* Action) const
{
    return 0.f;
}
