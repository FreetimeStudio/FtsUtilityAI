// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"

class UFtsUtilityAIAsset;
class IDetailsView;

/**
 * 
 */
class FtsUtilityAIAssetEditorToolkit
	: public FAssetEditorToolkit
	, public FEditorUndoClient
	, public FGCObject
{

private:

	/** The text asset being edited. */
	UFtsUtilityAIAsset* AiAsset;
	TSharedPtr<IDetailsView> DetailsWidget;

	TSharedPtr<FUICommandList> GraphEditorCommands;
	TSharedPtr<SGraphEditor> GraphEditor;

public:
	FtsUtilityAIAssetEditorToolkit();
	virtual ~FtsUtilityAIAssetEditorToolkit();

	void InitUtilityAiEditor(UFtsUtilityAIAsset* InAiAsset, const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost);

private:
	void CreateEdGraph();

	void OnSelectedNodesChanged(const TSet<UObject*>& NewSelection) const;

	FDelegateHandle OnPackageSavedDelegateHandle;
	void OnPackageSaved(const FString& PackageFileName, UObject* Outer) const;

	void CreateCommandList();

	void DeleteSelectedNodes();
	bool CanDeleteNodes();
	void OnRenameNode();
	bool CanRenameNodes() const;

	// FAssetEditorToolkit interface

	virtual FString GetDocumentationLink() const override;
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;

public:

	// IToolkit interface

	virtual FText GetBaseToolkitName() const override;
	virtual FName GetToolkitFName() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;

public:

	// FGCObject interface

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	
protected:

	// FEditorUndoClient interface

	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;

private:

	/** Callback for spawning the Properties tab. */
	TSharedRef<SDockTab> SpawnViewportTab(const FSpawnTabArgs& Args);
	FGraphAppearanceInfo GetGraphAppearance() const;
	TSharedRef<SDockTab> SpawnPropertyTab(const FSpawnTabArgs& Args);

};
