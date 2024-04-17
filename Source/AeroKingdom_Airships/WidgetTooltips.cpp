// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetTooltips.h"
#include "Components/TextBlock.h"

void UWidgetTooltips::SetKeyName(FString name)
{
	KeyBindName->SetText(FText::FromString(name));
}
