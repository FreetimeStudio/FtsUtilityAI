// (c) 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "FtsUtilityAIScoringMethod.h"
#include "FtsUtilityAICurveScoringMethod.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Curved Weight"))
class FTSUTILITYAI_API UFtsUtilityAICurveScoringMethod : public UFtsUtilityAIScoringMethod
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Bucket")
	UFtsUtilityAIScoringMethod* ModifiedScore;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Scoring", AdvancedDisplay)
	FRuntimeFloatCurve WeightCurve;

public:

	UFtsUtilityAICurveScoringMethod();
	
	virtual float EvaluateScore_Implementation(UFtsUtilityAIAction* Action) const override;
};

