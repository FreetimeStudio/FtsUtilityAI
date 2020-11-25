// (c) 2020 by FreetimeStudio


#include "Score/FtsUtilityAICurveScore.h"

#include "FtsUtilityAIComponent.h"

UFtsUtilityAICurveScore::UFtsUtilityAICurveScore()
    : Super()
{
}

void UFtsUtilityAICurveScore::InitializeScore_Implementation()
{
    Super::InitializeScore_Implementation();

    ModifiedScore = GetUtilityAiComponent()->GetScoreById(ModifiedScoreId);
}

float UFtsUtilityAICurveScore::EvaluateScore_Implementation(float DeltaSeconds)
{
    if(!IsValid(ModifiedScore))
    {
        return 0.f;
    }
    
    const auto Score = ModifiedScore->GetScore();
    return WeightCurve.GetRichCurveConst()->Eval(Score);
}

