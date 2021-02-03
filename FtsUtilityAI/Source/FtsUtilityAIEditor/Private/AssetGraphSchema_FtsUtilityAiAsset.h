// (c) MIT 2020 by FreetimeStudio
#pragma once

#include "CoreMinimal.h"

#include "EdNode_FtsUtilityAiObject.h"
#include "AssetGraphSchema_FtsUtilityAiAsset.generated.h"

class UEdNode_FtsUtilityAiScore;
class UAutoLayoutStrategy;


/** Add new score node action */
USTRUCT()
struct FAssetSchemaAction_FtsUtilityAiAsset_NewNode : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

public:
	FAssetSchemaAction_FtsUtilityAiAsset_NewNode(): NodeTemplate(nullptr) {}

	FAssetSchemaAction_FtsUtilityAiAsset_NewNode(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping), NodeTemplate(nullptr) {}

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	UEdNode_FtsUtilityAiObject* NodeTemplate;
};

UCLASS(MinimalAPI)
class UAssetGraphSchema_FtsUtilityAiAsset : public UEdGraphSchema
{
	GENERATED_BODY()

public:
	virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override;

 	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;

 	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;

 	virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;
};

