// (c) MIT 2020 by FreetimeStudio

#include "EdNode_FtsUtilityAiScoreModifier_Single.h"
#include "Score/FtsUtilityAIScore.h"

#define LOCTEXT_NAMESPACE "EdNode_FtsUtilityAiScoreModifier_Single"

void UEdNode_FtsUtilityAiScoreModifier_Single::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "SingleNode", FName("UtilityScore"), TEXT("Score"));
	CreatePin(EGPD_Output, "MultipleNodes", FName("UtilityScore"), TEXT("Result"));
}

FLinearColor UEdNode_FtsUtilityAiScoreModifier_Single::GetNodeTitleColor() const
{
	return FLinearColor::Green;
}

#undef LOCTEXT_NAMESPACE
