// (c) MIT 2020 by FreetimeStudio
#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "EdNode_FtsUtilityAiObject.generated.h"

class UFtsUtilityAiObject;
class SEdNode_FtsUtilityAiObject;

UCLASS(MinimalAPI)
class UEdNode_FtsUtilityAiObject : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UEdNode_FtsUtilityAiObject();
	virtual ~UEdNode_FtsUtilityAiObject();

	UPROPERTY(VisibleAnywhere, Instanced, Category = "Utility AI")
	UFtsUtilityAiObject* UtilityObject;

	UFtsUtilityAiObject* GetUtilityObject() const;
	void SetUtilityObject(UFtsUtilityAiObject* InUtilityObject);
	
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PrepareForCopying() override;
};
