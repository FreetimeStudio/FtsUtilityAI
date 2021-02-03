// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"

#include "FtsUtilityAIComponent.h"
#include "UObject/NoExportTypes.h"
#include "FtsUtilityAiObject.generated.h"

/**
 * Base object class for all Utility AI objects.
 * Provides simple handling for ids.
 */
UCLASS(Abstract)
class FTSUTILITYAI_API UFtsUtilityAiObject : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category="Utility AI")
	UFtsUtilityAIComponent* AiComponent;

	//TODO map to rename node
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Utility AI")
	FName UtilityId;

public:
	UFtsUtilityAiObject();
	void SetUtilityId(const FName& NewId);
	FName GetUtilityId() const;

	UFUNCTION(BlueprintCallable, Category="Utility AI")
    virtual UFtsUtilityAIComponent* GetUtilityComponent() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Utility AI")
    void Initialize(UFtsUtilityAIComponent* InAiComponent);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Utility AI")
	void Uninitialize();


#if WITH_EDITOR
	virtual FText GetNodeTitle() const;
	virtual void ClearInputs();
	virtual void AddInput(UFtsUtilityAiObject* NewInput);
#endif

	
};
