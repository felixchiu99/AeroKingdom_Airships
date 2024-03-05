// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstCannon.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

// Sets default values
AFirstCannon::AFirstCannon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Character is not occupied at start
	bHasPlayer = false;

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
		//CannonBase->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.5f));
		// set relative location of mesh
		CannonBase->SetRelativeLocation(FVector(0.0f, 0.0f, -1.f));
	}

	// Create a cannon Stand for visualisation
	CannonStand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonStand"));
	CannonStand->SetupAttachment(CannonBase);

	// set path for static mesh. Check path of mesh in content browser.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Stand(TEXT("/Script/Engine.StaticMesh'/Game/MyBlender/5InchCannon_Stand.5InchCannon_Stand'"));
	// check if path is valid. Check path of mesh in content browser.
	if (Stand.Succeeded())
	{
		// mesh = valid path
		CannonStand->SetStaticMesh(Stand.Object);
		// set relative location of mesh
		//CannonStand->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.5f));
		// set relative location of mesh
		CannonStand->SetRelativeLocation(FVector(0.0f, 0.0f, 58.f));
	}

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
		//CannonSupport->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.5f));
		// set relative location of mesh
		CannonSupport->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	}
	CannonSupport->SetupAttachment(CannonStand);

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
	CannonCarrier->SetupAttachment(CannonSupport);

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

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(CannonCarrier);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 20.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = false;
	FirstPersonCameraComponent->SetupAttachment(CannonCarrier);
}

// Called when the game starts or when spawned
void AFirstCannon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirstCannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFirstCannon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Turning
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &AFirstCannon::Turn);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AFirstCannon::Interact);
	}
}

void AFirstCannon::Turn(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Azimuth (Left/Right)
		if (MovementVector.X != 0) {
			FRotator BaseRotation = CannonStand->GetRelativeRotation();
			if (MovementVector.X > 0) {
				BaseRotation.Yaw += fAzimuthSpeed;
			}

			if (MovementVector.X < 0) {
				BaseRotation.Yaw -= fAzimuthSpeed;
			}
			BaseRotation.Yaw = FMath::Clamp(BaseRotation.Yaw, CannonAzimuth.X, CannonAzimuth.Y);
			CannonStand->SetRelativeRotation(BaseRotation);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, BaseRotation.ToString());
		}
		// Elevation (Up/Down)
		if (MovementVector.Y != 0) {
			FRotator BodyRotation = CannonCarrier->GetRelativeRotation();
			if (MovementVector.Y > 0) {
				BodyRotation.Pitch -= fElevationSpeed;
			}

			if (MovementVector.Y < 0) {
				BodyRotation.Pitch += fElevationSpeed;
			}
			BodyRotation.Pitch = FMath::Clamp(BodyRotation.Pitch, CannonElevation.X, CannonElevation.Y);
			CannonCarrier->SetRelativeRotation(BodyRotation);
		}
	}
}

void AFirstCannon::Interact(const FInputActionValue& Value)
{
	/* Return to character */
	UnPossess(GetController());
}

