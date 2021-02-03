// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "FtsUtilityAIMultiScoreModifier.h"
#include "FtsUtilityAIAverageScoreModifier.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Average"))
class FTSUTILITYAI_API UFtsUtilityAIAverageScoreModifier : public UFtsUtilityAIMultiScoreModifier
{
	GENERATED_BODY()

public:

	UFtsUtilityAIAverageScoreModifier();
	virtual float EvaluateScore_Implementation(float DeltaSeconds) override;
};
