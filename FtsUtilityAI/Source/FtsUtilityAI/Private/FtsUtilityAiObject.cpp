// BIONICLE and the BIONICLE logo are trademarks and property of The LEGO Company


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
