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

