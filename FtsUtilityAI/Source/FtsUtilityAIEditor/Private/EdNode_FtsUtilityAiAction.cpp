// (c) MIT 2020 by FreetimeStudio

#include "EdNode_FtsUtilityAiAction.h"
#include "Score/FtsUtilityAIScore.h"

#define LOCTEXT_NAMESPACE "EdNode_FtsUtilityAiAction"

UFtsUtilityAIScore* UEdNode_FtsUtilityAiAction::GetAiScore() const
{
	return Cast<UFtsUtilityAIScore>(GetUtilityObject());
}

void UEdNode_FtsUtilityAiAction::SetAiScore(UFtsUtilityAIScore* InAiScore)
{
	SetUtilityObject(InAiScore);
}

void UEdNode_FtsUtilityAiAction::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "MultipleNodes", FName("UtilityScore"), TEXT("Score"));
	CreatePin(EGPD_Output, "MultipleNodes", FName("UtilityAction"), TEXT("Action"));
}

FLinearColor UEdNode_FtsUtilityAiAction::GetNodeTitleColor() const
{
	return FLinearColor::Red;
}

#undef LOCTEXT_NAMESPACE
