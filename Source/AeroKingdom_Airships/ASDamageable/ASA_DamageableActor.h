// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASIDamageable.h"
#include "ASA_DamageableActor.generated.h"

class UASAC_DurabilityComponent;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AASA_DamageableActor : public AActor , public IASIDamageable
{
	GENERATED_BODY()
	
	UASAC_DurabilityComponent* Durability;

public:	
	// Sets default values for this actor's properties
	AASA_DamageableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void AddDamage(float fDamage = 0) override;
	virtual void RemoveDamage(float fDamage = 0) override;

	virtual float GetDurability() override;
	virtual float GetMaxDurability() override;

	virtual void OnDestroyed() override;
	virtual void OnDamage() override;

	virtual void OnFullDurability() override;
	virtual void OnRepair() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
	float fMaxDurability = 100;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
	float fDurability = fMaxDurability;


};
