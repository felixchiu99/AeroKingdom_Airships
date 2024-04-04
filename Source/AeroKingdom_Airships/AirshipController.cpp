// Fill out your copyright notice in the Description page of Project Settings.


#include "AirshipController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


AAirshipController::AAirshipController()
{
	VehicleControllerBase->SetCollisionProfileName(FName("ShipComponent"));
}

void AAirshipController::BeginPlay()
{
	Super::BeginPlay();
}

void AAirshipController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MoveAxisVector = Value.Get<FVector2D>();

	if (Airship) {
		ThrustAxis(MoveAxisVector.Y);
		YawAxis(MoveAxisVector.X);
	}
	
}

void AAirshipController::Lift(const FInputActionValue& Value)
{
	float Lift = Value.Get<float>();
	if (Airship) {
		UpAxis(Lift);
	}
}

void AAirshipController::ThrustAxis(float input)
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

void AAirshipController::YawAxis(float input)
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

void AAirshipController::UpAxis(float input)
{
	if (input != 0)
		Airship->AxisUpward(input);
}

void AAirshipController::SetAirshipPointer(AAirship* ship)
{
	this->Airship = ship;
}

void AAirshipController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Lift
		EnhancedInputComponent->BindAction(LiftAction, ETriggerEvent::Triggered, this, &AAirshipController::Lift);
	}
}
