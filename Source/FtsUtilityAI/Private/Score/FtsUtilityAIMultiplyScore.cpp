// (c) 2020 by FreetimeStudio


#include "Score/FtsUtilityAIMultiplyScore.h"

#include "FtsUtilityAIComponent.h"

void UFtsUtilityAIMultiplyScore::InitializeScore_Implementation()
{
    Super::InitializeScore_Implementation();

    for(auto ScoreId : SubScoresConfig)
    {
        auto Score = GetUtilityAiComponent()->GetScoreById(ScoreId);
        SubScores.Add(Score);
    }
}

float UFtsUtilityAIMultiplyScore::EvaluateScore_Implementation(float DeltaSeconds)
{
    auto FinalScore = 1.f;

    for(auto Score : SubScores)
    {
        if(!IsValid(Score))
        {
            continue;
        }
        
        FinalScore *= Score->GetScore();
    }

    return FinalScore;
}
