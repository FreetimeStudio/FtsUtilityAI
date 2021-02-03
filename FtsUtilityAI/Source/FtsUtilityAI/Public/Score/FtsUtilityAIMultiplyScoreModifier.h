// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "FtsUtilityAIMultiScoreModifier.h"
#include "FtsUtilityAIMultiplyScoreModifier.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Multiply"))
class FTSUTILITYAI_API UFtsUtilityAIMultiplyScoreModifier : public UFtsUtilityAIMultiScoreModifier
{
	GENERATED_BODY()


public:

	UFtsUtilityAIMultiplyScoreModifier();
	virtual float EvaluateScore_Implementation(float DeltaSeconds) override;
};
