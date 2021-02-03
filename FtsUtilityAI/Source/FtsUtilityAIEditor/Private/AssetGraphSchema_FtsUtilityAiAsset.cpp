// (c) MIT 2020 by FreetimeStudio

#include "AssetGraphSchema_FtsUtilityAiAsset.h"
#include "ToolMenus.h"
#include "EdNode_FtsUtilityAiAction.h"
#include "EdNode_FtsUtilityAiBucket.h"
#include "EdNode_FtsUtilityAiScore.h"
#include "EdNode_FtsUtilityAiScoreModifier_Multi.h"
#include "EdNode_FtsUtilityAiScoreModifier_Single.h"
#include "FtsUtilityAIAsset.h"
#include "FtsUtilityAIBucket.h"
#include "Score/FtsUtilityAIMultiScoreModifier.h"
#include "Score/FtsUtilityAIScore.h"
#include "Score/FtsUtilityAISingleScoreModifier.h"

#define LOCTEXT_NAMESPACE "AssetSchema_UtilityAiGraph"

UEdGraphNode* FAssetSchemaAction_FtsUtilityAiAsset_NewNode::PerformAction(UEdGraph* ParentGraph,
	UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
		UEdGraphNode* ResultNode = nullptr;
	
		if (NodeTemplate != nullptr)
		{
			const FScopedTransaction Transaction(LOCTEXT("UtilityAiGraphNewNode", "Utility AI New Node"));
			ParentGraph->Modify();
			if (FromPin != nullptr)
				FromPin->Modify();
	
			NodeTemplate->Rename(nullptr, ParentGraph);
			ParentGraph->AddNode(NodeTemplate, true, bSelectNewNode);
	
			NodeTemplate->CreateNewGuid();
			NodeTemplate->PostPlacedNewNode();
			NodeTemplate->AllocateDefaultPins();
			NodeTemplate->AutowireNewNode(FromPin);
	
			NodeTemplate->NodePosX = Location.X;
			NodeTemplate->NodePosY = Location.Y;
	
			NodeTemplate->UtilityObject->SetFlags(RF_Transactional);
			NodeTemplate->SetFlags(RF_Transactional);
	
			ResultNode = NodeTemplate;
		}
	
		return ResultNode;
}

void FAssetSchemaAction_FtsUtilityAiAsset_NewNode::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);
	Collector.AddReferencedObject(NodeTemplate);
}

EGraphType UAssetGraphSchema_FtsUtilityAiAsset::GetGraphType(const UEdGraph* TestEdGraph) const
{
	return GT_StateMachine;
}

void UAssetGraphSchema_FtsUtilityAiAsset::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	UFtsUtilityAIAsset* AiAsset = CastChecked<UFtsUtilityAIAsset>(ContextMenuBuilder.CurrentGraph->GetOuter());

	const bool bNoParent = (ContextMenuBuilder.FromPin == NULL);

	const auto ScoreCategoryText = LOCTEXT("AiScoreActionAiScore", "Score");
	const auto ActionCategoryText = LOCTEXT("AiScoreActionAiAction", "Action");
	const auto BucketCategoryText = LOCTEXT("AiScoreActionAiBucket", "Bucket");
	const FText AddToolTip = LOCTEXT("NewNodeTooltip", "Add node here");

	//Iterate through all loaded class objects
	for (TObjectIterator<UClass> Itr; Itr; ++Itr)
	{
		//Ignore generated class thingies (honestly no idea why they exist, but they come up) 
		if (Itr->GetName().StartsWith("REINST") || Itr->GetName().StartsWith("SKEL"))
		{
			continue;
		}

		//Sanitize the class name
		//TODO: Find out a way to get the bp display name
		FString Title = Itr->GetName();
		Title.RemoveFromEnd("_C");
		FText Desc = FText::FromString(Title);

		//Sort utility AI classes into categories and create context actions

		//AI Scores
		if (Itr->IsChildOf(UFtsUtilityAIScore::StaticClass()) && !Itr->HasAnyClassFlags(CLASS_Abstract))
		{
			TSharedPtr<FAssetSchemaAction_FtsUtilityAiAsset_NewNode> NewNodeAction(new FAssetSchemaAction_FtsUtilityAiAsset_NewNode(ScoreCategoryText, Desc, AddToolTip, 0));

			if (Itr->IsChildOf(UFtsUtilityAIMultiScoreModifier::StaticClass()))
			{
				NewNodeAction->NodeTemplate = NewObject<UEdNode_FtsUtilityAiScoreModifier_Multi>(ContextMenuBuilder.OwnerOfTemporaries);
			}
			else if (Itr->IsChildOf(UFtsUtilityAISingleScoreModifier::StaticClass()))
			{
				NewNodeAction->NodeTemplate = NewObject<UEdNode_FtsUtilityAiScoreModifier_Single>(ContextMenuBuilder.OwnerOfTemporaries);
			}
			else
			{
				NewNodeAction->NodeTemplate = NewObject<UEdNode_FtsUtilityAiScore>(ContextMenuBuilder.OwnerOfTemporaries);
			}

			NewNodeAction->NodeTemplate->UtilityObject = NewObject<UFtsUtilityAiObject>(NewNodeAction->NodeTemplate, *Itr);
			NewNodeAction->NodeTemplate->UtilityObject->Rename(nullptr, AiAsset);
			ContextMenuBuilder.AddAction(NewNodeAction);
		}

		//AI Actions
		if (Itr->IsChildOf(UFtsUtilityAIAction::StaticClass()) && !Itr->HasAnyClassFlags(CLASS_Abstract))
		{
			// FText Desc = FText::FromString(Itr->GetDefaultObject()->GetName());// FText::FromString("Test Node Name");// Graph->NodeType.GetDefaultObject()->ContextMenuName;
			TSharedPtr<FAssetSchemaAction_FtsUtilityAiAsset_NewNode> NewNodeAction(new FAssetSchemaAction_FtsUtilityAiAsset_NewNode(ActionCategoryText, Desc, AddToolTip, 0));
			NewNodeAction->NodeTemplate = NewObject<UEdNode_FtsUtilityAiAction>(ContextMenuBuilder.OwnerOfTemporaries);
			NewNodeAction->NodeTemplate->UtilityObject = NewObject<UFtsUtilityAiObject>(NewNodeAction->NodeTemplate, *Itr);
			//NewNodeAction->NodeTemplate->AiScore->Graph = Graph;
			ContextMenuBuilder.AddAction(NewNodeAction);
		}

		//AI Buckets
		if (Itr->IsChildOf(UFtsUtilityAIBucket::StaticClass()) && !Itr->HasAnyClassFlags(CLASS_Abstract))
		{
			// FText Desc = FText::FromString(Itr->GetDefaultObject()->GetName());// FText::FromString("Test Node Name");// Graph->NodeType.GetDefaultObject()->ContextMenuName;
			TSharedPtr<FAssetSchemaAction_FtsUtilityAiAsset_NewNode> NewNodeAction(new FAssetSchemaAction_FtsUtilityAiAsset_NewNode(BucketCategoryText, Desc, AddToolTip, 0));
			NewNodeAction->NodeTemplate = NewObject<UEdNode_FtsUtilityAiBucket>(ContextMenuBuilder.OwnerOfTemporaries);
			NewNodeAction->NodeTemplate->UtilityObject = NewObject<UFtsUtilityAiObject>(NewNodeAction->NodeTemplate, *Itr);
			//NewNodeAction->NodeTemplate->AiScore->Graph = Graph;
			ContextMenuBuilder.AddAction(NewNodeAction);
		}
	}	
}

const FPinConnectionResponse UAssetGraphSchema_FtsUtilityAiAsset::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	// Make sure the pins are not on the same node
	if (A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorSameNode", "Both are on the same node"));
	}
	
	// Compare the directions
	if ((A->Direction == EGPD_Input) && (B->Direction == EGPD_Input))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorInput", "Can't connect input node to input node"));
	}
	else if ((A->Direction == EGPD_Output) && (B->Direction == EGPD_Output))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorOutput", "Can't connect output node to output node"));
	}
	
	if(A->PinType.PinSubCategory != B->PinType.PinSubCategory)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorType", "Incompatible nodes"));
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, LOCTEXT("PinConnect", "Connect nodes"));
}

FLinearColor UAssetGraphSchema_FtsUtilityAiAsset::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return FColor::White;
}

#undef LOCTEXT_NAMESPACE
