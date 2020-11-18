// (c) 2020 by FreetimeStudio


#include "Score/FtsUtilityAIMultiplyScore.h"

void UFtsUtilityAIMultiplyScore::InitializeScore_Implementation(UFtsUtilityAIAction* Action)
{
    Super::InitializeScore_Implementation(Action);

    for(auto Score : SubScores)
    {
        if (IsValid(Score))
        {
            Score->InitializeScore(Action);
        }
    }
}

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
