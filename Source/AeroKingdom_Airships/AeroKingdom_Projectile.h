// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AeroKingdom_Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS(config = Game)
class AAeroKingdom_Projectile : public AActor
{
	GENERATED_BODY()
	
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* ProjectileMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

protected:
	//Niagara muzzle effect
	UPROPERTY(EditAnywhere, Category = "Animation")
	UNiagaraSystem* ShellOnHit;

	//Niagara muzzle effect
	UPROPERTY(EditAnywhere, Category = "Animation")
	UNiagaraSystem* ShellExplosion;

	//Explosion Timer Handle
	FTimerHandle ExplosionTimer;

	/** Sound to play each time the Shell Explodes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
	USoundBase* ExplosionSound;

	/** Sound Attenuation settings*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
	USoundAttenuation* AudioSetting;

public:	
	// Sets default values for this actor's properties
	AAeroKingdom_Projectile();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Pass Explosion On Explosion animation */
	UFUNCTION()
	void OnExplode();

	/** Pass Explosion On Hit animation */
	UFUNCTION()
	void OnHitExplode();

	/** Play Explosion animation */
	UFUNCTION()
	void PlayExplodeAnimation(UNiagaraSystem* Animation);

	/** Play Explosion Sound */
	UFUNCTION()
	void PlayExplodeSound();

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	// Auto Explode Timer
	UPROPERTY(EditAnywhere)
	float fExplodeTimer = 2.f;
};
