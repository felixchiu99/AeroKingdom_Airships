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
	CannonBase->SetupAttachment(GetRootComponent());

	// Create a cannon base for visualisation
	CannonBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonBaseMesh"));
	CannonBaseMesh->SetupAttachment(CannonBase);

	// set path for static mesh. Check path of mesh in content browser.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Script/Engine.StaticMesh'/Engine/EngineMeshes/Cube.Cube'"));
	// check if path is valid. Check path of mesh in content browser.
	if (Cube.Succeeded())
	{
		// mesh = valid path
		CannonBaseMesh->SetStaticMesh(Cube.Object);
		// set relative location of mesh
		CannonBaseMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.5f));
		// set relative location of mesh
		CannonBaseMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -50.f));
	}

	// Create a cannon Body for visualisation
	CannonBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonBody"));
	CannonBody->SetupAttachment(CannonBase);

	// Create a cannon base for visualisation
	CannonBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonBodyMesh"));
	CannonBodyMesh->SetupAttachment(CannonBody);

	if (Cube.Succeeded())
	{
		// mesh = valid path
		CannonBodyMesh->SetStaticMesh(Cube.Object);
		// set relative location of mesh
		CannonBodyMesh->SetRelativeScale3D(FVector(2.0f, 0.1f, 0.1f));
		// set relative location of mesh
		CannonBodyMesh->SetRelativeLocation(FVector(100.0f, 0.0f, -30.f));
	}

	// CapsuleComponent initialization
	EnterCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("EnterCapsuleComponent"));
	EnterCapsuleComponent->InitCapsuleSize(44.f, 60.f);
	EnterCapsuleComponent->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	EnterCapsuleComponent->SetupAttachment(CannonBase);
	EnterCapsuleComponent->SetRelativeScale3D(FVector(2.0f, 2.0f, 1.0f));
	EnterCapsuleComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = false;
	FirstPersonCameraComponent->SetupAttachment(CannonBodyMesh);
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

	}
}

void AFirstCannon::Turn(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));



	}
}

