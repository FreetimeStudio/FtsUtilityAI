// (c) 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "FtsUtilityAIScore.h"
#include "FtsUtilityAIMultiplyScore.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Multiply"))
class FTSUTILITYAI_API UFtsUtilityAIMultiplyScore : public UFtsUtilityAIScore
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Bucket")
	TArray<UFtsUtilityAIScore*> SubScores;

public:

	virtual void InitializeScore_Implementation(UFtsUtilityAIAction* Action) override;
	virtual float EvaluateScore_Implementation(UFtsUtilityAIAction* Action) const override;
};
