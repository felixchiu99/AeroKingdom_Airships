// Fill out your copyright notice in the Description page of Project Settings.


#include "ASPIAirshipController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


AASPIAirshipController::AASPIAirshipController()
{

	VehicleControllerBase->SetCollisionProfileName(FName("ShipComponent"));
}

void AASPIAirshipController::BeginPlay()
{
	Super::BeginPlay();
}

void AASPIAirshipController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MoveAxisVector = Value.Get<FVector2D>();

	if (Airship) {
		ThrustAxis(MoveAxisVector.Y);
		YawAxis(MoveAxisVector.X);
	}
	
}

void AASPIAirshipController::Lift(const FInputActionValue& Value)
{
	float Lift = Value.Get<float>();
	if (Airship) {
		UpAxis(Lift);
	}
}

void AASPIAirshipController::ThrustAxis(float input)
{
	///*
	if (input > 0) {
		Airship->MoveForward();
	}
	if (input < 0) {
		Airship->MoveBackward();
	}
	//*/
	// if(input != 0)
	//Airship->AxisForward(input);

}

void AASPIAirshipController::YawAxis(float input)
{
	/*
	if (input > 0) {
		Airship->YawLeft();
	}
	if (input < 0) {
		Airship->YawRight();
	}
	*/
	if(input != 0)
		Airship->Yaw(input);
}

void AASPIAirshipController::UpAxis(float input)
{
	if (input != 0)
		Airship->AxisUpward(input);
}

void AASPIAirshipController::SetAirshipPointer(AASAirship* ship)
{
	this->Airship = ship;
}

void AASPIAirshipController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Lift
		EnhancedInputComponent->BindAction(LiftAction, ETriggerEvent::Triggered, this, &AASPIAirshipController::Lift);
	}
}

void AASPIAirshipController::SetSteeringPos(float input)
{
}

void AASPIAirshipController::SetThrottlePos(float input)
{
}
