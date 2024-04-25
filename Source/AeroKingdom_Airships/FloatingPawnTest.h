// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASVehicle.h"
#include "FloatingPawnTest.generated.h"

class AAirshipController;
class UFloatingPawnMovement;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AFloatingPawnTest : public AASVehicle
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* Airship;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* Balloon;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* ShipBase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ChildActorComponent, meta = (OnlyPlaceable, AllowPrivateAccess = "true"))
	TSubclassOf<AAirshipController>	ACAttachmentType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AirshipController", meta = (AllowPrivateAccess = "true", AllowedClasses = "Cannon"))
	class UChildActorComponent* AirshipController;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UFloatingPawnMovement* Movement;

public:	
	// Sets default values for this actor's properties
	AFloatingPawnTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void MoveForward() override;

	virtual void MoveBackward() override;

};
