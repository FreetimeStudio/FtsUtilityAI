// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"

#include "FtsUtilityAIAsset.h"
#include "Components/ActorComponent.h"
#include "FtsUtilityAIComponent.generated.h"

class UFtsUtilityAIScore;
class UFtsUtilityAIAction;
class UFtsUtilityAIBucket;
class AAIController;
class UBlackboardComponent;
class UAIPerceptionComponent;
class UFtsUtilityAIComponent;

UCLASS( ClassGroup=AI, meta=(BlueprintSpawnableComponent), HideCategories=(Collision) )
class FTSUTILITYAI_API UFtsUtilityAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFtsUtilityAIComponent();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI")
	TAssetPtr<UFtsUtilityAIAsset> UtilityAiAsset;

	UPROPERTY(BlueprintReadOnly, Category="AI")
	UFtsUtilityAIAsset* UtilityAiInstance;

	UPROPERTY(BlueprintReadOnly, Instanced, Category="AI")
	UFtsUtilityAIAction* CurrentAction;

	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category="Utility AI", meta=(DeterminesOutputType="Class"))
	void ChooseNextAction(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category="Utility AI")
    virtual AAIController* GetAIController() const;

	UFUNCTION(BlueprintCallable, Category="Utility AI")
    virtual APawn* GetPawn() const;

	UFUNCTION(BlueprintCallable, Category="Utility AI")
    virtual UBlackboardComponent* GetBlackboard() const;

	UFUNCTION(BlueprintCallable, Category="Utility AI")
    virtual UAIPerceptionComponent* GetPerception() const;
};
