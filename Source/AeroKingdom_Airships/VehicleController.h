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

	/** First person camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

public:
	// Sets default values for this pawn's properties
	AVehicleController();

protected:
	/** Called for Interact input */
	void Interact(const FInputActionValue& Value);

	/* Called for Moving Character after Exiting the controller*/
	void MoveCharacter() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
