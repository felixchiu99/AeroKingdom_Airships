// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class AEROKINGDOM_AIRSHIPS_API LevelLoader
{
	UObject* WorldContext;
public:
	LevelLoader();
	~LevelLoader();
	void AddWorldContext(UObject* Context);
	void LoadLevel(FName LevelName);
};
