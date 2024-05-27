// Fill out your copyright notice in the Description page of Project Settings.


#include "ASBTT_ShipUpdateCheckpoint.h"
#include "../../ASComponents/ASAC_WaypointComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UASBTT_ShipUpdateCheckpoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Blackboard = OwnerComp.GetBlackboardComponent();
	SaveCheckpointLocation();
	return EBTNodeResult::Type();
}

void UASBTT_ShipUpdateCheckpoint::SaveCheckpointLocation()
{
	UASAC_WaypointComponent* ShipCheckpoint = Cast<UASAC_WaypointComponent>(Blackboard->GetValueAsObject(AirshipCheckpointSystemActorKey.SelectedKeyName));
	if (!ShipCheckpoint) {
		return;
	}
	FVector NextCheckpoint = ShipCheckpoint->GetWaypointLocation();
	Blackboard->SetValueAsVector(CheckpointLocationKey.SelectedKeyName, NextCheckpoint);
	Blackboard->SetValueAsBool(HasCheckpointKey.SelectedKeyName, true);
}
