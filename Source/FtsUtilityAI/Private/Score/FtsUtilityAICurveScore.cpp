// (c) 2020 by FreetimeStudio


#include "Score/FtsUtilityAICurveScore.h"

UFtsUtilityAICurveScore::UFtsUtilityAICurveScore()
    : Super()
{
    WeightCurve.GetRichCurve()->AddKey(0.f,1.f);
}

void UFtsUtilityAICurveScore::InitializeScore_Implementation(UFtsUtilityAIAction* Action)
{
    Super::InitializeScore_Implementation(Action);

    if (IsValid(ModifiedScore))
    {
        ModifiedScore->InitializeScore(Action);
    }
}

float UFtsUtilityAICurveScore::EvaluateScore_Implementation(UFtsUtilityAIAction* Action) const
{
    if(!IsValid(ModifiedScore))
    {
        return 0.f;
    }
    
    auto Score = ModifiedScore->GetScore(Action);
    if(WeightCurve.GetRichCurveConst())
    {
        Score = WeightCurve.GetRichCurveConst()->Eval(Score);
    }

    return Score * Weight;
}
