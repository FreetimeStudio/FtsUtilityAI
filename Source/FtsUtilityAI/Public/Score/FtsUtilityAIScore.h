// (c) 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"

#include "FtsUtilityAIAction.h"
#include "UObject/NoExportTypes.h"
#include "FtsUtilityAIScore.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, BlueprintType, Blueprintable, CollapseCategories, meta = (ShowWorldContextPin))
class FTSUTILITYAI_API UFtsUtilityAIScore : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Scoring")
	float Weight;

public:

	UFtsUtilityAIScore();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Scoring")
	virtual float GetScore(UFtsUtilityAIAction* Action) const;

	UFUNCTION(BlueprintNativeEvent, Category="Scoring")
    void InitializeScore(UFtsUtilityAIAction* Action);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category="Scoring")
	float EvaluateScore(UFtsUtilityAIAction* Action) const;
	
};
