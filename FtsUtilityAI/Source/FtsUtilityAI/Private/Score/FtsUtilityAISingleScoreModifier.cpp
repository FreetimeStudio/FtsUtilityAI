// (c) MIT 2020 by FreetimeStudio


#include "Score/FtsUtilityAISingleScoreModifier.h"

#if WITH_EDITOR

void UFtsUtilityAISingleScoreModifier::ClearInputs()
{
    ModifiedScore = nullptr;
}

void UFtsUtilityAISingleScoreModifier::AddInput(UFtsUtilityAiObject* NewInput)
{
    ModifiedScore = Cast<UFtsUtilityAIScore>(NewInput);
}

#endif