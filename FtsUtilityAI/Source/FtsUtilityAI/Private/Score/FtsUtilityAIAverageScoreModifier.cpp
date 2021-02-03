// (c) MIT 2020 by FreetimeStudio


#include "Score/FtsUtilityAIAverageScoreModifier.h"

#include "FtsUtilityAIComponent.h"


UFtsUtilityAIAverageScoreModifier::UFtsUtilityAIAverageScoreModifier()
    : Super()
{
    SetUtilityId(FName("Average"));
}

float UFtsUtilityAIAverageScoreModifier::EvaluateScore_Implementation(float DeltaSeconds)
{
    if(ModifiedScores.Num()==0)
    {
        return 0.f;
    }

    auto ScoreSum = 0.f;

    for(auto Score : ModifiedScores)
    {
        if(!IsValid(Score))
        {
            continue;
        }
        
        ScoreSum += Score->GetScore();
    }

    return ScoreSum / ModifiedScores.Num();
}
