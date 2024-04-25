// Fill out your copyright notice in the Description page of Project Settings.


#include "IToolTipInterface.h"
#include "Components/ArrowComponent.h"

// Add default functionality here for any IIToolTipInterface functions that are not pure virtual.

FText IIToolTipInterface::GetKeyName()
{
	return KeyName;
}

void IIToolTipInterface::SetKeyName(FText Name)
{
	KeyName = Name;
}

void IIToolTipInterface::DebugKeyName()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, KeyName.ToString());
}

FVector IIToolTipInterface::GetTooltipDisplayPoint()
{
	return FVector(0, 0, 0);
}

bool IIToolTipInterface::HasTooltipDisplayPoint()
{
	return false;
}

FText IIToolTipInterface::GetTooltipDisplayName()
{
	return FText();
}
