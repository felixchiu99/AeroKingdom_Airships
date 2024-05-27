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
	UASAC_AIShipWaypointSystem* ShipWaypointSystem = Cast<UASAC_AIShipWaypointSystem>(Blackboard->GetValueAsObject(AirshipWaypointSystemActorKey.SelectedKeyName));
	if (!ShipWaypointSystem) {
		return;
	}
	ShipWaypointSystem->GenerateCheckpoint();
	Blackboard->SetValueAsBool(HasWaypointKey.SelectedKeyName, true);
}

