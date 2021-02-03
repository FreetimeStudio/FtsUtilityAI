// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "FtsUtilityAIAssetFactory.generated.h"

/**
 * 
 */
UCLASS()
class UFtsUtilityAIAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	UFtsUtilityAIAssetFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
