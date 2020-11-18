// (c) 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"

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
class FTSUTILITYAI_API UFtsUtilityAIAction : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Action")
	FName ActionName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Action")
    float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Action")
	bool bDrawDebug;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Action")
	FColor DebugColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Action")
	TArray<UFtsUtilityAIScore*> Scores;
	
public:
	UFtsUtilityAIAction();

	void SetActionName(const FName& NewActionName);
	FName GetActionName() const;

	UFUNCTION(BlueprintCallable, Category="Action")
    virtual UFtsUtilityAIBucket* GetUtilityBucket() const;

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
	
	/**
	 * @brief Initializes Action after controller BeginPlay
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
    void InitializeAction();

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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
	void UninitializeAction();

};
