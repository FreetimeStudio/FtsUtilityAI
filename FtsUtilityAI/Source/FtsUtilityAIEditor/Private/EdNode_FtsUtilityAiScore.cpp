// (c) MIT 2020 by FreetimeStudio

#include "EdNode_FtsUtilityAiScore.h"
#include "Score/FtsUtilityAIScore.h"

#define LOCTEXT_NAMESPACE "EdNode_FtsUtilityAiScore"

UFtsUtilityAIScore* UEdNode_FtsUtilityAiScore::GetAiScore() const
{
	return Cast<UFtsUtilityAIScore>(GetUtilityObject());
}

void UEdNode_FtsUtilityAiScore::SetAiScore(UFtsUtilityAIScore* InAiScore)
{
	SetUtilityObject(InAiScore);
}

void UEdNode_FtsUtilityAiScore::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, "MultipleNodes", FName("UtilityScore"), TEXT("Score"));
}

FLinearColor UEdNode_FtsUtilityAiScore::GetNodeTitleColor() const
{
	return FLinearColor::Green;
}

#undef LOCTEXT_NAMESPACE
