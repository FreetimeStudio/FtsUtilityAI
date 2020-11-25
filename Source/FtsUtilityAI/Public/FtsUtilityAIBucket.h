// (c) 2020 by FreetimeStudio

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
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Bucket")
    TArray<UFtsUtilityAIAction*> Actions;

    UPROPERTY(BlueprintReadOnly, Category="Bucket")
    float CachedScore;

public:

    UFtsUtilityAIBucket();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
    void InitializeBucket();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
    float ScoreBucket();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
    float GetCachedScore() const;

    UFtsUtilityAIAction* ScoreHighestAction(float& OutScore);

    UFUNCTION(BlueprintCallable, Category="Action", meta=(DeterminesOutputType="Class"))
    UFtsUtilityAIAction* GetActionByClass(TSubclassOf<UFtsUtilityAIAction> ActionClass);

    UFUNCTION(BlueprintCallable, Category="Action", meta=(DeterminesOutputType="Class"))
    UFtsUtilityAIAction* GetActionByName(FName ActionName);

    UFUNCTION(BlueprintCallable, Category="Action", meta=(DeterminesOutputType="Class"))
    UFtsUtilityAIAction* CreateAction(TSubclassOf<UFtsUtilityAIAction> Class, FName ActionName = NAME_None);

    UFUNCTION(BlueprintCallable, Category="Action", meta=(DeterminesOutputType="Class"))
    void AddAction(UFtsUtilityAIAction* Action);

    UFUNCTION(BlueprintCallable, Category="Action", meta=(DeterminesOutputType="Class"))
    void RemoveAction(UFtsUtilityAIAction* Action);
    
    UFUNCTION(BlueprintCallable, Category="Action")
    void GetActions(TArray<UFtsUtilityAIAction*>& OutActions) const;
    
    UFUNCTION(BlueprintCallable, Category="Action")
    virtual UFtsUtilityAIComponent* GetUtilityComponent() const;
	
    UFUNCTION(BlueprintCallable, Category="Action")
    virtual AAIController* GetAIController() const;

    UFUNCTION(BlueprintCallable, Category="Action")
    virtual APawn* GetPawn() const;

    UFUNCTION(BlueprintCallable, Category="Action")
    virtual UBlackboardComponent* GetBlackboard() const;

    UFUNCTION(BlueprintCallable, Category="Action")
    virtual UAIPerceptionComponent* GetPerception() const;
};
