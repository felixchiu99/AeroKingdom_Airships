// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InteractableInterface.h"
#include "Logging/LogMacros.h"
#include "FirstCannon.generated.h"

class UInputComponent;
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class UArrowComponent;
class UCapsuleComponent;
class ACannon;
struct FInputActionValue;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AFirstCannon : public APawn, public IInteractableInterface
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

	/*
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* CannonCarrier;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* CannonBarrel;

	UPROPERTY(VisibleDefaultsOnly)
	UArrowComponent* FirePoint;
	*/

	UPROPERTY(VisibleDefaultsOnly)
	UCapsuleComponent* EnterCapsuleComponent;

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
	TSubclassOf<ACannon>	AttachmentType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cannon", meta = (AllowPrivateAccess = "true", AllowedClasses = "Cannon"))
	class UChildActorComponent* Cannon;


public:
	// Sets default values for this pawn's properties
	AFirstCannon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/** Bool for whether there is a player controlling*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasPlayer;

	/** float for cannon Azimuth Speed*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Attributes")
	float fAzimuthSpeed = 0.7f;

	/** float for cannon Elevation Speed*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Attributes")
	float fElevationSpeed = 0.5f;

	/** bool for allowing limitless rotation*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Attributes")
	bool bLimitAzimuth = true;

	/** FVector2D for Cannon Azimuth (Left/Right) Arc*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Attributes", meta = (EditCondition = "bLimitAzimuth", EditConditionHides))
	FVector2D CannonAzimuth = FVector2D(-50,50);

	/** FVector2D for Cannon Elevation (Up/Down) Arc*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Attributes")
	FVector2D CannonElevation = FVector2D(-20, 75);

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
	void StartFire(const FInputActionValue& Value);
	
	/** Called for StopFire input */
	void StopFire(const FInputActionValue& Value);

	/** Called for Fire input */
	void Fire(const FInputActionValue& Value);
};
