// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "AeroKingdom_Projectile.h"
#include "AeroKingdom_AirshipsProjectile.h"
#include "Components/ArrowComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACannon::ACannon()
{
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
	CannonCarrier->SetupAttachment(GetRootComponent());

	/*
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
	*/

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	CannonBarrelAnim = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CannonBarrelAnim"));
	// set path for static mesh. Check path of mesh in content browser.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Barrel(TEXT("/ Script / Engine.SkeletalMesh'/Game/MyBlender/5InchCannonAnim.5InchCannonAnim'"));
	CannonBarrelAnim->SetupAttachment(CannonCarrier);
	// check if path is valid. Check path of mesh in content browser.
	if (Barrel.Succeeded())
	{
		CannonBarrelAnim->SetSkeletalMesh(Barrel.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> BarrelAnim(TEXT("/Script/Engine.AnimSequence'/Game/MyBlender/5InchCannonAnim_Anim.5InchCannonAnim_Anim'"));
	if (BarrelAnim.Succeeded())
	{
		FireAnim = BarrelAnim.Object;
	}

	FirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(CannonBarrelAnim);
	FirePoint->SetRelativeLocation(FVector(370.0f, 0.0f, 0.0f));
}


void ACannon::Fire()
{
	if (bIsFiring && !bOnCooldown) {
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// Spawn the projectile at the muzzle
			World->SpawnActor<AAeroKingdom_Projectile>(ProjectileClass, FirePoint->GetComponentTransform(), ActorSpawnParams);

			// Set Fire Timer
			World->GetTimerManager().SetTimer(FireTimer, this, &ACannon::ResetCoolDown, CoolDownTimer, false);
			bOnCooldown = true;

			// Try and play the niagara Animation
			if (FireEffectMuzzle) {
				// This spawns the chosen effect on the owning WeaponMuzzle SceneComponent
				UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, FireEffectMuzzle, FirePoint->GetComponentLocation() + (FirePoint->GetForwardVector() * fMuzzleAnimOffset) , FirePoint->GetComponentRotation());
			}
		}
	
		// Try and play the sound if specified
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, FirePoint->GetComponentTransform().GetLocation(),1.f,1.f,0.0f, AudioSetting);
		}

		if (FireAnim != nullptr) {
			CannonBarrelAnim->PlayAnimation(FireAnim, false);
		}
	}
}

void ACannon::StartFire()
{
	bIsFiring = true;
	Fire();
}

void ACannon::StopFire()
{
	bIsFiring = false;
	FireTimer.Invalidate();
}

void ACannon::ResetCoolDown()
{
	bOnCooldown = false;
	if (bIsFiring)
		Fire();
}


