// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ASBTT_TurretAimBasic.generated.h"

/**
 * 
 */
class AASTurret;
class AAIController;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API UASBTT_TurretAimBasic : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool bRotateAzimuth = true;

	UPROPERTY(EditAnywhere)
	bool bRotateElevation = true;
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

protected:
	void RotateAzimuth(AASTurret* Turret, FVector AimTarget, AAIController* Controller);

	void RotateElevation(AASTurret* Turret, FVector AimTarget, AAIController* Controller);

	void RotateElevation(AASTurret* Turret, float Elevation, AAIController* Controller);

protected:
	bool bIsValidElevation = true;
};
