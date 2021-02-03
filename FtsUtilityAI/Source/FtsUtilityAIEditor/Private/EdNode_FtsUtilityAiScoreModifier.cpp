// (c) MIT 2020 by FreetimeStudio

#include "EdNode_FtsUtilityAiScoreModifier.h"
#include "Score/FtsUtilityAIScore.h"

#define LOCTEXT_NAMESPACE "EdNode_FtsUtilityAiScoreModifier"

void UEdNode_FtsUtilityAiScoreModifier::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "MultipleNodes", FName("UtilityScore"), TEXT("Score"));
	CreatePin(EGPD_Output, "MultipleNodes", FName("UtilityScore"), TEXT("Result"));
}

FLinearColor UEdNode_FtsUtilityAiScoreModifier::GetNodeTitleColor() const
{
	return FLinearColor::Green;
}

#undef LOCTEXT_NAMESPACE
