// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASVehicle.h"
#include "ASAirship.generated.h"

class AASPIAirshipController;
class UArrowComponent;
/**
 * 
 */
UCLASS()
class AEROKINGDOM_AIRSHIPS_API AASAirship : public AASVehicle
{
	GENERATED_BODY()

	protected:
		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* Balloon;

		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* ShipBase;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component-Cannon", meta = (OnlyPlaceable, AllowPrivateAccess = "true"))
		TSubclassOf<AASPIAirshipController>	ACAttachmentType;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AirshipController", meta = (AllowPrivateAccess = "true", AllowedClasses = "Cannon"))
		class UChildActorComponent* AirshipController;

		UPROPERTY(VisibleDefaultsOnly)
		UArrowComponent* RudderPoint;

	public:
		// Sets default values for this actor's properties
		AASAirship();

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:
		// Called every frame
		virtual void Tick(float DeltaTime) override;

		//Throttle Input
		virtual void MoveForward() override;

		virtual void MoveBackward() override;

		virtual void AxisForward(float input);

		virtual void AxisUpward(float input);

		// Yaw Input
		virtual void Yaw(float input);

		void ApplyYaw(float DeltaTime);

		void ReduceYaw(float DeltaTime);

		// Lift
		void ApplyLift(float StepTime);

		// Apply Neutral Lift (not including player reaction force)
		void ApplyNeutralLift(float StepTime, bool bDebug = false);

		// Apply Reactive Lift (counteract player reaction force)
		void ApplyReactiveLift(float StepTime, bool bDebug = false);

		void UpdateHeight();

		// Linear Damping
		void ApplyDamping(float DeltaTime);

		void DisplayAxisSpeed();

		FVector ApplyAbsAxis(FVector Axis);

	protected:
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LinearDamping")
		FVector SeperatedLinearDamping = FVector(0.3, 0.5, 0.1);

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LinearDamping")
		float MaxSpeed = 200.f;

		/** FVector2D for Rudder Azimuth (Left/Right) Arc*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rudder Attributes")
		FVector2D RudderLimits = FVector2D(-80, 80);

		// TurnSpeed by deg/second
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rudder Attributes")
		float fRudderTurnSpeed = 30.f;

		// How much the torque should be multiplied
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rudder Attributes")
		float fRudderTorqueMultiplier = 1.0f;

		/** FVector2D for Min/Max Height of airship to reach*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lift Attributes")
		FVector2D LiftLimit = FVector2D(-300, 25000);

private:
		bool bRudderTurn = false;

		float fRudderRotation = 0;
		float fThrottleForward = 0;
		float fThrottleUpward = 0;

		float fHeight = 0;
		float fCurrentHeight = 0;
		float fActiveLiftPower = 15.f;
		float fReactiveLiftMultiplier = 1.2f;

		float PushStrength = 5000000.f;

};
