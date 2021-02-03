// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "Score/FtsUtilityAIScore.h"
#include "FtsUtilityAIStaticScore.generated.h"

/**
 * 
 */
UCLASS()
class FTSUTILITYAI_API UFtsUtilityAIStaticScore : public UFtsUtilityAIScore
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Utility AI")
	float Score;


public:
	UFtsUtilityAIStaticScore();
	virtual float EvaluateScore_Implementation(float DeltaSeconds) override;

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
#endif
};
