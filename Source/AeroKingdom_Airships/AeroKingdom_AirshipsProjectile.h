// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AeroKingdom_AirshipsProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class AASA_DamageableActor;

UCLASS(config=Game)
class AAeroKingdom_AirshipsProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	AAeroKingdom_AirshipsProjectile();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }

	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	/** Returns ProjectileMovement initial speed **/
	float GetProjectileMovementSpeed();

protected:
	bool IsValidObject(AActor* OtherActor, UPrimitiveComponent* OtherComp);
	bool HasDurability(AActor* OtherActor);

	AASA_DamageableActor* GetDurabilityComponent(AActor* OtherActor);
};

