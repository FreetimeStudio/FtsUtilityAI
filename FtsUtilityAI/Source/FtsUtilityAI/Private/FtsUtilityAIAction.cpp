// (c) MIT 2020 by FreetimeStudio


#include "FtsUtilityAIAction.h"
#include "Score/FtsUtilityAIScore.h"
#include "FtsUtilityAIBucket.h"
#include "FtsUtilityAIComponent.h"

UFtsUtilityAIAction::UFtsUtilityAIAction()
    : Super()
{
    bDrawDebug = false;
    DebugColor = FColor::Orange;
}

#if WITH_EDITOR

void UFtsUtilityAIAction::ClearInputs()
{
    Score = nullptr;
}

void UFtsUtilityAIAction::AddInput(UFtsUtilityAiObject* NewInput)
{
    Score = Cast<UFtsUtilityAIScore>(NewInput);
}

#endif

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
    return Score->GetScore();
}
