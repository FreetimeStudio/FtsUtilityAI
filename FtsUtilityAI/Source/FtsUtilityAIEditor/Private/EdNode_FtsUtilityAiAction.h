// (c) MIT 2020 by FreetimeStudio
#pragma once

#include "EdNode_FtsUtilityAiObject.h"
#include "EdNode_FtsUtilityAiAction.generated.h"

class UFtsUtilityAIScore;
class SEdNode_FtsUtilityAiAction;

UCLASS(MinimalAPI)
class UEdNode_FtsUtilityAiAction : public UEdNode_FtsUtilityAiObject
{
	GENERATED_BODY()

public:
	UFtsUtilityAIScore* GetAiScore() const;
	void SetAiScore(UFtsUtilityAIScore* InAiScore);
	
	SEdNode_FtsUtilityAiAction* SEdNode;

	virtual void AllocateDefaultPins() override;


	virtual FLinearColor GetNodeTitleColor() const override;
};
