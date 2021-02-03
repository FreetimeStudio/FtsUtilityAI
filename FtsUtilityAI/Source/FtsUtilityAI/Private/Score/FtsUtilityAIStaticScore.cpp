// (c) MIT 2020 by FreetimeStudio


#include "Score/FtsUtilityAIStaticScore.h"

#define LOCTEXT_NAMESPACE "UFtsUtilityAIStaticScore"

UFtsUtilityAIStaticScore::UFtsUtilityAIStaticScore()
    : Super()
{
    Score = 1.f;
}

float UFtsUtilityAIStaticScore::EvaluateScore_Implementation(float DeltaSeconds)
{
    return Score;
}

#if WITH_EDITOR

FText UFtsUtilityAIStaticScore::GetNodeTitle() const
{
    return FText::Format(LOCTEXT("TitleFormat", "{0}"), Score);
}

#endif

#undef LOCTEXT_NAMESPACE