// (c) 2020 by FreetimeStudio


#include "Score/FtsUtilityAIAverageScore.h"

#include "FtsUtilityAIComponent.h"


void UFtsUtilityAIAverageScore::InitializeScore_Implementation()
{
    Super::InitializeScore_Implementation();

    for(auto ScoreId : SubScoresConfig)
    {
        auto Score = GetUtilityAiComponent()->GetScoreById(ScoreId);
        SubScores.Add(Score);
    }
}

float UFtsUtilityAIAverageScore::EvaluateScore_Implementation(float DeltaSeconds)
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
        
        ScoreSum += Score->GetScore();
    }

    return ScoreSum / SubScores.Num();
}
