// (c) MIT 2020 by FreetimeStudio

#include "EdNode_FtsUtilityAiBucket.h"
#include "Score/FtsUtilityAIScore.h"

#define LOCTEXT_NAMESPACE "EdNode_FtsUtilityAiBucket"

UFtsUtilityAIScore* UEdNode_FtsUtilityAiBucket::GetAiScore() const
{
	return Cast<UFtsUtilityAIScore>(GetUtilityObject());
}

void UEdNode_FtsUtilityAiBucket::SetAiScore(UFtsUtilityAIScore* InAiScore)
{
	SetUtilityObject(InAiScore);
}

void UEdNode_FtsUtilityAiBucket::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "MultipleNodes", FName("UtilityAction"), TEXT("Actions"));
}

FLinearColor UEdNode_FtsUtilityAiBucket::GetNodeTitleColor() const
{
	return FLinearColor::Blue;
}

#undef LOCTEXT_NAMESPACE
