// (c) 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FtsUtilityAIComponent.generated.h"

class UFtsUtilityAIScore;
class UFtsUtilityAIAction;
class UFtsUtilityAIBucket;
class AAIController;
class UBlackboardComponent;
class UAIPerceptionComponent;
class UFtsUtilityAIComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FTSUTILITYAI_API UFtsUtilityAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFtsUtilityAIComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="AI")
	TArray<UFtsUtilityAIScore*> Scores;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="AI")
	TArray<UFtsUtilityAIBucket*> Buckets;

	UPROPERTY(BlueprintReadOnly, Instanced, Category="AI")
	UFtsUtilityAIAction* CurrentAction;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Utility AI", meta=(DeterminesOutputType="Class"))
	void ChooseNextAction(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category="Utility AI", meta=(DeterminesOutputType="Class"))
    UFtsUtilityAIScore* GetScoreById(const FName& Id);
	
	UFUNCTION(BlueprintCallable, Category="Utility AI", meta=(DeterminesOutputType="Class"))
    UFtsUtilityAIBucket* GetBucketByClass(TSubclassOf<UFtsUtilityAIBucket> BucketClass);

	UFUNCTION(BlueprintCallable, Category="Utility AI", meta=(DeterminesOutputType="Class"))
    UFtsUtilityAIBucket* GetBucketByName(const FName& BucketName);

	UFUNCTION(BlueprintCallable, Category="Utility AI", meta=(DeterminesOutputType="Class"))
    UFtsUtilityAIBucket* CreateBucket(TSubclassOf<UFtsUtilityAIBucket> Class, FName BucketName = NAME_None);
	
	UFUNCTION(BlueprintCallable, Category="Utility AI", meta=(DeterminesOutputType="Class"))
    UFtsUtilityAIAction* GetActionByClass(TSubclassOf<UFtsUtilityAIAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category="Utility AI", meta=(DeterminesOutputType="Class"))
    UFtsUtilityAIAction* GetActionByName(FName ActionName);

	UFUNCTION(BlueprintCallable, Category="Utility AI", meta=(DeterminesOutputType="Class"))
    UFtsUtilityAIAction* CreateAction(FName BucketName, TSubclassOf<UFtsUtilityAIAction> Class, FName ActionName = NAME_None);
	
	UFUNCTION(BlueprintCallable, Category="Utility AI")
    virtual AAIController* GetAIController() const;

	UFUNCTION(BlueprintCallable, Category="Utility AI")
    virtual APawn* GetPawn() const;

	UFUNCTION(BlueprintCallable, Category="Utility AI")
    virtual UBlackboardComponent* GetBlackboard() const;

	UFUNCTION(BlueprintCallable, Category="Utility AI")
    virtual UAIPerceptionComponent* GetPerception() const;
		
};
