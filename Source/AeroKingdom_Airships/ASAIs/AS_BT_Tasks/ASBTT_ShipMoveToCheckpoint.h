// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ASBTT_ShipMoveToCheckpoint.generated.h"

/**
 * 
 */
class AASPIAirshipController;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API UASBTT_ShipMoveToCheckpoint : public UBTTaskNode
{
	GENERATED_BODY()
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector CheckpointLocationKey;
	
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector AirshipControllerKey;


	UPROPERTY(EditAnywhere, Category = Airship)
	float fRotationModifier = 5.f;

protected:
	void CalculateYaw(AASPIAirshipController* AirshipHelm);
	void CalculateThrust(AASPIAirshipController* AirshipHelm);

	void MoveThrustAxis(AASPIAirshipController* AirshipHelm, float Input);
	void MoveYawAxis(AASPIAirshipController* AirshipHelm, float Input);
	void MoveLiftAxis(AASPIAirshipController* AirshipHelm, float Input);

protected:
	UBlackboardComponent* Blackboard;

	float Thrust = 0;
	float Yaw = 0;
	float Lift = 0;
};
