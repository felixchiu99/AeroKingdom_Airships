// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASCannon.generated.h"

class UArrowComponent;
class USkeletalMeshComponent;
class UNiagaraSystem;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AASCannon : public AActor
{
	GENERATED_BODY()
	
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AAeroKingdom_Projectile> ProjectileClass;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* CannonCarrier;

	/*
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* CannonBarrel;
	*/

	/** barrelMesh) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* CannonBarrelAnim;

	UPROPERTY(VisibleDefaultsOnly, Category = Animation)
	UAnimSequence* FireAnim;

	UPROPERTY(VisibleDefaultsOnly)
	UArrowComponent* FirePoint;

	UPROPERTY(VisibleDefaultsOnly)
	float CoolDownTimer = 1.f;

public:
	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
	USoundBase* FireSound;

	/** Sound Attenuation settings*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
	USoundAttenuation* AudioSetting;

	//firing Timer Handle
	FTimerHandle FireTimer;

	//Niagara muzzle effect
	UPROPERTY(EditAnywhere, Category = "Animation")
	UNiagaraSystem* FireEffectMuzzle;

public:	
	// Sets default values for this actor's properties
	AASCannon();

	/** Called for Fire input */
	void Fire();

	/** Called for Fire input */
	void StartFire();

	/* Called for stop auto shoot*/
	void StopFire();
	
	/* Called for stop auto shoot*/
	void ResetCoolDown();

	/* return the initial Speed of the projectile the cannon has*/
	float GetProjectileInitialSpeed();

protected:
	/** Bool for whether there the cannons are shooting*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsFiring = false;

	/** Bool for whether there the cannons are shooting*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bOnCooldown = false;

	UPROPERTY(EditAnywhere, Category = "Animation")
	float fMuzzleAnimOffset = 30.f;

	UPROPERTY(EditAnywhere, Category = "Cannon Attributes")
	float fMaxRandomDegOffset = 0.0f;
};
