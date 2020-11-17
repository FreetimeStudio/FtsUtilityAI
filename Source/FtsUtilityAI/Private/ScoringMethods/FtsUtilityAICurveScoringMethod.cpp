// (c) 2020 by FreetimeStudio


#include "ScoringMethods/FtsUtilityAICurveScoringMethod.h"

UFtsUtilityAICurveScoringMethod::UFtsUtilityAICurveScoringMethod()
    : Super()
{
    WeightCurve.GetRichCurve()->AddKey(0.f,1.f);
}

float UFtsUtilityAICurveScoringMethod::EvaluateScore_Implementation(UFtsUtilityAIAction* Action) const
{
    auto Score = ModifiedScore->GetScore(Action);
    if(WeightCurve.GetRichCurveConst())
    {
        Score = WeightCurve.GetRichCurveConst()->Eval(Score);
    }

    return Score * Weight;
}
