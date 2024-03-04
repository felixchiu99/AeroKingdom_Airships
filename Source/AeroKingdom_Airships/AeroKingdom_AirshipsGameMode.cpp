// Copyright Epic Games, Inc. All Rights Reserved.

#include "AeroKingdom_AirshipsGameMode.h"
#include "AeroKingdom_AirshipsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAeroKingdom_AirshipsGameMode::AAeroKingdom_AirshipsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
