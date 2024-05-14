// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ASBTS_UpdateTargetLocation.generated.h"

/**
 * 
 */
UCLASS()
class AEROKINGDOM_AIRSHIPS_API UASBTS_UpdateTargetLocation : public UBTService
{
	GENERATED_BODY()

	UASBTS_UpdateTargetLocation();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector AimTargetKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector HasTargetKey;
};
