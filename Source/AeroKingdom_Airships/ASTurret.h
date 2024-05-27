// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ASInteractablePawn.h"
#include "Logging/LogMacros.h"
#include "ASTurret.generated.h"

class UInputComponent;
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class UArrowComponent;
class UCapsuleComponent;
class AASCannon;
class UASAC_TurretTargetList;

struct FInputActionValue;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AASTurret : public AASInteractablePawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* CannonBase;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* CannonStand;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* CannonSupport;

	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* CannonPivot;

	UPROPERTY(VisibleDefaultsOnly, Category = Interaction)
	UArrowComponent* ExitPoint;

	UPROPERTY(VisibleDefaultsOnly)
	UCapsuleComponent* EnterCapsuleComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UASAC_TurretTargetList* TargetList;

	/** First person camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TurnAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ChildActorComponent, meta = (OnlyPlaceable, AllowPrivateAccess = "true"))
	TSubclassOf<AASCannon>	AttachmentType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cannon", meta = (AllowPrivateAccess = "true", AllowedClasses = "Cannon"))
	class UChildActorComponent* Cannon;

public:
	// Sets default values for this pawn's properties
	AASTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** Called for Turning input */
	void Turn(const FInputActionValue& Value);

	/** Called for Interact input */
	void Interact(const FInputActionValue& Value);

	/** Called for OnFire input */
	void OnClickFire(const FInputActionValue& Value);
	
	/** Called for StopFire input */
	void UnClickFire(const FInputActionValue& Value);

	/** Called for StartFire function*/
	void StartFire();

	/** Called for StopFire function*/
	void StopFire();

	/** Called for Turn the turret Left */
	void RotateLeft();

	/** Called for Turn the turret Right */
	void RotateRight();

	/** Called for Turn the turret Up */
	void RotateUp();

	/** Called for Turn the turret Down */
	void RotateDown();

	void MoveCharacter() override;

public:
	/** Called for Turn the turret*/
	void RotateBase(const float input);

	/** Called for Elevate the turret*/
	void RotateElevation(const float input);

	/* return the aiming forward Vector*/
	FVector GetAimingVector();

	/* return the Vector pointing to Target*/
	FVector GetTargetVector(FVector TargetLocation);

	/* return the difference in altitude between the target and the cannon*/
	float GetAltitudeDifference(FVector TargetLocation);

	/* return the Initial Speed of the projectile cannon*/
	float GetProjectileVelocity(FVector TargetLocation);

	/** Called for Fire input */
	void Fire();

	UASAC_TurretTargetList* GetTargetList();

	/* return the initial Speed of the projectile the cannon has*/
	float GetProjectileInitialSpeed();

	/* return the current Elevation Angle of the cannnon*/
	float GetCurrentElevationAngle();

	/* return a Calculated Elevation based on the distance and target*/
	float CalculateTurretElevation(FVector AimTarget);

	/* return the ElevationAccuracyModifier of the cannnon*/
	float GetElevationAccuracyModifier() { return fElevationAccuracyModifier; }

	/* return the ElevationAccuracyModifier of the cannnon*/
	float GetElevationSpeedModifier() { return fElevationSpeedModifier; }

	/* return the AzimuthAccuracyModifier of the cannnon*/
	float GetAzimuthAccuracyModifier() { return fAzimuthAccuracyModifier; }

	/* return the AzimuthAccuracyModifier of the cannnon*/
	float GetAzimuthSpeedModifier() { return fAzimuthSpeedModifier; }

	/* Test if the Target would be in range of the turret's limits*/
	bool IsTargetInRange(FVector AimLocation);

protected:
	/** FVector2D for Cannon Azimuth (Left/Right) Arc*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Attributes", meta = (EditCondition = "bLimitAzimuth", EditConditionHides))
	FVector2D CannonAzimuth = FVector2D(-50, 50);

	/** FVector2D for Cannon Elevation (Up/Down) Arc*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Attributes")
	FVector2D CannonElevation = FVector2D(-20, 75);

	/** float for cannon Azimuth Speed per second*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Attributes")
	float fAzimuthSpeed = 30.f;

	/** float for cannon Elevation Speed per second*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Attributes")
	float fElevationSpeed = 30.f;

	/** bool for allowing limitless rotation*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Attributes")
	bool bLimitAzimuth = true;

	/** bool for Attached cannon firing mode*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Attributes")
	bool bIsAutoFire = false;

	/** bool for Attached cannon firing mode*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cannon Attributes", meta = (EditCondition = "bIsAutoFire", EditConditionHides))
	bool bIsFiring = false;

	/* AI Aimming Assist*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Attributes|AI")
	float fElevationAccuracyModifier = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Attributes|AI")
	float fElevationSpeedModifier = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Attributes|AI")
	float fAzimuthAccuracyModifier = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Attributes|AI")
	float fAzimuthSpeedModifier = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Attributes|AI")
	float fAimDistanceModifier = 0.00001f;
};
