// Fill out your copyright notice in the Description page of Project Settings.

#include "AeroKingdom_Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GIAirshipGameInstance.h"
#include "ASDamageable/ASA_DamageableActor.h"
#include "ASComponents/ASAC_DurabilityComponent.h"
#include "ASTurret.h"


// Sets default values
AAeroKingdom_Projectile::AAeroKingdom_Projectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AAeroKingdom_Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Create a Mesh for visualisation
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(CollisionComp);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 7000.f;
	ProjectileMovement->MaxSpeed = 7500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

}

float AAeroKingdom_Projectile::GetProjectileMovementSpeed()
{
	return GetProjectileMovement()->InitialSpeed;
}

void AAeroKingdom_Projectile::BeginPlay()
{
	Super::BeginPlay();
	// Die after 3 seconds by default
	InitialLifeSpan = fExplodeTimer + 1;
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		World->GetTimerManager().SetTimer(ExplosionTimer, this, &AAeroKingdom_Projectile::OnExplode, fExplodeTimer, false);
	}
}

void AAeroKingdom_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAeroKingdom_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if (IsValidObject(OtherActor, OtherComp))
	{
		if (OtherComp->IsSimulatingPhysics()) {
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		}
		if (HasDurability(OtherActor)) {
			AddDamage(OtherActor);
		}

	}
	OnHitExplode();
}

void AAeroKingdom_Projectile::OnExplode()
{
	PlayExplodeAnimation(ShellExplosion);
	OnDestroy();
}

void AAeroKingdom_Projectile::OnHitExplode()
{
	PlayExplodeAnimation(ShellOnHit);
	OnDestroy();
}

void AAeroKingdom_Projectile::OnDestroy()
{
	PlayExplodeSound();
	Destroy();
}

void AAeroKingdom_Projectile::PlayExplodeAnimation(UNiagaraSystem* Animation)
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		// Try and play the niagara Animation
		if (Animation) {
			// This spawns the chosen effect on the owning WeaponMuzzle SceneComponent
			UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, Animation, GetTransform().GetLocation());
		}
	}
}

void AAeroKingdom_Projectile::PlayExplodeSound()
{
	// Try and play the sound if specified
	if (ExplosionSound != nullptr)
	{
		//float fSFXVolume = GetGameInstance<UGIAirshipGameInstance>()->GetSFXVolume();
		//UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetTransform().GetLocation(), fSFXVolume, 1.f, 0.0f, AudioSetting);
		GetGameInstance<UGIAirshipGameInstance>()->SSPlaySFXAtLocation(this, ExplosionSound, GetActorLocation(), GetActorRotation(), 1.f, 1.f, 0.0f, AudioSetting);
	}
}

bool AAeroKingdom_Projectile::IsValidObject(AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
	return (OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr);
}

void AAeroKingdom_Projectile::AddDamage(AActor* OtherActor)
{
	AASA_DamageableActor* DamageableObj = GetDurabilityComponent(OtherActor);
	DamageableObj->AddDamage(CalculateDamage());
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Damage " + FString::SanitizeFloat(CalculateDamage())));

}

bool AAeroKingdom_Projectile::HasDurability(AActor* OtherActor)
{
	AASA_DamageableActor* DamageableObj = GetDurabilityComponent(OtherActor);
	return DamageableObj != nullptr;
}

AASA_DamageableActor* AAeroKingdom_Projectile::GetDurabilityComponent(AActor* OtherActor)
{
	UASAC_DurabilityComponent* DamageableComponent = Cast<UASAC_DurabilityComponent>(OtherActor->GetComponentByClass<UASAC_DurabilityComponent>());
	if (!DamageableComponent) {
		return nullptr;
	}
	AASA_DamageableActor* DamageableObj = Cast<AASA_DamageableActor>(DamageableComponent->GetOwner());
	return DamageableObj;
}

float AAeroKingdom_Projectile::CalculateDamage()
{
	return fBaseDamage;
}






