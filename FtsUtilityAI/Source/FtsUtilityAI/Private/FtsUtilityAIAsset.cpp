// (c) MIT 2020 by FreetimeStudio


#include "FtsUtilityAIAsset.h"

#include "FtsUtilityAIBucket.h"
#include "Score/FtsUtilityAIScore.h"

void UFtsUtilityAIAsset::Initialize(UFtsUtilityAIComponent* InAiComponent)
{
    for(auto Bucket : Buckets)
    {
        Bucket->Initialize(InAiComponent);
    }

    for(auto Score: Scores)
    {
        Score->Initialize(InAiComponent);
    }
}

void UFtsUtilityAIAsset::Uninitialize()
{
    for(auto Bucket : Buckets)
    {
        Bucket->Uninitialize();
    }

    for(auto Score: Scores)
    {
        Score->Uninitialize();
    }
}

#if WITH_EDITOR

void UFtsUtilityAIAsset::Clear()
{
    Scores.Empty();
    Buckets.Empty();
}

void UFtsUtilityAIAsset::AddScore(UFtsUtilityAIScore* NewScore)
{
    Scores.Add(NewScore);
}

void UFtsUtilityAIAsset::AddBucket(UFtsUtilityAIBucket* NewBucket)
{
    Buckets.Add(NewBucket);
}

#endif