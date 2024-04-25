// Fill out your copyright notice in the Description page of Project Settings.


#include "ASSoundSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GIAirshipGameInstance.h"

ASSoundSystem::ASSoundSystem()
{
}

ASSoundSystem::~ASSoundSystem()
{
}

void ASSoundSystem::PlaySFXAtLocation(
    const UObject* WorldContextObject,
    USoundBase* Sound,
    FVector Location,
    FRotator Rotation,
    float VolumeMultiplier,
    float PitchMultiplier,
    float StartTime,
    class USoundAttenuation* AttenuationSettings,
    USoundConcurrency* ConcurrencySettings,
    AActor* OwningActor
)
{

	UGameplayStatics::PlaySoundAtLocation(WorldContextObject, Sound, Location, Rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, OwningActor);
	
}
