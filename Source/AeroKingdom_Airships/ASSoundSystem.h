// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class AEROKINGDOM_AIRSHIPS_API ASSoundSystem
{
public:
	ASSoundSystem();
	~ASSoundSystem();

	void PlaySFXAtLocation(
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
    );
};
