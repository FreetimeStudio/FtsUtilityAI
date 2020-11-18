// (c) 2020 by FreetimeStudio


#include "Score/FtsUtilityAIAverageScore.h"


void UFtsUtilityAIAverageScore::InitializeScore_Implementation(UFtsUtilityAIAction* Action)
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

float UFtsUtilityAIAverageScore::EvaluateScore_Implementation(UFtsUtilityAIAction* Action) const
{
    if(SubScores.Num()==0)
    {
        return 0.f;
    }

    auto ScoreSum = 0.f;

    for(auto Score : SubScores)
    {
        if(!IsValid(Score))
        {
            continue;
        }
        
        ScoreSum += Score->GetScore(Action);
    }

    return ScoreSum / SubScores.Num();
}
