// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../ASDamageable/ASIDamageable.h"
#include "ASAC_DurabilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEROKINGDOM_AIRSHIPS_API UASAC_DurabilityComponent : public UActorComponent, public IASIDamageable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UASAC_DurabilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void AddDamage(float fDamage = 0) override;
	virtual void RemoveDamage(float fDamage = 0) override;

	virtual float GetDurability() override;
	virtual float GetMaxDurability() override;

	virtual bool IsAlive();
	virtual bool IsMaxDurability();

	virtual void OnDestroyed() override;
	virtual void OnDamage() override;

	virtual void OnFullDurability() override;
	virtual void OnRepair() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float fMaxDurability = 100;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float fDurability = fMaxDurability;
		
};
