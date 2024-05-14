// Fill out your copyright notice in the Description page of Project Settings.


#include "ASAC_DurabilityComponent.h"

// Sets default values for this component's properties
UASAC_DurabilityComponent::UASAC_DurabilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UASAC_DurabilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	fDurability = fMaxDurability;
}


// Called every frame
void UASAC_DurabilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UASAC_DurabilityComponent::AddDamage(float fDamage)
{
	fDurability -= fDamage;
	OnDamage();
	if (fDurability <= 0) {
		fDurability = 0;
		OnDestroyed();
	}
}

void UASAC_DurabilityComponent::RemoveDamage(float fDamage)
{
	fDurability += fDamage;
	OnRepair();
	if (fDurability >= fMaxDurability) {
		fDurability = fMaxDurability;
		OnFullDurability();
	}
}

float UASAC_DurabilityComponent::GetDurability()
{
	return fDurability;
}

float UASAC_DurabilityComponent::GetMaxDurability()
{
	return fMaxDurability;
}

bool UASAC_DurabilityComponent::IsAlive()
{
	return fDurability > 0;
}

bool UASAC_DurabilityComponent::IsMaxDurability()
{
	return fDurability >= fMaxDurability;
}

void UASAC_DurabilityComponent::OnDestroyed()
{
}

void UASAC_DurabilityComponent::OnDamage()
{
}

void UASAC_DurabilityComponent::OnFullDurability()
{
}

void UASAC_DurabilityComponent::OnRepair()
{
}

