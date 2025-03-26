// Fill out your copyright notice in the Description page of Project Settings.


#include "ASAC_AIShipWaypointSystem.h"
#include "ASAC_WaypointComponent.h"

// Sets default values for this component's properties
UASAC_AIShipWaypointSystem::UASAC_AIShipWaypointSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	WaypointSystem = CreateDefaultSubobject<UASAC_WaypointComponent>(TEXT("WaypointComponment"));
	CheckpointSystem = CreateDefaultSubobject<UASAC_WaypointComponent>(TEXT("CheckpointComponment"));
}


// Called when the game starts
void UASAC_AIShipWaypointSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CheckpointSystem = Cast<UASAC_WaypointComponent>(GetOwner()->GetComponentByClass(UASAC_WaypointComponent::StaticClass()));
}


// Called every frame
void UASAC_AIShipWaypointSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UASAC_WaypointComponent* UASAC_AIShipWaypointSystem::GetCheckpointSystem()
{
	if (CheckpointSystem) {
		return CheckpointSystem;
	}
	return nullptr;
}

void UASAC_AIShipWaypointSystem::GenerateCheckpoint()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Generating Checkpoint" ));

	FVector NextWaypoint = WaypointSystem->GetWaypointLocation();
	FVector CurrentLocation = GetOwner()->GetActorLocation();

	float length = (NextWaypoint - CurrentLocation).Length();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("NextWaypoint : " + FString::SanitizeFloat(length)));

	float fShortestDistModifier = fShortestDistMod;

	if (length < fNearDist) {
		fShortestDistModifier = 1.2f;
	}

	FVector MidPoint = CalculateNextCheckpoint(CurrentLocation, NextWaypoint, GetOwner()->GetActorForwardVector(), fShortestDistModifier);

	TArray<FVector> Checkpoints;

	if (length < fNearDist) {
		FVector direction = NextWaypoint - CurrentLocation;
		direction.Normalize();
		FVector Point1 = CalculateNextCheckpoint(CurrentLocation, MidPoint, -direction, 0.5f);
		//Checkpoints.Add(Point1);
		Checkpoints.Add(MidPoint);

		FVector P3Direction = MidPoint - Point1;
		P3Direction.Normalize();
		FVector Point3 = CalculateNextCheckpoint(MidPoint, NextWaypoint, P3Direction, 1.5f);
		Checkpoints.Add(Point3);
	}
	else {
		FVector Point1 = CalculateNextCheckpoint(CurrentLocation, MidPoint, GetOwner()->GetActorForwardVector(), fShortestDistModifier);
		FVector Point3 = CalculateNextCheckpoint(MidPoint, NextWaypoint, GetOwner()->GetActorForwardVector(), fShortestDistModifier);
		Checkpoints.Add(Point1);
		Checkpoints.Add(MidPoint);
		Checkpoints.Add(Point3);
	}

	Checkpoints.Add(NextWaypoint);

	CheckpointSystem->SetWaypoints(Checkpoints);

	DrawDebugLine(
		GetWorld(),
		CurrentLocation,
		CurrentLocation + FVector(0, 0, 500),
		FColor(0, 255, 255),
		false, fDisplayTime, 0,
		12.333
	);

	DebugWaypoint(Checkpoints);
}

FVector UASAC_AIShipWaypointSystem::CalculateNextCheckpoint(FVector V1, FVector V2, FVector ForwardVector, float fShortestDistModifier)
{
	FVector Result;
	FVector MidPoint = FMath::Lerp(V1, V2, 0.5f);

	float ShortestDist = abs(V1.X - V2.X);
	float Temp = abs(V1.Y - V2.Y);

	if (Temp < ShortestDist) {
		ShortestDist = Temp;
	}

	ShortestDist *= fShortestDistModifier;

	FVector Normal = FVector::CrossProduct((V2 - V1) , FVector(0, 0, 1));
	Normal.Normalize();

	FVector MidPoint2 = MidPoint + Normal * ShortestDist;
	FVector MidPoint3 = MidPoint - Normal * ShortestDist;

	FVector VectorToMid2 = MidPoint2 - V1;
	FVector VectorToMid3 = MidPoint3 - V1;

	VectorToMid2.Normalize();
	VectorToMid3.Normalize();

	float Angle = FMath::Acos(FVector::DotProduct(VectorToMid2, ForwardVector ));

	float Angle2 = FMath::Acos(FVector::DotProduct(VectorToMid3, ForwardVector ));

	if (Angle < Angle2) {
		Result = MidPoint2;
	}
	if (Angle > Angle2) {
		Result = MidPoint3;
	}

	return Result;
}

void UASAC_AIShipWaypointSystem::DebugWaypoint(TArray<FVector> Checkpoints)
{
	int temp = 0;

	for (auto Checkpoint : Checkpoints) {
		DrawDebugLine(
			GetWorld(),
			Checkpoint,
			Checkpoint + FVector(0, 0, 500),
			FColor(255, 50 * temp, 255/(temp+1)),
			false, fDisplayTime, 0,
			12.333
		);
		temp++;
	}
}


