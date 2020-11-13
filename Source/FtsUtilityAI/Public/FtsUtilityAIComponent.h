// (c) 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FtsUtilityAIComponent.generated.h"

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
	TArray<UFtsUtilityAIBucket*> Buckets;

    UPROPERTY()
	UFtsUtilityAIAction* CurrentAction;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Action", meta=(DeterminesOutputType="Class"))
	void ChooseNextAction();

	UFUNCTION(BlueprintCallable, Category="Action", meta=(DeterminesOutputType="Class"))
    UFtsUtilityAIBucket* GetBucketByClass(TSubclassOf<UFtsUtilityAIBucket> BucketClass);

	UFUNCTION(BlueprintCallable, Category="Action", meta=(DeterminesOutputType="Class"))
    UFtsUtilityAIBucket* GetBucketByName(const FName& BucketName);

	UFUNCTION(BlueprintCallable, Category="Action", meta=(DeterminesOutputType="Class"))
    UFtsUtilityAIBucket* CreateBucket(TSubclassOf<UFtsUtilityAIBucket> Class, FName BucketName = NAME_None);
	
	UFUNCTION(BlueprintCallable, Category="Action", meta=(DeterminesOutputType="Class"))
    UFtsUtilityAIAction* GetActionByClass(TSubclassOf<UFtsUtilityAIAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category="Action", meta=(DeterminesOutputType="Class"))
    UFtsUtilityAIAction* GetActionByName(FName ActionName);

	UFUNCTION(BlueprintCallable, Category="Action", meta=(DeterminesOutputType="Class"))
    UFtsUtilityAIAction* CreateAction(FName BucketName, TSubclassOf<UFtsUtilityAIAction> Class, FName ActionName = NAME_None);
	
	UFUNCTION(BlueprintCallable, Category="Action")
    virtual AAIController* GetAIController() const;

	UFUNCTION(BlueprintCallable, Category="Action")
    virtual APawn* GetPawn() const;

	UFUNCTION(BlueprintCallable, Category="Action")
    virtual UBlackboardComponent* GetBlackboard() const;

	UFUNCTION(BlueprintCallable, Category="Action")
    virtual UAIPerceptionComponent* GetPerception() const;
		
};
