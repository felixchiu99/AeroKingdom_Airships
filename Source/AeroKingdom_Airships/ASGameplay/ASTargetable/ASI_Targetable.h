// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ASI_Targetable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UASI_Targetable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AEROKINGDOM_AIRSHIPS_API IASI_Targetable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//return the location of the target
	virtual FVector GetLocation();

protected:
	// Called when the game starts
	virtual void BeginPlay();
};
