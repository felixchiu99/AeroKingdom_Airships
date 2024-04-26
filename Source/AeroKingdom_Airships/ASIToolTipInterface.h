// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ASIToolTipInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UASIToolTipInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AEROKINGDOM_AIRSHIPS_API IASIToolTipInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FText GetKeyName();
	virtual void SetKeyName(FText Name);
	virtual void DebugKeyName();

	virtual FVector GetTooltipDisplayPoint();
	virtual bool HasTooltipDisplayPoint();
	virtual FText GetTooltipDisplayName();
protected:

	FText KeyName;
};
