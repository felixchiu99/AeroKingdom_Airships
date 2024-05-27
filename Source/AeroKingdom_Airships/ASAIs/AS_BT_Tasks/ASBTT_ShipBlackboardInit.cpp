// Fill out your copyright notice in the Description page of Project Settings.


#include "ASBTT_ShipBlackboardInit.h"
#include "AIController.h"
#include "../../ASPIAirshipController.h"
#include "../../ASAirship.h"
#include "../../ASComponents/ASAC_AIShipWaypointSystem.h"
#include "../../ASComponents/ASAC_WaypointComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UASBTT_ShipBlackboardInit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	Blackboard->SetValueAsBool(IsInitializedKey.SelectedKeyName, false);

	AAIController* Controller = OwnerComp.GetAIOwner();
	AASPIAirshipController* AirshipHelm = Cast<AASPIAirshipController>(Controller->GetPawn());
	if (!AirshipHelm) {
		return EBTNodeResult::Type();
	}
	AASAirship* Airship = Cast<AASAirship>(Blackboard->GetValueAsObject(AirshipActorKey.SelectedKeyName));
	if (!Airship) {
		return EBTNodeResult::Type();
	}
	UASAC_AIShipWaypointSystem* ShipWaypoint = Cast<UASAC_AIShipWaypointSystem>(Airship->GetComponentByClass(UASAC_AIShipWaypointSystem::StaticClass()));
	if (!ShipWaypoint) {
		return EBTNodeResult::Type();
	}
	UASAC_WaypointComponent* ShipCheckpoint = ShipWaypoint->GetCheckpointSystem();
	if (!ShipCheckpoint) {
		return EBTNodeResult::Type();
	}

	Blackboard->SetValueAsObject(AirshipControllerKey.SelectedKeyName, AirshipHelm);
	Blackboard->SetValueAsObject(AirshipWaypointSystemActorKey.SelectedKeyName, ShipWaypoint);
	Blackboard->SetValueAsObject(AirshipCheckpointSystemActorKey.SelectedKeyName, ShipCheckpoint);


	Blackboard->SetValueAsBool(IsInitializedKey.SelectedKeyName, true);

	return EBTNodeResult::Type();
}
