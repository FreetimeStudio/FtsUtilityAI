// (c) MIT 2020 by FreetimeStudio


#include "FtsUtilityAIComponent.h"

#include "AIController.h"
#include "FtsUtilityAIAction.h"
#include "FtsUtilityAIBucket.h"
#include "Score/FtsUtilityAIScore.h"

// Sets default values for this component's properties
UFtsUtilityAIComponent::UFtsUtilityAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UtilityAiInstance = nullptr;
	// ...
}


// Called when the game starts
void UFtsUtilityAIComponent::BeginPlay()
{
	Super::BeginPlay();

	const auto LoadedAsset = UtilityAiAsset.LoadSynchronous();
	if(!IsValid(LoadedAsset))
	{
		return;
	}

	const auto InstanceName = MakeUniqueObjectName(this, UFtsUtilityAIAsset::StaticClass(), FName("Instance"));
	UtilityAiInstance = DuplicateObject<UFtsUtilityAIAsset>(LoadedAsset, this, InstanceName);
	UtilityAiInstance->SetFlags(GetFlags());
	UtilityAiInstance->Initialize(this);
}


// Called every frame
void UFtsUtilityAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!IsValid(UtilityAiInstance))
	{
		return;
	}
	
	ChooseNextAction(DeltaTime);
	
	// Update active action
	if(CurrentAction)
	{
		CurrentAction->TickAction(DeltaTime);
	}
}

void UFtsUtilityAIComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if(!IsValid(UtilityAiInstance))
	{
		return;
	}

	UtilityAiInstance->Uninitialize();
	UtilityAiInstance = nullptr;
}

void UFtsUtilityAIComponent::ChooseNextAction(float DeltaSeconds)
{
	check(UtilityAiInstance);
	
	for(auto Score: UtilityAiInstance->Scores)
	{
		if(IsValid(Score))
		{
			Score->UpdateScore(DeltaSeconds);
		}
	}

	for(auto Bucket: UtilityAiInstance->Buckets)
	{
		if(IsValid(Bucket))
		{
			Bucket->ScoreBucket();
		}
	}
	
	//Sort buckets by highest score first
	UtilityAiInstance->Buckets.Sort([](const UFtsUtilityAIBucket& A, const UFtsUtilityAIBucket& B)
    {
        return A.GetCachedScore() > B.GetCachedScore();
    });

	// Score all behaviors and choose highest one
	float HighestBehaviorScore = 0.f;
	UFtsUtilityAIAction* HighestAction = nullptr;
	
	for(auto Bucket : UtilityAiInstance->Buckets)
	{
		float BucketScore = 0.f;
		HighestAction = Bucket->ScoreHighestAction(BucketScore); 
		if(HighestAction && BucketScore > 0.f)
		{
			break;
		}
	}

	// If action changed, end current and start new
	if(CurrentAction != HighestAction)
	{
		if(CurrentAction)
		{
			CurrentAction->EndAction();
		}

		CurrentAction = HighestAction;
		
		if(CurrentAction)
		{
			CurrentAction->BeginAction();
		}
	}
}

AAIController* UFtsUtilityAIComponent::GetAIController() const
{
	return Cast<AAIController>(GetOwner());
}

APawn* UFtsUtilityAIComponent::GetPawn() const
{
	return GetAIController()->GetPawn();
}

UBlackboardComponent* UFtsUtilityAIComponent::GetBlackboard() const
{
	return GetAIController()->GetBlackboardComponent();
}

UAIPerceptionComponent* UFtsUtilityAIComponent::GetPerception() const
{
	return GetAIController()->GetPerceptionComponent();
}

