// (c) MIT 2020 by FreetimeStudio

#include "EdGraph_FtsUtilityAiAsset.h"

#include "EdNode_FtsUtilityAiObject.h"
#include "FtsUtilityAIBucket.h"
#include "FtsUtilityAiObject.h"
#include "Score/FtsUtilityAIScore.h"

UEdGraph_FtsUtilityAiAsset::UEdGraph_FtsUtilityAiAsset()
{

}

UEdGraph_FtsUtilityAiAsset::~UEdGraph_FtsUtilityAiAsset()
{

}

void UEdGraph_FtsUtilityAiAsset::RebuildAiAsset()
{
	UFtsUtilityAIAsset* Asset = GetAiAsset();

	Clear();

	for (int i = 0; i < Nodes.Num(); ++i)
	{
		if (UEdNode_FtsUtilityAiObject* EdNode = Cast<UEdNode_FtsUtilityAiObject>(Nodes[i]))
		{
			UFtsUtilityAiObject* UtilityObject = EdNode->UtilityObject;
			UtilityObject->ClearInputs();

			if(auto Score = Cast<UFtsUtilityAIScore>(UtilityObject))
			{
				Asset->AddScore(Score);
				Score->Rename(nullptr, Asset);
			}

			if(auto Bucket = Cast<UFtsUtilityAIBucket>(UtilityObject))
			{
				Asset->AddBucket(Bucket);
				Bucket->Rename(nullptr, Asset);
			}

			for (int PinIdx = 0; PinIdx < EdNode->Pins.Num(); ++PinIdx)
			{
				UEdGraphPin* Pin = EdNode->Pins[PinIdx];

				if (Pin->Direction != EEdGraphPinDirection::EGPD_Input)
					continue;

				for (int LinkToIdx = 0; LinkToIdx < Pin->LinkedTo.Num(); ++LinkToIdx)
				{
					UFtsUtilityAiObject* InputObject = nullptr;
					if (UEdNode_FtsUtilityAiObject* EdNode_Input = Cast<UEdNode_FtsUtilityAiObject>(Pin->LinkedTo[LinkToIdx]->GetOwningNode()))
					{
						InputObject = EdNode_Input->UtilityObject;
					}

					if (InputObject != nullptr)
					{
						UtilityObject->AddInput(InputObject);
					}
				}
			}
		}
	}
}

UFtsUtilityAIAsset* UEdGraph_FtsUtilityAiAsset::GetAiAsset() const
{
	return CastChecked<UFtsUtilityAIAsset>(GetOuter());
}

bool UEdGraph_FtsUtilityAiAsset::Modify(bool bAlwaysMarkDirty /*= true*/)
{
	bool Rtn = Super::Modify(bAlwaysMarkDirty);

	GetAiAsset()->Modify();

	for (int32 i = 0; i < Nodes.Num(); ++i)
	{
		Nodes[i]->Modify();
	}

	return Rtn;
}

void UEdGraph_FtsUtilityAiAsset::Clear()
{
	UFtsUtilityAIAsset* Asset = GetAiAsset();

	Asset->Clear();
	
	for (int i = 0; i < Nodes.Num(); ++i)
	{
		if (UEdNode_FtsUtilityAiObject* EdNode = Cast<UEdNode_FtsUtilityAiObject>(Nodes[i]))
		{
			UFtsUtilityAiObject* UtilityObject = EdNode->UtilityObject;
			UtilityObject->ClearInputs();
		}
	}
}
