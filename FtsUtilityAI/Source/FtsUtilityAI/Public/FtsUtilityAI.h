// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FFtsUtilityAIModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
