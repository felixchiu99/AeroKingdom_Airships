// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InteractableInterface.h"
#include "VehicleController.generated.h"

class UInputComponent;
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class UArrowComponent;
struct FInputActionValue;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AVehicleController : public APawn, public IInteractableInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* VehicleControllerBase;

	UPROPERTY(VisibleDefaultsOnly, Category = Interaction)
	UArrowComponent* ExitPoint;

	UPROPERTY(VisibleDefaultsOnly, Category = Camera)
	UStaticMeshComponent* CameraPoint;

	/** First person camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LiftAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

public:
	// Sets default values for this pawn's properties
	AVehicleController();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for Interact input */
	void Interact(const FInputActionValue& Value);

	/* Called for Moving Character after Exiting the controller*/
	void MoveCharacter() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
