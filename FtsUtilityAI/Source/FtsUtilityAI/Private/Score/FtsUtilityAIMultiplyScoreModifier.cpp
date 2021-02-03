// (c) MIT 2020 by FreetimeStudio


#include "Score/FtsUtilityAIMultiplyScoreModifier.h"

#include "FtsUtilityAIComponent.h"

UFtsUtilityAIMultiplyScoreModifier::UFtsUtilityAIMultiplyScoreModifier()
    : Super()
{
    SetUtilityId(FName("Multiply Score"));
}

float UFtsUtilityAIMultiplyScoreModifier::EvaluateScore_Implementation(float DeltaSeconds)
{
    auto FinalScore = 1.f;

    for(auto Score : ModifiedScores)
    {
        if(!IsValid(Score))
        {
            continue;
        }
        
        FinalScore *= Score->GetScore();
    }

    return FinalScore;
}
