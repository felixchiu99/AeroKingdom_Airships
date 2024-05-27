// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ASBTT_ShipUpdateCheckpoint.generated.h"

/**
 * 
 */
UCLASS()
class AEROKINGDOM_AIRSHIPS_API UASBTT_ShipUpdateCheckpoint : public UBTTaskNode
{
	GENERATED_BODY()

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

protected:
	void SaveCheckpointLocation();

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector AirshipCheckpointSystemActorKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector CheckpointLocationKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector HasCheckpointKey;

	UBlackboardComponent* Blackboard;
};
