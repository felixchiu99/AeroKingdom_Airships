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
	
}


// Called every frame
void UASAC_WaypointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UASAC_WaypointComponent::SetWaypoints(TArray<AASA_WaypointActor*> InWaypoints)
{
	Waypoints = InWaypoints;
}

TArray<AASA_WaypointActor*> UASAC_WaypointComponent::GetWaypoints()
{
	return Waypoints;
}

AASA_WaypointActor* UASAC_WaypointComponent::GetWaypoint()
{
	if (CurrentIndex < Waypoints.Num()) {
		return Waypoints[CurrentIndex];
	}
	else {
		return nullptr;
	}
	
}

FVector3d UASAC_WaypointComponent::GetWaypointLocation()
{
	if (CurrentIndex < Waypoints.Num()) {
		return Waypoints[CurrentIndex]->GetActorLocation();
	}
	else {
		return FVector3d(0);
	}
}

void UASAC_WaypointComponent::NextIndex()
{
	switch (Direction)
	{

	case TransverseDirection::Loop:
		if (CurrentIndex < Waypoints.Num()-1) {
			CurrentIndex++;
		}
		else {
			CurrentIndex = 0;
		}
		break;
	case TransverseDirection::PingPong:
		if (CurrentIndex >= Waypoints.Num()) {
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
		if (CurrentIndex < Waypoints.Num()) {
			CurrentIndex++;
		}
		break;
	default:
		break;
	}
}

