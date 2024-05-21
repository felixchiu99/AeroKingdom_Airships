// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AeroKingdom_Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class AASA_DamageableActor;

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

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }

	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	/** Returns ProjectileMovement initial speed **/
	float GetProjectileMovementSpeed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Pass Explosion On Explosion animation */
	UFUNCTION()
	void OnExplode();

	/** Pass Explosion On Hit animation */
	UFUNCTION()
	void OnHitExplode();

	/** Pass Explosion On Hit animation */
	UFUNCTION()
	void OnDestroy();

	/** Play Explosion animation */
	UFUNCTION()
	void PlayExplodeAnimation(UNiagaraSystem* Animation);

	/** Play Explosion Sound */
	UFUNCTION()
	void PlayExplodeSound();

	//Check general Valid hit target
	bool IsValidObject(AActor* OtherActor, UPrimitiveComponent* OtherComp);

	/** Durability adoptability related**/

	void AddDamage(AActor* OtherActor);

	bool HasDurability(AActor* OtherActor);

	//Return Durability component
	AASA_DamageableActor* GetDurabilityComponent(AActor* OtherActor);

	// Calculate Damage
	float CalculateDamage();

protected:

	// Auto Explode Timer
	UPROPERTY(EditAnywhere)
	float fExplodeTimer = 2.f;

	//Base Damage to be Dealt
	UPROPERTY(EditAnywhere)
	float fBaseDamage = 10.0f;

};
