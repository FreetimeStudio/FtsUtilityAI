// (c) MIT 2020 by FreetimeStudio


#include "AssetTypeActions_FtsUtilityAIAsset.h"


#include "AIModule.h"
#include "FtsUtilityAIAsset.h"
#include "FtsUtilityAIAssetEditorToolkit.h"

FText FAssetTypeActions_FtsUtilityAIAsset::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_FtsUtilityAIAsset", "Utility AI Asset");
}

FColor FAssetTypeActions_FtsUtilityAIAsset::GetTypeColor() const
{
	return FColor(149,70,255);
}

UClass* FAssetTypeActions_FtsUtilityAIAsset::GetSupportedClass() const
{
	return UFtsUtilityAIAsset::StaticClass(); 
}

void FAssetTypeActions_FtsUtilityAIAsset::OpenAssetEditor(const TArray<UObject*>& InObjects,
    TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric: EToolkitMode::Standalone;
	
	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UFtsUtilityAIAsset* Asset = Cast<UFtsUtilityAIAsset>(*ObjIt))
		{
			TSharedRef<FtsUtilityAIAssetEditorToolkit> EditorToolkit = MakeShareable(new FtsUtilityAIAssetEditorToolkit());
			EditorToolkit->InitUtilityAiEditor(Asset, Mode, EditWithinLevelEditor);
		}
	}
}

uint32 FAssetTypeActions_FtsUtilityAIAsset::GetCategories()
{
	IAIModule& AIModule = FModuleManager::LoadModuleChecked<IAIModule>("AIModule").Get();
	return AIModule.GetAIAssetCategoryBit();
}
