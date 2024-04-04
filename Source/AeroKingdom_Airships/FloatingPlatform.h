// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingPlatform.generated.h"

class UCapsuleComponent;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AFloatingPlatform : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* Airship;
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* BalloonMesh;
	
	//Move Timer Handle
	FTimerHandle MoveTimer;

	//move direct
	bool bIsForward = true;

	//move step
	float fStep = 1.f;
	
	//Mass
	float fMass = 1.f;

public:
	//lift
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lift);
	float fLift = 5000.f;

public:	
	// Sets default values for this actor's properties
	AFloatingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void AsyncPhysicsTickActor(float DeltaTime, float SimTime) override;

	void ApplyLift(float StepTime);

	void MovePlatform();

	void MoveForward();

	void MoveBackward();

	void ToggleMovementDirection();

};
