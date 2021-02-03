// (c) MIT 2020 by FreetimeStudio
#pragma once

#include "CoreMinimal.h"

#include "FtsUtilityAIAsset.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph_FtsUtilityAiAsset.generated.h"

class UGenericGraph;
class UGenericGraphNode;
class UGenericGraphEdge;
class UEdNode_GenericGraphNode;
class UEdNode_GenericGraphEdge;

UCLASS()
class UEdGraph_FtsUtilityAiAsset : public UEdGraph
{
	GENERATED_BODY()

public:
	UEdGraph_FtsUtilityAiAsset();
	virtual ~UEdGraph_FtsUtilityAiAsset();

	virtual void RebuildAiAsset();

	UFtsUtilityAIAsset* GetAiAsset() const;

	virtual bool Modify(bool bAlwaysMarkDirty = true) override;

protected:
	void Clear();
};
