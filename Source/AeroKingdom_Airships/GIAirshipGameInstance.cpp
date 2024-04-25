// Fill out your copyright notice in the Description page of Project Settings.


#include "GIAirshipGameInstance.h"

void UGIAirshipGameInstance::OnStart()
{
	SoundSystem = std::make_unique<ASSoundSystem>();
	LoadVolumeSettings();
}

void UGIAirshipGameInstance::LoadVolumeSettings()
{
	fMusicVolume = 1;
	fSFXVolume = 1;
	fAmbientVolume = 1;
}

void UGIAirshipGameInstance::SSPlaySFXAtLocation(
	const UObject* WorldContextObject,
	USoundBase* Sound, 
	FVector Location, 
	FRotator Rotation, 
	float VolumeMultiplier,
	float PitchMultiplier,
	float StartTime,
	USoundAttenuation* AttenuationSettings,
	USoundConcurrency* ConcurrencySettings,
	AActor* OwningActor
)
{
	SoundSystem->PlaySFXAtLocation(WorldContextObject, Sound, Location, Rotation, fSFXVolume * VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, OwningActor);
}

float UGIAirshipGameInstance::GetMusicVolume()
{
	return fMusicVolume;
}

float UGIAirshipGameInstance::GetSFXVolume()
{
	return fSFXVolume;
}

float UGIAirshipGameInstance::GetAmbientVolume()
{
	return fAmbientVolume;
}

void UGIAirshipGameInstance::SetMusicVolume(float volume)
{
	fMusicVolume = volume;
}

void UGIAirshipGameInstance::SetSFXVolume(float volume)
{
	fSFXVolume = volume;
}

void UGIAirshipGameInstance::SetAmbientVolume(float volume)
{
	fAmbientVolume = volume;
}
