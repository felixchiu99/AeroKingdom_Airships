// Fill out your copyright notice in the Description page of Project Settings.


#include "ASIToolTipInterface.h"
#include "Components/ArrowComponent.h"

// Add default functionality here for any IIToolTipInterface functions that are not pure virtual.

FText IASIToolTipInterface::GetKeyName()
{
	return KeyName;
}

void IASIToolTipInterface::SetKeyName(FText Name)
{
	KeyName = Name;
}

void IASIToolTipInterface::DebugKeyName()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, KeyName.ToString());
}

FVector IASIToolTipInterface::GetTooltipDisplayPoint()
{
	return FVector(0, 0, 0);
}

bool IASIToolTipInterface::HasTooltipDisplayPoint()
{
	return false;
}

FText IASIToolTipInterface::GetTooltipDisplayName()
{
	return FText();
}
