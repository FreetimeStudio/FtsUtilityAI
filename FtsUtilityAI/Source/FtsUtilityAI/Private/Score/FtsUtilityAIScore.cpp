// (c) 2020 by FreetimeStudio


#include "Score/FtsUtilityAIScore.h"
#include "FtsUtilityAIComponent.h"

UFtsUtilityAIScore::UFtsUtilityAIScore()
    : Super()
{
    Weight = 1.f;
    CachedScore = 0.f;
}

void UFtsUtilityAIScore::UpdateScore(float DeltaSeconds)
{
    CachedScore = EvaluateScore(DeltaSeconds);
}

float UFtsUtilityAIScore::GetScore() const
{
    return CachedScore;
}

UFtsUtilityAIComponent* UFtsUtilityAIScore::GetUtilityAiComponent() const
{
    return GetTypedOuter<UFtsUtilityAIComponent>();
}

void UFtsUtilityAIScore::InitializeScore_Implementation()
{
}

float UFtsUtilityAIScore::EvaluateScore_Implementation(float DeltaSeconds)
{
    return 0.f;
}
