// (c) MIT 2020 by FreetimeStudio


#include "FtsUtilityAIAssetEditorToolkit.h"

#include "AssetGraphSchema_FtsUtilityAiAsset.h"
#include "EdGraph_FtsUtilityAiAsset.h"
#include "EditorReimportHandler.h"
#include "FtsUtilityAIAsset.h"
#include "FtsUtilityAssetEditorWidget.h"
#include "Framework/Commands/GenericCommands.h"
#include "Kismet2/BlueprintEditorUtils.h"

#define LOCTEXT_NAMESPACE "FtsUtilityAIAssetEditorToolkit"

static const FName TextAssetEditorAppIdentifier("TextAssetEditorApp");
static const FName ViewportTabId("Viewport");
static const FName PropertiesTabId("Properties");


FtsUtilityAIAssetEditorToolkit::FtsUtilityAIAssetEditorToolkit()
{
    AiAsset = nullptr;
	OnPackageSavedDelegateHandle = UPackage::PackageSavedEvent.AddRaw(this, &FtsUtilityAIAssetEditorToolkit::OnPackageSaved);
}

FtsUtilityAIAssetEditorToolkit::~FtsUtilityAIAssetEditorToolkit()
{
    FReimportManager::Instance()->OnPreReimport().RemoveAll(this);
    FReimportManager::Instance()->OnPostReimport().RemoveAll(this);

	UPackage::PackageSavedEvent.Remove(OnPackageSavedDelegateHandle);

    GEditor->UnregisterForUndo(this);
}

void FtsUtilityAIAssetEditorToolkit::InitUtilityAiEditor(UFtsUtilityAIAsset* InAiAsset, const EToolkitMode::Type InMode,
    const TSharedPtr<IToolkitHost>& InToolkitHost)
{
    AiAsset = InAiAsset;
    CreateEdGraph();

    // Support undo/redo
    AiAsset->SetFlags(RF_Transactional);
    GEditor->RegisterForUndo(this);

    FDetailsViewArgs Args;
    Args.bHideSelectionTip = true;
    // Args.NotifyHook = this;
    
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    DetailsWidget = PropertyModule.CreateDetailView(Args);
    DetailsWidget->SetObject(AiAsset);
    

    // create tab layout
    const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("Standalone_UtilityAiAssetEditor")
        ->AddArea
        (
            FTabManager::NewPrimaryArea()
                ->SetOrientation(Orient_Horizontal)
                ->Split
                (
                    FTabManager::NewSplitter()
                        ->SetOrientation(Orient_Vertical)
                        ->SetSizeCoefficient(0.66f)
                        ->Split
                        (
                            FTabManager::NewStack()
                                ->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
                                ->SetHideTabWell(true)
                                ->SetSizeCoefficient(0.1f)
								
                        )
                        ->Split
                        (
					FTabManager::NewSplitter()
					        ->SetOrientation(Orient_Vertical)
                            -> Split(
                                FTabManager::NewStack()
                                    ->AddTab(ViewportTabId, ETabState::OpenedTab)
                                    ->SetHideTabWell(true)
                                    ->SetSizeCoefficient(0.7f)
                            )
                            -> Split(
                                FTabManager::NewStack()
            						->AddTab(PropertiesTabId, ETabState::OpenedTab)
                                    ->SetHideTabWell(true)
                                    ->SetSizeCoefficient(0.3f)
                            )
                        )
                )
        );

    FAssetEditorToolkit::InitAssetEditor(
        InMode,
        InToolkitHost,
        TextAssetEditorAppIdentifier,
        Layout,
        true,
        true,
        AiAsset);

    RegenerateMenusAndToolbars();
}

void FtsUtilityAIAssetEditorToolkit::CreateEdGraph()
{
    if (AiAsset->EdGraph == nullptr)
    {
        AiAsset->EdGraph = CastChecked<UEdGraph_FtsUtilityAiAsset>(FBlueprintEditorUtils::CreateNewGraph(AiAsset, NAME_None, UEdGraph_FtsUtilityAiAsset::StaticClass(), UAssetGraphSchema_FtsUtilityAiAsset::StaticClass()));
        AiAsset->EdGraph->bAllowDeletion = false;

        // Give the schema a chance to fill out any required nodes (like the results node)
        const UEdGraphSchema* Schema = AiAsset->EdGraph->GetSchema();
        Schema->CreateDefaultNodesForGraph(*AiAsset->EdGraph);
    }
}

void FtsUtilityAIAssetEditorToolkit::OnSelectedNodesChanged(const TSet<UObject*>& NewSelection) const
{
    if (NewSelection.Num() == 0) 
    {
        DetailsWidget->SetObject(AiAsset);
    }
    else
    {
        DetailsWidget->SetObjects(NewSelection.Array());
    }
}

void FtsUtilityAIAssetEditorToolkit::OnPackageSaved(const FString& PackageFileName, UObject* Outer) const
{
	if (AiAsset == nullptr)
	{
		return;
	}

	UEdGraph_FtsUtilityAiAsset* EdGraph = Cast<UEdGraph_FtsUtilityAiAsset>(AiAsset->EdGraph);
	check(EdGraph != nullptr);

	EdGraph->RebuildAiAsset();
}

void FtsUtilityAIAssetEditorToolkit::CreateCommandList()
{
	if (GraphEditorCommands.IsValid())
	{
		return;
	}

	GraphEditorCommands = MakeShareable(new FUICommandList);
    
	GraphEditorCommands->MapAction(FGenericCommands::Get().Delete,
		FExecuteAction::CreateRaw(this, &FtsUtilityAIAssetEditorToolkit::DeleteSelectedNodes),
		FCanExecuteAction::CreateRaw(this, &FtsUtilityAIAssetEditorToolkit::CanDeleteNodes)
	);
    
	GraphEditorCommands->MapAction(FGenericCommands::Get().Rename,
		FExecuteAction::CreateSP(this, &FtsUtilityAIAssetEditorToolkit::OnRenameNode),
		FCanExecuteAction::CreateSP(this, &FtsUtilityAIAssetEditorToolkit::CanRenameNodes)
	);
}

void FtsUtilityAIAssetEditorToolkit::DeleteSelectedNodes()
{
	if (!GraphEditor.IsValid())
	{
		return;
	}

	const FScopedTransaction Transaction(FGenericCommands::Get().Delete->GetDescription());

	GraphEditor->GetCurrentGraph()->Modify();

	const FGraphPanelSelectionSet SelectedNodes = GraphEditor->GetSelectedNodes();
	GraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator NodeIt(SelectedNodes); NodeIt; ++NodeIt)
	{
		UEdGraphNode* EdNode = Cast<UEdGraphNode>(*NodeIt);
		if (EdNode == nullptr || !EdNode->CanUserDeleteNode())
			continue;;

		UEdNode_FtsUtilityAiObject* AiNode = Cast<UEdNode_FtsUtilityAiObject>(EdNode);
		AiNode->Modify();

		const UEdGraphSchema* Schema = AiNode->GetSchema();
		if (Schema != nullptr)
		{
			Schema->BreakNodeLinks(*AiNode);
		}

		AiNode->DestroyNode();
	}
}

bool FtsUtilityAIAssetEditorToolkit::CanDeleteNodes()
{
    return true;
}

void FtsUtilityAIAssetEditorToolkit::OnRenameNode()
{
}

bool FtsUtilityAIAssetEditorToolkit::CanRenameNodes() const
{
    return true;
}

FString FtsUtilityAIAssetEditorToolkit::GetDocumentationLink() const
{
    return FString(TEXT("https://github.com/FreetimeStudio/FtsUtilityAI"));
}

void FtsUtilityAIAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    WorkspaceMenuCategory = TabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_UtilityAiEditor", "Utility AI Asset Editor"));
    auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

    FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

    InTabManager->RegisterTabSpawner(ViewportTabId, FOnSpawnTab::CreateSP(this, &FtsUtilityAIAssetEditorToolkit::SpawnViewportTab))
        .SetDisplayName(LOCTEXT("UtilityAiEditorTabName", "Utility AI Editor"))
        .SetGroup(WorkspaceMenuCategoryRef)
        .SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));

    InTabManager->RegisterTabSpawner(PropertiesTabId, FOnSpawnTab::CreateSP(this, &FtsUtilityAIAssetEditorToolkit::SpawnPropertyTab))
        .SetDisplayName(LOCTEXT("DetailsTab", "Properties"))
        .SetGroup(WorkspaceMenuCategoryRef)
        .SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));
    
}

void FtsUtilityAIAssetEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

    InTabManager->UnregisterTabSpawner(ViewportTabId);
    InTabManager->UnregisterTabSpawner(PropertiesTabId);
}

FText FtsUtilityAIAssetEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Utility AI Asset Editor");
}

FName FtsUtilityAIAssetEditorToolkit::GetToolkitFName() const
{
	return FName("UtilityAiAssetEditor");
}

FLinearColor FtsUtilityAIAssetEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

FString FtsUtilityAIAssetEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "UtilityAiAsset ").ToString();
}

void FtsUtilityAIAssetEditorToolkit::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(AiAsset);
}

void FtsUtilityAIAssetEditorToolkit::PostUndo(bool bSuccess)
{
}

void FtsUtilityAIAssetEditorToolkit::PostRedo(bool bSuccess)
{
	PostUndo(bSuccess);
}

TSharedRef<SDockTab> FtsUtilityAIAssetEditorToolkit::SpawnViewportTab(const FSpawnTabArgs& Args)
{
    SGraphEditor::FGraphEditorEvents InEvents;
    InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FtsUtilityAIAssetEditorToolkit::OnSelectedNodesChanged);

    CreateCommandList();

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
    
    return SNew(SDockTab)
    .TabRole(ETabRole::PanelTab)
    [
        SAssignNew(GraphEditor, SGraphEditor)
            .AdditionalCommands(GraphEditorCommands)
            .Appearance(this, &FtsUtilityAIAssetEditorToolkit::GetGraphAppearance)
            .TitleBar(TitleBarWidget)
            .GraphToEdit(AiAsset->EdGraph)
            .GraphEvents(InEvents)
    ];
}

FGraphAppearanceInfo FtsUtilityAIAssetEditorToolkit::GetGraphAppearance() const
{
    FGraphAppearanceInfo AppearanceInfo;
    AppearanceInfo.CornerText = LOCTEXT("AppearanceCornerText", "Utility AI");
    return AppearanceInfo;
}


TSharedRef<SDockTab> FtsUtilityAIAssetEditorToolkit::SpawnPropertyTab(const FSpawnTabArgs& Args)
{
    return SNew(SDockTab)
        .Icon(FEditorStyle::GetBrush("LevelEditor.Tabs.Details"))
        .Label(LOCTEXT("PropertiesTabLabel", "Properties"))
        [
            DetailsWidget.ToSharedRef()
        ];
}

#undef LOCTEXT_NAMESPACE
