// (c) 2020 by FreetimeStudio


#include "ScoringMethods/FtsUtilityAIMultiplyScoringMethod.h"

float UFtsUtilityAIMultiplyScoringMethod::EvaluateScore_Implementation(UFtsUtilityAIAction* Action) const
{
    auto Score = 1.f;

    for(auto Method : ScoringMethods)
    {
        Score *= Method->GetScore(Action);
    }

    return Score;
}
