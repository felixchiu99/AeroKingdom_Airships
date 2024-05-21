// Fill out your copyright notice in the Description page of Project Settings.


#include "ASBTT_TurretAimBasic.h"
#include "../../ASTurret.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Math/Quat.h"

EBTNodeResult::Type UASBTT_TurretAimBasic::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	AASTurret* Turret = Cast<AASTurret>(Controller->GetPawn());

	if (!Turret) {
		return EBTNodeResult::Type();
	}

	FVector AimTarget = Controller->GetBlackboardComponent()->GetValueAsVector(FName(TEXT("AimTarget")));

	FQuat rotation = FQuat::FindBetween(Turret->GetAimingVector(), AimTarget - Controller->GetPawn()->GetActorLocation());


	if (bRotateAzimuth) {
		RotateAzimuth(Turret, AimTarget, Controller);
	}

	if (bRotateElevation && Turret->IsTargetInRange(AimTarget)) {
		//RotateElevation(Turret, AimTarget, Controller);
		float Elevation = Turret->CalculateTurretElevation(AimTarget);
		if (Elevation == -10) {
			return EBTNodeResult::Type();
		}
		RotateElevation(Turret, Elevation, Controller);
	}

	return EBTNodeResult::Type();
}

void UASBTT_TurretAimBasic::RotateAzimuth(AASTurret* Turret, FVector AimTarget, AAIController* Controller)
{
	FQuat rotation = FQuat::FindBetween(Turret->GetAimingVector(), Turret->GetTargetVector(AimTarget));

	float fRotationSpeedModifier = 0.8f;
	float fRotationAccuracyModifier = 0.005f;

	float fAzimuthInput = fRotationSpeedModifier * rotation.Z > 0 ? 1 : -1;
	if (abs(rotation.Z) > fRotationAccuracyModifier) {
		Turret->RotateBase(fAzimuthInput);
	}
}

void UASBTT_TurretAimBasic::RotateElevation(AASTurret* Turret, FVector AimTarget, AAIController* Controller)
{
	FQuat rotation = FQuat::FindBetween(Turret->GetAimingVector(), Turret->GetTargetVector(AimTarget));

	float fRotationSpeedModifier = 0.05f;
	float fRotationAccuracyModifier = Turret->GetElevationAccuracyModifier();

	float fElevationInput = fRotationSpeedModifier * (rotation.Y > 0 ? -1 : 1);
	if (abs(rotation.Y) > fRotationAccuracyModifier) {
		Turret->RotateElevation(fElevationInput);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Y " + FString::SanitizeFloat(rotation.Y)));
	}
}

void UASBTT_TurretAimBasic::RotateElevation(AASTurret* Turret, float Elevation, AAIController* Controller)
{
	float fRotationSpeedModifier = Turret->GetElevationSpeedModifier();
	float fRotationAccuracyModifier = Turret->GetElevationAccuracyModifier();

	float AngleDiff = Elevation - Turret->GetCurrentElevationAngle();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Elevation " + FString::SanitizeFloat(Elevation)));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("CAngle " + FString::SanitizeFloat(Turret->GetCurrentElevationAngle())));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Diff " + FString::SanitizeFloat(Angle)));

	//float fElevationInput = fRotationSpeedModifier * (AngleDiff > 0 ? 1 : -1);
	float fElevationInput = fRotationSpeedModifier * AngleDiff;

	if (abs(AngleDiff) > Turret->GetElevationAccuracyModifier()) {
		Turret->RotateElevation(fElevationInput);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ElevationInput " + FString::SanitizeFloat(fElevationInput)));
	}
}
