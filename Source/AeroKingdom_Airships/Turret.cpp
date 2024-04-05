// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Cannon.h"

// Sets default values
ATurret::ATurret()
{
	// Create a cannon base for visualisation
	CannonBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonBase"));
	CannonBase->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
	CannonBase->SetupAttachment(GetRootComponent());
	// set path for static mesh. Check path of mesh in content browser.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Base(TEXT("/Script/Engine.StaticMesh'/Game/MyBlender/5InchCannon_Base.5InchCannon_Base'"));
	// check if path is valid. Check path of mesh in content browser.
	if (Base.Succeeded())
	{
		// mesh = valid path
		CannonBase->SetStaticMesh(Base.Object);
		// set relative location of mesh
		CannonBase->SetRelativeLocation(FVector(0.0f, 0.0f, -1.f));
	}

	// Create a cannon Stand for visualisation
	CannonStand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonStand"));
	CannonStand->SetupAttachment(CannonBase);
	CannonStand->SetRelativeLocation(FVector(0.0f, 0.0f, 0.f));

	// Create a cannon Support for visualisation
	CannonSupport = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonSupport"));
	// set path for static mesh. Check path of mesh in content browser.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Support(TEXT("/Script/Engine.StaticMesh'/Game/MyBlender/5InchCannon_GunSupport.5InchCannon_GunSupport'"));
	// check if path is valid. Check path of mesh in content browser.
	if (Support.Succeeded())
	{
		// mesh = valid path
		CannonSupport->SetStaticMesh(Support.Object);
		// set relative location of mesh
		CannonSupport->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f));
	}
	CannonSupport->SetupAttachment(CannonStand);

	// Create a cannon Pivot for cannon elevation (without changing the cannon)
	CannonPivot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonPivot"));
	CannonPivot->SetupAttachment(CannonSupport);

	// Create a Exit point for Character spawn after using the cannon
	ExitPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ExitPoint"));
	ExitPoint->SetupAttachment(CannonSupport);
	ExitPoint->SetRelativeLocation(FVector(-50.f, -80.0f, -20.f));
	/*
	// Create a cannon Support for visualisation
	CannonCarrier = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonCarrier"));
	// set path for static mesh. Check path of mesh in content browser.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Carrier(TEXT("/Script/Engine.StaticMesh'/Game/MyBlender/5InchCannon_GunCarrier.5InchCannon_GunCarrier'"));
	// check if path is valid. Check path of mesh in content browser.
	if (Carrier.Succeeded())
	{
		// mesh = valid path
		CannonCarrier->SetStaticMesh(Carrier.Object);
	}
	CannonCarrier->SetupAttachment(CannonPivot);

	// Create a cannon Support for visualisation
	CannonBarrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonBarrel"));
	CannonBarrel->SetupAttachment(CannonCarrier);
	// set path for static mesh. Check path of mesh in content browser.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Barrel(TEXT("/Script/Engine.StaticMesh'/Game/MyBlender/5InchCannon_Barrel.5InchCannon_Barrel'"));
	// check if path is valid. Check path of mesh in content browser.
	if (Barrel.Succeeded())
	{
		// mesh = valid path
		CannonBarrel->SetStaticMesh(Barrel.Object);
	}

	FirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(CannonBarrel);
	FirePoint->SetRelativeLocation(FVector(370.0f, 0.0f, 0.0f));
	*/

	//create a cannon sub actor
	Cannon = CreateOptionalDefaultSubobject<UChildActorComponent>(TEXT("Cannon"));
	Cannon->SetChildActorClass(AttachmentType);
	Cannon->SetupAttachment(CannonPivot);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("AimCamera"));
	FirstPersonCameraComponent->AttachToComponent(Cannon, FAttachmentTransformRules::KeepRelativeTransform);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-5.f, 0.f, 28.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (auto PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Turning
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATurret::Turn);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ATurret::Interact);

		// Fire
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATurret::OnClickFire);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &ATurret::UnClickFire);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Canceled, this, &ATurret::UnClickFire);
	}
}


void ATurret::OnClickFire(const FInputActionValue& Value)
{
	if (bIsAutoFire) {
		if (!bIsFiring) {
			StartFire();
		}
		else {
			StopFire();
		}
		bIsFiring = !bIsFiring;
	}
	else {
		StartFire();
	}
}

void ATurret::UnClickFire(const FInputActionValue& Value)
{
	if (!bIsAutoFire) {
		StopFire();
	}
}


void ATurret::StartFire()
{
	((ACannon*)Cannon->GetChildActor())->StartFire();
}
void ATurret::StopFire()
{
	((ACannon*)Cannon->GetChildActor())->StopFire();
}

void ATurret::Fire(const FInputActionValue& Value)
{
	((ACannon*)Cannon->GetChildActor())->Fire();
}

void ATurret::RotateLeft()
{
	RotateBase(-fAzimuthSpeed * FApp::GetDeltaTime());
}

void ATurret::RotateRight()
{
	RotateBase(fAzimuthSpeed * FApp::GetDeltaTime());
}

void ATurret::RotateBase(const float input)
{
	FRotator BaseRotation = CannonStand->GetRelativeRotation();
	BaseRotation.Yaw += input;
	if (bLimitAzimuth)
		BaseRotation.Yaw = FMath::Clamp(BaseRotation.Yaw, CannonAzimuth.X, CannonAzimuth.Y);
	CannonStand->SetRelativeRotation(BaseRotation);
}

void ATurret::RotateUp()
{
	RotateElevation(fElevationSpeed * FApp::GetDeltaTime());
}

void ATurret::RotateDown()
{
	RotateElevation(-fElevationSpeed * FApp::GetDeltaTime());
}

void ATurret::RotateElevation(const float input)
{
	FRotator BodyRotation = CannonPivot->GetRelativeRotation();
	BodyRotation.Pitch += input;
	BodyRotation.Pitch = FMath::Clamp(BodyRotation.Pitch, CannonElevation.X, CannonElevation.Y);
	CannonPivot->SetRelativeRotation(BodyRotation);
}

void ATurret::MoveCharacter()
{
	PossessedChar->SetActorLocation(ExitPoint->GetComponentLocation());
	PossessedChar->SetActorRotation(ExitPoint->GetComponentRotation());
}

void ATurret::Turn(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Azimuth (Left/Right)
		if (MovementVector.X != 0) {
			if (MovementVector.X > 0) {
				RotateRight();
			}

			if (MovementVector.X < 0) {
				RotateLeft();
			}
		}
		// Elevation (Up/Down)
		if (MovementVector.Y != 0) {
			if (MovementVector.Y > 0) {
				RotateDown();
			}

			if (MovementVector.Y < 0) {
				RotateUp();
			}
		}
	}
}



void ATurret::Interact(const FInputActionValue& Value)
{
	/* Return to character */
	AController* controller = GetController();
	if (auto PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(DefaultMappingContext);
		}
	}
	if(controller)
		UnPossess(controller);
}
