// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASVehicle.generated.h"

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AASVehicle : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* Core;

public:	
	// Sets default values for this actor's properties
	AASVehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void MoveForward();

	virtual void MoveBackward();

	virtual void MoveLeft();

	virtual void MoveRight();

	virtual void MoveUp();

	virtual void MoveDown();

	virtual void YawLeft();

	virtual void YawRight();

	virtual void RollLeft();

	virtual void RollRight();

	virtual void PitchUp();

	virtual void PitchDown();

	virtual void AxisForward(float input);

	virtual void AxisRight(float input);

	virtual void AxisUp(float input);

	virtual void Yaw(float input);

	virtual void Roll(float input);

	virtual void Pitch(float input);
};
