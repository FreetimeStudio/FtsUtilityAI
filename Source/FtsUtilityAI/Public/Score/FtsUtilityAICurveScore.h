// (c) 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "FtsUtilityAIScore.h"
#include "FtsUtilityAICurveScore.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Curved Weight"))
class FTSUTILITYAI_API UFtsUtilityAICurveScore : public UFtsUtilityAIScore
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Bucket")
	UFtsUtilityAIScore* ModifiedScore;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Scoring", AdvancedDisplay)
	FRuntimeFloatCurve WeightCurve;

public:

	UFtsUtilityAICurveScore();
	
	virtual float EvaluateScore_Implementation(UFtsUtilityAIAction* Action) const override;
};

