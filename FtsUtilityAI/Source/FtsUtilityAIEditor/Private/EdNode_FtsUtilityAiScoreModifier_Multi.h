// (c) MIT 2020 by FreetimeStudio
#pragma once

#include "EdNode_FtsUtilityAiScore.h"
#include "EdNode_FtsUtilityAiScoreModifier_Multi.generated.h"

class UFtsUtilityAIScore;

UCLASS(MinimalAPI)
class UEdNode_FtsUtilityAiScoreModifier_Multi : public UEdNode_FtsUtilityAiScore
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
	virtual FLinearColor GetNodeTitleColor() const override;
};
