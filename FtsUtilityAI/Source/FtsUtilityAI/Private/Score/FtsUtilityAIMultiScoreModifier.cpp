// (c) MIT 2020 by FreetimeStudio


#include "Score/FtsUtilityAIMultiScoreModifier.h"

#if WITH_EDITOR

void UFtsUtilityAIMultiScoreModifier::ClearInputs()
{
    ModifiedScores.Empty();
}

void UFtsUtilityAIMultiScoreModifier::AddInput(UFtsUtilityAiObject* NewInput)
{
    auto Score = Cast<UFtsUtilityAIScore>(NewInput);
    check(Score);
    ModifiedScores.Add(Score);
}

#endif