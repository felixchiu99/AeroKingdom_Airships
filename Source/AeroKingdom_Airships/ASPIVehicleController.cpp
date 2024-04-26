// Fill out your copyright notice in the Description page of Project Settings.


#include "ASPIVehicleController.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Sets default values
AASPIVehicleController::AASPIVehicleController()
{
	// Create a base for visualisation
	VehicleControllerBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ControllerBase"));
	VehicleControllerBase->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
	VehicleControllerBase->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Base(TEXT("/ Script / Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	// check if path is valid. Check path of mesh in content browser.
	if (Base.Succeeded())
	{
		// mesh = valid path
		VehicleControllerBase->SetStaticMesh(Base.Object);
	}
	
	// Create a Exit point for Character spawn after using the controlable object
	ExitPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ExitPoint"));
	ExitPoint->SetupAttachment(VehicleControllerBase);
	ExitPoint->SetRelativeLocation(FVector(-80.f, 0.f, 0.f));

	// Create a point for Spinning  the camera
	CameraPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraPoint"));
	CameraPoint->SetupAttachment(VehicleControllerBase);
	CameraPoint->SetRelativeLocation(FVector(-60.f, 0.f, 80.f));

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("1pCamera"));
	FirstPersonCameraComponent->AttachToComponent(CameraPoint, FAttachmentTransformRules::KeepRelativeTransform);
	FirstPersonCameraComponent->bUsePawnControlRotation = false;

	// Create a CameraComponent	
	ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("3pCamera"));
	ThirdPersonCameraComponent->AttachToComponent(CameraPoint, FAttachmentTransformRules::KeepRelativeTransform);
	ThirdPersonCameraComponent->bUsePawnControlRotation = false;
	ThirdPersonCameraComponent->SetRelativeLocation(FVector(-300.f, 0.f, 0.f));
	
	// Attach Tooltip Display to Component
	TooltipDisplayPoint->SetupAttachment(VehicleControllerBase);

	/*
	TooltipWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Tooltip Widget"));
	TooltipWidget->AttachToComponent(VehicleControllerBase, FAttachmentTransformRules::KeepRelativeTransform);
	TooltipWidget->SetWidgetSpace(EWidgetSpace::Screen);
	TooltipWidget->SetDrawAtDesiredSize(true);
	*/
	
}

// Called to bind functionality to input
void AASPIVehicleController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AASPIVehicleController::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AASPIVehicleController::Look);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AASPIVehicleController::Interact);
	}

}

void AASPIVehicleController::BeginPlay()
{
	Super::BeginPlay();
	//UWidgetTooltips* Tooltips = Cast<UWidgetTooltips>(TooltipWidget->GetUserWidgetObject());
	//Tooltips->SetToolTipInterface(Cast<UIToolTipInterface>(this));
}

void AASPIVehicleController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MoveAxisVector = Value.Get<FVector2D>();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, MoveAxisVector.ToString());
}

void AASPIVehicleController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("controlled"));

		FRotator CamRotation = CameraPoint->GetRelativeRotation();
		// add yaw input to controller
		CamRotation.Yaw += LookAxisVector.X;
		//CamRotation.Yaw = FMath::Clamp(CamRotation.Yaw, CannonAzimuth.X, CannonAzimuth.Y);
		CameraPoint->SetRelativeRotation(CamRotation);

		FRotator CamPitch = FirstPersonCameraComponent->GetRelativeRotation();
		// add pitch input to controller
		CamPitch.Pitch += -LookAxisVector.Y;
		CamPitch.Pitch = FMath::Clamp(CamPitch.Pitch, -89.9f, 89.9f);

		FirstPersonCameraComponent->SetRelativeRotation(CamPitch);
	}
}

void AASPIVehicleController::MoveCharacter()
{
	PossessedChar->SetActorLocation(ExitPoint->GetComponentLocation());
	FVector Rotation = ExitPoint->GetComponentRotation().Euler();
	Rotation.Z = 0;
	PossessedChar->SetActorRotation(Rotation.ToOrientationRotator());

}

void AASPIVehicleController::Interact(const FInputActionValue& Value)
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
	if (controller)
		UnPossess(controller);
}

