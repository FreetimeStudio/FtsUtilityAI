// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FtsUtilityAIAsset.generated.h"

class UFtsUtilityAIComponent;
class UFtsUtilityAIScore;
class UFtsUtilityAIBucket;

/**
 * 
 */
UCLASS(BlueprintType)
class FTSUTILITYAI_API UFtsUtilityAIAsset : public UObject
{
	GENERATED_BODY()

	friend class UFtsUtilityAIComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	TArray<UFtsUtilityAIScore*> Scores;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	TArray<UFtsUtilityAIBucket*> Buckets;

public:

	void Initialize(UFtsUtilityAIComponent* InAiComponent);
    void Uninitialize();

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	class UEdGraph* EdGraph;

#endif

#if WITH_EDITOR
	void Clear();
	void AddScore(UFtsUtilityAIScore* NewScore);
	void AddBucket(UFtsUtilityAIBucket* NewBucket);
#endif
};
