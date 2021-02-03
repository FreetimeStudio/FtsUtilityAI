// (c) MIT 2020 by FreetimeStudio


#include "FtsUtilityAssetEditorWidget.h"


#include "FtsUtilityAIAsset.h"
#include "GraphEditor.h"
#include "Runtime/Slate/Public/Widgets/Layout/SConstraintCanvas.h"

#define LOCTEXT_NAMESPACE "SFtsUtilityAssetEditorWidget"

void SFtsUtilityAssetEditorWidget::Construct(const FArguments& InArgs)
{
    AiAsset = InArgs._AiAsset;

	// Make title bar
	TSharedRef<SWidget> TitleBarWidget = 
        SNew(SBorder)
        .BorderImage( FEditorStyle::GetBrush( TEXT("Graph.TitleBackground") ) )
        .HAlign(HAlign_Fill)
        [
            SNew(SHorizontalBox)
            +SHorizontalBox::Slot()
            .HAlign(HAlign_Center)
            .FillWidth(1.f)
            [
                SNew(STextBlock)
                .Text(LOCTEXT("UtilityAiGraphLabel", "Utility AI"))
                .TextStyle( FEditorStyle::Get(), TEXT("GraphBreadcrumbButtonText") )
            ]
        ];
	
    ChildSlot
    [
        SNew(SBox)
        [
            SNew(SOverlay)

            +SOverlay::Slot()
            [
				SNew(SGraphEditor)
					.Appearance(this, &SFtsUtilityAssetEditorWidget::GetGraphAppearance)
					.TitleBar(TitleBarWidget)
					.GraphToEdit(AiAsset->EdGraph)
            ]
        ]
    ];
}

FGraphAppearanceInfo SFtsUtilityAssetEditorWidget::GetGraphAppearance() const
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("AppearanceCornerText", "Utility AI");
	return AppearanceInfo;
}

#undef LOCTEXT_NAMESPACE
