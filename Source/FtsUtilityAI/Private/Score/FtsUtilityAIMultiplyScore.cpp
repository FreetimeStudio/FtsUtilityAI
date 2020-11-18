// (c) 2020 by FreetimeStudio


#include "Score/FtsUtilityAIMultiplyScore.h"

float UFtsUtilityAIMultiplyScore::EvaluateScore_Implementation(UFtsUtilityAIAction* Action) const
{
    auto FinalScore = 1.f;

    for(auto Score : SubScores)
    {
        if(!IsValid(Score))
        {
            continue;
        }
        
        FinalScore *= Score->GetScore(Action);
    }

    return FinalScore;
}
