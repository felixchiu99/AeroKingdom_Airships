// Fill out your copyright notice in the Description page of Project Settings.


#include "ASCharacterMimic.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "ASMimicBase.h"
#include "../AeroKingdom_AirshipsCharacter.h"

// Sets default values
AASCharacterMimic::AASCharacterMimic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("RootArrow"));
	RootArrow->SetupAttachment(RootComponent);

	// Create a CameraComponent	

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(RootArrow);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AASCharacterMimic::BeginPlay()
{
	Super::BeginPlay();
	
}

void AASCharacterMimic::CalculateViewpoint()
{
	if (Character == nullptr) return;
	if (MimicReference == nullptr) return;
	if (RealReference == nullptr) return;

	FTransform referenceTransform = Character->GetTransform();
	UCameraComponent* referenceCamera = Character->GetFirstPersonCameraComponent();

	FTransform cameraTransform = referenceCamera->GetComponentTransform();
	FVector relativeCamLocation = MimicReference->GetRelativeLocation(cameraTransform.GetLocation());
	FVector mimicCamLocation = RealReference->GetActorLocation() + relativeCamLocation;

	FTransform mimicTransform = referenceTransform;
	FVector relativeLocation = MimicReference->GetRelativeLocation(mimicTransform.GetLocation());
	FVector mimicLocation = RealReference->GetActorLocation() + relativeLocation;


	mimicTransform.SetLocation(mimicLocation);
	this->SetActorTransform(mimicTransform);

	FirstPersonCameraComponent->SetWorldLocation(mimicCamLocation);
	const FRotator PawnViewRotation = Character->GetViewRotation();
	if (!PawnViewRotation.Equals(FirstPersonCameraComponent->GetComponentRotation()))
	{
		FirstPersonCameraComponent->SetWorldRotation(PawnViewRotation);
	}
}

void AASCharacterMimic::SetMimicCamTransform()
{
	if (Character == nullptr) return;
	if (MimicReference == nullptr) return;
	if (RealReference == nullptr) return;
	UCameraComponent* referenceCamera = Character->GetFirstPersonCameraComponent();
	FirstPersonCameraComponent->SetWorldTransform(referenceCamera->GetComponentTransform());
}

void AASCharacterMimic::OnExitViewpoint()
{
	if (Character == nullptr) return;
	if (MimicReference == nullptr) return;
	if (RealReference == nullptr) return;

	UCameraComponent* referenceCamera = Character->GetFirstPersonCameraComponent();
	FTransform cameraTransformReal = referenceCamera->GetComponentTransform();
	FVector relativeLocationReal = MimicReference->GetRelativeLocation(Character->GetTransform().GetLocation());

	FTransform cameraTransformMimic = FirstPersonCameraComponent->GetComponentTransform();
	FVector relativeLocationMimic = RealReference->GetRelativeLocation(this->GetTransform().GetLocation());

	FVector realDiff = referenceCamera->GetComponentLocation() - Character->GetTransform().GetLocation();
	FVector mimicDiff = FirstPersonCameraComponent->GetComponentLocation() - this->GetTransform().GetLocation();

	FTransform referenceTransformMimic = Character->GetTransform();
	FVector newLocationReal = RealReference->GetActorLocation() + relativeLocationMimic;
	referenceTransformMimic.SetLocation(newLocationReal);

	Character->SetActorTransform(referenceTransformMimic);
	Character->SetActorLocation(newLocationReal);

	const FRotator PawnViewRotation = Character->GetViewRotation();
	referenceCamera->SetWorldRotation(PawnViewRotation);

}

// Called every frame
void AASCharacterMimic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateViewpoint();
}

void AASCharacterMimic::SetMimicCharacter(AAeroKingdom_AirshipsCharacter* parent)
{
	Character = parent;
	Controller = Cast<APlayerController>(Character->GetController());

	FirstPersonCameraComponent->SetRelativeLocation(Character->GetFirstPersonCameraComponent()->GetRelativeLocation()); // Position the camera
}

void AASCharacterMimic::UnsetMimicCharacter()
{
	Character = nullptr;
	Controller = nullptr;
}

void AASCharacterMimic::SetMimicView()
{
	FViewTargetTransitionParams Params; 
	Controller->SetViewTarget(this, Params);

}

void AASCharacterMimic::UnsetMimicView()
{
	UCameraComponent* referenceCamera = Character->GetFirstPersonCameraComponent();
	FTransform cameraTransform = referenceCamera->GetComponentTransform();
	FTransform mimicCameraTransform = FirstPersonCameraComponent->GetComponentTransform();

	FViewTargetTransitionParams Params;
	Controller->SetViewTarget(Character, Params);
}

void AASCharacterMimic::SetMimicReference(AASMimicBase* parent)
{
	MimicReference = parent;
	MimicReference->SetHasChild(true);
}

void AASCharacterMimic::UnsetMimicReference()
{
	MimicReference->SetHasChild(false);
	MimicReference = nullptr;
	RealReference = nullptr;
}

void AASCharacterMimic::SetRealReference(AASMimicBase* parent)
{
	RealReference = parent;
}

void AASCharacterMimic::OnEnter(AAeroKingdom_AirshipsCharacter* character, AASMimicBase* mimicChild, AASMimicBase* mimicParent)
{
	SetMimicCharacter(character);
	SetMimicReference(mimicChild);
	SetRealReference(mimicParent);
	CalculateViewpoint();
	SetMimicView();
	this->SetActorHiddenInGame(false);
}

void AASCharacterMimic::OnExit()
{
	OnExitViewpoint();
	UnsetMimicReference();
	UnsetMimicView();
	UnsetMimicCharacter();
	this->SetActorHiddenInGame(true);
}

