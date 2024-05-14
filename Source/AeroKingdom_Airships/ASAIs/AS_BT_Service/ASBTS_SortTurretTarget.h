// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ASBTS_SortTurretTarget.generated.h"

/**
 * 
 */
UCLASS()
class AEROKINGDOM_AIRSHIPS_API UASBTS_SortTurretTarget : public UBTService
{
	GENERATED_BODY()
	
	UASBTS_SortTurretTarget();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector SelfActorKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector HasTargetKey;
};
