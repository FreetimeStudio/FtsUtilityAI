// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"

class IAssetTypeActions;
class FToolBarBuilder;
class FMenuBuilder;

class FFtsUtilityAIEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

	/**
	* Registers a single asset type action.
	*
	* @param Action The asset type action to register.
	*/
	void RegisterAssetTypeAction(TSharedRef<IAssetTypeActions> Action);

	/** Unregisters asset tool actions. */
	void UnregisterAssetTools();
	
	TSharedPtr<class FUICommandList> PluginCommands;
	TArray< TSharedPtr<IAssetTypeActions> > RegisteredAssetTypeActions;
};
