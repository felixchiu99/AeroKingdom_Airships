// Fill out your copyright notice in the Description page of Project Settings.


#include "ASBTS_TurretIsOnTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../ASTurret.h"
#include "AIController.h"
#include "Math/Quat.h"

UASBTS_TurretIsOnTarget::UASBTS_TurretIsOnTarget(){
	NodeName = "UpdateIsOnTarget";
}

void UASBTS_TurretIsOnTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* SelfActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(SelfActorKey.SelectedKeyName));
	FVector AimTarget = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AimTargetKey.SelectedKeyName);

	AAIController* Controller = OwnerComp.GetAIOwner();
	AASTurret* turret = Cast<AASTurret>(Controller->GetPawn());

	FQuat rotation = FQuat::FindBetween(turret->GetAimingVector(), turret->GetTargetVector(AimTarget));

	float fRotationAccuracyModifier = 0.01f;

	bool IsOnTargetAzimuth = abs(rotation.Z) < fRotationAccuracyModifier;
	bool IsOnTargetElevation = abs(rotation.Y) < fRotationAccuracyModifier;

	bool IsOnTarget = IsOnTargetAzimuth && IsOnTargetElevation;

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsOnTargetKey.SelectedKeyName, IsOnTarget);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsOnTargetAzimuthKey.SelectedKeyName, IsOnTargetAzimuth);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsOnTargetElevationKey.SelectedKeyName, IsOnTargetElevation);
}
