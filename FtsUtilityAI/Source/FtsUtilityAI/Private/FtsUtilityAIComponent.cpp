// (c) 2020 by FreetimeStudio


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

	// ...
}


// Called when the game starts
void UFtsUtilityAIComponent::BeginPlay()
{
	Super::BeginPlay();

	for(auto Bucket : Buckets)
	{
		if (IsValid(Bucket))
		{
			Bucket->InitializeBucket();
		}
	}

	for(auto Score: Scores)
	{
		Score->InitializeScore();
	}

	// ...
	
}


// Called every frame
void UFtsUtilityAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ChooseNextAction(DeltaTime);
	
	// Update active action
	if(CurrentAction)
	{
		CurrentAction->TickAction(DeltaTime);
	}
}

void UFtsUtilityAIComponent::ChooseNextAction(float DeltaSeconds)
{
	for(auto Score: Scores)
	{
		Score->UpdateScore(DeltaSeconds);
	}

	for(auto Bucket: Buckets)
	{
		Bucket->ScoreBucket();
	}
	
	//Sort buckets by highest score first
	Buckets.Sort([](const UFtsUtilityAIBucket& A, const UFtsUtilityAIBucket& B)
    {
        return A.GetCachedScore() > B.GetCachedScore();
    });

	// Score all behaviors and choose highest one
	float HighestBehaviorScore = 0.f;
	UFtsUtilityAIAction* HighestAction = nullptr;
	
	for(auto Bucket : Buckets)
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

UFtsUtilityAIScore* UFtsUtilityAIComponent::GetScoreById(const FName& Id)
{
	for(auto Score : Scores)
	{
		if(!IsValid(Score))
		{
			continue;
		}
		
		if(Score->GetUtilityId() == Id)
		{
			return Score;
		}
	}

	return nullptr;
}

UFtsUtilityAIBucket* UFtsUtilityAIComponent::GetBucketByClass(TSubclassOf<UFtsUtilityAIBucket> BucketClass)
{
	for(auto Bucket : Buckets)
	{
		if(!IsValid(Bucket))
		{
			continue;
		}
		
		if(Bucket->IsA(BucketClass))
		{
			return Bucket;
		}
	}

	return nullptr;
}

UFtsUtilityAIBucket* UFtsUtilityAIComponent::GetBucketByName(const FName& BucketName)
{
	for(auto Bucket : Buckets)
	{
		if(!IsValid(Bucket))
		{
			continue;
		}
		
		if(Bucket->GetUtilityId() == BucketName)
		{
			return Bucket;
		}
	}

	return nullptr;
}

UFtsUtilityAIBucket* UFtsUtilityAIComponent::CreateBucket(TSubclassOf<UFtsUtilityAIBucket> Class, FName BucketName)
{
	auto Bucket = NewObject<UFtsUtilityAIBucket>(this, Class, MakeUniqueObjectName(this, Class, BucketName));
	Bucket->SetUtilityId(BucketName);
	Buckets.Add(Bucket);
	return Bucket;
}

UFtsUtilityAIAction* UFtsUtilityAIComponent::GetActionByClass(TSubclassOf<UFtsUtilityAIAction> ActionClass)
{
	for(auto Bucket : Buckets)
	{
		const auto Action = Bucket->GetActionByClass(ActionClass);
		if(Action)
		{
			return Action;
		}
	}

	return nullptr;
}

UFtsUtilityAIAction* UFtsUtilityAIComponent::GetActionByName(FName ActionName)
{
	for(auto Bucket : Buckets)
	{
		const auto Action = Bucket->GetActionByName(ActionName);
		if(Action)
		{
			return Action;
		}
	}

	return nullptr;
}

UFtsUtilityAIAction* UFtsUtilityAIComponent::CreateAction(FName BucketName, TSubclassOf<UFtsUtilityAIAction> Class,
                                                          FName ActionName)
{
	for(auto Bucket : Buckets)
	{
		if(Bucket->GetUtilityId() == BucketName)
		{
			return Bucket->CreateAction(Class, ActionName);
		}
	}

	return nullptr;
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

