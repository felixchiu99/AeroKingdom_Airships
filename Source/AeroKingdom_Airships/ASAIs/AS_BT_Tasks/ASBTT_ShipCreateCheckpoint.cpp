// Fill out your copyright notice in the Description page of Project Settings.


#include "ASBTT_ShipCreateCheckpoint.h"
#include "AIController.h"
#include "../../ASAirship.h"
#include "../../ASComponents/ASAC_AIShipWaypointSystem.h"
#include "../../ASComponents/ASAC_WaypointComponent.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Math/Quat.h"

EBTNodeResult::Type UASBTT_ShipCreateCheckpoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Blackboard = OwnerComp.GetBlackboardComponent();
	CreateCheckpoint();
	return EBTNodeResult::Type();
}

void UASBTT_ShipCreateCheckpoint::CreateCheckpoint()
{
	AASAirship* Airship = Cast<AASAirship>(Blackboard->GetValueAsObject(ShipActorKey.SelectedKeyName));
	if (!Airship) {
		return;
	}
	UASAC_AIShipWaypointSystem* ShipWaypoint = Cast<UASAC_AIShipWaypointSystem>(Airship->GetComponentByClass(UASAC_AIShipWaypointSystem::StaticClass()));
	if (!ShipWaypoint) {
		return;
	}
	UASAC_WaypointComponent* ShipCheckpoint = ShipWaypoint->GetCheckpointSystem();
	if (!ShipCheckpoint) {
		return;
	}
	FVector NextCheckpoint = ShipCheckpoint->GetWaypointLocation();
	Blackboard->SetValueAsVector(CheckpointLocationKey.SelectedKeyName, NextCheckpoint);
	Blackboard->SetValueAsBool(HasCheckpointKey.SelectedKeyName, true);
}
