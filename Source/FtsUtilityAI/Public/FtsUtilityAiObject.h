// BIONICLE and the BIONICLE logo are trademarks and property of The LEGO Company

#pragma once

#include "CoreMinimal.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Utility AI")
	FName UtilityId;

public:
	UFtsUtilityAiObject();
	void SetUtilityId(const FName& NewId);
	FName GetUtilityId() const;
};
