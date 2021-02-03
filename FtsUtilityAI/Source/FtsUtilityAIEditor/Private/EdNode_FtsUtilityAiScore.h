// (c) MIT 2020 by FreetimeStudio
#pragma once

#include "EdNode_FtsUtilityAiObject.h"
#include "EdNode_FtsUtilityAiScore.generated.h"

class UFtsUtilityAIScore;
class SEdNode_FtsUtilityAiScore;

UCLASS(MinimalAPI)
class UEdNode_FtsUtilityAiScore : public UEdNode_FtsUtilityAiObject
{
	GENERATED_BODY()

public:
	UFtsUtilityAIScore* GetAiScore() const;
	void SetAiScore(UFtsUtilityAIScore* InAiScore);
	
	virtual void AllocateDefaultPins() override;

	virtual FLinearColor GetNodeTitleColor() const override;
};
