// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ASSoundSystem.h"
#include "GIAirshipGameInstance.generated.h"

/**
 * 
 */
class ASSoundSystem;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API UGIAirshipGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	void OnStart() override;

	void LoadVolumeSettings();
public:
	std::unique_ptr<ASSoundSystem> SoundSystem;

	void SSPlaySFXAtLocation(
		const UObject* WorldContextObject,
		USoundBase* Sound,
		FVector Location,
		FRotator Rotation = (FRotator(0, 0, 0)),
		float VolumeMultiplier = (1.0F),
		float PitchMultiplier = (1.0F),
		float StartTime = (0.0F),
		USoundAttenuation* AttenuationSettings = (USoundAttenuation*)nullptr,
		USoundConcurrency* ConcurrencySettings = (USoundConcurrency*)nullptr,
		AActor* OwningActor = (AActor*) nullptr
	);

	float GetMusicVolume();

	float GetSFXVolume();

	float GetAmbientVolume();

	void SetMusicVolume(float volume);

	void SetSFXVolume(float volume);

	void SetAmbientVolume(float volume);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float fMusicVolume = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float fSFXVolume = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float fAmbientVolume = 1;
};
