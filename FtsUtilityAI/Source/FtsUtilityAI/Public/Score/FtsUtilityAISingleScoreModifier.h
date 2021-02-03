// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "Score/FtsUtilityAIScoreModifier.h"
#include "FtsUtilityAISingleScoreModifier.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class FTSUTILITYAI_API UFtsUtilityAISingleScoreModifier : public UFtsUtilityAIScoreModifier
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Utility AI")
	UFtsUtilityAIScore* ModifiedScore;

public:
#if WITH_EDITOR
	virtual void ClearInputs() override;
	virtual void AddInput(UFtsUtilityAiObject* NewInput) override;
#endif
};
