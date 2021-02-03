// (c) MIT 2020 by FreetimeStudio
#pragma once

#include "EdNode_FtsUtilityAiObject.h"
#include "EdNode_FtsUtilityAiBucket.generated.h"

class UFtsUtilityAIScore;
class SEdNode_FtsUtilityAiBucket;

UCLASS(MinimalAPI)
class UEdNode_FtsUtilityAiBucket : public UEdNode_FtsUtilityAiObject
{
	GENERATED_BODY()

public:
	UFtsUtilityAIScore* GetAiScore() const;
	void SetAiScore(UFtsUtilityAIScore* InAiScore);
	
	SEdNode_FtsUtilityAiBucket* SEdNode;

	virtual void AllocateDefaultPins() override;

	virtual FLinearColor GetNodeTitleColor() const override;
};
