// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ASBTS_ShipCheckAtCheckpoint.generated.h"

/**
 * 
 */
UCLASS()
class AEROKINGDOM_AIRSHIPS_API UASBTS_ShipCheckAtCheckpoint : public UBTService
{
	GENERATED_BODY()

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	void CheckOnTarget(UBlackboardComponent* Blackboard);

protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector SelfActorKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector ShipActorKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector AirshipCheckpointSystemActorKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector CheckpointLocationKey;
	
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector HasCheckpointKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	float fDist = 500;
};
