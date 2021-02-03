// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"

#include "FtsUtilityAiObject.h"
#include "UObject/NoExportTypes.h"
#include "FtsUtilityAIBucket.generated.h"

class AAIController;
class UBlackboardComponent;
class UAIPerceptionComponent;
class UFtsUtilityAIComponent;
class UFtsUtilityAIBucket;
class UFtsUtilityAIAction;

/**
 * 
 */
UCLASS(EditInlineNew, BlueprintType, Blueprintable, CollapseCategories)
class FTSUTILITYAI_API UFtsUtilityAIBucket : public UFtsUtilityAiObject
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bucket")
    float Weight;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Bucket")
    TArray<UFtsUtilityAIAction*> Actions;

    UPROPERTY(BlueprintReadOnly, Category="Bucket")
    float CachedScore;

public:

    UFtsUtilityAIBucket();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
    float ScoreBucket();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
    float GetCachedScore() const;

    UFtsUtilityAIAction* ScoreHighestAction(float& OutScore);

    virtual void Initialize_Implementation(UFtsUtilityAIComponent* InAiComponent) override;
    virtual void Uninitialize_Implementation() override;
    
#if WITH_EDITOR
    virtual FText GetNodeTitle() const override;
    virtual void ClearInputs() override;
    virtual void AddInput(UFtsUtilityAiObject* NewInput) override;
#endif
};
