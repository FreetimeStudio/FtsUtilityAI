// (c) 2020 by FreetimeStudio


#include "ScoringMethods/FtsUtilityAIAverageScoringMethod.h"


float UFtsUtilityAIAverageScoringMethod::EvaluateScore_Implementation(UFtsUtilityAIAction* Action) const
{
    if(ScoringMethods.Num()==0)
    {
        return 0.f;
    }

    auto Score = 0.f;

    for(auto Method : ScoringMethods)
    {
        Score += Method->GetScore(Action);
    }

    return Score / ScoringMethods.Num();
}
