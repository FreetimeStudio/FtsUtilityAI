// (c) 2020 by FreetimeStudio


#include "FtsUtilityAIAction.h"

#include "FtsUtilityAIBucket.h"

UFtsUtilityAIAction::UFtsUtilityAIAction()
    : Super()
{
    Weight = 1.f;
    bDrawDebug = false;
    DebugColor = FColor::Orange;
    ActionName = NAME_None;
}

void UFtsUtilityAIAction::SetActionName(const FName& NewActionName)
{
    ActionName = NewActionName;
}

FName UFtsUtilityAIAction::GetActionName() const
{
    return ActionName;
}

UFtsUtilityAIBucket* UFtsUtilityAIAction::GetUtilityBucket() const
{
    return GetTypedOuter<UFtsUtilityAIBucket>();
}

UFtsUtilityAIComponent* UFtsUtilityAIAction::GetUtilityComponent() const
{
    return GetUtilityBucket()->GetUtilityComponent();
}

AAIController* UFtsUtilityAIAction::GetAIController() const
{
    return GetUtilityBucket()->GetAIController();
}

APawn* UFtsUtilityAIAction::GetPawn() const
{
    return GetUtilityBucket()->GetPawn();
}

UBlackboardComponent* UFtsUtilityAIAction::GetBlackboard() const
{
    return GetUtilityBucket()->GetBlackboard();
}

UAIPerceptionComponent* UFtsUtilityAIAction::GetPerception() const
{
    return GetUtilityBucket()->GetPerception();
}

void UFtsUtilityAIAction::UninitializeAction_Implementation()
{
}

void UFtsUtilityAIAction::EndAction_Implementation()
{
}

void UFtsUtilityAIAction::TickAction_Implementation(float DeltaSeconds)
{
}

void UFtsUtilityAIAction::BeginAction_Implementation()
{
}

float UFtsUtilityAIAction::ScoreAction_Implementation()
{
    return Weight;
}

void UFtsUtilityAIAction::InitializeAction_Implementation()
{
}
