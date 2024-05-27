// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ASBTT_ShipBlackboardInit.generated.h"

/**
 * 
 */
UCLASS()
class AEROKINGDOM_AIRSHIPS_API UASBTT_ShipBlackboardInit : public UBTTaskNode
{
	GENERATED_BODY()
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsInitializedKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector AirshipControllerKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector AirshipActorKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector AirshipWaypointSystemActorKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector AirshipCheckpointSystemActorKey;

};
