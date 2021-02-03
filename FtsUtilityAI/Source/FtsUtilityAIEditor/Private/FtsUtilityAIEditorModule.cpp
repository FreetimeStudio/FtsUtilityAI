// (c) MIT 2020 by FreetimeStudio

#include "FtsUtilityAIEditorModule.h"

#include "AssetToolsModule.h"
#include "AssetTypeActions_FtsUtilityAIAsset.h"
#include "FtsUtilityAIEditorStyle.h"
#include "FtsUtilityAIEditorCommands.h"
#include "IAssetTools.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName FtsUtilityAIEditorTabName("FtsUtilityAIEditor");

#define LOCTEXT_NAMESPACE "FFtsUtilityAIEditorModule"

void FFtsUtilityAIEditorModule::StartupModule()
{
	FFtsUtilityAIEditorStyle::Initialize();
	FFtsUtilityAIEditorStyle::ReloadTextures();

	FFtsUtilityAIEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	// Register asset type actions for custom utility AI asset
	RegisterAssetTypeAction(MakeShareable(new FAssetTypeActions_FtsUtilityAIAsset()));
}

void FFtsUtilityAIEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FFtsUtilityAIEditorStyle::Shutdown();

	FFtsUtilityAIEditorCommands::Unregister();

	// Unregister asset type actions for custom utility AI asset
	UnregisterAssetTools();
}

TSharedRef<SDockTab> FFtsUtilityAIEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FFtsUtilityAIEditorModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("FtsUtilityAIEditor.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FFtsUtilityAIEditorModule::RegisterAssetTypeAction(TSharedRef<IAssetTypeActions> Action)
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTools.RegisterAssetTypeActions(Action);
	RegisteredAssetTypeActions.Add(Action);
}

void FFtsUtilityAIEditorModule::UnregisterAssetTools()
{
	FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");

	if (AssetToolsModule != nullptr)
	{
		IAssetTools& AssetTools = AssetToolsModule->Get();

		for (auto Action : RegisteredAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(Action.ToSharedRef());
		}
	}
}

void FFtsUtilityAIEditorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(FtsUtilityAIEditorTabName);
}

void FFtsUtilityAIEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FFtsUtilityAIEditorCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FFtsUtilityAIEditorCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFtsUtilityAIEditorModule, FtsUtilityAIEditor)