// Copyright Epic Games, Inc. All Rights Reserved.

#include "AeroKingdom_AirshipsProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "ASDamageable/ASA_DamageableActor.h"
#include "ASComponents/ASAC_DurabilityComponent.h"

AAeroKingdom_AirshipsProjectile::AAeroKingdom_AirshipsProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AAeroKingdom_AirshipsProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AAeroKingdom_AirshipsProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}

bool AAeroKingdom_AirshipsProjectile::IsValidObject(AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
	return (OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr);
}


bool AAeroKingdom_AirshipsProjectile::HasDurability(AActor* OtherActor)
{
	AASA_DamageableActor* DamageableObj = GetDurabilityComponent(OtherActor);
	return DamageableObj != nullptr;
}

AASA_DamageableActor* AAeroKingdom_AirshipsProjectile::GetDurabilityComponent(AActor * OtherActor)
{
	UASAC_DurabilityComponent* DamageableComponent = Cast<UASAC_DurabilityComponent>(OtherActor->GetComponentByClass<UASAC_DurabilityComponent>());
	if (!DamageableComponent) {
		return nullptr;
	}
	AASA_DamageableActor* DamageableObj = Cast<AASA_DamageableActor>(DamageableComponent->GetOwner());
	return DamageableObj;
}

