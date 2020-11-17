// (c) 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"

#include "FtsUtilityAIAction.h"
#include "UObject/NoExportTypes.h"
#include "FtsUtilityAIScoringMethod.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, BlueprintType, Blueprintable, CollapseCategories, meta = (ShowWorldContextPin))
class FTSUTILITYAI_API UFtsUtilityAIScoringMethod : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Scoring")
	float Weight;

public:

	UFtsUtilityAIScoringMethod();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Scoring")
	virtual float GetScore(UFtsUtilityAIAction* Action) const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category="Scoring")
	float EvaluateScore(UFtsUtilityAIAction* Action) const;
	
};
