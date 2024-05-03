// Fill out your copyright notice in the Description page of Project Settings.


#include "ASBTT_TurretAimBasic.h"
#include "../../ASTurret.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Math/Quat.h"

EBTNodeResult::Type UASBTT_TurretAimBasic::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	AASTurret* turret = Cast<AASTurret>(Controller->GetPawn());
	FVector AimTarget = Controller->GetBlackboardComponent()->GetValueAsVector(FName(TEXT("AimTarget")));

	FQuat rotation = FQuat::FindBetween(turret->GetAimingVector(), AimTarget - Controller->GetPawn()->GetActorLocation());

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("X " + FString::SanitizeFloat(rotation.X)));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Y " + FString::SanitizeFloat(rotation.Y)));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Z " + FString::SanitizeFloat(rotation.Z)));
	if (bRotateAzimuth) {
		RotateAzimuth(turret, AimTarget, Controller);
	}

	if (bRotateElevation) {
		RotateElevation(turret, AimTarget, Controller);
	}

	return EBTNodeResult::Type();
}

void UASBTT_TurretAimBasic::RotateAzimuth(AASTurret* turret, FVector AimTarget, AAIController* Controller)
{
	FQuat rotation = FQuat::FindBetween(turret->GetAimingVector(), turret->GetTargetVector(AimTarget));

	float fRotationSpeedModifier = 0.8f;
	float fRotationAccuracyModifier = 0.005f;

	float fAzimuthInput = fRotationSpeedModifier * rotation.Z > 0 ? 1 : -1;
	if (abs(rotation.Z) > fRotationAccuracyModifier) {
		turret->RotateBase(fAzimuthInput);
	}
}

void UASBTT_TurretAimBasic::RotateElevation(AASTurret* turret, FVector AimTarget, AAIController* Controller)
{
	FQuat rotation = FQuat::FindBetween(turret->GetAimingVector(), turret->GetTargetVector(AimTarget));

	float fRotationSpeedModifier = 0.5f;
	float fRotationAccuracyModifier = 0.005f;

	float fElevationInput = fRotationSpeedModifier * rotation.Y > 0 ? -1 : 1;
	if (abs(rotation.Y) > fRotationAccuracyModifier) {
		turret->RotateElevation(fElevationInput);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Y " + FString::SanitizeFloat(rotation.Y)));
	}
}
