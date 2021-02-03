// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "Score/FtsUtilityAISingleScoreModifier.h"
#include "FtsUtilityAIWeightScoreModifier.generated.h"

/**
 * 
 */
UCLASS()
class FTSUTILITYAI_API UFtsUtilityAIWeightScoreModifier : public UFtsUtilityAISingleScoreModifier
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Utility AI")
	float Weight;

public:
	UFtsUtilityAIWeightScoreModifier();
	virtual float EvaluateScore_Implementation(float DeltaSeconds) override;


#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
#endif
};
