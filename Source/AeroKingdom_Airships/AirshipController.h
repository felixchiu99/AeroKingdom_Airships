// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehicleController.h"
#include "ASAirship.h"
#include "AirshipController.generated.h"

/**
 * 
 */
UCLASS()
class AEROKINGDOM_AIRSHIPS_API AAirshipController : public AVehicleController
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Airship)
	AASAirship* Airship;

public:
	// Sets default values for this pawn's properties
	AAirshipController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	virtual void Move(const FInputActionValue& Value);

	virtual void Lift(const FInputActionValue& Value);


	/* Called for linking Airship Functions*/
	virtual void ThrustAxis(float input);

	virtual void YawAxis(float input);

	virtual void UpAxis(float input);

public:
	void SetAirshipPointer(AASAirship* Airship);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetSteeringPos(float input);

	void SetThrottlePos(float input);
};
