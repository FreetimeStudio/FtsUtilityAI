// (c) 2020 by FreetimeStudio

#include "FtsUtilityAIBucket.h"

#include "FtsUtilityAIAction.h"
#include "FtsUtilityAIComponent.h"

UFtsUtilityAIBucket::UFtsUtilityAIBucket()
    : Super()
{
    BucketName = NAME_None;
    Weight = 1.f;
    CachedScore = 0.f;
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

UFtsUtilityAIAction* UFtsUtilityAIBucket::GetActionByClass(TSubclassOf<UFtsUtilityAIAction> ActionClass)
{
    for(auto Action : Actions)
    {
        if(!IsValid(Action))
        {
            continue;
        }

        if(Action->IsA(ActionClass))
        {
            return Action;
        }
    }

    return nullptr;
}

UFtsUtilityAIAction* UFtsUtilityAIBucket::GetActionByName(FName ActionName)
{
    for(auto Action : Actions)
    {
        if(!IsValid(Action))
        {
            continue;
        }

        if(Action->GetActionName() == ActionName)
        {
            return Action;
        }
    }

    return nullptr;
}

UFtsUtilityAIAction* UFtsUtilityAIBucket::CreateAction(TSubclassOf<UFtsUtilityAIAction> Class, FName ActionName)
{
    auto Action = NewObject<UFtsUtilityAIAction>(this, Class, MakeUniqueObjectName(this, Class, ActionName));
    Action->SetActionName(ActionName);
    AddAction(Action);
    return Action;
}

void UFtsUtilityAIBucket::AddAction(UFtsUtilityAIAction* Action)
{
    Actions.Add(Action);
    Action->InitializeAction();
}

void UFtsUtilityAIBucket::RemoveAction(UFtsUtilityAIAction* Action)
{
    if(Actions.Remove(Action))
    {
        Action->UninitializeAction();
    }
}

float UFtsUtilityAIBucket::ScoreBucket_Implementation()
{
    CachedScore = Weight;
    return GetCachedScore();
}

void UFtsUtilityAIBucket::GetActions(TArray<UFtsUtilityAIAction*>& OutActions) const
{
    OutActions = Actions;
}

UFtsUtilityAIComponent* UFtsUtilityAIBucket::GetUtilityComponent() const
{
    return GetTypedOuter<UFtsUtilityAIComponent>();
}

AAIController* UFtsUtilityAIBucket::GetAIController() const
{
    return GetUtilityComponent()->GetAIController();
}

APawn* UFtsUtilityAIBucket::GetPawn() const
{
    return GetUtilityComponent()->GetPawn();
}

UBlackboardComponent* UFtsUtilityAIBucket::GetBlackboard() const
{
    return GetUtilityComponent()->GetBlackboard();
}

UAIPerceptionComponent* UFtsUtilityAIBucket::GetPerception() const
{
    return GetUtilityComponent()->GetPerception();
}

void UFtsUtilityAIBucket::SetBucketName(const FName& NewName)
{
    BucketName = NewName;
}

FName UFtsUtilityAIBucket::GetBucketName() const
{
    return BucketName;
}
