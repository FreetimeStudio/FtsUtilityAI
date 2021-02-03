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
class FTSUTILITYAI_API UFtsUtilityAIScore : public UFtsUtilityAiObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Utility AI")
	float Weight;

	UPROPERTY(BlueprintReadOnly, Category="Utility AI")
	float CachedScore;
public:

	UFtsUtilityAIScore();

	virtual void UpdateScore(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Utility AI")
	virtual float GetScore() const;

	UFUNCTION(BlueprintNativeEvent, Category="Utility AI")
    void InitializeScore();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category="Utility AI")
	float EvaluateScore(float DeltaSeconds);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Utility AI")
    virtual UFtsUtilityAIComponent* GetUtilityAiComponent() const;
};
