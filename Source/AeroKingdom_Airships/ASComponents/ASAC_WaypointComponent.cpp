// Fill out your copyright notice in the Description page of Project Settings.


#include "ASAC_WaypointComponent.h"
#include "../ASTest/ASA_WaypointActor.h"

// Sets default values for this component's properties
UASAC_WaypointComponent::UASAC_WaypointComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UASAC_WaypointComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	InitWaypointVectorsFromActor();
}


// Called every frame
void UASAC_WaypointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UASAC_WaypointComponent::SetWaypointActors(TArray<AASA_WaypointActor*> InWaypointActors)
{
	WaypointsActors = InWaypointActors;
	InitWaypointVectorsFromActor();
}

void UASAC_WaypointComponent::SetWaypoints(TArray<FVector> InWaypoints)
{
	EmptyWaypoints();
	WaypointVectors = InWaypoints;
}

void UASAC_WaypointComponent::AddWaypoints(FVector InWaypoint)
{
	WaypointVectors.Add(InWaypoint);
}

void UASAC_WaypointComponent::EmptyWaypoints()
{
	WaypointVectors.Empty();
	CurrentIndex = 0;
}


TArray<FVector> UASAC_WaypointComponent::GetWaypoints()
{
	return WaypointVectors;
}

FVector UASAC_WaypointComponent::GetWaypoint()
{
	if (WaypointVectors.Num() == 1) {
		return WaypointVectors[0];
	}
	if (CurrentIndex < WaypointVectors.Num()) {
		return WaypointVectors[CurrentIndex];
	}
	else {
		return FVector(0);
	}
}

FVector UASAC_WaypointComponent::GetWaypointLocation()
{
	if (CurrentIndex < WaypointVectors.Num()) {
		return WaypointVectors[CurrentIndex];
	}
	else {
		return FVector(0);
	}
}

void UASAC_WaypointComponent::NextIndex()
{
	if (WaypointVectors.Num() == 1) {
		return;
	}
	switch (Direction)
	{

	case TransverseDirection::Loop:
		if (CurrentIndex < WaypointVectors.Num()-1) {
			CurrentIndex++;
		}
		else {
			CurrentIndex = 0;
		}
		break;
	case TransverseDirection::PingPong:
		if (CurrentIndex >= WaypointVectors.Num()-1) {
			bIsDecreasing = true;
		}
		if (CurrentIndex <= 0) {
			bIsDecreasing = false;
		}
		if (bIsDecreasing) {
			CurrentIndex--;
		}
		else {
			CurrentIndex++;
		}
		break;
	case TransverseDirection::None:
		if (CurrentIndex < WaypointVectors.Num()-1) {
			CurrentIndex++;
		}
		break;
	default:
		break;
	}
}

void UASAC_WaypointComponent::InitWaypointVectorsFromActor()
{
	EmptyWaypoints();
	for (auto Waypoint : WaypointsActors) {
		WaypointVectors.Add(Waypoint->GetActorLocation());
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("hi " + FString::SanitizeFloat(WaypointVectors.Num())));

}

