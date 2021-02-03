// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "Score/FtsUtilityAIScoreModifier.h"
#include "FtsUtilityAIMultiScoreModifier.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class FTSUTILITYAI_API UFtsUtilityAIMultiScoreModifier : public UFtsUtilityAIScoreModifier
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Utility AI")
	TArray<UFtsUtilityAIScore*> ModifiedScores;

public:

#if WITH_EDITOR
	virtual void ClearInputs() override;
	virtual void AddInput(UFtsUtilityAiObject* NewInput) override;
#endif
};
