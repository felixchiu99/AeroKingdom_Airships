// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"

/**
 * 
 */

class UPlayerController;
class UHUD;

UCLASS()
class AEROKINGDOM_AIRSHIPS_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UClass* PlayerControllerClass;
	UClass* HUDClass;

public:
	AMenuGameMode();
};
