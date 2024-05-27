// Fill out your copyright notice in the Description page of Project Settings.


#include "ASBTT_ShipMoveToCheckpoint.h"
#include "../../ASPIAirshipController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Math/Quat.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UASBTT_ShipMoveToCheckpoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//AAIController* Controller = OwnerComp.GetAIOwner();
	//AASPIAirshipController* AirshipHelm = Cast<AASPIAirshipController>(Controller->GetPawn());
	Blackboard = OwnerComp.GetBlackboardComponent();

	AASPIAirshipController* AirshipHelm = Cast<AASPIAirshipController>(Blackboard->GetValueAsObject(AirshipControllerKey.SelectedKeyName));
	if (!AirshipHelm) {
		return EBTNodeResult::Type();
	}

	CalculateYaw(AirshipHelm);
	CalculateThrust(AirshipHelm);

	MoveThrustAxis(AirshipHelm, Thrust);
	MoveYawAxis(AirshipHelm, Yaw);
	MoveLiftAxis(AirshipHelm, Lift);

	return EBTNodeResult::Type();
}

void UASBTT_ShipMoveToCheckpoint::CalculateYaw(AASPIAirshipController* AirshipHelm)
{
	Yaw = 0;

	FVector CheckpointLocation = Blackboard->GetValueAsVector(CheckpointLocationKey.SelectedKeyName);
	
	DrawDebugLine(
		GetWorld(),
		CheckpointLocation,
		CheckpointLocation + FVector(0, 0, 500),
		FColor(255, 0, 0),
		false, 0.01f, 0,
		12.333
	);

	FVector TargetVector = CheckpointLocation - AirshipHelm->GetActorLocation();
	FVector LocalTargetVector = UKismetMathLibrary::InverseTransformDirection(AirshipHelm->GetTransform(), TargetVector);

	FQuat Rotation = FQuat::FindBetween(AirshipHelm->GetActorForwardVector(), TargetVector);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("local " + FString::SanitizeFloat(Rotation.Z)));

	/*
	if (LocalTargetVector.Y > 1000) {
		Yaw = 1;
	}
	if (LocalTargetVector.Y < 1000) {
		Yaw = -1;
	}
	*/
	//Yaw = LocalTargetVector.Y * 0.0005f;
	/*
	if (abs(LocalTargetVector.Y) > 1000) {
		Yaw = LocalTargetVector.Y * 0.004f;
	}
	*/
	if (abs(Rotation.Z) > 0.01f) {
		Yaw = Rotation.Z * fRotationModifier;
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Yaw " + FString::SanitizeFloat(Yaw)));
}

void UASBTT_ShipMoveToCheckpoint::CalculateThrust(AASPIAirshipController* AirshipHelm)
{
	FVector CheckpointLocation = Blackboard->GetValueAsVector(CheckpointLocationKey.SelectedKeyName);
	FVector TargetVector = CheckpointLocation - AirshipHelm->GetActorLocation();
	FVector LocalTargetVector = UKismetMathLibrary::InverseTransformDirection(AirshipHelm->GetTransform(), TargetVector);

	if (LocalTargetVector.X > 0) {
		Thrust = 1; 
	}
	if (LocalTargetVector.X < 0) {
		Thrust = -1;
	}
	if (Yaw != 0) {
		Thrust *= 0.5f;
	}
}

void UASBTT_ShipMoveToCheckpoint::MoveThrustAxis(AASPIAirshipController* AirshipHelm, float Input)
{
	AirshipHelm->ThrustAxis(Input);
}

void UASBTT_ShipMoveToCheckpoint::MoveYawAxis(AASPIAirshipController* AirshipHelm, float Input)
{
	AirshipHelm->YawAxis(Input);
}

void UASBTT_ShipMoveToCheckpoint::MoveLiftAxis(AASPIAirshipController* AirshipHelm, float Input)
{
	AirshipHelm->UpAxis(Input);
}
