// (c) MIT 2020 by FreetimeStudio
#include "EdNode_FtsUtilityAiObject.h"
#include "FtsUtilityAiObject.h"

#define LOCTEXT_NAMESPACE "EdNode_UtilityAiObject"

UEdNode_FtsUtilityAiObject::UEdNode_FtsUtilityAiObject()
{
	bCanRenameNode = true;
}

UEdNode_FtsUtilityAiObject::~UEdNode_FtsUtilityAiObject()
{

}

UFtsUtilityAiObject* UEdNode_FtsUtilityAiObject::GetUtilityObject() const
{
	return UtilityObject;
}

void UEdNode_FtsUtilityAiObject::SetUtilityObject(UFtsUtilityAiObject* InUtilityObject)
{
	this->UtilityObject = InUtilityObject;
}

void UEdNode_FtsUtilityAiObject::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "MultipleNodes", FName(), TEXT("In"));
	CreatePin(EGPD_Output, "MultipleNodes", FName(), TEXT("Out"));
}

FText UEdNode_FtsUtilityAiObject::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (UtilityObject == nullptr)
	{
		return Super::GetNodeTitle(TitleType);
	}
	else
	{
		return UtilityObject->GetNodeTitle();
	}
}

void UEdNode_FtsUtilityAiObject::PrepareForCopying()
{
	UtilityObject->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
}


#undef LOCTEXT_NAMESPACE
