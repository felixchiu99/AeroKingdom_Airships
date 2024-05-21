// Fill out your copyright notice in the Description page of Project Settings.


#include "ASBTS_TurretIsOnTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../ASTurret.h"
#include "AIController.h"
#include "Math/Quat.h"
#include "Kismet/KismetMathLibrary.h"

UASBTS_TurretIsOnTarget::UASBTS_TurretIsOnTarget(){
	NodeName = "UpdateIsOnTarget";
}

void UASBTS_TurretIsOnTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	bIsValidElevation = true;
	AActor* SelfActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(SelfActorKey.SelectedKeyName));
	FVector AimTarget = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AimTargetKey.SelectedKeyName);

	AAIController* Controller = OwnerComp.GetAIOwner();
	AASTurret* Turret = Cast<AASTurret>(Controller->GetPawn());

	AimTurret(OwnerComp.GetBlackboardComponent(), AimTarget, Turret);
}

void UASBTS_TurretIsOnTarget::AimTurret(UBlackboardComponent* Blackboard, FVector AimTarget, AASTurret* Turret)
{
	float Elevation = Turret->CalculateTurretElevation(AimTarget);
	if (Elevation == -10) {
		return;
	}
	FQuat Rotation = FQuat::FindBetween(Turret->GetAimingVector(), Turret->GetTargetVector(AimTarget));
	SaveTurretAngle(Blackboard, Elevation, Rotation, Turret);
}

void UASBTS_TurretIsOnTarget::SaveTurretAngle(UBlackboardComponent* Blackboard, float Elevation, FQuat Rotation, AASTurret* Turret)
{

	float fRotationAccuracyModifier = 0.01f;

	bool IsOnTargetAzimuth = abs(Rotation.Z) < fRotationAccuracyModifier;
	bool IsOnTargetElevation = false;
	if (!bIsValidElevation) {
		IsOnTargetElevation = abs(Rotation.Y) < Turret->GetElevationAccuracyModifier();
	}
	else {
		IsOnTargetElevation = CheckElevationOnTarget(Elevation, Turret);
	}

	bool IsOnTarget = IsOnTargetAzimuth && IsOnTargetElevation;

	Blackboard->SetValueAsBool(IsOnTargetKey.SelectedKeyName, IsOnTarget);
	Blackboard->SetValueAsBool(IsOnTargetAzimuthKey.SelectedKeyName, IsOnTargetAzimuth);
	Blackboard->SetValueAsBool(IsOnTargetElevationKey.SelectedKeyName, IsOnTargetElevation);
}

bool UASBTS_TurretIsOnTarget::CheckElevationOnTarget(float Elevation, AASTurret* Turret)
{
	float Angle = Elevation - Turret->GetCurrentElevationAngle();

	if (abs(Angle) < Turret->GetElevationAccuracyModifier()) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("hi "));
		return true;
	}
	return false;
}
