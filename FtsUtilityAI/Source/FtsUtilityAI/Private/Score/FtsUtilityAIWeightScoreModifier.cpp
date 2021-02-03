// (c) MIT 2020 by FreetimeStudio


#include "Score/FtsUtilityAIWeightScoreModifier.h"

#define LOCTEXT_NAMESPACE "FtsUtilityAIWeightScoreModifier"

UFtsUtilityAIWeightScoreModifier::UFtsUtilityAIWeightScoreModifier()
    : Super()
{
    Weight = 1.f;
}

float UFtsUtilityAIWeightScoreModifier::EvaluateScore_Implementation(float DeltaSeconds)
{
    return ModifiedScore->GetScore() * Weight;
}

#if WITH_EDITOR

FText UFtsUtilityAIWeightScoreModifier::GetNodeTitle() const
{
     return FText::Format(LOCTEXT("TitleFormat", "x {0}"), Weight);
}

#endif

#undef LOCTEXT_NAMESPACE
