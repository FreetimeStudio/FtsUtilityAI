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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Utility AI")
	FName ModifiedScoreId;

	UPROPERTY(BlueprintReadWrite, Category="Utility AI")
	UFtsUtilityAIScore* ModifiedScore;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Utility AI", AdvancedDisplay)
	FRuntimeFloatCurve WeightCurve;

public:

	UFtsUtilityAICurveScore();

	virtual void InitializeScore_Implementation() override;
	virtual float EvaluateScore_Implementation(float DeltaSeconds) override;
};

