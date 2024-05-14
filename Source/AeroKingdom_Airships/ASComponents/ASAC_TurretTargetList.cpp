// Fill out your copyright notice in the Description page of Project Settings.


#include "ASAC_TurretTargetList.h"

// Sets default values for this component's properties
UASAC_TurretTargetList::UASAC_TurretTargetList()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UASAC_TurretTargetList::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UASAC_TurretTargetList::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UASAC_TurretTargetList::AddTarget(AActor* Target)
{
	ScoredTargets.Add(Target, -1);
	//CalculateTarget();
}

void UASAC_TurretTargetList::RemoveTarget(AActor* Target)
{
	ScoredTargets.Remove(Target);
	//CalculateTarget();
}

void UASAC_TurretTargetList::CalculateTarget()
{
	ScoredTargets.Remove(nullptr);
	ScoredTargets.Remove(NULL);
	TArray<AActor*> DelList;
	for (auto& TargetPair : ScoredTargets)
	{
		if (IsValid(TargetPair.Key))
		{
			float Score = CalculateScore(TargetPair.Key);
			ScoredTargets[TargetPair.Key] = Score;
		}
		else 
		{
			DelList.Add(TargetPair.Key);
		}
		
		
	}
	for (auto& ToBeDel : DelList)
	{
		ScoredTargets.Remove(ToBeDel);
	}
	DelList.Empty();

	ScoredTargets.ValueSort([](float A, float B) {
		return A < B; // sort keys in reverse
		}
	);
	CalculatedTarget = ScoredTargets.begin()->Key;

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("num " + FString::FromInt(ScoredTargets.Num())));
}

AActor* UASAC_TurretTargetList::GetCalulatedTarget()
{
	return CalculatedTarget;
}

float UASAC_TurretTargetList::CalculateScore(AActor* Target)
{
	if (Target) {
		float fDist = FMath::FloorToInt(FVector::Dist(
			GetOwner()->GetActorLocation(),
			Target->GetActorLocation()
		));
		return fDist;
	}
	return -1;
}

