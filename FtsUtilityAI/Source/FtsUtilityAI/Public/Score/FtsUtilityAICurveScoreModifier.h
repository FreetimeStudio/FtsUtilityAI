// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "FtsUtilityAISingleScoreModifier.h"
#include "FtsUtilityAICurveScoreModifier.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Curved Weight"))
class FTSUTILITYAI_API UFtsUtilityAICurveScoreModifier : public UFtsUtilityAISingleScoreModifier
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Utility AI")
	FRuntimeFloatCurve WeightCurve;

public:

	UFtsUtilityAICurveScoreModifier();
	virtual float EvaluateScore_Implementation(float DeltaSeconds) override;
};

