// (c) MIT 2020 by FreetimeStudio


#include "FtsUtilityAIAssetFactory.h"

#include "FtsUtilityAIAsset.h"

#define LOCTEXT_NAMESPACE "FtsUtilityAIPluginEditor" 

UFtsUtilityAIAssetFactory::UFtsUtilityAIAssetFactory()
{
    SupportedClass = UFtsUtilityAIAsset::StaticClass();
    bCreateNew = true;
    bEditAfterNew = true;
}

UObject* UFtsUtilityAIAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName,
                                                     EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UObject>(InParent, InClass, InName, Flags | RF_Transactional);
}

#undef LOCTEXT_NAMESPACE