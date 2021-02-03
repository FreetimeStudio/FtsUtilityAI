// (c) MIT 2020 by FreetimeStudio

#include "FtsUtilityAIBucket.h"

#include "FtsUtilityAIAction.h"
#include "FtsUtilityAIComponent.h"

#define LOCTEXT_NAMESPACE "UFtsUtilityAIBucket"

UFtsUtilityAIBucket::UFtsUtilityAIBucket()
    : Super()
{
    Weight = 1.f;
    CachedScore = 0.f;
    SetUtilityId(FName("Default"));
}

float UFtsUtilityAIBucket::GetCachedScore_Implementation() const
{
    return CachedScore;
}

UFtsUtilityAIAction* UFtsUtilityAIBucket::ScoreHighestAction(float& OutScore)
{
    // Score all actions and choose highest one
    float HighestScore = 0.f;
    UFtsUtilityAIAction* HighestAction = nullptr;

    for(auto Action : Actions)
    {
        if(!IsValid(Action))
        {
            continue;
        }
        
        const float Score = Action->ScoreAction();
        if(Score > HighestScore)
        {
            HighestAction = Action;
            HighestScore = Score;
        }
    }

    OutScore = HighestScore;
    return HighestAction;
}

float UFtsUtilityAIBucket::ScoreBucket_Implementation()
{
    CachedScore = Weight;
    return GetCachedScore();
}

void UFtsUtilityAIBucket::Initialize_Implementation(UFtsUtilityAIComponent* InAiComponent)
{
    Super::Initialize_Implementation(InAiComponent);
    
    for(auto Action : Actions)
    {
        if (IsValid(Action))
        {
            Action->Initialize(InAiComponent);
        }
    }
}

void UFtsUtilityAIBucket::Uninitialize_Implementation()
{
    Super::Uninitialize_Implementation();
    
    for(auto Action : Actions)
    {
        if (IsValid(Action))
        {
            Action->Uninitialize();
        }
    }
}

#if WITH_EDITOR

FText UFtsUtilityAIBucket::GetNodeTitle() const
{
    FFormatNamedArguments Args;
    Args.Add(TEXT("BucketName"), FText::FromName(GetUtilityId()));
    Args.Add(TEXT("Weight"), FText::AsNumber(Weight));
    return FText::Format(LOCTEXT("NodeTitle", "{BucketName} [{Weight} x]"), Args);
}

void UFtsUtilityAIBucket::ClearInputs()
{
    Actions.Empty();
}

void UFtsUtilityAIBucket::AddInput(UFtsUtilityAiObject* NewInput)
{
    const auto NewAction = Cast<UFtsUtilityAIAction>(NewInput);
    check(NewAction);
    NewAction->Rename(nullptr, this);
    Actions.Add(NewAction);
}

#endif

#undef LOCTEXT_NAMESPACE
