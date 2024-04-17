// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetTooltipComponent.h"
#include "Components/TextBlock.h"

UWidgetTooltipComponent::UWidgetTooltipComponent()
{
	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawAtDesiredSize(true);
}

void UWidgetTooltipComponent::SetVisible(bool bIsVisible)
{

}
