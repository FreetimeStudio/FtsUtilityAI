// (c) MIT 2020 by FreetimeStudio


#include "Score/FtsUtilityAICurveScoreModifier.h"

#include "FtsUtilityAIComponent.h"

UFtsUtilityAICurveScoreModifier::UFtsUtilityAICurveScoreModifier()
    : Super()
{
    SetUtilityId(FName("Score Curve"));
}

float UFtsUtilityAICurveScoreModifier::EvaluateScore_Implementation(float DeltaSeconds)
{
    if(!IsValid(ModifiedScore))
    {
        return 0.f;
    }
    
    const auto Score = ModifiedScore->GetScore();
    return WeightCurve.GetRichCurveConst()->Eval(Score);
}

