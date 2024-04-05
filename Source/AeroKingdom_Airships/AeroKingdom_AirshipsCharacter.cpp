// Copyright Epic Games, Inc. All Rights Reserved.

#include "AeroKingdom_AirshipsCharacter.h"
#include "AeroKingdom_AirshipsProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InteractableInterface.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AAeroKingdom_AirshipsCharacter

AAeroKingdom_AirshipsCharacter::AAeroKingdom_AirshipsCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void AAeroKingdom_AirshipsCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

//////////////////////////////////////////////////////////////////////////// Input

void AAeroKingdom_AirshipsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAeroKingdom_AirshipsCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAeroKingdom_AirshipsCharacter::Look);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AAeroKingdom_AirshipsCharacter::Interact);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AAeroKingdom_AirshipsCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AAeroKingdom_AirshipsCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AAeroKingdom_AirshipsCharacter::Interact(const FInputActionValue& Value)
{
	FVector Start;
	FVector End;

	FVector PlayerEyesLoc;
	FRotator PlayerEyesRot;

	GetActorEyesViewPoint(PlayerEyesLoc, PlayerEyesRot);

	float LineTraceDistance = 600.f;

	Start = PlayerEyesLoc;
	End = PlayerEyesLoc + (PlayerEyesRot.Vector() * LineTraceDistance);

	FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true, this);

	FHitResult InteractHit = FHitResult(ForceInit);

	// get hit object type
	FCollisionObjectQueryParams ObjectTypeParams;
	ObjectTypeParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectTypeParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectTypeParams.AddObjectTypesToQuery(ECC_GameTraceChannel2);
	ObjectTypeParams.AddObjectTypesToQuery(ECC_GameTraceChannel3);
	ObjectTypeParams.AddObjectTypesToQuery(ECC_GameTraceChannel4);

	//bool bIsHit = GetWorld()->LineTraceSingleByChannel(InteractHit, Start, End, ECC_GameTraceChannel3, TraceParams);
	bool bIsHit = GetWorld()->LineTraceSingleByObjectType(InteractHit, Start, End, ObjectTypeParams, TraceParams);
	if (bIsHit && InteractHit.GetActor() != this) {
		if (InteractHit.GetActor()->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass())) {
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interactable!"));
			//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.f, ECC_WorldStatic, 1.f);

			/* see if the thing is already possessed */
			IInteractableInterface* InteractableObj = Cast<IInteractableInterface>(InteractHit.GetActor());
			APawn* PossessAbleObj = Cast<APawn>(InteractHit.GetActor());
			if (InteractableObj && PossessAbleObj && !InteractableObj->IsPossessed()) {
				/* Save controller */
				if (!SavedController) {
					SavedController = GetController();
				}

				/* unpossess current controller */
				SavedController->UnPossess();
				/* Disable state management on the possessed character */
				/* Disable Movement */
				//GetCharacterMovement()

				/* Possess Character */
				InteractableObj->Possess(this);
				SavedController->Possess(PossessAbleObj);

				/* Enable Movement */
			}
		}
		else {
			//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5.f, ECC_WorldStatic, 1.0f);
		}
	}
	else {
		//DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 5.f, ECC_WorldStatic, 1.0f);
	}
}

void AAeroKingdom_AirshipsCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AAeroKingdom_AirshipsCharacter::GetHasRifle()
{
	return bHasRifle;
}