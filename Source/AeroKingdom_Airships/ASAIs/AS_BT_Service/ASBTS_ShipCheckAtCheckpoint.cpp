// Fill out your copyright notice in the Description page of Project Settings.


#include "ASBTS_ShipCheckAtCheckpoint.h"
#include "../../ASAirship.h"
#include "../../ASComponents/ASAC_AIShipWaypointSystem.h"
#include "../../ASComponents/ASAC_WaypointComponent.h"

#include "BehaviorTree/BlackboardComponent.h"

void UASBTS_ShipCheckAtCheckpoint::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	CheckOnTarget(OwnerComp.GetBlackboardComponent());
}

void UASBTS_ShipCheckAtCheckpoint::CheckOnTarget(UBlackboardComponent* Blackboard)
{
	AASAirship* Airship = Cast<AASAirship>(Blackboard->GetValueAsObject(ShipActorKey.SelectedKeyName));
	if (!Airship) {
		return;
	}

	FVector NextCheckpoint = Blackboard->GetValueAsVector(CheckpointLocationKey.SelectedKeyName);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Dist " + FString::SanitizeFloat((NextCheckpoint - Airship->GetActorLocation()).Length())));

	if ((NextCheckpoint - Airship->GetActorLocation()).Length() < fDist) {
		/*
		UASAC_AIShipWaypointSystem* ShipWaypoint = Cast<UASAC_AIShipWaypointSystem>(Airship->GetComponentByClass(UASAC_AIShipWaypointSystem::StaticClass()));
		if (!ShipWaypoint) {
			return;
		}
		UASAC_WaypointComponent* ShipCheckpoint = ShipWaypoint->GetCheckpointSystem();
		if (!ShipCheckpoint) {
			return;
		}
		*/

		UASAC_WaypointComponent* ShipCheckpoint = Cast<UASAC_WaypointComponent>(Blackboard->GetValueAsObject(AirshipCheckpointSystemActorKey.SelectedKeyName));
		ShipCheckpoint->NextIndex();

		Blackboard->SetValueAsBool(HasCheckpointKey.SelectedKeyName, false);
	}

	
}
