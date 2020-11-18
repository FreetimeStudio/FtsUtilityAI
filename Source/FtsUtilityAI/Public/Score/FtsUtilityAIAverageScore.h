// (c) 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "FtsUtilityAIScore.h"
#include "FtsUtilityAIAverageScore.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Average"))
class FTSUTILITYAI_API UFtsUtilityAIAverageScore : public UFtsUtilityAIScore
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Bucket")
	TArray<UFtsUtilityAIScore*> ScoringMethods;

public:
	virtual float EvaluateScore_Implementation(UFtsUtilityAIAction* Action) const override;
};
