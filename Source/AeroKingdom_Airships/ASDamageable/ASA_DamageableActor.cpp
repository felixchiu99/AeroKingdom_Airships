// Fill out your copyright notice in the Description page of Project Settings.


#include "ASA_DamageableActor.h"
#include "../ASComponents/ASAC_DurabilityComponent.h"

// Sets default values
AASA_DamageableActor::AASA_DamageableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Durability = CreateDefaultSubobject<UASAC_DurabilityComponent>(TEXT("DurabilityComponent"));
}

// Called when the game starts or when spawned
void AASA_DamageableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AASA_DamageableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AASA_DamageableActor::AddDamage(float fDamage)
{
	Durability->AddDamage(fDamage);
	OnDamage();
}

void AASA_DamageableActor::RemoveDamage(float fDamage)
{
	Durability->AddDamage(fDamage);
	OnRepair();
}

float AASA_DamageableActor::GetDurability()
{
	return Durability->GetDurability();
}

float AASA_DamageableActor::GetMaxDurability()
{
	return Durability->GetMaxDurability();
}

void AASA_DamageableActor::OnDestroyed()
{
	Durability->OnDestroyed();
}

void AASA_DamageableActor::OnDamage()
{
	Durability->OnDamage();
	if (!Durability->IsAlive()) {
		OnDestroyed();
		Destroy();
	}
}

void AASA_DamageableActor::OnFullDurability()
{
	Durability->OnFullDurability();
}

void AASA_DamageableActor::OnRepair()
{
	Durability->OnRepair();
	if (!Durability->IsMaxDurability()) {
		OnFullDurability();
	}
}

