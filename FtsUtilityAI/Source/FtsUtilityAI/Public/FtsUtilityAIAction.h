// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "FtsUtilityAiObject.h"
#include "UObject/NoExportTypes.h"
#include "FtsUtilityAIAction.generated.h"

class AAIController;
class UBlackboardComponent;
class UAIPerceptionComponent;
class UFtsUtilityAIComponent;
class UFtsUtilityAIBucket;
class UFtsUtilityAIScore;

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, BlueprintType, Blueprintable, CollapseCategories, meta = (ShowWorldContextPin))
class FTSUTILITYAI_API UFtsUtilityAIAction : public UFtsUtilityAiObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug", AdvancedDisplay)
	bool bDrawDebug;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug", AdvancedDisplay)
	FColor DebugColor;

	UPROPERTY(BlueprintReadWrite, Category="Action")
	UFtsUtilityAIScore* Score;
	
public:
	UFtsUtilityAIAction();

	/**
	 * @brief Evaluates this Action and returns a score   
	 * @return Score this Action has
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
	float ScoreAction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
	void BeginAction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
	void TickAction(float DeltaSeconds);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
	void EndAction();

#if WITH_EDITOR
	virtual void ClearInputs() override;
	virtual void AddInput(UFtsUtilityAiObject* NewInput) override;
#endif
};
