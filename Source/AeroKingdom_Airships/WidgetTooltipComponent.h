// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ASIToolTipInterface.h"
#include "WidgetTooltipComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AEROKINGDOM_AIRSHIPS_API UWidgetTooltipComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UWidgetTooltipComponent();

	void SetToolTipInterface(UASIToolTipInterface* InInterface)
	{
		ToolTipInterfaceObject = InInterface;
	}

protected:
	void SetVisible(bool bIsVisible);

	TWeakObjectPtr<UASIToolTipInterface> ToolTipInterfaceObject;

};
