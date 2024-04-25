// Fill out your copyright notice in the Description page of Project Settings.


#include "ASInteractablePawn.h"
#include "Components/ArrowComponent.h"

// Sets default values
AASInteractablePawn::AASInteractablePawn()
{
	// Create Tooltip Point
	TooltipDisplayPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("TooltipDisplay"));
}

FVector AASInteractablePawn::GetTooltipDisplayPoint()
{
	if (HasTooltipDisplayPoint()) {
		return TooltipDisplayPoint->GetComponentLocation();
	}		
	else
		return FVector(0, 0, 0);
}

bool AASInteractablePawn::HasTooltipDisplayPoint()
{
	return TooltipDisplayPoint->IsValidLowLevel();
}

FText AASInteractablePawn::GetTooltipDisplayName()
{
	return TooltipLabelText;
}
