// Copyright Epic Games, Inc. All Rights Reserved.

#include "AeroKingdom_AirshipsCharacter.h"
#include "AeroKingdom_AirshipsProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ASIInteractableInterface.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

#include "Components/WidgetComponent.h"
#include "WidgetTooltipComponent.h"
#include "WidgetTooltips.h"
#include "UWTabMenu.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AAeroKingdom_AirshipsCharacter

AAeroKingdom_AirshipsCharacter::AAeroKingdom_AirshipsCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

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

	TooltipWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Tooltip Widget"));
	TooltipWidget->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	TooltipWidget->SetWidgetSpace(EWidgetSpace::Screen);
	TooltipWidget->SetDrawAtDesiredSize(true);
	TooltipWidget->SetOnlyOwnerSee(true);
	TooltipWidget->SetVisibility(true);

}

void AAeroKingdom_AirshipsCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Only create the UI on the local machine (dose not excist on the server.)
	if (IsLocalPlayerControllerViewingAPawn())
	{
		if (TabMenuClass) // Check the selected UI class is not NULL
		{
			if (!TabMenuWidget) // If the widget is not created and == NULL
			{
				TabMenuWidget = Cast<UUWTabMenu> (CreateWidget<UUserWidget>(GetWorld(), TabMenuClass)); // Create Widget
				if (!TabMenuWidget)
					return;
				TabMenuWidget->AddToViewport(); // Add it to the viewport so the Construct() method in the UUserWidget:: is run.
				TabMenuWidget->SetVisibility(ESlateVisibility::Hidden); // Set it to hidden so its not open on spawn.
			}
		}
	}
}

void AAeroKingdom_AirshipsCharacter::Tick(float DeltaTime)
{
	if (LookingAt->IsValidLowLevel() && IsInteractable())
	{
		/* Update looking at world position*/
		//TooltipWidget->SetWorldLocation(LookingAt->GetActorLocation());
		UpdateTooltipLocation();
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
		
		// Menu
		EnhancedInputComponent->BindAction(MenuAction, ETriggerEvent::Started, this, &AAeroKingdom_AirshipsCharacter::OpenTabMenu);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AAeroKingdom_AirshipsCharacter::ToggleTabMenu()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("hi "));
	if (TabMenuWidget)
		TabMenuWidget->ToggleMenu();
}

void AAeroKingdom_AirshipsCharacter::UpdateTooltipLocation()
{
	IASIInteractableInterface* Interactable = Cast<IASIInteractableInterface>(LookingAt);
	if (Interactable == nullptr)
		return;
	if (Interactable->HasTooltipDisplayPoint()) {
		TooltipWidget->SetWorldLocation(Interactable->GetTooltipDisplayPoint());
	}
	else {
		TooltipWidget->SetWorldLocation(LookingAt->GetActorLocation());
	}
}

void AAeroKingdom_AirshipsCharacter::UpdateTooltipLabel(UWidgetTooltips* Tooltip)
{
	IASIInteractableInterface* Interactable = Cast<IASIInteractableInterface>(LookingAt);
	Tooltip->SetKeyName(Interactable->GetTooltipDisplayName().ToString() + " : " + GetMappedKeys(InteractAction));
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
	GetLookedAt();

}

void AAeroKingdom_AirshipsCharacter::Interact(const FInputActionValue& Value)
{
	GetMappedKeys(InteractAction);

	if (IsInteractable()) {
		InteractPossessable();
	}
	else {
		//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5.f, ECC_WorldStatic, 1.0f);
	}
}

void AAeroKingdom_AirshipsCharacter::OpenTabMenu(const FInputActionValue& Value)
{
	ToggleTabMenu();
}

FString AAeroKingdom_AirshipsCharacter::GetMappedKeys(UInputAction* QueryAction)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			auto keys = Subsystem->QueryKeysMappedToAction(QueryAction);
			if (!keys.IsEmpty()) {
				return keys[0].ToString();
			}
		}
	}
	return "N/A";
}

void AAeroKingdom_AirshipsCharacter::GetLookedAt()
{
	FVector Start;
	FVector End;

	FVector PlayerEyesLoc;
	FRotator PlayerEyesRot;

	GetActorEyesViewPoint(PlayerEyesLoc, PlayerEyesRot);

	float LineTraceDistance = 600.f;

	Start = PlayerEyesLoc;
	End = PlayerEyesLoc + (PlayerEyesRot.Vector() * LineTraceDistance);

	FCollisionQueryParams TraceParams(FName(TEXT("LookAtTrace")), true, this);

	FHitResult InteractHit = FHitResult(ForceInit);

	// get hit object type
	FCollisionObjectQueryParams ObjectTypeParams;
	ObjectTypeParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectTypeParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectTypeParams.AddObjectTypesToQuery(ECC_GameTraceChannel2);
	ObjectTypeParams.AddObjectTypesToQuery(ECC_GameTraceChannel3);
	ObjectTypeParams.AddObjectTypesToQuery(ECC_GameTraceChannel4);

	bool bShowTooltip = false;
	bool bIsHit = GetWorld()->LineTraceSingleByObjectType(InteractHit, Start, End, ObjectTypeParams, TraceParams);
	if (bIsHit && InteractHit.GetActor() != this) {
		if (LookingAt != InteractHit.GetActor()) {
			LookingAt = InteractHit.GetActor();
			if (IsInteractable()) {
				UWidgetTooltips* Tooltip = Cast<UWidgetTooltips>(TooltipWidget->GetUserWidgetObject());
				if (Tooltip) {
					UpdateTooltipLabel(Tooltip);
					//Tooltip->SetKeyName("test : " + GetMappedKeys(InteractAction));
					UpdateTooltipLocation();
					TooltipWidget->SetVisibility(true);
					bShowTooltip = true;
				}
			}
		}
		else {
			bShowTooltip = true;
		}
		
	}


	if(!bShowTooltip) {
		LookingAt = nullptr;
		TooltipWidget->SetVisibility(false);
	}
}

bool AAeroKingdom_AirshipsCharacter::IsInteractable()
{
	if (!LookingAt)
		return false;
	if (LookingAt->GetClass()->ImplementsInterface(UASIInteractableInterface::StaticClass())) {
		return true;
	}
	return false;
}

void AAeroKingdom_AirshipsCharacter::InteractPossessable()
{
	/* see if the thing is already possessed */
	IASIInteractableInterface* InteractableObj = Cast<IASIInteractableInterface>(LookingAt);
	InteractableObj->SetKeyName(FText::FromString("Test"));

	APawn* PossessAbleObj = Cast<APawn>(LookingAt);
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
		InteractableObj->DebugKeyName();
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