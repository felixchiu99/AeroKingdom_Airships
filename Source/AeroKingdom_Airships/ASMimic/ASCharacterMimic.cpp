// Fill out your copyright notice in the Description page of Project Settings.


#include "ASCharacterMimic.h"
#include "Camera/CameraComponent.h"
#include "ASMimicBase.h"
#include "../AeroKingdom_AirshipsCharacter.h"

// Sets default values
AASCharacterMimic::AASCharacterMimic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create a CameraComponent	

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(RootComponent);
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

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "tick");

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

	FirstPersonCameraComponent->SetWorldTransform(cameraTransform);
	FirstPersonCameraComponent->SetWorldLocation(mimicCamLocation);

}

void AASCharacterMimic::MimicTransform()
{
	if (Character == nullptr) return;
	if (MimicReference == nullptr) return;
	if (RealReference == nullptr) return;
	UCameraComponent* referenceCamera = Character->GetFirstPersonCameraComponent();
	FTransform referenceTransform = Character->GetTransform();
	FVector relativeLocation = MimicReference->GetRelativeLocation(referenceTransform.GetLocation());
	FVector mimicLocation = RealReference->GetActorLocation() + relativeLocation;

	FTransform mimicTransform = referenceTransform;
	mimicTransform.SetLocation(mimicLocation);

	this->SetActorTransform(mimicTransform);

}

void AASCharacterMimic::OnExitViewpoint()
{
	if (Character == nullptr) return;
	if (MimicReference == nullptr) return;
	if (RealReference == nullptr) return;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("OnExitViewpoint"));

	UCameraComponent* referenceCamera = Character->GetFirstPersonCameraComponent();
	FTransform cameraTransformReal = referenceCamera->GetComponentTransform();
	FVector relativeLocationReal = MimicReference->GetRelativeLocation(Character->GetTransform().GetLocation());

	FTransform cameraTransformMimic = FirstPersonCameraComponent->GetComponentTransform();
	FVector relativeLocationMimic = RealReference->GetRelativeLocation(this->GetTransform().GetLocation());

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Real Relative" + relativeLocationReal.ToCompactString());
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Mimic Relative" + relativeLocationMimic.ToCompactString());
	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Real Cam Relative" + referenceCamera->GetRelativeLocation().ToCompactString());
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Mimic Cam Relative" + FirstPersonCameraComponent->GetRelativeLocation().ToCompactString());

	FTransform referenceTransformMimic = Character->GetTransform();
	FVector newLocationReal = RealReference->GetActorLocation() + relativeLocationMimic;
	referenceTransformMimic.SetLocation(newLocationReal);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Temp Relative" + referenceTransformMimic.ToHumanReadableString());

	Character->SetActorTransform(referenceTransformMimic);
	Character->SetActorLocation(newLocationReal);

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
	UCameraComponent* referenceCamera = Character->GetFirstPersonCameraComponent();
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(referenceCamera->GetRelativeLocation(), referenceCamera->GetRelativeRotation());
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

void AASCharacterMimic::OnExit()
{
	OnExitViewpoint();
	UnsetMimicView();
	UnsetMimicReference();
	UnsetMimicCharacter();
}

