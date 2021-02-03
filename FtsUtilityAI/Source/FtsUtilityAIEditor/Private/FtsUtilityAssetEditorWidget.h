// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "Widgets/SCompoundWidget.h"

class UFtsUtilityAIAsset;
class SConstraintCanvas;

/**
 * 
 */
class SFtsUtilityAssetEditorWidget : public SCompoundWidget
{
private:
	
	SLATE_BEGIN_ARGS(SFtsUtilityAssetEditorWidget){}
  
	SLATE_ARGUMENT(UFtsUtilityAIAsset*, AiAsset)

    SLATE_END_ARGS()

private:
	UFtsUtilityAIAsset* AiAsset;
	TSharedPtr<SConstraintCanvas> CanvasPanel;

	
public:
	void Construct(const FArguments& InArgs);
	FGraphAppearanceInfo GetGraphAppearance() const;
};
