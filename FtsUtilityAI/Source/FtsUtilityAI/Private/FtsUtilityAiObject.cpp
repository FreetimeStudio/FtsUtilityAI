// (c) MIT 2020 by FreetimeStudio


#include "FtsUtilityAiObject.h"

UFtsUtilityAiObject::UFtsUtilityAiObject()
    : Super()
{
    UtilityId = NAME_None;
}

void UFtsUtilityAiObject::SetUtilityId(const FName& NewId)
{
    UtilityId = NewId;
}

FName UFtsUtilityAiObject::GetUtilityId() const
{
    return UtilityId;
}

UFtsUtilityAIComponent* UFtsUtilityAiObject::GetUtilityComponent() const
{
    return AiComponent;
}

void UFtsUtilityAiObject::Initialize_Implementation(UFtsUtilityAIComponent* InAiComponent)
{
    AiComponent = InAiComponent;
}

void UFtsUtilityAiObject::Uninitialize_Implementation()
{
}

#if WITH_EDITOR

FText UFtsUtilityAiObject::GetNodeTitle() const
{
    return FText::FromName(UtilityId);
}

void UFtsUtilityAiObject::ClearInputs()
{
}

void UFtsUtilityAiObject::AddInput(UFtsUtilityAiObject* NewInput)
{
}

#endif
