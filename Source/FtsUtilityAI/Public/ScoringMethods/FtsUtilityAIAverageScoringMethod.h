// (c) 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "FtsUtilityAIScoringMethod.h"
#include "FtsUtilityAIAverageScoringMethod.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Average"))
class FTSUTILITYAI_API UFtsUtilityAIAverageScoringMethod : public UFtsUtilityAIScoringMethod
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Bucket")
	TArray<UFtsUtilityAIScoringMethod*> ScoringMethods;

public:
	virtual float EvaluateScore_Implementation(UFtsUtilityAIAction* Action) const override;
};
